import { Fragment, useContext, useState } from "react";
import CartContext from "../../store/cart-context";
import Checkout from "./Checkout";
import Modal from "../UI/Modal";
import classes from "./Cart.module.css";
import CartItem from "./CartItem";
import useFetch from "../../hooks/use-fetch";
import LoadingSpinner from "../UI/LoadingSpinner";

const Cart = (props) => {
  const [didSubmit, setDidSubmit] = useState(false);
  const [isCheckout, setIsCheckout] = useState(false);
  const [isSubmitting, setIsSubmitting] = useState(false);

  const { error, isLoading, fetchAPI: updateCart } = useFetch();
  const cartCtx = useContext(CartContext);

  const hasItems = cartCtx.items.length > 0;
  const totalAmount = `$${cartCtx.totalAmount.toFixed(2)}`;

  const cartItemRemoveHandler = (id) => {
    cartCtx.removeItem(id);
  };

  const cartItemAddHandler = (item) => {
    cartCtx.addItem({
      ...item,
      amount: 1,
    });
  };

  const checkoutHandler = () => {
    setIsCheckout((cartIsShown) => !cartIsShown);
  };

  const submitOrderHandler = async (userData) => {
    setIsSubmitting(true);
    await updateCart(
      "https://food-order-app-74b26-default-rtdb.firebaseio.com/orders.json",
      {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: {
          user: userData,
          order: cartCtx,
        },
      }
    );

    console.log(error); // ???
    cartCtx.clearCart();
    setDidSubmit(true);
    setIsSubmitting(false);
  };

  const cartItems = (
    <ul className={classes["cart-items"]}>
      {cartCtx.items.map((item) => (
        <CartItem
          key={item.id}
          name={item.name}
          price={item.price}
          amount={item.amount}
          onRemove={cartItemRemoveHandler.bind(null, item.id)}
          onAdd={cartItemAddHandler.bind(null, item)}
        />
      ))}
    </ul>
  );

  const modalActions = (
    <div className={classes.actions}>
      <button onClick={props.onClose} className={classes["button--alt"]}>
        Close
      </button>
      {hasItems && (
        <button onClick={checkoutHandler} className={classes.button}>
          Order
        </button>
      )}
    </div>
  );

  const cartModalContent = (
    <Fragment>
      {!isCheckout && cartItems}
      <div className={classes.total}>
        <span>Total Amount</span>
        <span>{totalAmount}</span>
      </div>
      {isCheckout && (
        <Checkout onCancel={checkoutHandler} onSubmit={submitOrderHandler} />
      )}
      {!isCheckout && modalActions}
    </Fragment>
  );

  let isSubmittingModalContent;
  if (isLoading) {
    isSubmittingModalContent = <LoadingSpinner />;
  }
  if (!isLoading && error) {
    isSubmittingModalContent = (
      <Fragment>
        <p className={classes.error}>{error}. Try again Later!</p>
        <div className={classes.actions}>
          <button onClick={props.onClose} className={classes.button}>
            Close
          </button>
        </div>
      </Fragment>
    );
  }
  // (didSubmit && !error) // doesn't work. Don't know why yet ?
  if (didSubmit) {
    isSubmittingModalContent = (
      <Fragment>
        <p className={classes.success}>Successful Request</p>
        <div className={classes.actions}>
          <button onClick={props.onClose} className={classes.button}>
            Close
          </button>
        </div>
      </Fragment>
    );
  }

  return (
    <Modal onClick={props.onClose}>
      {!isSubmitting && !didSubmit && cartModalContent}
      {(didSubmit || isSubmitting) && isSubmittingModalContent}
    </Modal>
  );
};

export default Cart;
