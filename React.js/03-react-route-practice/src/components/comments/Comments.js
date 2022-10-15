import { useState } from "react";
import useHttp from "../../hooks/use-http";
import { FIREBASE_DOMAIN } from "../../lib/config";
import LoadingSpinner from "../UI/LoadingSpinner";

import classes from "./Comments.module.css";
import NewCommentForm from "./NewCommentForm";
import CommentItem from "./CommentItem";

const Comments = (props) => {
  const { quoteId } = props;
  const [isAddingComment, setIsAddingComment] = useState(false);
  const {
    isLoading,
    error,
    data: commentsData,
    fetchAPI: getCemments,
  } = useHttp(`${FIREBASE_DOMAIN}/comments/${quoteId}.json`);

  const startAddCommentHandler = () => {
    setIsAddingComment(true);
  };

  const addCommentHandler = async () => {
    await getCemments(`${FIREBASE_DOMAIN}/comments/${quoteId}.json`);
    setIsAddingComment(false);
  };

  const loadedComments = [];
  for (const key in commentsData) {
    const commentObj = { id: key, ...commentsData[key] };
    loadedComments.push(commentObj);
  }

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

  if (!isLoading && loadedComments.length === 0) {
    comments = (
      <div className="centered">
        <p>No comments at the moment</p>
      </div>
    );
  }

  if (!isLoading && loadedComments.length > 0) {
    comments = loadedComments.map((comment) => (
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
