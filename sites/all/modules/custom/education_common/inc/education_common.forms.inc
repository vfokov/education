<?php

///////Enable lesson date form

function education_common_enable_lesson_date($form, &$form_state) {
  global $user;

  $form['enable_info'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="form__desc">Do you want to enable this lesson date?<br /><br /></div>',
    '#theme_wrappers' => array(),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['enable_product_id'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['enable_teacher_uid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  /*
  $form['enable_lesson_date'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );
  */

  $form['enabled_date'] = array(
    '#type' => 'container',
  );

  $form['enabled_date']['enable_lesson_date'] = array(
    //'#title' => 'Lesson date',
    '#title' => '',
    //'#type' => 'textfield',
    '#type' => 'date_popup',
    '#default_value' =>'',
    '#date_format' => 'Y-m-d',
    '#date_year_range' => '-3:+3',
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['enabled_enable_date_range'] = array(
    '#type' => 'checkbox',
    '#title' => t('Or select another date for range'),
  );

  // Date to hidden while enabled_enable_date_range is not checked
  $form['enabled_date']['enable_lesson_date_to'] = array(
    '#title' => 'Date to',
    '#type' => 'date_popup',
    '#default_value' =>'',
    '#date_format' => 'Y-m-d',
    '#date_year_range' => '-3:+3',
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="enabled_enable_date_range"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['enabled_date']['enable_time'] = array(
    //'#type' => 'datetime',
    '#type' => 'date_popup',
    '#title' => 'Select time for one position',
    '#size' => 20,
    '#date_format' => 'H:i',
    '#date_increment' => 30,
    '#default_value' => '00:00',
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="enabled_enable_time_range"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Uncheck anonymous field when the name field is filled.
  $form['enabled_enable_time_range'] = array(
    '#type' => 'checkbox',
    '#title' => t('Or select time range'),
    /*
    '#states' => array(
      'unchecked' => array(
        ':input[name="name"]' => array('filled' => TRUE),
        ':input[name="enable_time[time]"]' => array('filled' => TRUE),
      ),
    ),
    */
  );

  $form['enabled_time_range'] = array(
    '#input_title' => NULL,
    '#input2_title' => NULL,
    '#type' => 'slider',
    '#default_value' => array('value' => 0.00, 'value2' => 23.00),
    '#range' => TRUE,
    '#min' => 0.00,
    '#max' => 23.00,
    '#step' => 1.00,
    '#display_inputs' => FALSE,
    '#display_values' => TRUE,
    '#display_values_format' => '%{value}%.00',
    //'#weight' => 29,
    '#states' => array(
      'visible' => array(
        ':input[name="enabled_enable_time_range"]' => array('checked' => TRUE),
      ),
    ),
  );

  // TODO get lessons_products_nids of current user
  $type = 'lesson';
  $uid = $user->uid;
  $query = new EntityFieldQuery;
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('status', 1)
    ->propertyCondition('type', $type)
    ->propertyCondition('uid', $uid)
    ->execute();

  if (!empty($result['node'])) {
    $nids = array_keys($result['node']);
    $nodes = node_load_multiple($nids);
    $options = array();
    foreach ($nodes as $node) {
      $options[$node->nid] = $node->title;
    }
    $form['enable_lesson_nid'] = array(
      '#type' => 'select',
      '#title' => 'Select lesson to assign date',
      '#options' => $options,
      '#default_value' => '',
    );
  }

  //TODO time field
  // maybe https://www.drupal.org/project/timefield ?

  /*
  $form['enable_time'] = array(
    '#title' => 'Time',
    '#type' => 'timefield_default',
    '#default_value' => '',
  );
  */

  $form['current_path'] = array(
    '#type' => 'hidden',
    '#default_value' => current_path(),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit enable_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'education_common_enable_lesson_date_ajax_callback',
    ),
  );

  $form['no_enable'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit cancel enable_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  //honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));
  return $form;
}


// !!!!! TODO CHANGE this
function education_common_enable_lesson_date_submit(&$form, &$form_state) {

  $enable_product_id = $form_state['values']['enable_product_id'];
  $enable_teacher_uid = $form_state['values']['enable_teacher_uid'];
  $enable_lesson_date = $form_state['values']['enable_lesson_date'];
  $enable_lesson_time = $form_state['values']['enable_time'];
  $enable_lesson_nid = $form_state['values']['enable_lesson_nid'];

  $lesson_node = node_load($enable_lesson_nid);

  // collect date ranges when Date to is set
  $dates_range = array($enable_lesson_date);
  if (!empty($form_state['values']['enabled_enable_date_range'])) {
    $date_from = $form_state['values']['enable_lesson_date'];
    $date_to = $form_state['values']['enable_lesson_date_to'];

    $date_calc = $date_from;
    $date_calc_time = strtotime($date_calc);
    $date_to_time = strtotime($date_to);
    while ($date_calc_time < $date_to_time) {
      $date_calc = date('Y-m-d', strtotime('+1 day', strtotime($date_calc)) );
      $dates_range[] = $date_calc;
      $date_calc_time = strtotime($date_calc);
    }
  }

  // if time range selected
  if (!empty($form_state['values']['enabled_enable_time_range'])) {
    $new_date_items = array();
    $time_ranges = $form_state['values']['enabled_time_range'];
    $range_to = $time_ranges['value2'];
    $range_from = $time_ranges['value'];

    foreach ($dates_range as $enable_lesson_date) { // dates range
      for ($i = $range_from; $i <= $range_to; $i++) {

        $hour_value = $i < 10 ? '0' . $i : $i;
        $enable_lesson_time_item = $hour_value . ':' . '00';
        $enable_lesson_time_item_half = $hour_value . ':' . '30';
        $enable_lesson_date_time = $enable_lesson_date . ' ' . $enable_lesson_time_item;
        if ($i != $range_to) {
          $enable_lesson_date_time_half = $enable_lesson_date . ' ' . $enable_lesson_time_item_half;
        }

        //$new_date_items[] = array (
        $new_date_items_hour = array(
          'value' => $enable_lesson_date_time,
          // TODO change
          'timezone' => 'Asia/Yekaterinburg',
          'timezone_db' => 'Asia/Yekaterinburg',
          'date_type' => 'datetime',
        );

        if (isset($enable_lesson_date_time_half)) {
          $new_date_items_hour_half = array(
            'value' => $enable_lesson_date_time_half,
            // TODO change
            'timezone' => 'Asia/Yekaterinburg',
            'timezone_db' => 'Asia/Yekaterinburg',
            'date_type' => 'datetime',
          );
        }

        if ($lesson_node->field_lesson_date[LANGUAGE_NONE]) {
          //array_unshift($lesson_node->field_lesson_date['und'], $new_date_items);
          array_unshift($lesson_node->field_lesson_date[LANGUAGE_NONE], $new_date_items_hour);
          if (isset($enable_lesson_date_time_half)) {
            array_unshift($lesson_node->field_lesson_date[LANGUAGE_NONE], $new_date_items_hour_half);
          }
        }
      }
    }
    /*
    if ($lesson_node->field_lesson_date['und']) {
      array_unshift($lesson_node->field_lesson_date['und'], $new_date_items);
    }
    */
  }

  else { // ADD one position
    foreach ($dates_range as $enable_lesson_date) { // dates range
      $enable_lesson_date = $enable_lesson_date . ' ' . $enable_lesson_time;
      $new_date_item = array(
        'value' => $enable_lesson_date,
        // TODO change
        'timezone' => 'Asia/Yekaterinburg',
        'timezone_db' => 'Asia/Yekaterinburg',
        'date_type' => 'datetime',
      );

      if ($lesson_node->field_lesson_date[LANGUAGE_NONE]) {
        array_unshift($lesson_node->field_lesson_date[LANGUAGE_NONE], $new_date_item);
      }
    }
  }

  node_save($lesson_node); //break;

}

function education_common_enable_lesson_date_ajax_callback(&$form, &$form_state) {

  if ($form_state['values']['current_path']) {
    $current_path_text = 'Return to page';
    $current_path = $form_state['values']['current_path'];

    if ( strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
      $current_path_text = 'Return to page';
    }
  }

  $message = "<p>";
  $path_to_return = l($current_path_text, $current_path);

  $message .= '<div class="form__block"><div class="form__desc">
  You have enabled date for this lesson.<br />
      <br />' . $path_to_return . '</div></div>';

  $message .= "</p>";
  $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));

  return array('#type' => 'ajax', '#commands' => $commands);
}
///// END enable lesson date







///////Disable lesson date form

function education_common_disable_lesson_date($form, &$form_state) {

  $form['disable_info'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="form__desc">Do you want to disable this lesson date?<br /><br /></div>',
    '#theme_wrappers' => array(),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['disable_product_id'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['disable_teacher_uid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['disable_lesson_date'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );
  $form['disable_lesson_nid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['current_path'] = array(
    '#type' => 'hidden',
    '#default_value' => current_path(),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit disable_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'education_common_disable_lesson_date_ajax_callback',
    ),
  );

  $form['no_disable'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit cancel disable_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  //honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));
  return $form;
}

function education_common_disable_lesson_date_submit(&$form, &$form_state) {

  $disable_product_id = $form_state['values']['disable_product_id'];
  $disable_teacher_uid = $form_state['values']['disable_teacher_uid'];
  $disable_lesson_date = $form_state['values']['disable_lesson_date'];
  $disable_lesson_nid = $form_state['values']['disable_lesson_nid'];

  $d = 1;

  $lesson_node = node_load($disable_lesson_nid);

  if (isset($lesson_node->field_lesson_date[LANGUAGE_NONE])) {
    foreach($lesson_node->field_lesson_date[LANGUAGE_NONE] as $key => $lesson_date_item ) {
      if ($lesson_date_item['value'] == $disable_lesson_date) {
        //unset($lesson_node->field_lesson_date['und'][$key]);
        $lesson_node->field_lesson_date[LANGUAGE_NONE][$key] = null;
        node_save($lesson_node); break;
      }
    }
  }

}

function education_common_disable_lesson_date_ajax_callback(&$form, &$form_state) {

  if ($form_state['values']['current_path']) {
    $current_path_text = 'Return to page';
    $current_path = $form_state['values']['current_path'];

    if ( strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
      $current_path_text = 'Return to page';
    }
  }

  $message = "<p>";
  $path_to_return = l($current_path_text, $current_path);

  $message .= '<div class="form__block"><div class="form__desc">
  You have disabled date from this lesson.<br />
      <br />' . $path_to_return . '</div></div>';

  $message .= "</p>";
  $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));

  return array('#type' => 'ajax', '#commands' => $commands);
}
///// END disable lesson date





///////Close date form

function education_common_close_lesson_date($form, &$form_state) {

  $form['close_info'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="form__desc">Do you want to close this lesson date?<br /><br /></div>',
    '#theme_wrappers' => array(),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['close_product_id'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['close_teacher_uid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['close_lesson_date'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );
  $form['close_lesson_nid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['current_path'] = array(
    '#type' => 'hidden',
    '#default_value' => current_path(),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit close_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'education_common_close_lesson_date_ajax_callback',
    ),
  );

  $form['no_close'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit cancel close_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  //honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));
  return $form;
}

function education_common_close_lesson_date_submit(&$form, &$form_state) {

  $close_product_id = $form_state['values']['close_product_id'];
  $close_teacher_uid = $form_state['values']['close_teacher_uid'];
  $close_lesson_date = $form_state['values']['close_lesson_date'];
  $close_lesson_nid = $form_state['values']['close_lesson_nid'];

  $lesson_node = node_load($close_lesson_nid);

  if (isset($lesson_node->field_lesson_date[LANGUAGE_NONE])) {
    foreach($lesson_node->field_lesson_date[LANGUAGE_NONE] as $key => $lesson_date_item ) {
      if ($lesson_date_item['value'] == $close_lesson_date) {
        unset($lesson_node->field_lesson_date[LANGUAGE_NONE][$key]);
        node_save($lesson_node); break;
      }
    }
  }

}

function education_common_close_lesson_date_ajax_callback(&$form, &$form_state) {

  if ($form_state['values']['current_path']) {
    $current_path_text = 'Return to page';
    $current_path = $form_state['values']['current_path'];

    if ( strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
      $current_path_text = 'Return to page';
    }
  }

  $message = "<p>";
  $path_to_return = l($current_path_text, $current_path);

  $message .= '<div class="form__block"><div class="form__desc">
  You have removed date from this lesson.<br />
      <br />' . $path_to_return . '</div></div>';

  $message .= "</p>";
  $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));

  return array('#type' => 'ajax', '#commands' => $commands);
}


/**
 * Quick order form
 */
function education_common_quick_order($form, &$form_state) {
  global $user;
  $user_profile = user_load($user->uid);
  $form['info'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="form__desc">For quick booking fill the form.<br /></div>',
    '#theme_wrappers' => array(),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Your name',
    '#attributes' => array(
      'placeholder' => 'Your name',
    ),
    //'#theme_wrappers' => array(),
    '#default_value' => isset($user_profile->name) ? $user_profile->name :  '',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['user_phone'] = array(
    '#type' => 'textfield',
    '#title' => 'Phone',
    '#attributes' => array(
      'placeholder' => t('Phone'),
    ),
    //'#theme_wrappers' => array(),
    '#default_value' =>  isset($user_profile->field_phone[LANGUAGE_NONE]) ? $user_profile->field_phone[LANGUAGE_NONE][0]['value'] :  '',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => 'E-mail',
    '#attributes' => array(
      'placeholder' => 'E-mail',
    ),
    //'#theme_wrappers' => array(),
    '#default_value' => isset($user_profile->mail) ? $user_profile->mail :  '',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['current_path'] = array(
    '#type' => 'hidden',
    '#default_value' => current_path(),
  );

  $type = 'lesson';
  $uid = arg(1);

  // check uid
  if ($uid == 'schedule') {
    if (!empty($_GET['uid'])) {
      $user_name = $_GET['uid'];
      $t_user = user_load_by_name($user_name);
      $uid = $t_user->uid;
    }
  }

  $query = new EntityFieldQuery;
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('status', 1)
    ->propertyCondition('type', $type)
    ->propertyCondition('uid', $uid)
    ->execute();

  if (!empty($result['node'])) {
    $nids = array_keys($result['node']);
    $nodes = node_load_multiple($nids);
    $options = array();
    foreach ($nodes as $node) {
      $p_nid = $node->field_product_reference[LANGUAGE_NONE][0]['product_id'];
      $options[$p_nid] = $node->title;
    }
    $form['product_id'] = array(
      '#type' => 'select',
      '#title' => 'Select lesson',
      '#options' => $options,
      '#default_value' => '',
    );
  }
  //else {}

  /* // TODO видимо нужно селект как выше
  $form['product_id'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );
  */

  $form['teacher_uid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['lesson_date'] = array(
    /*
    '#type' => 'hidden',
    '#default_value' =>'',
    */
    '#type' => 'textfield',
    '#title' => 'Lesson date',
    '#attributes' => array(
      'placeholder' => t('Lesson date'),
    ),
    //'#theme_wrappers' => array(),
    '#default_value' =>  isset($user_profile->field_phone['und']) ? $user_profile->field_phone[LANGUAGE_NONE][0]['value'] :  '',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['skype'] = array(
    '#type' => 'textfield',
    '#title' => 'Skype login',
    '#attributes' => array(
      'placeholder' => t('Skype login'),
    ),
    //'#theme_wrappers' => array(),
    '#default_value' =>  isset($user_profile->field_skype[LANGUAGE_NONE]) ? $user_profile->field_skype[LANGUAGE_NONE][0]['value'] :  '',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['product_quantity'] = array(
    '#type' => 'hidden',
    '#default_value' =>'1',
  );
  $form['product_price'] = array(
    '#type' => 'hidden',
    //'#default_value' =>'1',
  );

  $form['is_paid'] = array(
    '#type' => 'hidden',
    '#default_value' =>'0',
  );

  /*
  $form['is_cart'] = array(
    '#type' => 'hidden',
    '#default_value' => current_path() == 'cart' ? '1' : '0',
  );
  */

  /*
  $form['terms_of_use'] = array(
    '#theme_wrappers' => array(),
    '#type' => 'checkbox',
    '#title' => 'Terms of use agree.',
    '#required' => TRUE,
    '#suffix' => '<a class="term_of_use" href="/terms-of-use">Learn more</a>',
  );
  */


  $form['paypal_button'] = array(
    '#markup' => '<div id="paypal-button-container"></div>'
  );

  /*

  <script>
  paypal.Buttons().render('#paypal-button-container');
    // This function displays Smart Payment Buttons on your web page.
  </script>
  */

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Book'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'education_common_quick_order_ajax_callback',
    ),
  );

  //honeypot_add_form_protection($form, $form_state, array('honeypot', 'time_restriction'));
  return $form;
}


function education_common_quick_order_submit(&$form, &$form_state) {
  global $user;

  $product_id = $form_state['values']['product_id'];

  if ($form_state['values']['product_quantity']) {
    if ($product_id) {
      $teacher_uid = $form_state['values']['teacher_uid'];
      $date = $form_state['values']['lesson_date'];

      $is_cart = FALSE;
      $is_paid = $form_state['values']['is_paid'];
      //$form_state['values']['is_cart']
      $order_id = education_common_create_quick_order($user, $product_id, $form_state['values']['product_quantity'], $date, $teacher_uid,
        $form_state['values']['user_phone'], $form_state['values']['name'], $form_state['values']['email'], $form_state['values']['skype'], $is_cart, $is_paid);

      $form_state['values']['order_id'] = $order_id;

      $order = commerce_order_load($order_id);
      //$order_mail_data = education_common_get_order_mail_data($order);
      //$order_mail_data_admin = education_common_get_order_mail_data_admin($order);

      $order_user = user_load($order->uid);
      // получим тип заказа

      $order_mail_data = education_common_get_order_mail_data($order);

      //13 BY
      $teacher_user = user_load($teacher_uid);
      $teacher_mail = $teacher_user->mail;

      rules_invoke_event('education_common_send_message_to_user', $form_state['values']['email'], $form_state['values']['name'],
        $form_state['values']['user_phone'], $form_state['values']['skype'], $order_id, $order_mail_data, $teacher_mail);

    }
  }
}

function education_common_quick_order_ajax_callback(&$form, &$form_state) {
  $current_path = '';
  $current_path_text = '';

  if (form_get_errors()) {
    $commands[] = ajax_command_html('#' . $form['#id'], render($form));
    $errors = form_get_errors();
    if (isset($errors['name'])) {

      if ($errors['name'] == 'user_mail_exists') {
        $commands[] = ajax_command_after('#fast_cart input[name="name"]', '<div class="field__error">This value is in use</div>');
      }
      else {
        $commands[] = ajax_command_after('#fast_cart input[name="name"]', '<div class="field__error">Field "Name" is required</div>');
      }
    }

    if (isset($errors['user_phone'])) {
      $commands[] = ajax_command_after('#fast_cart input[name="user_phone"]', '<div class="field__error">Field "Phone" is required</div>');
    }

    if (isset($errors['email'])) {

      $email_error_text = $errors['email'] == 'email_error' ? 'E-mail address is not corrent' : 'Field "E-mail" is required';

      if ($errors['email'] == 'user_mail_exists') {
        $email_error_text = 'This value is in use';
      }

      $commands[] = ajax_command_after('#fast_cart input[name="email"]', '<div class="field__error">' . $email_error_text . '</div>');
    }

    if (isset($errors['terms_of_use'])) {
      $commands[] = ajax_command_after('#fast_cart .term_of_use', '<div class="field__error terms">Must be your agreement</div>');
    }
  }

  else {
    if (isset($form_state['values']['is_cart'])) {
      $commands[] = array('command' => 'reloadPage');
    }

    if ($form_state['values']['current_path']) {
      $current_path_text = 'Return to page';
      $current_path = $form_state['values']['current_path'];

      if ( strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
        $current_path_text = 'Return to page';
      }
    }

    $message = "<p>";
    $path_to_return = l($current_path_text, $current_path);

    if (isset($form_state['values']['is_cr'])) {
    }

    else {
      $message .= '<div class="form__block"><div class="form__desc">Thanks for booking!<br />
    Details of the booking were send to email.
        <br />' . $path_to_return . '</div></div>';
    }

    $message .= "</p>";
    $commands[] = ajax_command_replace('#' . $form['#id'], $message);
    $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));
  }

  return array('#type' => 'ajax', '#commands' => $commands);

}

/**
 * Implements hook_form_FORM_ID_alter()
 * user register
 */
function education_common_form_user_register_form_alter(&$form, &$form_state, $form_id) {
  // if form for pupil registartion
  if (request_uri() == '/pupil-registration') {

    $form['field_is_a_teacher']['#access'] = FALSE;
    $form['field_teaching_format']['#access'] = FALSE;

    $form['account']['name']['#description'] = '';
    $form['account']['mail']['#description'] = '';

    $pupil_role_options = $form['field_select_pupil_role'][LANGUAGE_NONE]['#options'];
    unset($pupil_role_options['_none']);
    $form['field_select_pupil_role'][LANGUAGE_NONE]['#options'] = $pupil_role_options;

    $student_age_category_options = $form['field_student_age_category'][LANGUAGE_NONE]['#options'];
    unset($student_age_category_options['_none']);
    $form['field_student_age_category'][LANGUAGE_NONE]['#options'] = $student_age_category_options;

    $form['field_select_pupil_role']['#states'] = array(
      'visible' => array(
        ':input[name="field_student_age_category[und]"]' => array('value' => 'schoolboy'),
      ),
    );

    //field-student-age-category
    //$pupil_role_options = $form['field_select_pupil_role'][LANGUAGE_NONE]['#options'];
    $options_with_img = array();
    foreach ($student_age_category_options as $val => $student_age_category_option) {
      $img_var_fid = variable_get('pupil_registration_image_' . $val);
      $file = file_load($img_var_fid);

      $op_img = theme('image_style', array(
        'style_name' => 'teacher_list',
        'path' => $file->uri,
        //'alt' => $file->alt,
        //'title' => $file->title,
        'attributes' => array(),
      )) . '<br>' . $student_age_category_option;

      $options_with_img[$val] = $op_img;
    }
    $form['field_student_age_category'][LANGUAGE_NONE]['#options'] = $options_with_img;

  }
  else {
    $form['field_age_category']['#access'] = FALSE;
  }

  if (drupal_is_front_page()) {
    $form['account']['name']['#description'] = '';
    $form['account']['name']['#attributes']['placeholder'] = 'name';
    $form['account']['mail']['#description'] = '';
    $form['account']['mail']['#attributes']['placeholder'] = 'E-mail';
    $form['account']['name']['#title'] = '';
    $form['account']['mail']['#title'] = '';

    $form['account']['mail']['#theme_wrappers'] = array();
    $form['account']['name']['#theme_wrappers'] = array();
    $form['field_phone']['#theme_wrappers'] = array();
    $form['field_phone'][LANGUAGE_NONE][0]['value']['#theme_wrappers'] = array();
    //$form['field_phone'][LANGUAGE_NONE][0]['#title'] = '';
    $form['field_phone'][LANGUAGE_NONE][0]['value']['#title'] = '';
    $form['field_phone'][LANGUAGE_NONE][0]['value']['#attributes']['placeholder'] = 'Phone';
    //echo '<pre>'; print_r($form['field_phone']); echo '</pre>'; die();
    //$form['field_phone']['#title'] = '';
    $form['actions']['submit']['#value'] = 'Try fo free';

    $form['actions']['submit']['#buttontype'] = 'button';
    $form['#after_build'][] = 'education_common_force_triggering_element';
  }
}


/**
 * Implements hook_form_FORM_ID_alter()
 * user profile (student)
 */
function education_common_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
  // if form for pupil registartion
  if (user_has_role(STUDENT_ROLE) || user_has_role(TEACHER_ROLE)) {
    $form['field_balance']['#access'] = FALSE;
  }
  if (request_uri() == '/pupil/profile' || user_has_role(STUDENT_ROLE)) {
    $form['field_is_a_teacher']['#access'] = FALSE;
    $form['field_ready_to_get_news']['#access'] = FALSE;
    $form['field_terms_of_service']['#access'] = FALSE;
    $form['field_student_age_category']['#access'] = FALSE;
    $form['field_age_category']['#access'] = FALSE;
    $form['field_select_pupil_role']['#access'] = FALSE;
    $form['field_not_available_dates']['#access'] = FALSE;
    $form['field_languages_can_teach']['#access'] = FALSE;
    $form['field_hourly_rate_']['#access'] = FALSE;
    $form['field_resume_']['#access'] = FALSE;
    $form['field_grade_subject']['#access'] = FALSE;
    $form['field_documents']['#access'] = FALSE;
    $form['field_teaching_format']['#access'] = FALSE;

    $form['field_gender']['#access'] = FALSE;
    $form['field_university']['#access'] = FALSE;
    $form['field_speciality']['#access'] = FALSE;
    $form['field_graduation_year']['#access'] = FALSE;
    $form['field_academic_degree']['#access'] = FALSE;

    $form['mimemail']['#access'] = FALSE;

    //if (isset($_SERVER["HTTP_REFERER"]) && strstr( $_SERVER["HTTP_REFERER"], 'user/reset') ) {
    if (isset($_GET["pass-reset-token"]) ) {
      $form['field_first_name'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_teacher_last_name'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_phone'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_city'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_skype'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      //$form['account']['pass'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['account']['pass']['#required'] = TRUE;
      $form['field_student_promocode']['#access'] = FALSE;
      //field_student_promocode
    }
  }

  if (user_has_role(TEACHER_ROLE)) {

    $form['field_is_a_teacher']['#access'] = FALSE;
    $form['field_ready_to_get_news']['#access'] = FALSE;
    $form['field_terms_of_service']['#access'] = FALSE;
    $form['field_select_pupil_role']['#access'] = FALSE;
    $form['field_student_promocode']['#access'] = FALSE;
    $form['field_student_age_category']['#access'] = FALSE;
    $form['field_hourly_rate_']['#access'] = FALSE;
    $form['field_teaching_format']['#access'] = FALSE;

    if (isset($_GET["pass-reset-token"]) ) {
      $form['field_first_name'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_teacher_last_name'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_phone'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_city'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_skype'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['field_speciality'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      //$form['field_languages_can_teach'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      //$form['account']['pass'][LANGUAGE_NONE][0]['value']['#required'] = TRUE;
      $form['account']['pass']['#required'] = TRUE;

      $form['field_gender']['#access'] = FALSE;
      $form['field_academic_degree']['#access'] = FALSE;
      $form['field_languages_can_teach']['#access'] = FALSE;


    }
  }
}




/**
 * @file
 * Allows users to login with their username or email address in the same input box.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Alters the main user login form.
 */
function education_common_form_user_login_alter(&$form, &$form_state, $form_id) {
  //$form['name']['#title'] = t('Username or email address');
  $form['name']['#title'] = '';
  $form['name']['#attributes']['placeholder'] = 'Username or email address';
  $form['pass']['#title'] = '';
  $form['pass']['#attributes']['placeholder'] = 'Enter password';
  //$form['name']['#description'] = t('Enter your username or email address.');
  $form['pass']['#description'] = '';
  $form['name']['#element_validate'][] = 'education_common_user_login_validate';
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Alters the user login block form.
 */
function education_common_form_user_login_block_alter(&$form, &$form_state, $form_id) {
  $form['name']['#title'] = t('Username or email');
  $form['name']['#element_validate'][] = 'education_common_user_login_validate';
}

/**
 * Form element validation handler for the user login form.
 *
 * Allows users to authenticate by username OR email.
 */
function education_common_user_login_validate($form, &$form_state) {
  $name_input = $form_state['values']['name'];

  // Try loading by email.
  if ($user = user_load_by_mail($name_input)) {
    // Set the username for further validation.
    $form_state['values']['name'] = $user->name;
    return TRUE;
  }

  // Try loading by username.
  if ($user = user_load_by_name($name_input)) {
    return TRUE;
  }

  return FALSE;
}

function lesson_pay_form($form, &$form_state) {
  global $user;

  $form['lesson_pay'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['order_price'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

  $form['paypal_button'] = array(
    '#markup' => '<div id="paypal-button-container"></div>'
  );

  // todo balance

  if ($user->uid) {
    $current_user = user_load($user->uid);
    $existing_summ = isset($current_user->field_balance[LANGUAGE_NONE]) ? $current_user->field_balance[LANGUAGE_NONE][0]['value'] : 0;
    if ($existing_summ) {
      $form['existing_summ'] = array(
        '#markup' => '<div class="user_balance">Account Balance: ' . $existing_summ . ' C$</div>',
      );

      $form['pay_from_balance'] = array(
        '#type' => 'submit',
        '#value' => t('Pay from Balance'),
        '#attributes' => array(
          'class' => array(
            'btn btn_red form__submit pay_from_balance_button',
          ),
        ),
        '#prefix' => '<div class="form__block">',
        '#suffix' => '</div>',
        '#ajax' => array(
          'callback' => 'lesson_pay_from_balance_form_ajax_callback',
        ),
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Pay'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit pay_lesson_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'lesson_pay_form_ajax_callback',
    ),
  );
  return $form;
}

function lesson_pay_from_balance_form_ajax_callback($form, &$form_state) {
  global $user;
  if ($form_state['values']['current_path']) {
    $current_path_text = 'Return to page';
    $current_path = $form_state['values']['current_path'];

    if (strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
      $current_path_text = 'Return to page';
    }
  }

  $message = "<p>";
  $path_to_return = l($current_path_text, $current_path);

  $message_text = 'You have paid this lesson';
  $popup__title = 'Thank you';
  // todo take from user balance
  if ($form_state['values']['order_price']) {
    $order_price = substr($form_state['values']['order_price'], 1);
    $current_user = user_load($user->uid);
    $existing_summ = isset($current_user->field_balance[LANGUAGE_NONE]) ? $current_user->field_balance[LANGUAGE_NONE][0]['value'] : 0;
    if ($existing_summ) {
      $summ_to_left = $existing_summ - $order_price;
      if ($summ_to_left < 0) {
        $popup__title = 'Not enough money';
        $message_text = 'Not enough money on balance';
      }
      else {
        $current_user->field_balance[LANGUAGE_NONE][0]['value'] = $summ_to_left;
        user_save($current_user);
      }
    }
  }

  $message .= '<div class="form__block"><div class="form__desc">' . $message_text . '<br />
      <br />' . $path_to_return . '</div></div>';

  $message .= "</p>";
  $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  $commands[] = ajax_command_html('#lesson_pay .popup__title', $popup__title);
  $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));

  return array('#type' => 'ajax', '#commands' => $commands);
}

function lesson_pay_form_submit($form, &$form_state) {
  global $user;
  $lesson_pay_id = $form_state['values']['lesson_pay'];
  //$order_price = $form_state['values']['order_price'];

  //echo '<pre>'; print_r($form_state['values']); echo '</pre>'; die();

  $change_order_status = TRUE;
  if ($form_state['values']['op'] == 'Pay from Balance') {
    // todo check balance
    $order_price = substr($form_state['values']['order_price'], 1);
    $current_user = user_load($user->uid);
    $existing_summ = isset($current_user->field_balance[LANGUAGE_NONE]) ? $current_user->field_balance[LANGUAGE_NONE][0]['value'] : 0;
    if ($existing_summ) {
      $summ_to_left = $existing_summ - $order_price;
      if ($summ_to_left < 0) {
        $change_order_status = FALSE;
      }
    }
  }

  if ($change_order_status) {
    $order = commerce_order_load($lesson_pay_id);
    $order->status = 'paid';

    // get order product (lesson)
    $product_id = 0;
    foreach (entity_metadata_wrapper('commerce_order', $order)->commerce_line_items as $delta => $line_item_wrapper) {
      if (in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
        $product_id = $line_item_wrapper->commerce_product->raw();
      }
    }

    // get lesson product display
    if ($product_id) {
      $product_display = get_product_display_by_product_id($product_id, 'lesson', 'field_product_reference');
      // TODO
      // create new classroom
      $node_classroom = new stdClass();
      $node_classroom->type = 'classroom';
      $node_classroom->language = LANGUAGE_NONE;
      node_object_prepare($node_classroom);

      $node_classroom->title = 'Classroom ' . $product_display->title;
      $node_classroom->status = 1;
      $node_classroom->promote = 0;
      $node_classroom->sticky = 0;

      $node_classroom->uid = $order->field_lesson_teacher_uid[LANGUAGE_NONE][0]['uid'];
      $node_classroom->field_order_id[LANGUAGE_NONE][0]['value'] = $order->order_id;
      node_save($node_classroom);

      // set field_classroom to lesson product display
      $product_display->field_classroom[LANGUAGE_NONE][0]['nid'] = $node_classroom->nid;
      node_save($product_display);

      // TODO COMMENT vox creating
      /*
      //TODO создать в vox два юзера, предварительно проверив поля vox
      // ТИЧЕР $order->field_lesson_teacher_uid[LANGUAGE_NONE][0]['uid']
       $teacher = user_load($order->field_lesson_teacher_uid[LANGUAGE_NONE][0]['uid']);
       $teacher_name = $teacher->name;
       $student_name =  $user->name;

      vox_create_user($teacher);
      vox_create_user($user);
      */

      //->field_vox_username[LANGUAGE_NONE]
      /*
      $data = array(
        'account_id' => '3616974',
        'api_key' => '4e3b7b77-95db-4072-9860-6c3ab747f18a',
        'user_name' => '',
        'user_display_name' => '',
        'user_password' => '',
        'application_id' => '10229034',
      );

      $options = array(
        'method' => 'GET',
        'data' => drupal_http_build_query($data),
        'timeout' => 15,
      );

      $result = drupal_http_request('https://api.voximplant.com/platform_api/AddUser/', $options);
      */

      // drupal_http_build_query
      // https://api.voximplant.com/platform_api/AddUser/?account_id=3616974&api_key=4e3b7b77-95db-4072-9860-6c3ab747f18a&user_name=iden1&user_display_name=iden1&user_password=1234567&application_id=10229034
    }
    commerce_order_save($order);
  }
}

function vox_create_user($user) {
  $user_account = user_load($user->uid);
  if (isset($user_account->field_vox_username[LANGUAGE_NONE]) && !empty($user_account->field_vox_username[LANGUAGE_NONE][0])) {
    //return;
  }
  else {

    $edit = array(
      'field_vox_username' => array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => 'vox_'. clean_vox_name($user->name),
          ),
        ),
      ),
      'field_vox_password' => array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => 'vox_'. clean_vox_name($user->name),
          ),
        ),
      ),
    );

    $data = array(
      'account_id' => '3616974',
      'api_key' => '4e3b7b77-95db-4072-9860-6c3ab747f18a',
      'user_name' => 'vox_'. clean_vox_name($user->name),
      'user_display_name' => 'vox_'. clean_vox_name($user->name),
      'user_password' => 'vox_'. clean_vox_name($user->name),
      'application_id' => '10229034',
    );

    $result = file_get_contents('https://api.voximplant.com/platform_api/AddUser/?' . drupal_http_build_query($data));
    user_save($user, $edit);
  }
}

function clean_vox_name($s) {
  $s = preg_replace( "/[^a-zA-Z0-9]/", '', $s );
  return $s;
}


function get_product_display_by_product_id($product_id, $bundle = 'product_display', $field_name = 'field_product') {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->propertyCondition('type', $bundle);
  $query->fieldCondition($field_name, 'product_id', $product_id);
  $query->range(0, 1);
  $result = $query->execute();
  if ($result) {
    $product_display_nid = key($result['node']);
    return node_load($product_display_nid);
  }
}

function lesson_pay_form_ajax_callback(&$form, &$form_state) {
  if ($form_state['values']['current_path']) {
    $current_path_text = 'Return to page';
    $current_path = $form_state['values']['current_path'];

    if ( strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
      $current_path_text = 'Return to page';
    }
  }

  $message = "<p>";
  $path_to_return = l($current_path_text, $current_path);

  $message .= '<div class="form__block"><div class="form__desc">
  You have paid this lesson.<br />
      <br />' . $path_to_return . '</div></div>';

  $message .= "</p>";
  $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  $commands[] = ajax_command_html('#lesson_pay .popup__title', 'Thank you');
  $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));

  return array('#type' => 'ajax', '#commands' => $commands);
}

function balance_pay_form($form, &$form_state) {
  global $user;

  $form['summ'] = array(
    '#title' => 'Enter summ to recharge you balance',
    '#type' => 'textfield',
    '#default_value' =>'',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['paypal_button'] = array(
    '#markup' => '<div id="paypal-button-container"></div>'
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Pay'),
    '#attributes' => array(
      'class' => array(
        'btn btn_red form__submit balance_recharge_button',
      ),
    ),
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'balance_pay_form_ajax_callback',
    ),
  );
  return $form;
}

function balance_pay_form_submit($form, &$form_state) {
  global $user;
  $summ = $form_state['values']['summ'];

  $current_user = user_load($user->uid);
  $existing_summ = isset($current_user->field_balance[LANGUAGE_NONE]) ? $current_user->field_balance[LANGUAGE_NONE][0]['value'] : 0;

  $edit = array(
    'field_balance' => array(
      LANGUAGE_NONE => array(
        0 => array(
          'value' => $summ + $existing_summ,
        ),
      ),
    ),
  );
  user_save($current_user, $edit);
}

function balance_pay_form_ajax_callback(&$form, &$form_state) {
  if ($form_state['values']['current_path']) {
    $current_path_text = 'Return to page';
    $current_path = $form_state['values']['current_path'];

    if ( strstr($current_path, 'products') || strstr($current_path, 'cart') ) {
      $current_path_text = 'Return to page';
    }
  }

  $message = "<p>";
  $path_to_return = l($current_path_text, $current_path);

  $message .= '<div class="form__block"><div class="form__desc">
  You have successfully recharged your balance.<br />
      <br />' . $path_to_return . '</div></div>';

  $message .= "</p>";
  $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  $commands[] = ajax_command_invoke('.popup__close', 'addClass', array('close_reload'));

  return array('#type' => 'ajax', '#commands' => $commands);
}


