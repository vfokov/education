/**
 * @file
 * Canvas js integration.
 */

(function ($) {

  var lock = 0;

  // send changes to server via ajax
  function sendChangesToServer(text, classroom_nid) {
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
        },
        success: function (msg) {

          setTimeout(function () {
            lock = 0;
          }, 1000)

          console.log('saved');
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

  function sendUpdateRequest(classroom_nid, lc){
    console.log('lll_lock =' + lock);
    if (lock == 0) {

      $.ajax({
        type: 'POST',
        url: "/get-changes-from-server",
        data: {nid: classroom_nid},
        dataType: 'json',
        success: function (msg) {

          if (msg.text) {

            //console.log(msg.text);
            settings = Drupal.settings.drawingfield;
            var imageSize = {width: settings.width, height: settings.height};

            //console.log(imageSize);
            //console.log(settings);

            var carr_val =  $('.drawingfield.export input').val();

            var check = true;
            if (carr_val != msg.text) {
              //check = true;
            }


            if (check) {
              ///////////////////////
              /*
              var lc = LC.init(
                document.getElementsByClassName('drawingfield export')[0], {
                  imageSize: imageSize,
                  backgroundColor: settings.backgroundColor,
                  imageURLPrefix: settings.imageUrlPrefix
                });
                */

              var localStorageKey = 'drawing'
              json = msg.drawing_edit_path;

              localStorage.setItem(localStorageKey, json);
              if (localStorage.getItem(localStorageKey)) {
                lc.loadSnapshotJSON(localStorage.getItem(localStorageKey));
                console.log(lc);
              }
            }

            /////////////////////


          }

          ///////////////////////////////////////////


          setTimeout(function () {
            sendUpdateRequest(classroom_nid); //this will send request again and again;
          }, 6000);


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
      console.log(imageSize);
      console.log(settings);

      var lc = LC.init(
        document.getElementsByClassName('drawingfield export')[0],{imageSize: imageSize,backgroundColor: settings.backgroundColor,imageURLPrefix: settings.imageUrlPrefix});
      var localStorageKey = 'drawing'
      json = settings.drawingEditPath;

      localStorage.setItem(localStorageKey, json);
      if (localStorage.getItem(localStorageKey)) {
        lc.loadSnapshotJSON(localStorage.getItem(localStorageKey));
      }
      lc.on('drawingChange', function() {
        json = lc.getSnapshotJSON();
        var base64 = lc.getImage().toDataURL();
        var jsonBase64 = json + 'JSON' + base64;
        paintId = $(".form-group").find("input.output").attr('id');
        $("#" + paintId).val(jsonBase64);
        lock = 1;
        timer = setTimeout(function(){
          sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid);
        }, 700);
        console.log('drawChange')
        //console.log(jsonBase64);
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
        //console.log('d end');
        lock = 0;
      });
      lc.on('pointerup', function() { //http://literallycanvas.com/api/events.html
        console.log('p_UP');
        lock = 0;

        /////paintId = $(".form-group").find("input.output").attr('id');
        //$("#" + paintId).val(jsonBase64);


        ///lock = 1;
        ///sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid);

        /*
        json = lc.getSnapshotJSON();
        var base64 = lc.getImage().toDataURL();
        var jsonBase64 = json + 'JSON' + base64;
        //paintId = $(".form-group").find("input.output").attr('id');
        //$("#" + paintId).val(jsonBase64);

        //console.log(jsonBase64);
        //sendChangesToServer(jsonBase64, Drupal.settings.classroom_nid);

        lock = 0;
        */


        setTimeout(function () {
          //setInterval(function () {
          console.log(Drupal.settings.classroom_nid);
          console.log('lock = ' + lock);
          //if (!lock) {
          sendUpdateRequest(Drupal.settings.classroom_nid, lc); //this will send request again and again;
          //}
          //$('.field-name-body').show();
          //var lock = 1;
        }, 3000);

        //setInterval(function () {
        //console.log(Drupal.settings.classroom_nid);
        //console.log('lock = ' + lock);
        //if (!lock) {
        ///sendUpdateRequest(Drupal.settings.classroom_nid); //this will send request again and again;
        //}
        //$('.field-name-body').show();
        //var lock = 1;
        //}, 3000);

      });




      //console.log(localStorage);

    }
  }


  $(document).ready(function($) {

    /*
    setTimeout(function () {
    //setInterval(function () {
      console.log(Drupal.settings.classroom_nid);
      console.log('lock = ' + lock);
      //if (!lock) {
        sendUpdateRequest(Drupal.settings.classroom_nid); //this will send request again and again;
      //}
      //$('.field-name-body').show();
      //var lock = 1;
   }, 3000);
   */


    //console.log(lc);

    $('.field-desk-add-more-wrapper').mouseup(function(){
      console.log('mouseup');
    });

  })

})(jQuery);
