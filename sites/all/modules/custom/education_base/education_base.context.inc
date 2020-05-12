<?php

/**
 * @file
 * education_base.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function education_base_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'user_tabs';
  $context->description = '';
  $context->tag = 'User';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~user/*/orders' => '~user/*/orders',
        'user' => 'user',
      ),
    ),
    'user' => array(
      'values' => array(
        'Teacher' => 'Teacher',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'quicktabs-teacher_tabs' => array(
          'module' => 'quicktabs',
          'delta' => 'teacher_tabs',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('User');
  $export['user_tabs'] = $context;

  return $export;
}
