<?php

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

  if (isset($lesson_node->field_lesson_date['und'])) {
    foreach($lesson_node->field_lesson_date['und'] as $key => $lesson_date_item ) {
      if ($lesson_date_item['value'] == $close_lesson_date) {
        unset($lesson_node->field_lesson_date['und'][$key]);
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
    '#markup' => '<div class="form__desc">For quick booking fill the form.<br /> Our manager will get in touch with you.<br /></div>',
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
    '#default_value' =>  isset($user_profile->field_phone['und']) ? $user_profile->field_phone['und'][0]['value'] :  '',
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

  $form['product_id'] = array(
    '#type' => 'hidden',
    '#default_value' =>'',
  );

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
    '#default_value' =>  isset($user_profile->field_phone['und']) ? $user_profile->field_phone['und'][0]['value'] :  '',
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
    '#default_value' =>  isset($user_profile->field_skype['und']) ? $user_profile->field_skype['und'][0]['value'] :  '',
    '#required' => TRUE,
    '#prefix' => '<div class="form__block">',
    '#suffix' => '</div>',
  );

  $form['product_quantity'] = array(
    '#type' => 'hidden',
    '#default_value' =>'1',
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

      $order_id = education_common_create_quick_order($user, $product_id, $form_state['values']['product_quantity'], $date, $teacher_uid,
        $form_state['values']['user_phone'], $form_state['values']['name'], $form_state['values']['email'], $form_state['values']['skype'], $form_state['values']['is_cart']);

      $form_state['values']['order_id'] = $order_id;

      $order = commerce_order_load($order_id);
      //$order_mail_data = education_common_get_order_mail_data($order);
      //$order_mail_data_admin = education_common_get_order_mail_data_admin($order);

      $order_user = user_load($order->uid);
      // получим тип заказа
      if ($order_user && in_array(2, array_keys($order_user->roles))) {
        $order_type_title = 'заказ';
      }

      if ($order_user && in_array(5, array_keys($order_user->roles))) {
        $order_type_title = 'оптовый заказ';
      }

      $order_mail_data = education_common_get_order_mail_data($order);

      /*
      rules_invoke_event('education_common_send_message_to_user', $form_state['values']['email'], $form_state['values']['name'],
        $form_state['values']['user_phone'], $order_id, $order_mail_data, $order_mail_data_admin, $order_type_title);
      */

      rules_invoke_event('education_common_send_message_to_user', $form_state['values']['email'], $form_state['values']['name'],
        $form_state['values']['user_phone'], $form_state['values']['skype'], $order_id, $order_mail_data);

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
    if ($form_state['values']['is_cart']) {
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
    Details of the booking were send to email.<br />
        Our manager will get in touch with you soon<br /><br />' . $path_to_return . '</div></div>';
    }

    $message .= "</p>";
    $commands[] = ajax_command_replace('#' . $form['#id'], $message);
  }

  return array('#type' => 'ajax', '#commands' => $commands);

}

