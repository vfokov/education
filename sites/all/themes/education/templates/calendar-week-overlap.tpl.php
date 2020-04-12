<?php
/**
 * @file
 * Template to display a view as a calendar week with overlapping items
 *
 * @see template_preprocess_calendar_week.
 *
 * $day_names: An array of the day of week names for the table header.
 * $rows: The rendered data for this week.
 *
 * For each day of the week, you have:
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period]['values'] - An array of formatted items for a time period.
 *
 * $view: The view.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 *
 */

/*
$header_ids = array();
foreach ($day_names as $key => $value) {<?php
/**
 * @file
 * Template to display a view as a calendar week with overlapping items
 *
 * @see template_preprocess_calendar_week.
 *
 * $day_names: An array of the day of week names for the table header.
 * $rows: The rendered data for this week.
 *
 * For each day of the week, you have:
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period]['values'] - An array of formatted items for a time period.
 *
 * $view: The view.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 *
 */

/*
$header_ids = array();
foreach ($day_names as $key => $value) {
  $header_ids[$key] = $value['header_id'];
}
*/
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);


$current_day_number = date("w");
$seconds_in_day = 86400;
//$current_time = mktime();
$current_time = time();
$what_time_was_in_monday = $current_time - (($current_day_number-1)*$seconds_in_day);

$week_array = array();
for($i = -1; $i <=5; $i++) {
  $next_day = $what_time_was_in_monday + (86400*$i);
  $week_day = date("D",$next_day);
  //$date = date("Y-m-d H:i",$next_day);
  $date = date("Y-m-d",$next_day);

  $week_array[$week_day] = $date;
  // echo $date;
  // echo '<br>';
}

$week_days = array(
  'Sun',
  'Mon',
  'Tue',
  'Wed',
  'Thu',
  'Fri',
  'Sat',
);

//print '--------------------------------';

//echo '<pre>'; print_r($week_array); echo '</pre>'; die();


$teacher_dates = array();
$type = 'lesson';
$uid = arg(1);
$query = new EntityFieldQuery;
$result = $query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('status', 1)
  ->propertyCondition('type', $type)
  ->propertyCondition('uid', $uid)
  ->execute();

if (!empty($result['node'])) {
  $nids = array_keys($result['node']);
  $nodes = node_load_multiple($nids);

  foreach ($nodes as $lesson_node) {
    if (isset($lesson_node->field_lesson_date['und'])) {
      foreach($lesson_node->field_lesson_date['und'] as $key => $lesson_date_item ) {
       $teacher_dates[] = $lesson_date_item['value'];
      }
    }
  }
}

//echo '<pre>'; print_r($teacher_dates); echo '</pre>'; die();


?>

