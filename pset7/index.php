<?php

    // configuration
    require("../includes/config.php"); 
    
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if($stock !== false)
        {
            $positions[] = [ "name" => $stock["name"],
                "price" => $stock["price"],
                "total" => $stock["price"]*$row["shares"],
                "shares" => $row["shares"], "symbol" => $row["symbol"]];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions,
        "balance" => number_format($cash[0]["cash"],2),
        "title" => "Portfolio"]);
?>
