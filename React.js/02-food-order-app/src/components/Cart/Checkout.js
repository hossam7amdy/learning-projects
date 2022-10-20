import React from "react";

import useInput from "../../hooks/use-input";
import classes from "./Checkout.module.css";

const isNotEmpty = (text) => {
  return text.trim() !== "";
};

const isFiveChars = (text) => {
  return text.trim().length === 5;
};

const Checkout = (props) => {
  const {
    value: enteredName,
    isValid: nameIsValid,
    hasError: nameHasError,
    valueInputBlurHandler: nameBlurHandler,
    valueInputChangeHandler: nameChangeHandler,
    reset: nameResetHandler,
  } = useInput(isNotEmpty);

  const {
    value: enteredStreet,
    isValid: streetIsValid,
    hasError: streetHasError,
    valueInputBlurHandler: streetBlurHandler,
    valueInputChangeHandler: streetChangeHandler,
    reset: streetResetHandler,
  } = useInput(isNotEmpty);

  const {
    value: enteredPostalCode,
    isValid: postalCodeIsValid,
    hasError: postalCodeHasError,
    valueInputBlurHandler: postalCodeBlurHandler,
    valueInputChangeHandler: postalCodeChangeHandler,
    reset: postalCodeResetHandler,
  } = useInput(isNotEmpty);

  const {
    value: enteredCity,
    isValid: cityIsValid,
    hasError: cityHasError,
    valueInputBlurHandler: cityBlurHandler,
    valueInputChangeHandler: cityChangeHandler,
    reset: cityResetHandler,
  } = useInput(isNotEmpty);

  const formIsValid =
    nameIsValid &&
    streetIsValid &&
    postalCodeIsValid &&
    cityIsValid &&
    isFiveChars(enteredPostalCode);

  const confirmHandler = (event) => {
    event.preventDefault();

    if (!formIsValid) {
      return;
    }

    props.onSubmit({
      user: enteredName,
      street: enteredStreet,
      postalCode: enteredPostalCode,
      city: enteredCity,
    });

    nameResetHandler();
    streetResetHandler();
    postalCodeResetHandler();
    cityResetHandler();
  };

  const nameClasses = `${classes.control} ${
    nameHasError ? classes.invalid : ""
  }`;
  const streetClasses = `${classes.control} ${
    streetHasError ? classes.invalid : ""
  }`;
  const postalCodeClasses = `${classes.control} ${
    postalCodeHasError && !isFiveChars(enteredPostalCode) ? classes.invalid : ""
  }`;
  const cityClasses = `${classes.control} ${
    cityHasError ? classes.invalid : ""
  }`;

  return (
    <form className={classes.form} onSubmit={confirmHandler}>
      <div className={nameClasses}>
        <label htmlFor="name">Your Name</label>
        <input
          type="text"
          id="name"
          value={enteredName}
          onChange={nameChangeHandler}
          onBlur={nameBlurHandler}
        />
        {nameHasError && (
          <p className={classes.error}>Name must be not empty</p>
        )}
      </div>
      <div className={streetClasses}>
        <label htmlFor="street">Street</label>
        <input
          type="text"
          id="street"
          value={enteredStreet}
          onChange={streetChangeHandler}
          onBlur={streetBlurHandler}
        />
        {streetHasError && (
          <p className={classes.error}>street must be not empty</p>
        )}
      </div>
      <div className={postalCodeClasses}>
        <label htmlFor="postal">Postal Code</label>
        <input
          type="text"
          id="postal"
          value={enteredPostalCode}
          onChange={postalCodeChangeHandler}
          onBlur={postalCodeBlurHandler}
        />
        {postalCodeHasError && (
          <p className={classes.error}>Postal Code must be exactly 5 letters</p>
        )}
      </div>
      <div className={cityClasses}>
        <label htmlFor="city">City</label>
        <input
          type="text"
          id="city"
          value={enteredCity}
          onChange={cityChangeHandler}
          onBlur={cityBlurHandler}
        />
        {cityHasError && (
          <p className={classes.error}>City must be not empty</p>
        )}
      </div>
      <div className={classes.actions}>
        <button type="button" onClick={props.onCancel}>
          Cancel
        </button>
        <button disabled={!formIsValid} className={classes.submit}>
          Confirm
        </button>
      </div>
    </form>
  );
};

export default Checkout;
