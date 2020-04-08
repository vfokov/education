<?php
$date = $row->field_data_field_lesson_date_field_lesson_date_value;

$query = new EntityFieldQuery;
$type = 'lesson';
$result = $query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('status', 1)
  ->propertyCondition('type', $type)
  ->fieldCondition('field_lesson_date', 'value',  '2020-04-08 15:30:00', '=')
  //->propertyCondition('uid', $uid)
  ->execute();
if (!empty($result['node'])) {
//echo '<pre>'; print_r($result['node']); echo '</pre>'; die();

  $users = array();
  foreach ($result['node'] as $n_obj) {
    $node = node_load($n_obj->nid);
    $users[] = user_load($node->uid);
  }
}



?>


<span class="box" data-tooltip='{"showOn":"click", "orientation":"bottom",

      "text": "<ul><?php foreach($users as $user):?><li> <?php  print $user->name; ?></li><?php endforeach; ?></ul>"

      }' ><?php print count($users); ?> teachers</span><br/>

<!--
<nav class="teachers-nav">
  <ul class="teachers-wrapper">
    <li>

    </li>
  </ul>
</nav>
-->

<?php print $output; ?><br />
<?php //print $date; ?>
