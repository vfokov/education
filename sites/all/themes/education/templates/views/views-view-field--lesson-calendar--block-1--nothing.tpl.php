<?php
global $user;
// TODO перенести в preprocess field

if (strstr(current_path(), 'user')) {
  $current_path_uid = arg(1);
}
else {
  if (request_uri() == '/teacher-schedule') {
    $current_path_uid =  $user->uid;
  }
}


  if ($current_path_uid == $user->uid ) {
    $product_id = $row->commerce_product_field_data_field_product_reference_product_;
    $date = $row->field_data_field_lesson_date_field_lesson_date_value;
    $teacher_uid = $row->node_uid;
    $lesson_nid = $row->nid;
    /*
    $output = '<a href="#" class="btn lesson_date_close popup__link"
        data-popup="lesson_date_close" data-lesson-nid="' . $lesson_nid . '"
        data-product-id="' . $product_id . '" data-date="' . $date . '" data-teacher-uid="' . $teacher_uid . '">
Close this position</a>';
    */
    $output = '<a href="#" class="btn lesson_date_disable popup__link"
        data-popup="lesson_date_disable" data-lesson-nid="' . $lesson_nid . '"
        data-product-id="' . $product_id . '" data-date="' . $date . '" data-teacher-uid="' . $teacher_uid . '">
Disable this position</a>';
    /*
    $output = '<a href="#" class="btn lesson_date_enable popup__link"
        data-popup="lesson_date_enable" data-lesson-nid="' . $lesson_nid . '"
        data-product-id="' . $product_id . '" data-date="' . $date . '" data-teacher-uid="' . $teacher_uid . '">
enable this position</a>';
    */
  }
//}
?>
<?php print $output; ?>
