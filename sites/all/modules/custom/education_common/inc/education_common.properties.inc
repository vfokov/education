<?php

/**
 * Allow modules to alter metadata about entity properties.
 *
 * @see hook_entity_property_info()
 */
function education_common_entity_property_info_alter(&$info) {
  $info['user']['properties']['teacher_lessons'] = array(
    'label' => 'Teacher lessons',
    'type' => 'list',
    'description' => 'Teacher lesson',
    'getter callback' => 'education_common_teacher_lessons',
    'entity views field' => TRUE,
  );

  $info['user']['properties']['teacher_lessons_dates'] = array(
    'label' => 'Teacher lessons dates',
    'type' => 'list<date>',
    'description' => 'Teacher lesson date',
    'getter callback' => 'education_common_teacher_lessons_dates',
    'entity views field' => TRUE,
  );
}

/**
 * Callback for property: is_wholesale
 * @param $account
 * @return bool
 */
function education_common_teacher_lessons($account) {
  $return = array();

  $field_query = new EntityFieldQuery();
  $field_query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'lesson')
    ->propertyCondition('status', 1)
    ->propertyCondition('uid', $account->uid);
  //$field_query->fieldCondition('commerce_customer_billing', 'profile_id', $variables['element']['#object']->profile_id);
  $result = $field_query->execute();
  $r = 1;
  if(!empty($result['node']) && is_array($result['node'])){
    foreach ($result['node'] as $res) {
      $return[] = $res->nid;
    }
  }
  return $return;
}


/**
 * Callback for property: is_wholesale
 *
 * @param $account
 * @return bool
 */
function education_common_teacher_lessons_dates($account) {
  $return = array();

  $field_query = new EntityFieldQuery();
  $field_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'lesson')
    ->propertyCondition('status', 1)
    ->propertyCondition('uid', $account->uid);
  //$field_query->fieldCondition('commerce_customer_billing', 'profile_id', $variables['element']['#object']->profile_id);
  $result = $field_query->execute();
  $r = 1;
  if(!empty($result['node']) && is_array($result['node'])){
    foreach ($result['node'] as $res) {
      //$return[] = $res->nid;
      $lesson_node = node_load($res->nid);

      $lesson_dates = $lesson_node->field_lesson_date[LANGUAGE_NONE];
      foreach ($lesson_dates as $lesson_date) {
        $return[] = strtotime($lesson_date['value']);
        //$return[] = $lesson_date['value'];
      }

      $ld = 1;
    }
  }
  return $return;
}
