<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Validate passwords
        // Check to see if password and confirmation are not blank - give apology message if not
        if (empty($_POST["password"]) || empty($_POST["confirmation"])) {
            apologize("The password and/or confirmation field is empty");
        }
        // Check that password and confirmation are the same - give apology if not
        if ($_POST["password"] != $_POST["confirmation"]) {
            apologize("The password and confirmation does not match");
        }
        
        // add user to database
        $addUserResult =  CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        if ($addUserResult !== 1) {
            apologize("User already exists"); // throw error
            //error_reporting("User already exists");
        }
        // Remember user
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        $_SESSION["id"] = $id;
        // Redirect to index.php
        redirect("index.php");
        
    }

?>