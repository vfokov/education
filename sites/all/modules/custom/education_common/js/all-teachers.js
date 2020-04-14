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


    /*
    $('body').click(function(){
      $('.tooltip-close').click();
    });
    */

    /*
    $('#header .tooltip-bottom.tooltip.darkgrey').mouseover(function() {
    //$('#header .tooltip-bottom.tooltip.darkgrey').mouseout(function() {
    //$('#header .tooltip-bottom.tooltip.darkgrey').click(function() {
      console.log('m out');
      //$('.tooltip-close').click();
      //$(this).hide();



      //$(this).find('.tooltip-close').trigger('mousedown');

      var close_button = $(this).find('.tooltip-close');

      if ((close_button).length) {
        console.log('dsdadadsddddddlllll');
        $(close_button[0]).click();
        $(close_button[0]).trigger('click');
        $(close_button[0]).mousedown();
      }

      console.log($(this).find('.tooltip-close'));




    });
    */

    $('span.box').bind('click', function(){
      $('.tooltip-bottom.tooltip.darkgrey .tooltip-close').click();
    })

  });

})(jQuery);
