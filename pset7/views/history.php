<table class="table">
<?php if (isset($positions)): ?>

     <thead>
      <tr>
        <th>Transaction</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
        <th>Date/Time</th>
      </tr>
    </thead>
    <tbody>
    <?php foreach ($positions as $position): ?>
        <tr> 
            <td><?= $position["transaction"] ?></td>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= $position["price"] ?></td>
            <td><?= $position["timestamp"] ?></td>
        </tr>
    <?php endforeach ?>
    <?php else: ?>
        <div>USER HAS NO HISTORY</div>
<?php endif ?>
    </tbody>
</table>
