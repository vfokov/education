<?php
/**
 * Created by PhpStorm.
 * User: kostya
 * Date: 13.05.16
 * Time: 18:54
 */ 
?>

<div id="fast_cart" class="popup" style="display: none;">
  <button class="popup__close"></button>

  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <div class="popup__title" style="text-align:center;"><?php print $block->subject ?></div>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php print $content ?>
  
  <div class="kupit_v_credit-wrapper">
    <a style="display: none; text-align:center;" id="kupit_v_credit" class="kupit_v_credit" href="#">оформить в кредит</a>
  </div>
  
</div>


