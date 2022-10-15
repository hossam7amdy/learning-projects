import { useContext } from "react";
import useFetch from "../../hooks/use-fetch";
import CartContext from "../../store/cart-context";
import classes from "./MealItem.module.css";
import MealItemForm from "./MealItemForm";

const MealItem = (props) => {
  const cartCtx = useContext(CartContext);
  const { fetchAPI: sendMealsToCart } = useFetch();

  const price = `$${props.price.toFixed(2)}`;

  const onAddToCartHandler = async (amount) => {
    cartCtx.addItem({
      id: props.id,
      name: props.name,
      price: props.price,
      amount,
    });

    await sendMealsToCart(
      "https://food-order-app-74b26-default-rtdb.firebaseio.com/cart.json",
      {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: {
          meals: cartCtx.items,
          totalAmount: cartCtx.totalAmount,
        },
      }
    );
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
