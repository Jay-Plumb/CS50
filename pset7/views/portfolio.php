<table class="table">
<?php if (isset($positions) && isset($cash)): ?>

     <thead>
      <tr>
        <th>Symbol</th>
        <th>Name</th>
        <th>Shares</th>
        <th>Price</th>
        <th>TOTAL</th>
      </tr>
    </thead>
    <tbody>
    <?php foreach ($positions as $position): ?>
        <tr> 
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= $position["price"] ?></td>
            <td>$<?= $cash ?></td>
        </tr>
    <?php endforeach ?>
    <?php else: ?>
        <div>USER HAS NO POSITIONS</div>
<?php endif ?>
    </tbody>
</table>