<div class="calendar-calendar"><div class="week-view vvvvvvvvv">
    <div id="header-container">
      <table class="full">
        <tbody>
        <tr class="holder"><td class="calendar-time-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td>
          </tr>
        <tr>
          <th class="calendar-agenda-hour">&nbsp;</th>
          <?php foreach ($day_names as $cell): ?>
            <th class="<?php print $cell['class']; ?> " data-week-date ="<?php print $week_array[$cell['data']]; ?>" id="<?php print $cell['header_id']; ?>">
              <?php print $cell['data']; /*. ' ' . $week_array[$cell['data']];*/ ?>
            </th>
          <?php endforeach; ?>
          <th class="calendar-day-holder margin-right"></th>
        </tr>
        </tbody>
      </table>
    </div>



    <div class="header-body-divider">&nbsp;</div>
    <div id="single-day-container">
      <?php if (!empty($scroll_content)) : ?>
        <script>
          try {
            // Hide container while it renders...  Degrade w/o javascript support
            jQuery('#single-day-container').css('visibility','hidden');
          }catch(e){
            // swallow
          }
        </script>
      <?php endif; ?>
      <table class="full">
        <tbody>
        <tr class="holder"><td class="calendar-time-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td></tr>
        <tr>
          <?php for ($index = 0; $index < 8; $index++): ?>
            <?php if ($index == 0 ): ?>
              <td class="first" headers="<?php print isset($header_ids[$index]) ? $header_ids[$index] : ''; ?>">
            <?php elseif ($index == 7 ) : ?>
              <td class="last"">
            <?php else : ?>
              <td headers="<?php print isset($header_ids[$index]) ? $header_ids[$index] : ''; ?>" data-week-day="<?php print $week_array[$week_days[$index-1]]; ?>">
            <?php endif; ?>
            <?php foreach ($start_times as $time_cnt => $start_time): ?>
            <?php
            if ($time_cnt == 0) {
              $class = 'first ';
            }
            elseif ($time_cnt == count($start_times) - 1) {
              $class = 'last ';
            }
            else {
              $class = '';
            } ?>
            <?php if( $index == 0 ): ?>
              <?php $time = $items[$start_time];?>
              <div class="<?php print $class?>calendar-agenda-hour">
                <span class="calendar-hour"><?php print $time['hour'] == 'Before 01' ? '00' : $time['hour']; ?>:00</span><span class="calendar-ampm"><?php print $time['ampm']; ?></span>
              </div>
            <?php else: ?>
            <?php $day_date = $week_array[$week_days[$index-1]]; ?>
            <?php //$day_date_time = $week_array[$week_days[$index-1]]; //$teacher_dates ?>
            <div class="<?php print $class?>calendar-agenda-items single-day" data-week-day="<?php print $day_date  ?>">
            <?php $time_cnt_output = $time_cnt < 10 ? '0' . $time_cnt : $time_cnt;  ?>
            <?php $date_time = $day_date . ' ' . $time_cnt_output . ':00:00';  ?>


            <?php $av_class = (in_array($date_time, $teacher_dates)) ? 'avail' : ''; ?>
            <div class="half-hour full-hour <?php print $av_class; ?>" data-hour-full="<?php print $day_date; print ' '; print  $time_cnt_output . ':00:00' ; ?>" >
              <?php //print $date_time; ?> &nbsp;
              <?php if (in_array($date_time, $teacher_dates)): ?>
                <a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="1" data-date="<?php print $date_time; ?>" data-teacher-uid="<?php print $uid; ?>">Available</a>
              <?php endif; ?>
            </div>

            <?php $with_half_date_time = $day_date . ' ' . $time_cnt_output . ':30:00'; ?>
            <?php $av_class_half = (in_array($with_half_date_time, $teacher_dates)) ? 'avail' : ''; ?>

            <div class="half-hour <?php print $av_class_half; ?>" data-hour-with-half="<?php print $day_date; print ' '; print $time_cnt_output . ':30:00' ?>" >
              <?php //print $with_half_date_time; ?> &nbsp;
              <?php if (in_array($with_half_date_time, $teacher_dates)): ?>
                <a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="1" data-date="<?php print $with_half_date_time; ?>" data-teacher-uid="<?php print $uid; ?>">Available</a>
              <?php endif; ?>
            </div>
            <div class="calendar item-wrapper">
              <div class="inner">
                <?php if(!empty($items[$start_time]['values'][$index - 1])) :?>
                <?php foreach($items[$start_time]['values'][$index - 1] as $item) :?>
                <?php if (isset($item['is_first']) && $item['is_first']) :?>
                <div class="item <?php print $item['class']?> first_item">
                  <?php else : ?>
                  <div class="item <?php print $item['class']?>">
                    <?php endif; ?>
                    <?php print $item['entry'] ?>
                  </div>
                  <?php endforeach; ?>
                  <?php endif; ?>
                </div>
              </div>
            </div>
            <?php endif; ?>
          <?php endforeach;?>
            </td>
          <?php endfor;?>
        </tr>
        </tbody>
      </table>
    </div>
    <div class="single-day-footer">&nbsp;</div>
  </div></div>
<?php if (!empty($scroll_content)) : ?>
  <script>
    try {
      // Size and position the viewport inline so there are no delays
      calendar_resizeViewport(jQuery);
      calendar_scrollToFirst(jQuery);

      // Show it now that it is complete and positioned
      jQuery('#single-day-container').css('visibility','visible');
    }catch(e){
      // swallow
    }
  </script>
<?php endif; ?>
