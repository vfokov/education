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

</div>

<script>
  /*
  (function ($) {
  paypal.Buttons({
    createOrder: function(data, actions) {
      // This function sets up the details of the transaction, including the amount and line item details.
      return actions.order.create({
        purchase_units: [{
          amount: {
            value: '0.01'
          }
        }]
      });
    },
    onApprove: function(data, actions) {
      // This function captures the funds from the transaction.
      return actions.order.capture().then(function(details) {
        // This function shows a transaction success message to your buyer.
        alert('Transaction completed by ' + details.payer.name.given_name);
      });
    }
  }).render('#paypal-button-container');
  // This function displays Smart Payment Buttons on your web page.

  })(jQuery);
  */
</script>


