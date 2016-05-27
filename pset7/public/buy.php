<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // Check the stock is one that the user is currently holding
        if (empty($_POST["symbol"]) || empty($_POST["shares"])) { // covers the case when numberOfShares is 0 for some reason
            apologize("Please enter a stock to sell and the number of shares to sell");
        }
        // Make sure share is a whole number 
        if (preg_match("/^\d+$/", $_POST["shares"])) {
            // Convert input into uppercase
            $symbol = strtoupper($_POST["symbol"]);
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?",$_SESSION["id"],$symbol, $_POST["shares"], $_POST["shares"]);
            // update cash: reduce money - make sure they have enough money
            $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $stock = lookup($_POST["symbol"]);
            $totalStock = $stock["price"]*$_POST["shares"]; // Add in the number of stocks sold
           // echo $cash[0]["cash"]. $totalStock;
            if ($cash[0]["cash"] >= $totalStock) {
                CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $totalStock, $_SESSION["id"]);
                CS50::query("INSERT INTO history( user_id, transaction, symbol, shares, price, TIMESTAMP ) VALUES (?, 'BUY', ?, ?, ?, NOW( ) )", $_SESSION["id"], $symbol, $_POST["shares"], $stock["price"]);
            }
            
            redirect("index.php");
        } else {
            apologize("Please enter positive stock value");
        }
    
    }


    

?><?php 
function console( $data ) {

    if ( is_array( $data ) )
        $output = "<script>console.log( 'Debug Objects: " . implode( ',', $data) . "' );</script>";
    else
        $output = "<script>console.log( 'Debug Objects: " . $data . "' );</script>";

    echo $output;
}
?>
