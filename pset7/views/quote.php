<?php if (isset($name) && isset($sym) && isset($quote)): ?>
    <?php number_format($quote,2); ?>
        <h1> <?= $sym ?> <?= $name ?> $<?= $quote ?></h1>
    <?php else: ?>
         <div>Error showing stock...</div>
<?php endif ?>