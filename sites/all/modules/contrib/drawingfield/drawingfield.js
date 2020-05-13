/**
 * @file
 * Canvas js integration.
 */

(function ($) {

  // send changes to server via ajax
  function sendChangesToServer(text, classroom_nid) {
    window.setTimeout(function () {
      //$('.info').addClass('show');
      //$('.info').text('Saving...');
      console.log(text);
      $.ajax({
        type: 'POST',
        url: '/save-onchange',
        //processData: false,
        ////dataType: "html",
        //processData: false,

        //processData: false,
        //contentType: 'application/json',
        //data: JSON.stringify(data),

        data: {
          //text: JSON.stringify(text),
          text: text,
          nid: classroom_nid,
        },
        success: function (msg) {
          var lock = 0;
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

  Drupal.behaviors.drawingfield = {
    attach: function(context, settings) {
      settings = Drupal.settings.drawingfield;
      var imageSize = {width: settings.width, height: settings.height};
      console.log(imageSize);

      //console.log(Drupal.settings.classroom_nid);

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

        sendChangesToServer($("#" + paintId).val(), Drupal.settings.classroom_nid);

        console.log(jsonBase64);
      });

      //lc.on('lc-pointerup', function() {
      lc.on('pointerup', function() { //http://literallycanvas.com/api/events.html
        console.log('p_UP');

        json = lc.getSnapshotJSON();
        var base64 = lc.getImage().toDataURL();
        var jsonBase64 = json + 'JSON' + base64;
        //paintId = $(".form-group").find("input.output").attr('id');
        //$("#" + paintId).val(jsonBase64);

        //console.log(jsonBase64);

        //sendChangesToServer(jsonBase64, Drupal.settings.classroom_nid);

      });

    }
  }
})(jQuery);
