<?php

global $user;
// TODO ��������� � preprocess field

/*
if (strstr(current_path(), 'user')) {
  $current_path_uid = arg(1);

  if ($current_path_uid == $user->uid ) {
    $product_id = $row->commerce_product_field_data_field_product_reference_product_;
    $date = $row->field_data_field_lesson_date_field_lesson_date_value;
    $teacher_uid = $row->node_uid;
    $lesson_nid = $row->nid;
    $output = '<a href="#" class="btn lesson_date_disable popup__link"
        data-popup="lesson_date_disable" data-lesson-nid="' . $lesson_nid . '"
        data-product-id="' . $product_id . '" data-date="' . $date . '" data-teacher-uid="' . $teacher_uid . '">
Disable this position</a>';
  }
}
*/

$output = '';
if (!empty($_GET['uid'])) {
  //$user_by_name = user_load_by_name($_GET['uid']);
  //$uid = $user_by_name->uid;

  $output = '';
}

?>

<?php print $output; ?>
