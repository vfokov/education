<?php
/**
 * Created by PhpStorm.
 * User: kostya
 * Date: 26.05.16
 * Time: 16:17
 */

function education_zoom_variable_group_info() {
  $groups['education_zoom'] = array(
    'title' => 'Zoom Data',
    'description' => 'Zoom Data',
    'access' => 'administer nodes',
  );


  return $groups;
}

/**
 * Implements hook_variable_info()
 */
function education_zoom_variable_info($options) {

  $variables['education_zoom_api_key'] = array(
    'type' => 'text',
    'title' => 'Zoom API Key.',
    'default' => 'e3gMd40BQv-zGbBgU9uszQ',
    'required' => TRUE,
    'module' => 'education_zoom',
    'group' => 'education_zoom',
    'localize' => TRUE,
  );

  $variables['education_zoom_api_secret'] = array(
    'type' => 'text',
    'title' => 'Zoom API secret.',
    'default' => 'GVwuCgqu4AbAbC7vzpwkNPuQHDI3J4y1rBV7',
    'required' => TRUE,
    'module' => 'education_zoom',
    'group' => 'education_zoom',
    'localize' => TRUE,
  );

  $variables['education_zoom_url'] = array(
    'type' => 'text',
    'title' => 'Zoom API Url.',
    'default' => 'https://api.zoom.us/v2/',
    'required' => TRUE,
    'module' => 'education_zoom',
    'group' => 'education_zoom',
    'localize' => TRUE,
  );

  return $variables;
}
