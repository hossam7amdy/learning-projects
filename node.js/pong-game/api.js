const path = require("path");
const express = require("express");

const api = express();

api.use(express.static(path.join(__dirname, "public")));

api.use("/", express.static("index.html"));

module.exports = api;
