<?php
    //configuration
    require("../includes/config.php");
    
    //if user reached page via GET (as by clicking a link or via redirect)
    if($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    //else if user reached page via POST (a by submitting a form via POST)
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(!empty($_POST["username"]) && !empty($_POST["password"]) && 
        !empty($_POST["confirmation"]) && $_POST["password"] === $_POST["confirmation"])
        {
            $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
            if($result === false)
            {
                apologize("Username already exist, please provide another username");
            }
            else
            {
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
            }
        redirect("/");
        }
        else
        {
            if($_POST["password"] !== $_POST["confirmation"])
            {
                apologize("Your password does not match your confirmation, please try again");            
            }
            else
            {
                apologize("Please provide a username, and password");
            }
        }
    }
?>
