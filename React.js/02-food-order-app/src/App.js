import React, { useContext, useEffect, useState } from "react";

import Cart from "./components/Cart/Cart";
import Header from "./components/Layout/Header";
import Meals from "./components/Meals/Meals";
import LoadingSpinner from "./components/UI/LoadingSpinner";

import useFetch from "./hooks/use-fetch";
import CartContext from "./store/cart-context";
import CartProvider from "./store/CartProvider";

let isInitial = true;

function App() {
  const cartCtx = useContext(CartContext);
  const [cartIsShown, setCartIsShown] = useState(false);
  const {
    isLoading,
    data: cartData,
    fetchAPI: sendCartItems,
  } = useFetch(
    "https://food-order-app-74b26-default-rtdb.firebaseio.com/cart.json"
  );

  useEffect(() => {
    if (cartData) {
      // BUG: cart does not update
      cartCtx.replaceCartItems({
        items: cartData.meals,
        totalAmount: cartData.totalAmount,
      });
    }
  }, [cartData, cartCtx]);

  useEffect(() => {
    if (isInitial) {
      isInitial = false;
      return;
    }

    if (cartCtx.changed) {
      sendCartItems(
        "https://food-order-app-74b26-default-rtdb.firebaseio.com/cart.json",
        {
          method: "PUT",
          headers: { "Content-Type": "application/json" },
          body: { items: cartCtx.items, totalAmount: cartCtx.totalAmount },
        }
      );
    }
  }, [cartCtx, sendCartItems]);

  const showCartHandler = () => {
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
    <CartProvider>
      {cartIsShown && <Cart onClose={showCartHandler} />}
      <Header onShowCart={showCartHandler} />
      <main>
        <Meals />
      </main>
    </CartProvider>
  );
}

export default App;
