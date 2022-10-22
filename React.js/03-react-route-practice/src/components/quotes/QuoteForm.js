import { Prompt } from "react-router-dom";
import { useRef, useState } from "react";

import Card from "../UI/Card";
import classes from "./QuoteForm.module.css";
import LoadingSpinner from "../UI/LoadingSpinner";

const QuoteForm = (props) => {
  const [isEntering, setIsEntering] = useState(false);
  const authorInputRef = useRef();
  const textInputRef = useRef();

  function submitFormHandler(event) {
    event.preventDefault();

    const enteredAuthor = authorInputRef.current.value;
    const enteredText = textInputRef.current.value;

    // optional: Could validate here
    if (enteredAuthor.trim().length === 0 || enteredText.trim().length === 0) {
      return; // TODO: send feedback to the user
    }

    props.onAddQuote({ author: enteredAuthor, text: enteredText });
  }

  const formFocusHandler = () => {
    setIsEntering(true);
  };

  const finishEnteringHandler = () => {
    setIsEntering(false);
  };

  return (
    <Card>
      <Prompt
        when={isEntering}
        message={
          "Are you sure you want to leave. All your entered data will be lost"
        }
      />
      <form
        onFocus={formFocusHandler}
        className={classes.form}
        onSubmit={submitFormHandler}
      >
        {props.isLoading && (
          <div className={classes.loading}>
            <LoadingSpinner />
          </div>
        )}

        <div className={classes.control}>
          <label htmlFor="author">Author</label>
          <input type="text" id="author" ref={authorInputRef} />
        </div>
        <div className={classes.control}>
          <label htmlFor="text">Text</label>
          <textarea id="text" rows="5" ref={textInputRef}></textarea>
        </div>
        <div className={classes.actions}>
          <button onClick={finishEnteringHandler} className="btn">
            Add Quote
          </button>
        </div>
      </form>
    </Card>
  );
};

export default QuoteForm;
