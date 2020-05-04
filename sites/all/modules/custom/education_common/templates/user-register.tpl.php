<?php
if (request_uri() == '/tutor-registration') {
  hide($form['field_student_age_category']);
  hide($form['field_select_pupil_role']);
}

if (drupal_is_front_page()) {
  hide($form['field_student_age_category']);
  hide($form['field_select_pupil_role']);
  hide($form['field_is_a_teacher']);
  hide($form['field_teaching_format']);
  hide($form['field_ready_to_get_news']);
  hide($form['field_terms_of_service']);
  hide($form['field_student_promocode']);
}

?>

<?php
  //print drupal_render($form);
  if (request_uri() == '/pupil-registration') {
    print drupal_render($form['field_student_age_category']);
    print drupal_render($form['field_select_pupil_role']);
  }

  print drupal_render_children($form);
?>
