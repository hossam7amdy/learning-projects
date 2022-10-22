import { useState } from "react";

import LoadingSpinner from "../UI/LoadingSpinner";
import NewCommentForm from "./NewCommentForm";
import CommentItem from "./CommentItem";
import useHttp from "../../hooks/use-http";
import classes from "./Comments.module.css";

const Comments = ({ quoteId }) => {
  const [isAddingComment, setIsAddingComment] = useState(false);
  const {
    error,
    isLoading,
    data: loadedComments,
    request,
  } = useHttp(`comments?quoteId=${quoteId}`);

  const startAddCommentHandler = () => {
    setIsAddingComment(true);
  };

  const addCommentHandler = () => {
    request(`comments?quoteId=${quoteId}`).finally(() =>
      setIsAddingComment(false)
    );
  };

  let comments;

  if (isLoading) {
    comments = (
      <div className="centered">
        <LoadingSpinner />
      </div>
    );
  }

  if (error) {
    comments = (
      <div className="centered">
        <p>{error || "something went wrong💥💥💥"}</p>
      </div>
    );
  }

  if (!isLoading && loadedComments?.length === 0) {
    comments = (
      <div className="centered">
        <p>No comments at the moment</p>
      </div>
    );
  }

  if (!isLoading && loadedComments?.length > 0) {
    comments = loadedComments?.map((comment) => (
      <CommentItem key={comment.id} text={comment.text} />
    ));
  }

  return (
    <section className={classes.comments}>
      <h2>User Comments</h2>
      {!isAddingComment && (
        <button className="btn" onClick={startAddCommentHandler}>
          Add a Comment
        </button>
      )}
      {isAddingComment && (
        <NewCommentForm quoteId={quoteId} onAddComment={addCommentHandler} />
      )}
      {comments}
    </section>
  );
};

export default Comments;
