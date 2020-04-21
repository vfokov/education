<?php
if (request_uri() == '/tutor-registration') {
  hide($form['field_student_age_category']);
  hide($form['field_select_pupil_role']);
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
