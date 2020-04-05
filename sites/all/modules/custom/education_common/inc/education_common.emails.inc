<?php

/**
 * Order mail data after order created
 * после оформления заказа
 */
function education_common_get_order_mail_data($order){

  $order_items = array();

  // инициализируем доставку-адрес
  //$delivery_address = '';

  $product_article = '';
  $shipping_data = '';
  $total =  commerce_currency_format($order->commerce_order_total[LANGUAGE_NONE][0]['amount'], $order->commerce_order_total[LANGUAGE_NONE][0]['currency_code']);
  foreach ($order->commerce_line_items[LANGUAGE_NONE] as $line_item) {
    $items[] = commerce_line_item_load($line_item['line_item_id']);
  }

  $header = array(
    array('data' => 'Article', 'class' =>'product-sku' ),
    array('data' => 'Title', 'class' =>'product-title' ),
    'Price',
    'Quantity',
    'Total'
  );
  $rows = array();

  $order_items_count = 0;
  foreach ($items as $item) {

    $product = commerce_product_load($item->commerce_product[LANGUAGE_NONE][0]['product_id']);
    $formatted_price = commerce_currency_format($item->commerce_unit_price[LANGUAGE_NONE][0]['amount'], $item->commerce_unit_price[LANGUAGE_NONE][0]['currency_code']);

    if (isset($product->field_moysklad_article['und'])) {
      $product_article = !empty($product->field_moysklad_article['und'][0]['value']) ? $product->field_moysklad_article['und'][0]['value'] : '';
    }

    if ($item->type != 'shipping') {

      $formatted_summary = commerce_currency_format($item->commerce_total[LANGUAGE_NONE][0]['amount'], $item->commerce_total[LANGUAGE_NONE][0]['currency_code']);

      $rows[] = array($product_article, $product->title, $formatted_price,  number_format($item->quantity), $formatted_summary);

      // позиции заказа
      $order_items[$order_items_count]['position'] = $order_items_count + 1;
      $order_items[$order_items_count]['title'] = $product->title;
      $order_items[$order_items_count]['quantity'] = number_format($item->quantity);
      $order_items[$order_items_count]['formatted_summary'] = $formatted_summary;
      // позиция товара в заказа
      $order_items_count++;
    }
    else {
      $shipping_data = $item->line_item_label;
    }

  }

  $output = '';
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= "\nSumm: " . $total . "\n";

  // Данные пользователя
  $output .= "\nДанные пользователя: \n";
  if (isset($order->mail)) {
    $output .= "E-mail: " . $order->mail . "\n";
  }

  $output = theme('education_common_mail_body', array(
    'order_items' => $order_items,
    'order_num' => $order->order_id,
    'order_uid' => $order->uid,
    'order_total' => $total,
    //'order_delivery' => $delivery_address,
    // 'order_payment'=> $order_payment,
    // 'order_comment'=> $order_comment,
  ));

  return $output;
}
