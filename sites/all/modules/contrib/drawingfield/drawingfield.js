/**
 * @file
 * Canvas js integration.
 */

(function ($) {

  var lock = 0;

  // send changes to server via ajax
  function sendChangesToServer(text, classroom_nid, uid) {
    window.setTimeout(function () {
      //$('.info').addClass('show');
      //$('.info').text('Saving...');
      //console.log(text);
      $.ajax({
        type: 'POST',
        url: '/save-onchange',
        ////dataType: "html",
        //processData: false,
        //contentType: 'application/json',
        //data: JSON.stringify(data),
        data: {
          text: text,
          nid: classroom_nid,
          uid: uid,
        },
        success: function (msg) {
          setTimeout(function () {
            lock = 0;
          }, 1000)

          //console.log('saved');
          /*
          $('.info').text('Saved');
          setTimeout(function(){
            $('.info').removeClass('show');
          }, 1000);
          */

        },
        error: function () {
          //console.log('err');
        }
      });
    });
  }

  function sendUpdateRequest(classroom_nid){
    //console.log('lll_lock =' + lock);
    if (lock == 0) {

      $.ajax({
        type: 'POST',
        url: "/get-changes-from-server",
        data: {nid: classroom_nid},
        dataType: 'json',
        success: function (msg) {

          if (msg.text) {
            settings = Drupal.settings.drawingfield;
            var imageSize = {width: settings.width, height: settings.height};

            //console.log(imageSize);
            //console.log(settings);
            /*
            var carr_val =  $('.drawingfield.export input').val();
            console.log(carr_val);
            var check = true;
            if (carr_val != msg.text) {
              check = true;
            }
            */
            var check = true;
            var editor_uid = msg.current_editor_uid;
            if (editor_uid == Drupal.settings.classroom_uid) {
              check = false;
            }

            if (check) {
              var lc = LC.init(
                document.getElementsByClassName('drawingfield export')[0], {
                  imageSize: imageSize,
                  backgroundColor: settings.backgroundColor,
                  imageURLPrefix: settings.imageUrlPrefix
                });
              var localStorageKey = 'drawing'
              json = msg.drawing_edit_path;

              localStorage.setItem(localStorageKey, json);
              if (localStorage.getItem(localStorageKey)) {
                lc.loadSnapshotJSON(localStorage.getItem(localStorageKey));
                //console.log(lc);
              }
              //////////////////////////////////////////////////////////////////////
              lc.on('drawingChange', function () {
                json = lc.getSnapshotJSON();
                var base64 = lc.getImage().toDataURL();
                var jsonBase64 = json + 'JSON' + base64;
                paintId = $(".form-group").find("input.output").attr('id');
                $("#" + paintId).val(jsonBase64);
                lock = 1;
                timer = setTimeout(function () {
                  var uid = Drupal.settings.classroom_uid;
                  sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid, uid);
                }, 700);
                //console.log('drawChange')
              });

              // Clear image
              lc.on('clear', function () {
                json = lc.getSnapshotJSON();
                var base64 = lc.getImage().toDataURL();
                var jsonBase64 = json + 'JSON' + base64;
                paintId = $(".form-group").find("input.output").attr('id');
                $("#" + paintId).val(jsonBase64);
                lock = 1;
                timer = setTimeout(function () {
                  var uid = Drupal.settings.classroom_uid;
                  sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid, uid);
                }, 700);
                console.log('Clear')
              });

              // toolChange
              lc.on('toolChange', function () {
                json = lc.getSnapshotJSON();
                var base64 = lc.getImage().toDataURL();
                var jsonBase64 = json + 'JSON' + base64;
                paintId = $(".form-group").find("input.output").attr('id');
                $("#" + paintId).val(jsonBase64);
                lock = 1;
                timer = setTimeout(function () {
                  var uid = Drupal.settings.classroom_uid;
                  sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid, uid);
                }, 700);
                console.log('toolChange')
              });

              lc.on('primaryColorChange', function() {
                console.log('colorIsChanged');
                lock = 1;
              });

              lc.on('backgroundColorChange', function() {
                console.log('backgroundColorChange');
                lock = 1;
              });
              //lc.on('lc-pointerup', function() {
              lc.on('drawContinue', function() {
                console.log('drawContinue');
                lock = 1;
              });
              lc.on('pointerdown', function() {
                lock = 1;
                console.log('down =' + lock);
              });

              lc.on('drawEnd', function() {
                lock = 0;
              });
              lc.on('pointerup', function() { //http://literallycanvas.com/api/events.html
                console.log('p_UP');
                lock = 0;
              });
              //////////////////////////////////////////////////////////////////////


            }
            /////////////////////
          }

          ///////////////////////////////////////////

          if (editor_uid != Drupal.settings.classroom_uid) {
            setTimeout(function () {
              ///////////sendUpdateRequest(classroom_nid); //this will send request again and again;
            }, 2000);
          }


        },
        error: function (msg) {
          //console.log(msg);
        }
      });
    }
  }

  Drupal.behaviors.drawingfield = {
    attach: function(context, settings) {
      settings = Drupal.settings.drawingfield;
      var imageSize = {width: settings.width, height: settings.height};
      //console.log(imageSize);
      //console.log(settings);

      var lc = LC.init(
      document.getElementsByClassName('drawingfield export')[0],{imageSize: imageSize,backgroundColor: settings.backgroundColor,imageURLPrefix: settings.imageUrlPrefix});
      var localStorageKey = 'drawing'
      json = settings.drawingEditPath;

      localStorage.setItem(localStorageKey, json);
      if (localStorage.getItem(localStorageKey)) {
        lc.loadSnapshotJSON(localStorage.getItem(localStorageKey));
      }
      // drawingChange
      lc.on('drawingChange', function() {
        json = lc.getSnapshotJSON();
        var base64 = lc.getImage().toDataURL();
        var jsonBase64 = json + 'JSON' + base64;
        paintId = $(".form-group").find("input.output").attr('id');
        $("#" + paintId).val(jsonBase64);
        lock = 1;
        timer = setTimeout(function(){
          var uid = Drupal.settings.classroom_uid;
          sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid, uid);
          }, 700);
          //console.log('drawChange')
      });

      // Clear image
      lc.on('clear', function() {
        json = lc.getSnapshotJSON();
        var base64 = lc.getImage().toDataURL();
        var jsonBase64 = json + 'JSON' + base64;
        paintId = $(".form-group").find("input.output").attr('id');
        $("#" + paintId).val(jsonBase64);
        lock = 1;
        timer = setTimeout(function(){
          var uid = Drupal.settings.classroom_uid;
          sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid, uid);
        }, 700);
        console.log('Clear')
      });

      // toolChange
      lc.on('toolChange', function() {
        json = lc.getSnapshotJSON();
        var base64 = lc.getImage().toDataURL();
        var jsonBase64 = json + 'JSON' + base64;
        paintId = $(".form-group").find("input.output").attr('id');
        $("#" + paintId).val(jsonBase64);
        lock = 1;
        timer = setTimeout(function(){
          var uid = Drupal.settings.classroom_uid;
          sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid, uid);
        }, 700);
        console.log('toolChange')
      });
      lc.on('primaryColorChange', function() {
        console.log('colorIsChanged');
        lock = 1;
      });

      lc.on('backgroundColorChange', function() {
        console.log('backgroundColorChange');
        lock = 1;
      });

      //lc.on('lc-pointerup', function() {
      //lc.on('pointerdown', function() {
      lc.on('drawContinue', function() {
        console.log('drawContinue');
        lock = 1;
      });
      lc.on('pointerdown', function() {
        lock = 1;
        console.log('down =' + lock);
      });

      lc.on('drawEnd', function() {
        lock = 0;
      });
      lc.on('pointerup', function() { //http://literallycanvas.com/api/events.html
        //console.log('p_UP');
        lock = 0;
      });

      $('.square-toolbar-button').on('click', function(){
        lock = 1;
        console.log('square-toolbar-button clicked');
      });

      $('.lc-color-pickers').on('click', function(){
        lock = 1;
        console.log('lc-color-pickers clicked');
      });

    }
  }

  $(document).ready(function($) {
    setInterval(function () {
      //console.log(Drupal.settings.classroom_nid);
      //console.log('lock = ' + lock);
      sendUpdateRequest(Drupal.settings.classroom_nid); //this will send request again and again;
    }, 3000);

    $('.field-desk-add-more-wrapper').mouseup(function(){
      //console.log('mouseup');
    });
  })

})(jQuery);
