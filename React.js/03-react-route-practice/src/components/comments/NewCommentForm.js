import { useRef } from "react";
import useHttp from "../../hooks/use-http";
import { FIREBASE_DOMAIN } from "../../lib/config";
import LoadingSpinner from "../UI/LoadingSpinner";

import classes from "./NewCommentForm.module.css";

const NewCommentForm = (props) => {
  const commentTextRef = useRef();
  const { isLoading, fetchAPI: sendComment } = useHttp();

  const submitFormHandler = async (event) => {
    event.preventDefault();
    const { quoteId } = props;
    const enteredText = commentTextRef.current.value;

    if (enteredText.trim().length === 0) {
      return; // TODO: send feedback to the user
    }

    // send comment to server
    await sendComment(`${FIREBASE_DOMAIN}/comments/${quoteId}.json`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: { text: enteredText },
    });

    commentTextRef.current.value = ""; // FIXME: bad practice
    props.onAddComment();
  };

  return (
    <form className={classes.form} onSubmit={submitFormHandler}>
      {isLoading && (
        <div className="centered">
          <LoadingSpinner />
        </div>
      )}
      <div className={classes.control} onSubmit={submitFormHandler}>
        <label htmlFor="comment">Your Comment</label>
        <textarea id="comment" rows="5" ref={commentTextRef}></textarea>
      </div>
      <div className={classes.actions}>
        <button className="btn">Add Comment</button>
      </div>
    </form>
  );
};

export default NewCommentForm;
