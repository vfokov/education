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

if (!user_is_anonymous()) {



 // Temporary after vox user creation need to replace for real vox data
 if (user_has_role(TEACHER_ROLE)) {
   $to_call = 'ladovod3';
 }

 if (user_has_role(STUDENT_ROLE)) {
   $to_call = 'ladovod';
 }

  $classroom_node = node_load(arg(1));
  $classroom_nid = arg(1);

//var_dump($classroom_node); die();

 $order_id = isset($classroom_node->field_order_id[LANGUAGE_NONE]) ?
   $classroom_node->field_order_id[LANGUAGE_NONE][0]['value'] : '';
 $order = commerce_order_load($order_id);

 $zoom_link = isset($classroom_node->field_join_lesson_link[LANGUAGE_NONE]) ?
   $classroom_node->field_join_lesson_link[LANGUAGE_NONE][0]['value'] : '';

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

if ($order_id && user_has_role(TEACHER_ROLE)) {
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

  <!--<iframe class="video-frame" src="" id="raz2"></iframe> -->

  <div class="content"<?php print $content_attributes; ?>>
    <?php if ($zoom_link): ?>
      <a class="classroom-video-link" href="<?php print $zoom_link; ?>" target="_blank">Join Lesson link</a>
    <?php endif; ?>
    <!--<a class="classroom-video-link" href="https://talky.io/educt_<?php //print $classroom_nid; ?>#size-window">Open Video</a> -->
</div>
</div>


<?php } ?>
