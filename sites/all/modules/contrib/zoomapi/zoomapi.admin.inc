<?php

/**
 * @file
 * Page callbacks for Zoom API administrative pages.
 */

/**
 * Settings Form.
 */
function zoomapi_settings_form($form, &$form_state) {
  $api_key = variable_get('zoomapi_key', '');
  $api_secret = variable_get('zoomapi_secret', '');

  $form['zoomapi_create_on_new_user'] = [
    '#title' => t('Create Zoom User for every account'),
    '#description' => t('Create a zoom account for each new user. Note: this is not retroactive.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('zoomapi_create_on_new_user', FALSE),
  ];

  $form['zoomapi_user_email_pattern'] = [
    '#title' => t('Zoom user email pattern'),
    '#description' => t('The pattern used to auto generate email addresses for new user accounts when an email is not provided.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('zoomapi_user_email_pattern', ZOOMAPI_USER_EMAIL_PATTERN_DEFAULT),
  ];

  $form['zoomapi_use_account_email'] = [
    '#title' => t('User Drupal account email addresses'),
    '#description' => t('Check this to use Drupal account email addresses for Zoom user email addresses. Off by default as this can lead to potential issues if that email address is already used on Zoom.'),
    '#type' => 'checkbox',
    '#value' => variable_get('zoomapi_use_account_email', FALSE),
  ];

  $form['credentials'] = [
    '#title' => t('Credentials'),
    '#description' => t('Enter or update Zoom account credentials.'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => ($api_key && $api_secret),
  ];

  // API Key.
  $form['credentials']['zoomapi_key'] = [
    '#title' => t('Zoom API Key'),
    '#description' => 'https://developer.zoom.us/',
    '#default_value' => $api_key,
    '#type' => 'textfield',
    '#required' => TRUE,
  ];

  // API Secret.
  $form['credentials']['zoomapi_secret'] = [
    '#title' => t('Zoom API Secret'),
    '#description' => 'https://developer.zoom.us/',
    '#default_value' => $api_secret,
    '#type' => 'textfield',
    '#required' => TRUE,
  ];

  return system_settings_form($form);
}

/**
 * Report: Custom List.
 *
 * @todo this makes multiple api calls to get the full list of items so they
 * can be paged / sorted. Look into caching.
 * @todo make certain variables easier to access in form alter.
 */
function zoomapi_report_custom_list_form($form, &$form_state, $api) {
  $form['api'] = [
    '#type' => 'value',
    '#value' => $api,
  ];

  _zoomapi_build_data_list($form, $form_state, $api);

  return $form;
}

/**
 * Build data / report table.
 */
function _zoomapi_build_data_list(&$form, &$form_state, $api) {
  $zoom_client = zoomapi_client();
  $query = drupal_get_query_parameters();
  $pager_info = [
    'page_size' => !empty($query['page_size']) ? $query['page_size'] : 20,
    'page_number' => !empty($query['page_number']) ? $query['page_number'] + 1 : 1,
    'sort_field' => !empty($query['order']) ? str_replace(' ', '_', strtolower($query['order'])) : '',
    'sort_dir' => !empty($query['sort']) ? $query['sort'] : 'asc',
    'total_records' => 0,
    'page_count' => 0,
  ];
  // @todo $params currently not used with fetchAll.
  $params = [
    'page_size' => $pager_info['page_size'],
    'page_number' => $pager_info['page_number'],
  ];

  $cid = "zoomapi_data_list:{$api}";
  $items = [];
  $using_cached = FALSE;

  if ($cache = cache_get($cid)) {
    $items = ($cache->expire > REQUEST_TIME) ? $cache->data : [];
    $using_cached = !empty($items);
  }

  if (!$items) {
    $items = $zoom_client->api($api)->fetchAll();

    if ($items) {
      cache_set($cid, $items, 'cache', strtotime('+1 hour'));
    }
  }

  $form['list_wrapper'] = [
    'header' => [],
    'list' => [],
    'pager' => [],
    'empty' => [],
  ];

  if ($items) {
    $pager_info['total_records'] = count($items);
    $pager_info['page_count'] = ceil($pager_info['total_records'] / $pager_info['page_size']);

    $properties = _zoomapi_report_custom_list_get_properties($items);
    $header = _zoomapi_report_custom_list_get_header($properties);
    $defaults = array_fill_keys(array_keys($properties), '');

    array_walk($items, function (&$item) use ($defaults) {
      $item = array_replace($defaults, $item);
    });

    if ($pager_info['sort_field']) {
      usort($items, function ($a, $b) use ($pager_info) {
        $direction = ($pager_info['sort_dir'] == 'asc') ? 1 : -1;
        $cmp = strnatcasecmp($a[$pager_info['sort_field']], $b[$pager_info['sort_field']]);
        return $cmp * $direction;
      });
    }

    foreach ($items as $delta => &$item) {
      foreach ($item as $property => $value) {
        if (is_array($value)) {
          $item[$property] = implode('<br/>', $value);
        }
      }
    }

    $pager_info['current_page'] = pager_default_initialize($pager_info['total_records'], $pager_info['page_size']);
    $chunks = array_chunk($items, $pager_info['page_size'], TRUE);

    $form['list_wrapper']['list'] = [
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => !empty($chunks[$pager_info['current_page']]) ? $chunks[$pager_info['current_page']] : [],
    ];
    $form['list_wrapper']['pager'] = [
      '#theme' => 'pager',
      '#variables' => [
        'quantity' => $pager_info['page_count'],
      ],
    ];
  }
  else {
    $form['list_wrapper']['empty'] = [
      '#markup' => t('No "@api" records found.', [
        '@api' => $api,
      ]),
    ];
  }

  if ($using_cached) {
    $form['list_wrapper']['header']['clear_cache'] = [
      '#type' => 'submit',
      '#value' => t('Reload'),
      '#submit' => ['_zoomapi_build_data_list_clear_cache_submit'],
    ];
  }
}

/**
 * Submit handler: Clear cached data.
 */
function _zoomapi_build_data_list_clear_cache_submit($form, &$form_state) {
  $api = $form_state['values']['api'];
  $cid = "zoomapi_data_list:{$api}";
  cache_clear_all($cid, 'cache');
}

/**
 * Evaluate all items to generate list of properties in array.
 *
 * Note: We need to evaluate each item since any single item may not have all
 * properties.
 */
function _zoomapi_report_custom_list_get_properties($items, $limit = 0) {
  $properties = [];

  foreach ($items as $item) {
    foreach ($item as $key => $value) {
      $properties[$key] = ucwords(str_replace('_', ' ', $key));
    }
  }

  return $properties;
}

/**
 * Dynamically generate a table header based on an associative array.
 */
function _zoomapi_report_custom_list_get_header($properties) {
  $header = [];

  foreach ($properties as $property => $label) {
    $header[$property] = [
      'data' => $label,
      'field' => $property,
    ];
  }

  return $header;
}
