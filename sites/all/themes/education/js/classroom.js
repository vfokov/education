(function ($) {


  var username = '';
  var password = '';


  $(document).ready(function($) {
    //console.log('classroom');
    //console.log(lc);

    username = Drupal.settings.vox_username;
    password = Drupal.settings.vox_password;
    console.log(Drupal.settings.classroom_nid);
    console.log('uname ' + username);
    console.log('upass ' + password);


  });
})(jQuery);
