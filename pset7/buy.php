<?php
    // configuration
    require("../includes/config.php");
    
    //if user reached page via GET (as by clicking a link or via redirect)
    if($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $cash = query("SELECT cash FROM users WHERE id = ?", 
                $_SESSION["id"]);           
        #dump($cash);
        //else render form
        render("buy_form.php", ["title" => "Buy", 
            "actualcash" => number_format($cash[0]["cash"], 2)]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $cash = query("SELECT cash FROM users WHERE id = ?", 
                $_SESSION["id"]);
                
        if(!empty($_POST["symbol"]))
        {
#            $looksymbol = [];
            $symbolbuy = lookup($_POST["symbol"]);
#            if($symbolbuy !== false)
#            {
#                $looksymbol = ["price" => $symbolbuy["price"]];
#            }
        }
        else
        {
            apologize("Please provide a stock symbol");
        }
        
        if(empty($_POST["shares"]))
        {
            apologize("Please provide de number of shares you would like to buy");
        }
        
        $total = $_POST["shares"] * $symbolbuy["price"];
        render("buy_form1.php", ["total" => number_format($total, 2), 
                 "actualcash" => number_format($cash[0]["cash"], 2),
                 "shares" => $_POST["shares"],
                 "symbol" => $_POST["symbol"]]);
                                 
        if( isset($_POST["confirmation"]) && $_POST["confirmation"] === "Y")
        {
            if($cash[0]["cash"] < $total)
            {
                apologize("You don't have enough cash to buy this stock");
                redirect("buy_form.php");
            }
            else
            {
                $_POST["symbol"] = strtoupper($_POST["symbol"]);
                $result = query("INSERT into portfolio (id, symbol, shares)
                      VALUES(?, ?, ?) 
                      ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", 
                      $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);

                $balance = query("UPDATE users SET cash = cash - ? WHERE id = ?",
                           $total, $_SESSION["id"]);
               
                $history = query("INSERT INTO history
                           (`id`, `symbol`, `shares`, `price`,
                           `sold/bought`) 
                           VALUES (?,?,?,?,\"bought\")",
                           $_SESSION["id"], $_POST["symbol"],
                           $_POST["shares"],
                           $symbolbuy["price"]);
            }
            
            redirect("/");
        }
        else if( isset($_POST["confirmation"]) && $_POST["confirmation"] === "N")
        {
            redirect("/");
        }
    }
    
?>
