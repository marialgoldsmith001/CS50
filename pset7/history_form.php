<div>
    <table class = "table">
    <thead>
        <tr>
            <th><center>Symbol</center></th>
            <th><center>Share</center></th>
            <th><center>Price</center></th>
            <th><center>Transaction</center></th>
            <th><center>Date/Time</center></th>
        </tr>
    </thead>
    <tbody>
        <?php
            foreach($table as $row)
            {
                print("<tr>");
                print("<td>".$row["symbol"]."</td>");
                print("<td>".$row["shares"]."</td>");
                print("<td>".$row["price"]."</td>");
                print("<td>" .$row["sold/bought"]."</td>");
                print("<td>" . date('d/m/y, g:i A', strtotime($row["timestamp"])) . "</td>");
                print("</tr>");
            }
        ?>
    </tbody>
    </table>
</div>

<div>
    get <a href="index.php">back</a> to your portfolio.
</div>
