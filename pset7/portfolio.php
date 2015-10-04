
<div id="middle">

<div>
    <table class = "table-condensed">
        <td colspan = "7">BALANCE</td>
        <td><?= $balance ?> $</td>
    </table>
</div>

<div>
    <table class = "table">
    <thead>
        <tr>
            <th><center>Symbol</center></th>
            <th><center>Name</center></th>
            <th><center>Shares</center></th>
            <th><center>Price</center></th>
            <th><center>TOTAL</center></th>
        </tr>
    </thead>
    <tbody>
        <?php
            foreach($positions as $position)
            {
                print("<tr>");
                print("<td>{$position["symbol"]}</td>");
                print("<td>{$position["name"]}</td>");
                print("<td>{$position["shares"]}</td>");
                print("<td>{$position["price"]}</td>");
                print("<td>{$position["total"]}</td>");
                print("</tr>");
            }
        ?>
    </tbody>
    </table>
</div>

<div>
<ul class="nav nav-pills">
<center>
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="changepassword.php">Change your password</a></li>
</center>
</ul>

</div>

</div>

<div>
    <a href="logout.php">Log Out</a>
</div>
