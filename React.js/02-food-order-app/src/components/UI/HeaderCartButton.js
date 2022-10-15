import { useContext, useEffect, useState } from "react";
import CartContext from "../../store/cart-context";
import CartIcon from "../Cart/CartIcon";
import classes from "./HeaderCartButton.module.css";

const HeaderCartButton = (props) => {
  const cartCtx = useContext(CartContext);
  const [btnIsHighlighted, setBtnIsHighlighted] = useState(false);

  const numberOfCartItems = cartCtx.items.reduce(
    (acc, item) => acc + item.amount,
    0
  );

  useEffect(() => {
    setBtnIsHighlighted(true);

    const timer = setTimeout(() => {
      setBtnIsHighlighted(false);
    }, 300);

    return () => {
      // always clear created timers
      clearTimeout(timer);
    };
  }, [numberOfCartItems]);

  const cartBtnClasses = `${classes.button} ${
    btnIsHighlighted && classes.bump
  }`;

  return (
    <button onClick={props.onClick} className={cartBtnClasses}>
      <span className={classes.icon}>
        <CartIcon className={classes.icon} />
      </span>
      <span>Your Cart</span>
      <span className={classes.badge}>{numberOfCartItems}</span>
    </button>
  );
};

export default HeaderCartButton;
