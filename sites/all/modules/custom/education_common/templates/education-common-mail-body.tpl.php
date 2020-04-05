<span style="font-size:16px">You've made booking №  <?php print $order_num; ?> in http://education.designseonweb.com/<br>
<br>
<strong>Contents of booking:&nbsp;</strong>
  <?php foreach ($order_items as $order_item): ?>
    <?php print $order_item['position']; ?>. <?php print $order_item['title']; ?> - <?php print $order_item['quantity']; ?> , summ <?php print $order_item['formatted_summary']; ?>.&nbsp;<br>
  <?php endforeach; ?>


