import { useEffect, useState } from "react";
import useFetch from "../../hooks/use-fetch";
import Card from "../UI/Card";
import LoadingSpinner from "../UI/LoadingSpinner";
import classes from "./AvailableMeals.module.css";
import MealItem from "./MealItem";

const AvailableMeals = () => {
  const [mealsList, setMealsList] = useState([]);
  const { isLoading, error, data } = useFetch(
    "https://food-order-app-74b26-default-rtdb.firebaseio.com/meals.json"
  );

  useEffect(() => {
    const mealsArray = [];
    for (const key in data) {
      mealsArray.push({ id: key, ...data[key] });
    }
    setMealsList(mealsArray);
  }, [data]);

  const mealsItems = mealsList.map((meal) => {
    return (
      <MealItem
        id={meal.id}
        key={meal.id}
        name={meal.name}
        description={meal.description}
        price={meal.price}
      />
    );
  });

  let content;
  if (isLoading) {
    content = <LoadingSpinner />;
  }
  if (error) {
    content = <p className={classes.error}>{error}</p>;
  }
  if (mealsItems.length > 0) {
    content = mealsItems;
  }

  return (
    <section className={classes.meals}>
      <Card>
        <ul>{content}</ul>
      </Card>
    </section>
  );
};

export default AvailableMeals;
