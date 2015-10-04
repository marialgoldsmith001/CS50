<form action= "buy.php" method= "POST">
<div id = "middle">

<div>
    <table class = "table-condensed">
        <td colspan = "7">BALANCE</td>
        <td> $<?= $actualcash ?></td>
    </table>
</div>

<fieldset>
    <div class="form-group">
        <input class= "form control" name ="symbol" placeholder="Stock Symbol" type= "text"/>
    </div>
    <div class="form-group">
        <input class= "form control" name ="shares" placeholder="Amount of shares" type= "number" min = "0"/>
    </div>
    <div class = "form-group">
        <button type= "submit" class = "btn btn-default">Buy</button>
    </div>
</fieldset>

</div>
</form>
