(function ($) {

  function getTimerFromServer() {
    var classroom_nid = $('input[name="classroom_nid"]').val();
    var timer_editor_uid = $('input[name="timer_editor_uid"]').val();
    console.log('t_clas_nid' + classroom_nid);
    $.ajax({
      type: 'POST',
      url: '/get-timer-from-server',
      data: {
        classroom_nid: classroom_nid,
      },
      dataType: 'json',
      success: function (msg) {
        if (msg.seconds) {
          var is_paused = msg.is_paused;
          console.log(msg)
          if (msg.seconds) {
            var time_st = '+' + msg.seconds;
            console.log('time_st=' + time_st);
            var liftoffTime = new Date();
            console.log('liftoffTime=' + liftoffTime);
            //console.log('liftoffTime=' + liftoffTime);

            if (is_paused == '1' && msg.timer_editor_uid != timer_editor_uid) {
            //if (msg.timer_editor_uid != timer_editor_uid) {

              console.log('Will be updated');

              $('#classroom-timer').countdown('destroy');
              $('#classroom-timer').countdown({until: time_st, compact: true, description: ''});

              pause(false);
              $('#pauseResume').removeClass('pause')
              $('#pauseResume').addClass('resume');
              $('#pauseResume').text('Resume');
            }
          }
        }
      },
      error: function () {

      }
    });
  }

  function start() {
    $('#classroom-timer').countdown('resume');
    var classroom_nid = $('input[name="classroom_nid"]').val();
    var timer_editor_uid = $('input[name="timer_editor_uid"]').val();
    $.ajax({
      type: 'POST',
      url: '/start-timer',
      data: {
        //seconds: seconds,
        classroom_nid: classroom_nid,
        timer_editor_uid: timer_editor_uid,
      },
      success: function (msg) {

      },
      error: function () {

      }
    });
  }
  function pause(editor) {
    $('#classroom-timer').countdown('pause');
    var periods = $('#classroom-timer').countdown('getTimes');
    var minutes = periods[5];
    var seconds = periods[6];

    seconds = parseInt(seconds) + parseInt(minutes) * 60;
    var classroom_nid = $('input[name="classroom_nid"]').val();
    var timer_editor_uid = $('input[name="timer_editor_uid"]').val();
    if (editor) {
      $.ajax({
        type: 'POST',
        url: '/pause-timer',
        data: {
          seconds: seconds,
          classroom_nid: classroom_nid,
          timer_editor_uid: timer_editor_uid
        },
        success: function (msg) {

        },
        error: function () {

        }
      });
    }
  }

  /*
  Drupal.behaviors.classroomTimer = {
    attach: function(context, settings) {

      $('#pauseButton').click(function () {
        console.log('pause');
        pause();
      });
    }
  };
  */

  $(document).ready(function($) {
    // $('#classroom-timer').countdown({until: new Date(2020, 12-1, 25)});
    //$('#classroom-timer').countdown({until: new Date(2020, 5, 13), format: 'dHM'});
    console.log('time st' + Drupal.settings.time_stared);
    if (Drupal.settings.time_stared) {
      var time_st = '+' + Drupal.settings.time_stared;
      var liftoffTime = new Date();
      $('#classroom-timer').countdown({until: time_st, compact: true, description: ''});
    }

    console.log('timer');

    $('#pauseResume').click(function (e) {
      e.preventDefault();
      console.log('can pause');
      console.log('pause');
      if ($(this).hasClass('pause')) {
        $(this).removeClass('pause');
        $(this).addClass('resume');
        $(this).text('Resume');
        pause(true);


      }
      else {
        $(this).removeClass('resume');
        $(this).addClass('pause');
        $(this).text('Pause');
        start();
      }

    });




    //$('#resume').click(start);

    /*
    $('#pauseResume').toggle(
      function() {
        console.log('pause');
        $(this).text('Resume');
        $('#classroom-timer').countdown('pause');
      },
      function() {
        $(this).text('Pause');
        console.log('Resume');
        $('#classroom-timer').countdown('resume');
      }
    );

     */


    //setInterval(getTimerFromServer, 2000);

    setInterval(function () {
      //console.log(Drupal.settings.classroom_nid);
      //console.log('lock = ' + lock);
      getTimerFromServer(); //this will send request again and again; // field_timer_editor_uid‎
    }, 4000);

  });
})(jQuery);
