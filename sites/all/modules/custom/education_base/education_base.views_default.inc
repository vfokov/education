<?php

/**
 * @file
 * education_base.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function education_base_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'lesson_calendar';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Lesson calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Lesson calendar';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['calendar_colors_type'] = array(
    'article' => '#ffffff',
    'page' => '#ffffff',
    'lesson' => '#ffffff',
  );
  /* Relationship: Content: Referenced products */
  $handler->display->display_options['relationships']['field_product_reference_product_id']['id'] = 'field_product_reference_product_id';
  $handler->display->display_options['relationships']['field_product_reference_product_id']['table'] = 'field_data_field_product_reference';
  $handler->display->display_options['relationships']['field_product_reference_product_id']['field'] = 'field_product_reference_product_id';
  /* Field: Content: Author uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Content: Lesson date */
  $handler->display->display_options['fields']['field_lesson_date']['id'] = 'field_lesson_date';
  $handler->display->display_options['fields']['field_lesson_date']['table'] = 'field_data_field_lesson_date';
  $handler->display->display_options['fields']['field_lesson_date']['field'] = 'field_lesson_date';
  $handler->display->display_options['fields']['field_lesson_date']['label'] = '';
  $handler->display->display_options['fields']['field_lesson_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_date']['type'] = 'date_plain';
  $handler->display->display_options['fields']['field_lesson_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => 'd.m.Y H:i',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  $handler->display->display_options['fields']['field_lesson_date']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_lesson_date']['delta_offset'] = '0';
  /* Field: Commerce Product: Product ID */
  $handler->display->display_options['fields']['product_id']['id'] = 'product_id';
  $handler->display->display_options['fields']['product_id']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['product_id']['field'] = 'product_id';
  $handler->display->display_options['fields']['product_id']['relationship'] = 'field_product_reference_product_id';
  $handler->display->display_options['fields']['product_id']['label'] = '';
  $handler->display->display_options['fields']['product_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['product_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['product_id']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['product_id']['link_to_product'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="[product_id]" data-date="[field_lesson_date]" data-teacher-uid="[uid]">Book a lesson</a> ';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Lesson date (field_lesson_date) */
  $handler->display->display_options['arguments']['field_lesson_date_value']['id'] = 'field_lesson_date_value';
  $handler->display->display_options['arguments']['field_lesson_date_value']['table'] = 'field_data_field_lesson_date';
  $handler->display->display_options['arguments']['field_lesson_date_value']['field'] = 'field_lesson_date_value';
  $handler->display->display_options['arguments']['field_lesson_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_lesson_date_value']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['field_lesson_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_lesson_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_lesson_date_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_lesson_date_value']['granularity_reset'] = 0;
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'lesson' => 'lesson',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'lesson-calendar';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['lesson_calendar'] = $view;

  $view = new view();
  $view->name = 'teachers_index';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_teachers';
  $view->human_name = 'Teachers index';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Teachers';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Indexed User: Teachecr photo */
  $handler->display->display_options['fields']['field_teachecr_pic']['id'] = 'field_teachecr_pic';
  $handler->display->display_options['fields']['field_teachecr_pic']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['field_teachecr_pic']['field'] = 'field_teachecr_pic';
  $handler->display->display_options['fields']['field_teachecr_pic']['label'] = '';
  $handler->display->display_options['fields']['field_teachecr_pic']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_teachecr_pic']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_teachecr_pic']['settings'] = array(
    'image_style' => 'teacher_list',
    'image_link' => 'content',
  );
  /* Field: Indexed User: User ID */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['link_to_entity'] = 0;
  /* Field: Indexed User: Teacher Last Name */
  $handler->display->display_options['fields']['field_teacher_last_name']['id'] = 'field_teacher_last_name';
  $handler->display->display_options['fields']['field_teacher_last_name']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['field_teacher_last_name']['field'] = 'field_teacher_last_name';
  $handler->display->display_options['fields']['field_teacher_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_teacher_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_teacher_last_name']['element_label_colon'] = FALSE;
  /* Field: Indexed User: First Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['alter']['text'] = '[field_first_name] [field_teacher_last_name]';
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: Indexed User: Grade and subject */
  $handler->display->display_options['fields']['field_grade_subject']['id'] = 'field_grade_subject';
  $handler->display->display_options['fields']['field_grade_subject']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['field_grade_subject']['field'] = 'field_grade_subject';
  $handler->display->display_options['fields']['field_grade_subject']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_grade_subject']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_grade_subject']['bypass_access'] = 0;
  /* Field: Indexed User: Hourly Rate  */
  $handler->display->display_options['fields']['field_hourly_rate_']['id'] = 'field_hourly_rate_';
  $handler->display->display_options['fields']['field_hourly_rate_']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['field_hourly_rate_']['field'] = 'field_hourly_rate_';
  $handler->display->display_options['fields']['field_hourly_rate_']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Indexed User: Languages can teach */
  $handler->display->display_options['fields']['field_languages_can_teach']['id'] = 'field_languages_can_teach';
  $handler->display->display_options['fields']['field_languages_can_teach']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['fields']['field_languages_can_teach']['field'] = 'field_languages_can_teach';
  $handler->display->display_options['fields']['field_languages_can_teach']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_languages_can_teach']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_languages_can_teach']['bypass_access'] = 0;
  /* Filter criterion: Indexed User: Grade and subject */
  $handler->display->display_options['filters']['field_grade_subject']['id'] = 'field_grade_subject';
  $handler->display->display_options['filters']['field_grade_subject']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['filters']['field_grade_subject']['field'] = 'field_grade_subject';
  $handler->display->display_options['filters']['field_grade_subject']['value'] = array();
  $handler->display->display_options['filters']['field_grade_subject']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grade_subject']['expose']['operator_id'] = 'field_grade_subject_op';
  $handler->display->display_options['filters']['field_grade_subject']['expose']['label'] = 'Grade and subject';
  $handler->display->display_options['filters']['field_grade_subject']['expose']['operator'] = 'field_grade_subject_op';
  $handler->display->display_options['filters']['field_grade_subject']['expose']['identifier'] = 'field_grade_subject';
  $handler->display->display_options['filters']['field_grade_subject']['expose']['remember_roles'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['field_grade_subject']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed User: Languages can teach */
  $handler->display->display_options['filters']['field_languages_can_teach']['id'] = 'field_languages_can_teach';
  $handler->display->display_options['filters']['field_languages_can_teach']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['filters']['field_languages_can_teach']['field'] = 'field_languages_can_teach';
  $handler->display->display_options['filters']['field_languages_can_teach']['value'] = array();
  $handler->display->display_options['filters']['field_languages_can_teach']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_languages_can_teach']['expose']['operator_id'] = 'field_languages_can_teach_op';
  $handler->display->display_options['filters']['field_languages_can_teach']['expose']['label'] = 'Languages can teach';
  $handler->display->display_options['filters']['field_languages_can_teach']['expose']['operator'] = 'field_languages_can_teach_op';
  $handler->display->display_options['filters']['field_languages_can_teach']['expose']['identifier'] = 'field_languages_can_teach';
  $handler->display->display_options['filters']['field_languages_can_teach']['expose']['remember_roles'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['field_languages_can_teach']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed User: Age category */
  $handler->display->display_options['filters']['field_age_category']['id'] = 'field_age_category';
  $handler->display->display_options['filters']['field_age_category']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['filters']['field_age_category']['field'] = 'field_age_category';
  $handler->display->display_options['filters']['field_age_category']['value'] = array();
  $handler->display->display_options['filters']['field_age_category']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_age_category']['expose']['operator_id'] = 'field_age_category_op';
  $handler->display->display_options['filters']['field_age_category']['expose']['label'] = 'Age category';
  $handler->display->display_options['filters']['field_age_category']['expose']['operator'] = 'field_age_category_op';
  $handler->display->display_options['filters']['field_age_category']['expose']['identifier'] = 'field_age_category';
  $handler->display->display_options['filters']['field_age_category']['expose']['remember_roles'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['field_age_category']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed User: Teacher lessons dates */
  $handler->display->display_options['filters']['teacher_lessons_dates']['id'] = 'teacher_lessons_dates';
  $handler->display->display_options['filters']['teacher_lessons_dates']['table'] = 'search_api_index_teachers';
  $handler->display->display_options['filters']['teacher_lessons_dates']['field'] = 'teacher_lessons_dates';
  $handler->display->display_options['filters']['teacher_lessons_dates']['exposed'] = TRUE;
  $handler->display->display_options['filters']['teacher_lessons_dates']['expose']['operator_id'] = 'teacher_lessons_dates_op';
  $handler->display->display_options['filters']['teacher_lessons_dates']['expose']['operator'] = 'teacher_lessons_dates_op';
  $handler->display->display_options['filters']['teacher_lessons_dates']['expose']['identifier'] = 'teacher_lessons_dates';
  $handler->display->display_options['filters']['teacher_lessons_dates']['expose']['remember_roles'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['teacher_lessons_dates']['widget_type'] = 'date_popup';
  $handler->display->display_options['filters']['teacher_lessons_dates']['date_popup_format'] = 'Y-m-d';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'teachers';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Teachers';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['teachers_index'] = $view;

  return $export;
}
