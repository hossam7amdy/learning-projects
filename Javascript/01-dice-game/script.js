'use strict';

// GLOBAL VARIABLES
const MAX_POINTS = 100;
let scores, activePlayer, curScore, playing;

// DICE IMAGE
const dice = document.querySelector('.dice');
// PLAYER 0
const player0El = document.querySelector('.player--0');
const score0El = document.getElementById('score--0');
const currentScore0El = document.getElementById('current--0');
// PLAYER 1
const player1El = document.querySelector('.player--1');
const score1El = document.getElementById('score--1');
const currentScore1El = document.getElementById('current--1');
// BUTTONS
const btnHold = document.querySelector('.btn--hold');
const btnNewGame = document.querySelector('.btn--new');
const btnRollDice = document.querySelector('.btn--roll');

/// Helper Utilities ///
const initGame = function () {
  playing = true;
  curScore = 0;
  activePlayer = 0;
  scores = [0, 0];

  dice.classList.add('hidden');
  player0El.classList.remove('player--winner');
  player1El.classList.remove('player--winner');
  score0El.textContent = score1El.textContent = 0;
  currentScore0El.textContent = currentScore1El.textContent = 0;
};

const switchPlayers = function () {
  curScore = 0;
  document.getElementById(`current--${activePlayer}`).textContent = curScore;
  activePlayer = activePlayer === 0 ? 1 : 0;
  player0El.classList.toggle('player--active');
  player1El.classList.toggle('player--active');
};

// Game Logic
initGame(); // Reset at Start

btnRollDice.addEventListener('click', function () {
  if (playing) {
    // 1- Generate Random number
    const num = Math.trunc(Math.random() * 6) + 1;

    // 2- Display Dice
    dice.classList.remove('hidden');
    dice.src = `dice-${num}.png`;

    // 3- Check for rolled one
    if (num !== 1) {
      curScore += num;
      document.getElementById(`current--${activePlayer}`).textContent =
        curScore;
    } else {
      switchPlayers();
    }
  }
});

btnHold.addEventListener('click', function () {
  if (playing) {
    // 1- accumulate score to current player
    scores[activePlayer] += curScore;
    document.getElementById(`score--${activePlayer}`).textContent =
      scores[activePlayer];

    // 2- check if he wins
    if (scores[activePlayer] >= MAX_POINTS) {
      playing = false;
      dice.classList.add('hidden');
      document
        .querySelector(`.player--${activePlayer}`)
        .classList.add('player--winner');

      // 3- otherwise swich roles
    } else switchPlayers();
  }
});

btnNewGame.addEventListener('click', initGame);
