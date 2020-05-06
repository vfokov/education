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
?>
<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <h2<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>

    <?php if (drupal_is_front_page()): ?>
      <h2>Study perfectly,</h2>
      <div class="front-page-tutor-search-text">
        <?php print variable_get_value('front_page_search_text'); ?>
      </div>
    <?php endif; ?>


        <div class="b-main__jumbotron-form l-row clearfix">
          <div class="b-main__jumbotron-form__tabs l-col l-full">
            <div class="l-row clearfix">

              <?php if (user_is_anonymous()): ?>
              <div class="l-col l-third">
                <div class="e-form-tab try-for-free m-active" data-tab="free">Try for free</div>
              </div>
              <?php endif; ?>

              <div class="l-col l-third">
                <div class="e-form-tab sign-up-lesson <?php print !user_is_anonymous() ? 'm-active' : '' ?>" data-tab="reserve">Sign up for the lesson</div>
              </div>

              <div class="l-col l-third">
                <div class="e-form-tab select-tutor" data-tab="select">Select Tutor</div>
              </div>
            </div>
          </div>
        </div>

    <div class="search-forms <?php print user_is_anonymous() ? 'hidden' : ''; ?> ">
      <?php print $content; ?>
    </div>

    <?php if (user_is_anonymous()): ?>
      <?php $register_form = drupal_get_form('user_register_form'); ?>
      <?php print render($register_form); ?>
    <?php endif; ?>


    <div class="b-main__jumbotron-form__next_steps__group l-col l-full">
      <div class="l-row clearfix try-for-free-step <?php print user_is_anonymous() ? 'm-active' : '' ?>" data-tab-form-description="free">
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-tutor-speaker">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>We'll choose a teacher for your preference.</p>
          </div>
        </div>
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-lesson-schedule">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>We'll agree on the time of the first lesson.</p>
          </div>
        </div>
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-tutor-card">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>We'll make personalized training recommendations.</p>
          </div>
        </div>
      </div>
      <div class="l-row clearfix  sign-up-lesson-step <?php print !user_is_anonymous() ? 'm-active' : '' ?>" data-tab-form-description="reserve">
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-lesson-schedule">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>Plan a lesson for your subject at a time convenient for you.</p>
          </div>
        </div>
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-lesson-tasks">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>Plan a lesson for your subject at a time convenient for you .</p>
          </div>
        </div>
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-tutor-card">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>Get recommendations on your subject.</p>
          </div>
        </div>
      </div>
      <div class="l-row clearfix select-tutor-step" data-tab-form-description="select">
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-tutor-speaker">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>Choose a tutor for your subject.</p>
          </div>
        </div>
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon i-lesson-schedule">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>Schedule a lesson at a time convenient for you.</p>
          </div>
        </div>
        <div class="l-col l-third">
          <div class="l-col l-quart"><span class="icon  i-lesson-tasks">&nbsp;</span></div>
          <div class="l-col l-three-quart">
            <p>Solve all the tasks before the lesson and get recommendations.</p>
          </div>
        </div>
      </div>
    </div>

  </div>
</div>
