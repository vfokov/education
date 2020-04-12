<?php

/**
 * @file
 * education_base.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function education_base_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create lesson content'.
  $permissions['create lesson content'] = array(
    'name' => 'create lesson content',
    'roles' => array(
      'Teacher' => 'Teacher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own lesson content'.
  $permissions['edit own lesson content'] = array(
    'name' => 'edit own lesson content',
    'roles' => array(
      'Teacher' => 'Teacher',
    ),
    'module' => 'node',
  );

  return $permissions;
}
