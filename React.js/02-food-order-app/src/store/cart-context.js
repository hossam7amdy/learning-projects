import React from "react";

const CartContext = React.createContext({
  items: [],
  totalAmount: 0,
  changed: false,
  addItem: (item) => {},
  removeItem: (id) => {},
  clearCart: () => {},
  replaceCartItems: (cart) => {},
});

export default CartContext;
