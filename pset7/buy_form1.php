<form action= "buy.php" method= "POST">
<fieldset>
<p>
<center>
    Your total would be $<?= $total?>
</center>
</p>

<p>
    Your actual balance is $<?= $actualcash ?>
    Would you like to proceed?
</p>

    <input name="shares" type="checkbox" value="<?= $shares?>"/> <?= $shares?> shares</br>
    <input name="symbol" type="checkbox" value="<?= $symbol?>"/> of <?= $symbol?></br>
    <input name= "confirmation" type="radio" value="Y"/> Yes
    <input name="confirmation" type="radio" value="N"/> No
    </br>
    <div class = "form-group">
        <button type= "submit" class = "btn btn-default">Continue</button>
    </div>
</fieldset>
</form>
