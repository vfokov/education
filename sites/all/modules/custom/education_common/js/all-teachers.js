(function ($) {
  $(document).ready(function($) {
    console.log('tc');
    //btn product__card-fast popup__link

    /*
    $('nav.teachers-nav li').hover(
      function() {
        $('ul', this).stop().slideDown(200);
      },
      function() {
        $('ul', this).stop().slideUp(200);
      }
    );
    */

    $('span.box').click(function(){
      $('.calendar-agenda-items.single-day').css('position', 'relative').css('z-index', '0');
      $(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().css('z-index', '1');
    });

    $('.tooltip-close.icon.icon_cross').click(function(){
      $('.calendar-agenda-items.single-day').css('position', 'static').css('z-index', '1');
      //$(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().css('z-index', '1');
    });

  });

})(jQuery);
