<?php
    // configuration
    require("../includes/config.php");
    
    //select all stocks that the user has in portfolio 
    $shares = query("SELECT symbol FROM portfolio WHERE id = ?", $_SESSION["id"]);

    render("sell_form.php", ["symbols" => $shares]);
    
    // delete the symbol sold
    // update the amount of cash user has available
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        //select amount of shares that the person has
        $user_share = query("SELECT shares FROM portfolio WHERE id = ?
            AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        $stock = lookup($_POST["symbol"]);
        
        // see how much is going to be the sell
        // make sure that sell is configured to two decimal places
        $profit = $user_share[0]["shares"] * $stock["price"];
        $sold = query("DELETE FROM portfolio WHERE id = ? AND symbol = ?",
            $_SESSION["id"], $_POST["symbol"]);
            
        $update = query("UPDATE users SET cash = cash + ? WHERE id = ?",
            $profit, $_SESSION["id"]);
        
        $history = query("INSERT INTO history
                (`id`, `symbol`, `shares`, `price`, `sold/bought`) 
                VALUES (?,?,?,?,\"sold\")", 
                        $_SESSION["id"],$_POST["symbol"],
                        $user_share[0]["shares"],$stock["price"]);
            
        redirect("/");
    }
?>
