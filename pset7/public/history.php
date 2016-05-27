<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET") {

        $rows = CS50::query("SELECT * FROM history WHERE user_id = ? ", $_SESSION["id"]);
        
        $positions = [];
        foreach ($rows as $row) {
          
               $positions[] = [
                    "transaction" => $row["transaction"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"],
                    "price" => $row["price"],
                    "timestamp" => $row["timestamp"]
                ];
        }
    
        render("history.php", ["title" => "History", "positions" => $positions]);
    }
?>