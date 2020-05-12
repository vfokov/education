(function ($) {

  $(document).ready(function($) {
    //alert(Drupal.settings.time_stared); // покажет "bar"
    // $('#classroom-timer').countdown({until: new Date(2020, 12-1, 25)});
    //$('#classroom-timer').countdown({until: new Date(2020, 5, 13), format: 'dHM'});
    if (Drupal.settings.time_stared) {
      var time_st = '+' + Drupal.settings.time_stared;
      var liftoffTime = new Date();
      $('#classroom-timer').countdown({until: time_st, compact: true, description: ''});
    }
  });
})(jQuery);
