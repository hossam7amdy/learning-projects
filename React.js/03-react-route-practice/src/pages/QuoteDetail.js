import { Fragment } from "react";
import { Link, Route, useParams, useRouteMatch } from "react-router-dom";
import Comments from "../components/comments/Comments";
import HighlightedQuote from "../components/quotes/HighlightedQuote";
import NoQuoteFound from "../components/quotes/NoQuotesFound";
import LoadingSpinner from "../components/UI/LoadingSpinner";
import useHttp from "../hooks/use-http";
import { FIREBASE_DOMAIN } from "../lib/config";

const QuoteDetail = () => {
  const { quoteId } = useParams();
  const match = useRouteMatch();

  const {
    isLoading,
    error,
    data: loadedQuote,
  } = useHttp(`${FIREBASE_DOMAIN}/quotes/${quoteId}.json`);

  if (isLoading) {
    return <LoadingSpinner />;
  }

  if (error) {
    return (
      <p className="centered focused">
        {error || "something went wrong💥💥💥"}
      </p>
    );
  }

  if (!loadedQuote) {
    return <NoQuoteFound />;
  }

  return (
    <Fragment>
      <HighlightedQuote author={loadedQuote.author} text={loadedQuote.text} />
      <Route path={`${match.path}`} exact>
        <div className="centered">
          <Link className="btn--flat" to={`${match.url}/comments`}>
            Load Comments
          </Link>
        </div>
      </Route>
      <Route path={`${match.url}/comments`}>
        <Comments quoteId={quoteId} />
      </Route>
    </Fragment>
  );
};

export default QuoteDetail;
