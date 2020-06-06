(function ($) {
  /*
  function myWindow2(e) {// создать iframe и добавить его после кнопки
    if (e.nextSibling.nodeName.toLowerCase() != "iframe") {// если после кнопки нет iframe
      var iframe = document.createElement('iframe');
      iframe.setAttribute('src', 'https://talky.io/educt_'+ classroom_nid + '#size-window"');
      iframe.setAttribute('height', '200');
      //e.parentNode.insertBefore(iframe, e.nextSibling);
      //e.parentNode.insertBefore(iframe, e.nextSibling);
      //$('#video-content').insertAfter(iframe);
      $(iframe).insertAfter('#video-content');
    }
  }

  function myWindow211(classroom_nid) {

    var iframe = document.createElement('iframe');
    iframe.setAttribute('src', 'https://talky.io/educt_'+ classroom_nid + '#size-window');
    iframe.setAttribute('height', '200');
    e.parentNode.insertBefore(iframe, e.nextSibling);
  }
  */

  function OpenVideo(classroom_nid){
    var height = 500;
    var width = 550;
    var top = 0;
    var left = screen.availWidth-width;
    window.open(
      //'https://meet.jit.si/classroom' + classroom_nid,
      'https://talky.io/educt_'+ classroom_nid + '#size-window' ,
      '',
      'location=yes,height='+height+',width='+width+',top='+top+',left='+left+',scrollbars=yes,status=yes'
    );
  };

  Drupal.behaviors.classroomVideoLink = {
    attach: function(context, settings) {

    }
  };

  $(document).ready(function($) {

    $('.classroom-video-link').click(function(e){
      e.preventDefault();
      var classroom_nid = Drupal.settings.classroom_nid;
      OpenVideo(classroom_nid);
    });


   var classroom_nid = Drupal.settings.classroom_nid;
    OpenVideo(classroom_nid);
    //$('.video-frame').attr('src', 'https://talky.io/educt_'+ classroom_nid);
  });
})(jQuery);
