<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("cash.php", ["title" => "Cash"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["cash"])) { // handles if input is 0
            apologize("Please enter a value");
        } else if ($_POST["cash"] < 0) {
            apologize("Please enter a positive value");
        }
        
        if ($_POST["cash"] > 1000) {
            apologize("Maximum amount to deposit is $1000");
        }
        
        // Update cash in database
         CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["cash"], $_SESSION["id"]);
        redirect("index.php");
    }
?>