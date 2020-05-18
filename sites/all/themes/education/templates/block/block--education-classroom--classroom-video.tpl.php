<?php

/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */

 // Temporary after vox user creation need to replace for real vox data
 if (user_has_role(TEACHER_ROLE)) {
   $to_call = 'ladovod3';
 }

 if (user_has_role(STUDENT_ROLE)) {
   $to_call = 'ladovod';
 }

 $classroom_node = node_load(arg(1));

 $order_id = $classroom_node->field_order_id[LANGUAGE_NONE][0]['value'];
 $order = commerce_order_load($order_id);

if (user_has_role(STUDENT_ROLE)) {
  $teacher = user_load($order->field_lesson_teacher_uid[LANGUAGE_NONE][0]['uid']);
  if (isset($teacher->field_vox_username[LANGUAGE_NONE])) {
    $to_call = $teacher->field_vox_username[LANGUAGE_NONE][0]['value'];
  }
  else {
    // test acc
    $to_call = 'ladovod';
  }
}

if (user_has_role(TEACHER_ROLE)) {
  $student = user_load($order->uid);
  if (isset($student->field_vox_username[LANGUAGE_NONE])) {
    $to_call = $student->field_vox_username[LANGUAGE_NONE][0]['value'];
  }
  else {
    // test acc
    $to_call = 'ladovod3';
  }
}

?>

<!--<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>-->

<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <h2<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <div id="video-content" class="panel-body">
      <div id="voximplant_container"></div>
      <div id="controls" style="display:none">
        <div class="input-wrapper">
          <div class="input-group">
            <!--<span class="input-group-addon">@</span> -->
            <!--<input id="phonenum" type="text" class="form-control" placeholder="Username" value="<?php //print $to_call; ?>"> -->
            <input id="phonenum" type="hidden" class="form-control" placeholder="Username" value="<?php print $to_call; ?>">
          </div>
        </div>
        <div class="btn-group btn-group-justified">
          <div class="btn-group">
            <button type="button" class="btn btn-success" id="callButton">Connect</button>
            <!--<button type="button" class="btn btn-default" id="fsButton">Enter fullscreen</button>-->
          </div>
        </div>
      </div>
      <div id="log" class="well hidden">
      </div>
    </div>
  </div>
</div>
