<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<div id="front__logos">
  <?php foreach ($rows as $id => $row): ?>
    <div class="item" >
      <?php print $row; ?>
    </div>
  <?php endforeach; ?>
</div>
