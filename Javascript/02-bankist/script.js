'use strict';

// Data
const account1 = {
  owner: 'Jonas Schmedtmann',
  movements: [200, 455.23, -306.5, 25000, -642.21, -133.9, 79.97, 1300],
  interestRate: 1.2, // %
  pin: 1111,

  movementsDates: [
    '2021-11-18T21:31:17.178Z',
    '2021-12-23T07:42:02.383Z',
    '2022-01-28T09:15:04.904Z',
    '2022-04-01T10:17:24.185Z',
    '2022-05-08T14:11:59.604Z',
    '2022-07-05T17:01:17.194Z',
    '2022-07-07T23:36:17.929Z',
    '2022-07-06T10:51:36.790Z',
  ],
  currency: 'EUR',
  locale: 'pt-PT', // de-DE
};

const account2 = {
  owner: 'Jessica Davis',
  movements: [5000, 3400, -150, -790, -3210, -1000, 8500, -30],
  interestRate: 1.5,
  pin: 2222,

  movementsDates: [
    '2021-11-01T13:15:33.035Z',
    '2021-11-30T09:48:16.867Z',
    '2021-12-25T06:04:23.907Z',
    '2022-01-25T14:18:46.235Z',
    '2022-02-05T16:33:06.386Z',
    '2022-04-10T14:43:26.374Z',
    '2022-06-25T18:49:59.371Z',
    '2022-07-07T12:01:20.894Z',
  ],
  currency: 'USD',
  locale: 'en-US',
};

const account3 = {
  owner: 'Hossam Hamdy',
  movements: [200, -200, 340, -300, -20, 50, 400, -460],
  interestRate: 0.7,
  pin: 3333,

  movementsDates: [
    '2021-09-01T13:15:33.035Z',
    '2021-10-30T09:48:16.867Z',
    '2021-11-25T06:04:23.907Z',
    '2022-02-25T14:18:46.235Z',
    '2022-03-05T16:33:06.386Z',
    '2022-05-10T14:43:26.374Z',
    '2022-07-05T18:49:59.371Z',
    '2022-07-07T12:01:20.894Z',
  ],
  currency: 'EGP',
  locale: 'en-EG',
};

const account4 = {
  owner: 'Sarah Mohamed',
  movements: [430, 1000, 700, 50, 90],
  interestRate: 1,
  pin: 4444,

  movementsDates: [
    '2022-02-25T14:18:46.235Z',
    '2022-03-05T16:33:06.386Z',
    '2022-05-10T14:43:26.374Z',
    '2022-07-05T18:49:59.371Z',
    '2022-07-07T12:01:20.894Z',
  ],
  currency: 'JOD',
  locale: 'en-PS',
};

const accounts = [account1, account2, account3, account4];

// Elements
const labelWelcome = document.querySelector('.welcome');
const labelDate = document.querySelector('.date');
const labelBalance = document.querySelector('.balance__value');
const labelSumIn = document.querySelector('.summary__value--in');
const labelSumOut = document.querySelector('.summary__value--out');
const labelSumInterest = document.querySelector('.summary__value--interest');
const labelTimer = document.querySelector('.timer');

const containerApp = document.querySelector('.app');
const containerMovements = document.querySelector('.movements');

const btnLogin = document.querySelector('.login__btn');
const btnTransfer = document.querySelector('.form__btn--transfer');
const btnLoan = document.querySelector('.form__btn--loan');
const btnClose = document.querySelector('.form__btn--close');
const btnSort = document.querySelector('.btn--sort');

const inputLoginUsername = document.querySelector('.login__input--user');
const inputLoginPin = document.querySelector('.login__input--pin');
const inputTransferTo = document.querySelector('.form__input--to');
const inputTransferAmount = document.querySelector('.form__input--amount');
const inputLoanAmount = document.querySelector('.form__input--loan-amount');
const inputCloseUsername = document.querySelector('.form__input--user');
const inputClosePin = document.querySelector('.form__input--pin');

