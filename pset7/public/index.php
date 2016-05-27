<?php

    // configuration
    require("../includes/config.php"); 
    
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $cashRow = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    
    // pass in users cash also from index.php to portfolio.php via render
    $positions = [];
    foreach ($rows as $row) {
      
       $stock = lookup($row["symbol"]);
       
       if ($stock !== false) {

           $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
       }
    }
    if ($cashRow !== false) {
        $cash = $cashRow[0]["cash"];
    }
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);
    
?>

<?php 
function console( $data ) {

    if ( is_array( $data ) )
        $output = "<script>console.log( 'Debug Objects: " . implode( ',', $data) . "' );</script>";
    else
        $output = "<script>console.log( 'Debug Objects: " . $data . "' );</script>";

    echo $output;
}
?>
