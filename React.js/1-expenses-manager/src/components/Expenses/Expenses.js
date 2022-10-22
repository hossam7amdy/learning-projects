import Card from "../UI/Card";
import ExpensesFilter from "./ExpensesFilter";
import ExpensesList from "./ExpensesList";
import ExpensesChart from "./ExpensesChart";

import "./Expenses.css";
import { useState } from "react";

function Expenses(props) {
  const [selectedYear, setSelectedYear] = useState("2020");

  const selectedYearHandler = (year) => {
    setSelectedYear(year);
  };

  const filteredYear = props.items.filter(
    (expense) => expense.date.getFullYear().toString() === selectedYear
  );

  return (
    <li>
      <Card className="expenses">
        <ExpensesFilter
          selected={selectedYear}
          onYearChange={selectedYearHandler}
        />
        <ExpensesChart expenses={filteredYear} />
        <ExpensesList items={filteredYear} />
      </Card>
    </li>
  );
}

export default Expenses;
