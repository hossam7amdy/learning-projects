import React, { useReducer } from "react";
import CartContext from "./cart-context";

const initCartState = {
  items: [],
  totalAmount: 0,
  changed: false,
};

const cartReducer = (state, action) => {
  if (action.type === "REPLACE") {
    return {
      items: action.cart.items || [],
      totalAmount: action.cart.totalAmount || 0,
      changed: false,
    };
  }
  if (action.type === "ADD") {
    const itemIdx = state.items.findIndex((item) => item.id === action.item.id);
    let updatedItems;
    let updatedAmount;
    if (itemIdx === -1) {
      updatedItems = state.items.concat(action.item);
      updatedAmount =
        state.totalAmount + action.item.amount * action.item.price;
    } else {
      updatedItems = state.items;
      updatedAmount = state.totalAmount;

      updatedItems[itemIdx].amount += action.item.amount;
      updatedAmount += action.item.amount * action.item.price;
    }
    return {
      items: updatedItems,
      totalAmount: updatedAmount,
      changed: true,
    };
  }
  if (action.type === "REMOVE") {
    const itemIdx = state.items.findIndex((item) => item.id === action.id);

    const updatedItems = state.items;
    const updatedAmount = state.totalAmount - updatedItems[itemIdx].price;

    if (updatedItems[itemIdx].amount === 1) {
      updatedItems.splice(itemIdx, 1);
    } else {
      --updatedItems[itemIdx].amount;
    }
    return {
      items: updatedItems,
      totalAmount: updatedAmount,
      changed: true,
    };
  }
  if (action.type === "CLEAR") {
    return {
      items: [],
      totalAmount: 0,
      changed: true,
    };
  }
  return initCartState;
};

const CartProvider = (props) => {
  const [cartState, dispatchCartState] = useReducer(cartReducer, initCartState);

  const addItemToCartHandler = (item) => {
    dispatchCartState({ type: "ADD", item });
  };

  const removeItemFromCartHandler = (id) => {
    dispatchCartState({ type: "REMOVE", id });
  };

  const clearCartHandler = () => {
    dispatchCartState({ type: "CLEAR" });
  };

  const replaceCartHandler = (cart) => {
    console.log(cart);
    dispatchCartState({ type: "REPLACE", cart });
  };

  const cartContext = {
    ...cartState,
    addItem: addItemToCartHandler,
    removeItem: removeItemFromCartHandler,
    clearCart: clearCartHandler,
    replaceCartItems: replaceCartHandler,
  };

  return (
    <CartContext.Provider value={cartContext}>
      {props.children}
    </CartContext.Provider>
  );
};

export default CartProvider;