// Globals
let currentAccount, timer;

// Helper Methods
const formatMovementDate = function (date, locale) {
  const calcDaysPassed = (date1, date2) =>
    Math.round(Math.abs(date1 - date2) / (1000 * 60 * 60 * 24));

  const days = calcDaysPassed(new Date(date), new Date());

  if (days === 0) return `Today`;
  else if (days === 1) return `Yesterday`;
  else if (days <= 7) return `${days} Days Ago`;

  const toDate = new Date(date);
  // const year = `${toDate.getFullYear()}`;
  // const month = `${toDate.getMonth() + 1}`.padStart(2, 0);
  // const day = `${toDate.getDate()}`.padStart(2, 0);
  return `${new Intl.DateTimeFormat(locale).format(toDate)}`;
};

const formatCurrency = (locale, currency, amount) =>
  `${new Intl.NumberFormat(locale, {
    style: 'currency',
    currency: currency,
  }).format(amount)}`;

const startLogoutTimer = function () {
  const tick = () => {
    const min = String(Math.trunc(time / 60)).padStart(2, 0);
    const sec = String(time % 60).padStart(2, 0);

    // In each call, print the remaining time to UI
    labelTimer.textContent = `${min}:${sec}`;

    // When 0 seconds, stop timer and log out user
    if (time === 0) {
      clearInterval(timer);
      labelWelcome.textContent = 'Log in to get started';
      containerApp.style.opacity = 0;
    }
    // decrease 1s
    time--;
  };

  // Set time to 5 minutes
  let time = 300;

  tick(); // Immediate Call,
  // then Call every second
  timer = setInterval(tick, 1000);
};

// App Functionality
const displayMovements = function (account, sort = false) {
  containerMovements.innerHTML = '';

  const movs = sort
    ? account.movements.slice().sort((a, b) => a - b)
    : account.movements;

  movs.forEach(function (mov, idx) {
    const type = mov > 0 ? 'deposit' : 'withdrawal';
    const displayDate = formatMovementDate(
      account.movementsDates[idx],
      account.locale
    );
    const displayCurrency = formatCurrency(
      account.locale,
      account.currency,
      mov
    );

    const html = `<div class="movements__row">
      <div class="movements__type movements__type--${type}">
        ${idx + 1} ${type}</div>
        <div class="movements__date">${displayDate}</div>
      <div class="movements__date"></div>
      <div class="movements__value">${displayCurrency}</div>
    </div>`;

    containerMovements.insertAdjacentHTML('afterbegin', html);
  });
};

const createUsernames = function (accs) {
  accs.forEach(function (acc) {
    acc.username = acc.owner
      .toLowerCase()
      .split(' ')
      .map(user => user[0])
      .join('');
  });
};

const calcDisplayBalance = function (account) {
  account.balance = account.movements.reduce((accu, mov) => accu + mov, 0);

  labelBalance.textContent = formatCurrency(
    account.locale,
    account.currency,
    account.balance
  );
};

const calcDisplaySummery = function (account) {
  // CHAINING / PIPELINE
  const income = account.movements
    .filter(mov => mov > 0)
    .reduce((acc, mov) => acc + mov, 0);
  labelSumIn.textContent = formatCurrency(
    account.locale,
    account.currency,
    income
  );

  const out = account.movements
    .filter(mov => mov < 0)
    .reduce((acc, mov) => acc + mov, 0);
  labelSumOut.textContent = formatCurrency(
    account.locale,
    account.currency,
    -out
  );

  const interest = account.movements
    .filter(mov => mov > 0)
    .map(deposit => deposit * (account.interestRate / 100))
    .filter(int => int >= 1)
    .reduce((acc, int) => acc + int, 0);
  labelSumInterest.textContent = formatCurrency(
    account.locale,
    account.currency,
    interest
  );
};

