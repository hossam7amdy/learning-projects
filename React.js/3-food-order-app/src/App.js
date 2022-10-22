import React, { useContext, useEffect, useState } from "react";

import Cart from "./components/Cart/Cart";
import Meals from "./components/Meals/Meals";
import Header from "./components/Layout/Header";
import LoadingSpinner from "./components/UI/LoadingSpinner";

import useFetch from "./hooks/use-fetch";
import useMutate from "./hooks/use-mutate";
import CartContext from "./store/cart-context";

function App() {
  const { request } = useMutate();
  const cartCtx = useContext(CartContext);
  const [cartIsShown, setCartIsShown] = useState(false);
  const { isLoading, data: cartData } = useFetch("http://localhost:4000/cart");

  useEffect(() => {
    if (cartData) {
      cartCtx.replaceCartItems(...cartData);
    }
    // eslint-disable-next-line
  }, [cartData]);

  useEffect(() => {
    if (cartCtx.changed) {
      const hasItems = cartCtx.items.length !== 0;

      const config = {
        method: "put",
        url: "http://localhost:4000/cart/cart",
        data: {
          id: "cart",
          items: cartCtx.items,
          totalAmount: hasItems ? cartCtx.totalAmount : 0,
        },
      };

      request(config);
    }
  }, [cartCtx, request]);

  const toggleCartHandler = () => {
    setCartIsShown(!cartIsShown);
  };

  if (isLoading) {
    return (
      <div className="centered">
        <LoadingSpinner />
      </div>
    );
  }

  return (
    <>
      {cartIsShown && <Cart onClose={toggleCartHandler} />}
      <Header onShowCart={toggleCartHandler} />
      <main>
        <Meals />
      </main>
    </>
  );
}

export default App;
