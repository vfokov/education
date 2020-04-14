<?php
/**
 * Created by PhpStorm.
 * User: kostya
 * Date: 26.05.16
 * Time: 16:17
 */

function education_common_variable_group_info() {
  $groups['education_info'] = array(
    'title' => 'Info Education',
    'description' => 'Education info',
    'access' => 'administer nodes',
  );


  return $groups;
}

/**
 * Implements hook_variable_info()
 */
function education_common_variable_info($options) {
  /*
  $variables['slogan_one_line'] = array(
    'type' => 'text',
    'title' => 'Слоган сайта (в одну строку).',
    'default' => '',
    'required' => TRUE,
    'module' => 'd2b4_base',
    'group' => 'education_info',
    'localize' => TRUE,
  );
  */

  $variables['pupil_registration_image_adult'] = array(
    'type' => 'image_managed',
    'title' => 'Image form pupil regiatration adult',
    'default' => variable_get('pupil_registration_image_adult'),
    'module' => 'education_common',
    'group' => 'education_info',
    'localize' => TRUE,
  );

  $variables['pupil_registration_image_schoolboy'] = array(
    'type' => 'image_managed',
    'title' => 'Image form pupil regiatration schoolboy',
    'default' => variable_get('pupil_registration_image_schoolboy'),
    'module' => 'education_common',
    'group' => 'education_info',
    'localize' => TRUE,
  );

  $variables['pupil_registration_image_student'] = array(
    'type' => 'image_managed',
    'title' => 'Image form pupil regiatration student',
    'default' => variable_get('pupil_registration_image_student'),
    'module' => 'education_common',
    'group' => 'education_info',
    'localize' => TRUE,
  );

  return $variables;
}
