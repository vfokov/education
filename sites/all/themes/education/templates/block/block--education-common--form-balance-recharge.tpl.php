<?php
/**
 * Created by PhpStorm.
 * User: kostya
 * Date: 13.05.16
 * Time: 18:54
 */
?>

<div id="balance_recharge" class="popup" style="display: none;">
  <button class="popup__close"></button>

  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <div class="popup__title" style="text-align:center;"><?php print $block->subject ?></div>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php print $content ?>

</div>


