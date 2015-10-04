<?php
    //configuration
    require("../includes/config.php");
    
    //if user reached page via GET (as by clicking a link or via redirect)
    if($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //else render form
        render("changeform.php", ["title" => "Change Password"]);
    }
    
    //else if user reached page via POST (a by submitting a form via POST)
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(!empty($_POST["actualpass"]) && !empty($_POST["newpass"])
           && !empty($_POST["confirm"]))
        {
            $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            if (crypt($_POST["actualpass"], $rows[0]["hash"]) == $rows[0]["hash"])
            {
                if($_POST["newpass"] === $_POST["confirm"])
                {
                    query("UPDATE users SET hash = ? WHERE id =?", crypt($_POST["newpass"]), $_SESSION["id"]);
                    render("changeform1.php", ["title" => "Change Password"]);
                }
                else
                {
                    apologize("Your new password and the confirmation does not match");
                }    
            }
            else
            {
                apologize("Wrong Password");
            }
        }
        else
        {
            apologize("Please provide your actual password, your new password, and the confirmation");
        }
    }
?>
