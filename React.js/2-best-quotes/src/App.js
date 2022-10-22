import react, { Suspense } from "react";
import { Redirect, Route, Switch } from "react-router-dom";

import Layout from "./components/layout/Layout";
import LoadingSpinner from "./components/UI/LoadingSpinner";

const AllQuotes = react.lazy(() => import("./pages/AllQuotes"));
const NewQuote = react.lazy(() => import("./pages/NewQuote"));
const NotFound = react.lazy(() => import("./pages/NotFound"));
const QuoteDetail = react.lazy(() => import("./pages/QuoteDetail"));

function App() {
  return (
    <Layout>
      <Suspense
        fallback={
          <div className="centered">
            <LoadingSpinner />
          </div>
        }
      >
        <Switch>
          <Route path={"/"} exact>
            <Redirect to={"/quotes"} />
          </Route>
          <Route path={"/quotes"} exact>
            <AllQuotes />
          </Route>
          <Route path={"/quotes/:quoteId"}>
            <QuoteDetail />
          </Route>
          <Route path={"/new-quote"}>
            <NewQuote />
          </Route>
          <Route path={"*"}>
            <NotFound />
          </Route>
        </Switch>
      </Suspense>
    </Layout>
  );
}

export default App;
