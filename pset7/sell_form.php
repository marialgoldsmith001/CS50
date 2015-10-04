<form action= "sell.php" method = "post">
<div id = "middle">
Shares Available:
    <fieldset>
        <div class = "form-group">
            <select class = "form-control" name = "symbol">
                <option value = ""></option>
                 
                <?php
                    foreach($symbols as $symbol)
                    {
                        echo "<option value= \"".$symbol["symbol"]."\">".
                            $symbol["symbol"]."</option>";
                    }
                ?>
            </select>
        </div>
        <div class = "form-group">
            <button type= "submit" class = "btn btn-default">Sell</button>
        </div>
    </fieldset>
</div>
</form>
