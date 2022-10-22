import useHttp from "../hooks/use-http";
import QuoteList from "../components/quotes/QuoteList";
import NoQuotesFound from "../components/quotes/NoQuotesFound";
import LoadingSpinner from "../components/UI/LoadingSpinner";

const AllQuotes = () => {
  const { data: loadedQuotes, error, isLoading } = useHttp(`quotes`);

  if (isLoading) {
    return (
      <div className="centered">
        <LoadingSpinner />;
      </div>
    );
  }

  if (error) {
    return <div className="centered focused">{error}</div>;
  }

  if (loadedQuotes?.length === 0) {
    return <NoQuotesFound />;
  }

  return <QuoteList quotes={loadedQuotes || []} />;
};

export default AllQuotes;
