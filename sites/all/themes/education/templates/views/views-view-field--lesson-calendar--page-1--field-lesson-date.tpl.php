<?php

$current_path = '/' . current_path();
$date = $row->field_data_field_lesson_date_field_lesson_date_value;

$query = new EntityFieldQuery;
$type = 'lesson';
$query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('status', 1)
  ->propertyCondition('type', $type)
  //->fieldCondition('field_lesson_date', 'value',  '2020-04-08 15:30:00', '=');
  ->fieldCondition('field_lesson_date', 'value',  $date, '=');
  if (!empty($_GET['field_lesson_subject_tid']) && $_GET['field_lesson_subject_tid'] != 'All') {
    $query->fieldCondition('field_lesson_subject', 'tid',  $_GET['field_lesson_subject_tid'], '=');
  }

  if (!empty($_GET['field_age_category_tid']) && $_GET['field_age_category_tid'] != 'All') {
    $query->fieldCondition('field_age_category_tid', 'tid',  $_GET['field_age_category_tid'], '=');
  }

if (!empty($_GET['uid'])) {
  $less_user = user_load_by_name($_GET['uid']);
  $query->propertyCondition('uid', $less_user->uid);
}

$result =  $query->execute();
if (!empty($result['node'])) {
  $users = array();
  foreach ($result['node'] as $n_obj) {
    $node = node_load($n_obj->nid);
    $users[$node->uid] = user_load($node->uid);
  }
}

?>

<?php if (empty($_GET['uid'])): ?>

<span class="box" data-tooltip='{"showOn":"click", "orientation":"bottom",
      "text": "<ul><?php foreach($users as $user):?><li><a href=\"<?php print $current_path ?>?uid=<?php print $user->name;?>\"> <?php  print $user->name; ?></a></li><?php endforeach; ?></ul>"
      }' ><?php print count($users); ?> <?php print count($users) > 1 ? 'teachers' : 'teacher'; ?></span><br/>

<?php endif; ?>
<?php
if (isset($_GET['uid'])) {
  $output = '';
}
?>
<?php //print $output; ?>

