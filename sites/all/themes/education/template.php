<?php


/**
 * Override of theme_button().
 *
 * Render the button element as a button and the submit element as an input element.
 */
function education_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';

  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  if (isset($element['#buttontype']) && $element['#buttontype'] == 'button') {
    $value = $element['#value'];
    unset($element['#attributes']['value']);
    return '<button' . drupal_attributes($element['#attributes']) . '>' . $value . '</button>';
  }
  else {
    return '<input' . drupal_attributes($element['#attributes']) . ' />';
  }
}

function education_form_element($variables) {
  $element = $variables['element'];
  // Disable radio button N/A
  if ($element['#type'] == 'radio' /*&& $element['#return_value'] === '_none'*/) {
    //$variables['element']['#attributes']['disabled'] = TRUE;

    $element =& $variables['element'];

    // This function is invoked as theme wrapper, but the rendered form element
    // may not necessarily have been processed by form_builder().
    $element += array(
      '#title_display' => 'before',
    );

    // Add element #id for #type 'item'.
    if (isset($element['#markup']) && !empty($element['#id'])) {
      $attributes['id'] = $element['#id'];
    }

    // Add element's #type and #name as class to aid with JS/CSS selectors.
    $attributes['class'] = array(
      'form-item',
    );
    if (!empty($element['#type'])) {
      $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
    }
    if (!empty($element['#name'])) {
      $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(
          ' ' => '-',
          '_' => '-',
          '[' => '-',
          ']' => '',
        ));
    }

    // Add a class for disabled elements to facilitate cross-browser styling.
    if (!empty($element['#attributes']['disabled'])) {
      $attributes['class'][] = 'form-disabled';
    }
    $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

    // If #title is not set, we don't display any label or required marker.
    if (!isset($element['#title'])) {
      $element['#title_display'] = 'none';
    }
    $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
    $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';
    switch ($element['#title_display']) {
      case 'before':
      case 'invisible':
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        $output .= ' ' . theme('form_element_label', $variables);

        break;
      case 'after':
        if (strstr($element['#id'], 'edit-field-student-age-category-und')) {
          $output .= ' ' . theme('form_element_label', $variables) . "\n";
          $output .= ' ' . $prefix . $element['#children'] . $suffix;
        }
        else {
          $output .= ' ' . $prefix . $element['#children'] . $suffix;
          $output .= ' ' . theme('form_element_label', $variables) . "\n";
        }

        break;
      case 'none':
      case 'attribute':

        // Output no label and no required marker, only the children.
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
    if (!empty($element['#description'])) {
      $output .= '<div class="description">' . $element['#description'] . "</div>\n";
    }
    $output .= "</div>\n";
    return $output;


  }
  return theme_form_element($variables);
}

/**
 * use  hook_theme_registry_alter().
 */
function education_theme_registry_alter(&$theme_registry) {
  $theme_path = path_to_theme();

  // Checkboxes.
  /*
  if (isset($theme_registry['checkbox'])) {
    $theme_registry['checkbox']['type'] = 'theme';
    $theme_registry['checkbox']['theme path'] = $theme_path;
    $theme_registry['checkbox']['template'] = $theme_path. '/templates/fields/field--type-checkbox';
    unset($theme_registry['checkbox']['function']);
  }
  */

  // Radios.
  if (isset($theme_registry['radio'])) {
    $theme_registry['radio']['type'] = 'theme';
    $theme_registry['radio']['theme path'] = $theme_path;
    $theme_registry['radio']['template'] = $theme_path . '/templates/fields/field--type-radio';
    unset($theme_registry['radio']['function']);
  }
}

function education_preprocess_html(&$variables) {
  // Add variables for path to theme.
  $variables['base_path'] = base_path();
  $variables['path_to_resbartik'] = drupal_get_path('theme', 'education');

  // Add local.css stylesheet
  if (file_exists(drupal_get_path('theme', 'education') . '/css/local.css')) {
    drupal_add_css(drupal_get_path('theme', 'education') . '/css/local.css',
      array('group' => CSS_THEME, 'every_page' => TRUE));
  }

  // Add body classes if certain regions have content.
  if (!empty($variables['page']['featured'])) {
    $variables['classes_array'][] = 'featured';
  }

  if (!empty($variables['page']['triptych_first'])
    || !empty($variables['page']['triptych_middle'])
    || !empty($variables['page']['triptych_last'])
  ) {
    $variables['classes_array'][] = 'triptych';
  }

  if (!empty($variables['page']['footer_firstcolumn'])
    || !empty($variables['page']['footer_secondcolumn'])
    || !empty($variables['page']['footer_thirdcolumn'])
    || !empty($variables['page']['footer_fourthcolumn'])
  ) {
    $variables['classes_array'][] = 'footer-columns';
  }
}

/**
 * Override or insert variables into the page template for HTML output.
 */
function education_process_html(&$variables)
{
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
 * Override or insert variables into the page template.
 */
function education_process_page(&$variables)
{
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name'] = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
  // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($variables['title_suffix']['add_or_remove_shortcut']) && $variables['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $variables['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $variables['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $variables['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function education_preprocess_maintenance_page(&$variables)
{
  // By default, site_name is set to Drupal if no db connection is available
  // or during site installation. Setting site_name to an empty string makes
  // the site and update pages look cleaner.
  // @see template_preprocess_maintenance_page
  if (!$variables['db_is_active']) {
    $variables['site_name'] = '';
  }
  drupal_add_css(drupal_get_path('theme', 'education') . '/css/maintenance-page.css');
}

/**
 * Override or insert variables into the maintenance page template.
 */
function education_process_maintenance_page(&$variables)
{
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name'] = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
}

/**
 * Override or insert variables into the page template.
 */
function education_preprocess_page(&$variables) {

  /*
  $node = node_load(42);
  //var_dump($node->field_desk[LANGUAGE_NONE][0]['data']); die();
  $image_data = $node->field_desk[LANGUAGE_NONE][0]['data'];

  $values = unserialize($image_data);
  $drawing_edit_path = $values['json'];
  echo $drawing_edit_path; die();
  */


  if (drupal_is_front_page()) {
    drupal_set_title('');
    drupal_add_js(drupal_get_path('theme', 'education') . '/js/owl.carousel.min.js');
    drupal_add_js(drupal_get_path('theme', 'education') . '/js/front-slider.js');
    drupal_add_css(drupal_get_path('theme', 'education') . '/css/owl.carousel.css');
  }
}

/**
 * Override or insert variables into the node template.
 */
function education_preprocess_node(&$variables)
{
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
}

/**
 * Override or insert variables into the block template.
 */
function education_preprocess_block(&$variables)
{
  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
}

/**
 * Implements theme_menu_tree().
 */
function education_menu_tree($variables)
{
  return '<ul class="menu clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_field__field_type().
 */
function education_field__taxonomy_term_reference($variables)
{
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 class="field-label">' . $variables['label'] . ': </h3>';
  }

  // Render the items.
  $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}
