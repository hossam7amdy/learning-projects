import { useHistory } from "react-router-dom";

import useHttp from "../hooks/use-http";
import QuoteForm from "../components/quotes/QuoteForm";
import LoadingSpinner from "../components/UI/LoadingSpinner";

const NewQuote = () => {
  const history = useHistory();
  const { isLoading, request: sendQuote } = useHttp("quotes");

  const addQuoteHandler = (quoteData) => {
    const config = {
      url: "quotes",
      method: "post",
      data: { ...quoteData },
    };

    sendQuote(config).then(() => history.push("/quotes"));
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
