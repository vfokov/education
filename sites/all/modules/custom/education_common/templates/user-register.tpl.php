<?php ?>

<?php
  //print drupal_render($form);

  print drupal_render($form['field_student_age_category']);
  print drupal_render($form['field_select_pupil_role']);

  print drupal_render_children($form);
?>
