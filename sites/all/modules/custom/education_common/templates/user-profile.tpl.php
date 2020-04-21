<?php

if (request_uri() != '/tutor-setup') {
  hide($form['account']['mail']);
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
}

hide($form['mimemail']);

?>

<?php
  print drupal_render_children($form);
?>

<?php if (request_uri() != '/tutor-setup') { ?>
<div id="pupils-accordion">
  <h3>Identification data</h3>
  <div>
    <p>

      ID<br />

      <?php print render($form['account']['mail']); ?>
      <!--
      Mauris mauris ante, blandit et, ultrices a, suscipit eget, quam. Integer
      ut neque. Vivamus nisi metus, molestie vel, gravida in, condimentum sit
      amet, nunc. Nam a nibh. Donec suscipit eros. Nam mi. Proin viverra leo ut
      odio. Curabitur malesuada. Vestibulum a velit eu ante scelerisque vulputate.
      -->
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

      <!--
      Sed non urna. Donec et ante. Phasellus eu ligula. Vestibulum sit amet
      purus. Vivamus hendrerit, dolor at aliquet laoreet, mauris turpis porttitor
      velit, faucibus interdum tellus libero ac justo. Vivamus non quam. In
      suscipit faucibus urna.
      -->
    </p>
  </div>
  <h3>Alerts and subscriptions</h3>
  <div>
    <p>
      Nam enim risus, molestie et, porta ac, aliquam ac, risus. Quisque lobortis.
      Phasellus pellentesque purus in massa. Aenean in pede. Phasellus ac libero
      ac tellus pellentesque semper. Sed ac felis. Sed commodo, magna quis
      lacinia ornare, quam ante aliquam nisi, eu iaculis leo purus venenatis dui.
    </p>
    <ul>
      <li>List item one</li>
      <li>List item two</li>
      <li>List item three</li>
    </ul>
  </div>
  <h3>Change password</h3>
  <div>
    <p>
      <?php print render($form['account']['current_pass']); ?>
      <?php print render($form['account']['pass']); ?>
      Cras dictum. Pellentesque habitant morbi tristique senectus et netus
      et malesuada fames ac turpis egestas. Vestibulum ante ipsum primis in
      faucibus orci luctus et ultrices posuere cubilia Curae; Aenean lacinia
      mauris vel est.
    </p>

  </div>
</div>

<div class="profile-actions">
  <?php print render($form['actions']); ?>
</div>

<?php } ?>
