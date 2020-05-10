<?php

hide($form['field_not_available_dates']);


if (request_uri() != '/tutor-setup' && user_has_role(STUDENT_ROLE)) {
  hide($form['account']['mail']);
  hide($form['account']['name']);
  hide($form['field_teacher_last_name']);
  hide($form['field_first_name']);
  hide($form['field_phone']);
  hide($form['field_skype']);
  hide($form['field_city']);

  hide($form['account']['current_pass']);
  hide($form['account']['pass']);
  hide($form['field_teachecr_pic']);
  hide($form['field_student_promocode']);
  hide($form['actions']);
  hide($form['field_teaching_format']);
  hide($form['field_gender']);
  hide($form['field_university']);
  hide($form['field_speciality']);
  hide($form['field_graduation_year']);
  hide($form['field_academic_degree']);

} else {

  hide($form['field_documents']);
  hide($form['field_university']);
  hide($form['field_speciality']);
  hide($form['field_graduation_year']);
  hide($form['field_academic_degree']);
  hide($form['field_phone']);
  hide($form['field_first_name']);
  hide($form['field_teacher_last_name']);
  hide($form['field_gender']);
  hide($form['field_skype']);

  hide($form['field_languages_can_teach']);
  hide($form['field_grade_subject']);
  hide($form['field_age_category']);
  hide($form['field_hourly_rate_']);

  hide($form['field_teachecr_pic']);
  hide($form['field_resume_']);

  hide($form['account']['mail']);
  hide($form['account']['name']);
  hide($form['account']['pass']);
  hide($form['field_phone']);
  hide($form['field_first_name']);
  hide($form['field_teacher_last_name']);
  hide($form['field_gender']);
  hide($form['actions']);
}

hide($form['mimemail']);

?>

<?php
if (user_has_role(TEACHER_ROLE)) {
  hide($form['field_select_pupil_role']);
  hide($form['field_student_age_category']);

  hide($form['field_is_a_teacher']['#access']);
  hide($form['field_ready_to_get_news']['#access']);
  hide($form['field_terms_of_service']['#access']);
}
?>

<?php
  print drupal_render_children($form);
?>

<?php if (request_uri() != '/tutor-setup' && !user_has_role(TEACHER_ROLE) ) : ?>
  <div id="pupils-accordion">
    <h3>Identification data</h3>
    <div>
      <p>
        ID<br />
        <?php print render($form['account']['mail']); ?><br />
        <?php print render($form['account']['name']); ?>
        <?php //echo '<pre>'; print_r($form['account']); echo '</pre>'; die(); ?>
      </p>
    </div>
    <h3>Personal data</h3>
    <div>
      <p>
        <?php print render($form['field_teachecr_pic']); ?>
        <?php print render($form['field_first_name']); ?>
        <?php print render($form['field_teacher_last_name']); ?>
        <?php print render($form['field_phone']); ?>
        <?php print render($form['field_city']); ?>
        <?php print render($form['field_skype']); ?>
        <?php print render($form['field_student_promocode']); ?>

      </p>
    </div>
    <h3>Alerts and subscriptions</h3>
    <div>

    </div>
    <h3>Change password</h3>
    <div>
      <p>
        <?php print render($form['account']['current_pass']); ?>
        <?php print render($form['account']['pass']); ?>
      </p>

    </div>
  </div>

  <div class="profile-actions">
    <?php print render($form['actions']); ?>
  </div>

<!-- TUTOR -->
<?php else: ?>

<?php if (request_uri() == '/tutor-setup'){ ?>
  <!-- Load to в form_alter-->
  <script src="https://code.jquery.com/jquery-1.12.4.js"></script>
  <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.js"></script>
  <script>
    $( function() {
      $( "#tabs" ).tabs().addClass( "ui-tabs-vertical ui-helper-clearfix" );
      $( "#tabs li" ).removeClass( "ui-corner-top" ).addClass( "ui-corner-left" );
    } );
  </script>
  <div id="tabs">
    <ul>
      <li class="personal-data"><a href="#personal-data"><strong>Personal data</strong></a></li>
      <li class="tutor-place"><a href="#tutor-place"><strong>Tutor place</strong></a></li>
      <li class="subjects"><a href="#subjects"><strong>Subjects</strong></a></li>
      <li class="education-n-documents"><a href="#education-n-documents"><strong>Education and documents</strong></a></li>
      <li class="profile"><a href="#profile"><strong>Profile</strong></a></li>
    </ul>

    <div class="vertical-tabs-panes vertical-tabs-processed">
      <div id="personal-data">
        <?php print render($form['account']['name']); ?>
        <?php print render($form['account']['mail']); ?>
        <?php print render($form['account']['pass']); ?>
        <?php print render($form['field_phone']); ?>
        <?php print render($form['field_first_name']); ?>
        <?php print render($form['field_teacher_last_name']); ?>
        <?php print render($form['field_gender']); ?>
      </div>
      <div id="tutor-place">
        <?php print render($form['field_skype']); ?>
      </div>
      <div id="subjects">
        <?php print render($form['field_languages_can_teach']); ?>
        <?php print render($form['field_grade_subject']); ?>
        <?php print render($form['field_age_category']); ?>
        <?php //print render($form['field_hourly_rate_']); ?>
      </div>
      <div id="education-n-documents">
        <?php print render($form['field_documents']); ?>
        <?php print render($form['field_university']); ?>
        <?php print render($form['field_speciality']); ?>
        <?php print render($form['field_graduation_year']); ?>
        <?php print render($form['field_academic_degree']); ?>
      </div>
      <div id="profile">
        <?php print render($form['field_teachecr_pic']); ?>
        <?php print render($form['field_resume_']); ?>
      </div>
    </div>
  </div>

  <div class="profile-actions">
    <?php print render($form['actions']); ?>
  </div>

<?php } ?>
<?php endif; ?>
