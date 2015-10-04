<?php

    // configuration
    require("../includes/config.php"); 
    
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
#    $positions = [];
#    foreach ($rows as $row)
#    {
#        $positions[] = [ "id" => $row["id"],
#                         "symbol" => $row["symbol"],
#                         "shares" => $row["shares"],
#                         "price" => $row["price"], 
#                         "sold/bought" => $row["sold/bought"]
#                         "timestamp" => $row["timestamp"]];
#    }
#    
    // render portfolio
    render("history_form.php", ["table" => $rows,
           "title" => "History"]);
