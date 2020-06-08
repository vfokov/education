<?php

/**
 * @file
 * Page callbacks for Zoom API module.
 */

/**
 * Page callback: Zoom API Webhooks.
 */
function zoomapi_webhooks_callback() {
  $content = trim(file_get_contents('php://input'));
  $data = json_decode($content, TRUE);
  $webhook_part = _zoomapi_get_webhook_url_part(request_uri()) ?: 'default';

  if (variable_get('zoomapi_debug', FALSE)) {
    watchdog('zoomapi_debug', '!debug', [
      '!debug' => '<pre>' . print_r($data, TRUE) . '</pre>',
    ], WATCHDOG_DEBUG);
  }

  if (!variable_get('zoomapi_webhooks_log_disabled', FALSE)) {
    $record = [
      'url' => $_SERVER['HTTP_HOST'] . request_uri(),
      'url_part' => $webhook_part,
      'ip_address' => ip_address(),
      'event' => !empty($data['event']) ? $data['event'] : '',
      'data' => serialize($data),
      'realm' => zoomapi_realm(),
      'created' => REQUEST_TIME,
    ];
    db_insert('zoomapi_webhooks_log')
      ->fields($record)
      ->execute();
  }

  // @todo validate meeting uuid (with host_id?) in meeting tracker table before
  // invoking hook?
  module_invoke_all('zoomapi_webhooks', $data);

  return drupal_json_output(['status' => 'ok']);
}
