import { useRef } from "react";

import useHttp from "../../hooks/use-http";
import LoadingSpinner from "../UI/LoadingSpinner";

import classes from "./NewCommentForm.module.css";

const NewCommentForm = ({ quoteId, onAddComment }) => {
  const commentTextRef = useRef();
  const { isLoading, request: sendComment } = useHttp();

  const submitFormHandler = (event) => {
    event.preventDefault();
    const enteredText = commentTextRef.current.value;

    if (enteredText.trim().length === 0) {
      return; // TODO: send feedback to the user
    }

    const config = {
      url: `comments`,
      method: "post",
      data: { quoteId, text: enteredText },
    };

    // send comment to server
    sendComment(config).then(() => {
      commentTextRef.current.value = ""; // FIXME: bad practice
      onAddComment();
    });
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