const updateUI = function (account) {
  calcDisplayBalance(account);
  calcDisplaySummery(account);
  displayMovements(account);
};

// Run App
createUsernames(accounts); // side effect = do something to accounts Array

// FAKE SIGN IN
// currentAccount = account1;
// updateUI(currentAccount);
// containerApp.style.opacity = 100;

// Events Handler
btnLogin.addEventListener('click', function (e) {
  e.preventDefault(); // prevent form from submitting

  currentAccount = accounts.find(
    acc => acc.username === inputLoginUsername.value
  );

  if (currentAccount?.pin === Number(inputLoginPin.value)) {
    if (timer) clearInterval(timer);
    startLogoutTimer();

    updateUI(currentAccount);

    // Current date and time
    const now = new Date();
    // const day = `${now.getDate()}`.padStart(2, 0);
    // const month = `${now.getMonth() + 1}`.padStart(2, 0);
    // const year = `${now.getFullYear()}`;
    // const hour = `${now.getHours()}`.padStart(2, 0);
    // const minute = `${now.getMinutes()}`.padStart(2, 0);

    // Using Internationaling API
    const curDateTime = new Intl.DateTimeFormat(currentAccount.locale).format(
      now
    );

    labelDate.textContent = curDateTime;
    inputLoginPin.blur(); // lose focus
    inputLoginUsername.value = inputLoginPin.value = '';
    labelWelcome.textContent = `Wellcome back ${
      currentAccount.owner.split(' ')[0]
    }`;
    containerApp.style.opacity = 100;
  } else {
    alert('Wrong username or password. Try again!!');
  }
});

btnTransfer.addEventListener('click', function (e) {
  if (timer) clearInterval(timer);
  startLogoutTimer();

  e.preventDefault();

  const amount = Math.floor(inputTransferAmount.value);
  const recipient = accounts.find(
    acc =>
      acc.username === inputTransferTo.value &&
      acc.username != currentAccount.username
  );

  inputTransferAmount.blur();
  inputTransferTo.value = inputTransferAmount.value = '';

  if (!recipient || 0 >= amount || amount > currentAccount.balance) {
    alert('Wrong Entry. Try again!!');
  } else {
    recipient.movements.push(amount);
    recipient.movementsDates.push(new Date());

    currentAccount.movements.push(-amount);
    currentAccount.movementsDates.push(new Date());

    updateUI(currentAccount);
  }
});

btnClose.addEventListener('click', function (e) {
  e.preventDefault();

  if (
    currentAccount.username === inputCloseUsername.value &&
    currentAccount.pin === Number(inputClosePin.value)
  ) {
    const index = accounts.findIndex(account => account === currentAccount);

    accounts.splice(index, 1); // do deletion

    containerApp.style.opacity = 0; // hide UI
    labelWelcome.textContent = 'Log in to get started';
  } else {
    alert('Wrong Entry. Try again!!');
  }
  inputClosePin.blur();
  inputCloseUsername.value = inputClosePin.value = '';
});

btnLoan.addEventListener('click', function (e) {
  e.preventDefault();

  const loanAmount = Math.floor(inputLoanAmount.value);
  inputLoanAmount.blur();
  inputLoanAmount.value = '';
  if (
    loanAmount > 0 &&
    currentAccount.movements.some(mov => mov > loanAmount * 0.1)
  ) {
    setTimeout(function () {
      // reset timer
      if (timer) clearInterval(timer);
      startLogoutTimer();

      // wait for approval !!
      currentAccount.movements.push(loanAmount);
      currentAccount.movementsDates.push(new Date());
      updateUI(currentAccount);
    }, 2500);
  } else {
    alert('Wrong Entry. Try again!!');
  }
});

let isSorted = false;
btnSort.addEventListener('click', function () {
  isSorted = !isSorted;
  displayMovements(currentAccount, isSorted);
});
