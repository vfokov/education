<?php

//echo '<pre>'; print_r($row); echo '</pre>'; die();
//$total = commerce_currency_format($row->commerce_order_total[LANGUAGE_NONE][0]['amount'], $order->commerce_order_total[LANGUAGE_NONE][0]['currency_code']);
$total = $row->field_commerce_order_total[0]['rendered']['#markup'];
?>

<?php
 print $output;
?>

<?php if ($row->commerce_order_status == 'pending'): ?>
<a href="#"
   class="btn product__lesson_pay popup__link" data-order-price="<?php print $total; ?>"
   data-popup="lesson_pay" data-order-id="<?php print $row->order_id; ?>" >Pay for the Lesson</a>


<?php else: ?>
  <span class="is_paid">Paid</span>
<?php endif; ?>
