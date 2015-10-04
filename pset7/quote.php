<?php
    require("../includes/config.php");
    
    //Once the form is submitted
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //make sure user provide name
        if(empty($_POST["code"]))
        {
            apologize("Provide a symbol, please");
        }
        
        $stock = lookup($_POST["code"]);
        
        // Check if stock symbol exist
        if($stock === false)
        {
            apologize("Invalid symbol");
        }
        else
        {
            render("quote_form_2.php", ["title" => "Quote", "symbol" => $stock["symbol"],
             "name" => $stock["name"], "price" => $stock["price"]]);
        }
    }
    else
    {
        render("quote_form_1.php", ["title" => "Quote"]);
    }
    ?>
