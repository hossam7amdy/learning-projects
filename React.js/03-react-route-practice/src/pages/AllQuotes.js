import NoQuotesFound from "../components/quotes/NoQuotesFound";
import QuoteList from "../components/quotes/QuoteList";
import LoadingSpinner from "../components/UI/LoadingSpinner";
import useHttp from "../hooks/use-http";
import { FIREBASE_DOMAIN } from "../lib/config";

const AllQuotes = () => {
  const {
    data: quotesData,
    error,
    isLoading,
  } = useHttp(`${FIREBASE_DOMAIN}/quotes.json`);

  const loadedQuotes = [];

  for (const key in quotesData) {
    const quoteObj = {
      id: key,
      ...quotesData[key],
    };
    loadedQuotes.push(quoteObj);
  }

  if (isLoading) {
    return (
      <div className="centered">
        <LoadingSpinner />;
      </div>
    );
  }

  if (error) {
    return (
      <div className="centered focused">
        {error || "something went wrong💥💥💥"}
      </div>
    );
  }

  if (loadedQuotes.length === 0) {
    return <NoQuotesFound />;
  }

  return <QuoteList quotes={loadedQuotes} />;
};

export default AllQuotes;
