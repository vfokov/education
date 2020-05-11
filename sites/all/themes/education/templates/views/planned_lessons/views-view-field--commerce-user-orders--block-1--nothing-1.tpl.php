<?php
$lesson = node_load($row->field_product_reference_commerce_product_nid);
$classroom_nid = isset($lesson->field_classroom[LANGUAGE_NONE]) ?
  $lesson->field_classroom[LANGUAGE_NONE][0]['nid'] : '';
?>
<?php if ($row->commerce_order_status == 'paid' && $classroom_nid): ?>
<a href="/classroom/<?php print $classroom_nid; ?>"
   class="btn classroom_link" >Go to classroom</a>
<?php else: ?>
  <span></span>
<?php endif; ?>
