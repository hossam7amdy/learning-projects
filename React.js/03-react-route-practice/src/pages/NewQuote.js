import { useHistory } from "react-router-dom";
import useHttp from "../hooks/use-http";
import QuoteForm from "../components/quotes/QuoteForm";
import { FIREBASE_DOMAIN } from "../lib/config";
import LoadingSpinner from "../components/UI/LoadingSpinner";

const NewQuote = () => {
  const history = useHistory();
  const { isLoading, fetchAPI: sendQuote } = useHttp();

  const addQuoteHandler = async (quoteData) => {
    await sendQuote(`${FIREBASE_DOMAIN}/quotes.json`, {
      method: "POST",
      body: quoteData,
      headers: {
        "Content-Type": "application/json",
      },
    });

    history.push("/quotes");
  };

  if (isLoading) {
    return (
      <div className="centered">
        <LoadingSpinner />
      </div>
    );
  }

  return <QuoteForm onAddQuote={addQuoteHandler} />;
};

export default NewQuote;
