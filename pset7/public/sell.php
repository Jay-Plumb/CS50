<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell.php", ["title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Check the stock is one that the user is currently holding
        if (empty($_POST["sell"]) || empty($_POST["numberOfShares"])) { // covers the case when numberOfShares is 0 for some reason
            apologize("Please enter a stock to sell and the number of shares to sell");
        }
        
         if (preg_match("/^\d+$/", $_POST["numberOfShares"])) {
            

            // Check the stock is one that the user is currently holding
            // Get number of shares 
            $numberShares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"] );
            
            // echo "inputfield " . $_POST["numberOfShares"] ." querydb ". $numberShares[0]["shares"]; // 100
    
            // Make sure the number of shares being sold is valid
            if ($_POST["numberOfShares"] > (int) $numberShares[0]["shares"]) {
                apologize("You are trying to sell too many number of shares"); 
            } else {
               
             $row = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"]);
            
            
             if (count($row) == 1) { // this check passes if $row is empty
                $stock = lookup($_POST["sell"]);
                // Delete from portfolios table
                if ($_POST["numberOfShares"] == (int) $numberShares[0]["shares"]) {
                    $result = CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"]); // only delete if all stocks gone
                } else {
                    CS50::query("UPDATE portfolios SET shares = shares - ? WHERE user_id = ? AND symbol = ?",$_POST["numberOfShares"] ,$_SESSION["id"], $_POST["sell"]);
                }
                
                $totalStock = $stock["price"]*$_POST["numberOfShares"]; // Add in the number of stocks sold
                CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $totalStock, $_SESSION["id"]);
                CS50::query("INSERT INTO history( user_id, transaction, symbol, shares, price, TIMESTAMP ) VALUES (?, 'SELL', ?, ?, ?, NOW( ) )", $_SESSION["id"], $_POST["sell"], $_POST["numberOfShares"], $stock["price"]); // update history
                redirect("index.php");
                
             }
        } 
    } else {
            apologize("Please enter a whole stock number");
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
