import React, { useContext } from "react";

import MealItemForm from "./MealItemForm";
import CartContext from "../../store/cart-context";
import classes from "./MealItem.module.css";

const MealItem = (props) => {
  const cartCtx = useContext(CartContext);

  const price = `$${props.price.toFixed(2)}`;

  const onAddToCartHandler = (amount) => {
    const item = {
      id: props.id,
      name: props.name,
      price: props.price,
      amount,
    };

    cartCtx.addItem(item);
  };

  return (
    <li className={classes.meal}>
      <div>
        <h3>{props.name}</h3>
        <p className={classes.description}>{props.description}</p>
        <div className={classes.price}>{price}</div>
      </div>
      <MealItemForm onAddToCart={onAddToCartHandler} />
    </li>
  );
};

export default MealItem;
