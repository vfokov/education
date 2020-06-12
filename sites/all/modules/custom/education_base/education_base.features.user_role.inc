<?php

/**
 * @file
 * education_base.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function education_base_user_default_roles() {
  $roles = array();

  // Exported role: Student.
  $roles['Student'] = array(
    'name' => 'Student',
    'weight' => 4,
  );

  // Exported role: Teacher.
  $roles['Teacher'] = array(
    'name' => 'Teacher',
    'weight' => 3,
  );

  return $roles;
}
