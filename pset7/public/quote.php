<?php

// configuration
    require("../includes/config.php");
    
// controller

if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
       render("quote_form.php", ["title" => "quote"]);
    }
else if ($_SERVER["REQUEST_METHOD"] == "POST") {
   
    if ( empty($_POST["symbol"])) {
        apologize("Please enter a stock to lookup");
    } else {
      $stock = lookup($_POST["symbol"]);  
      //$stock = lookup("googl");
    } 
     
    if ($stock === false) {
        apologize("Could not find stock for " . $_POST["symbol"]);
    } else {
       // print("Price: " . $stock["price"]);  
        //render("quote.php", ["quote" => $stock ]);
        
        render("quote.php", ["name" => $stock["name"], "sym" => $stock["symbol"], "quote" => $stock["price"]]);
    }
   
}
?>