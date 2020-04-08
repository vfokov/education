<p style="font-size:16px">You've made booking at http://education.designseonweb.com/ </p>
<p>Contents of booking:&nbsp;</p>
<?php foreach ($order_items as $order_item): ?>
  <?php print $order_item['position']; ?>. <?php print $order_item['title']; ?> - <?php print $order_item['quantity']; ?> , summ <?php print $order_item['formatted_summary']; ?>.&nbsp;<br>
<?php endforeach; ?>

