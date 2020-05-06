(function ($) {
  $(document).ready(function($) {

    $("#front__logos").owlCarousel({
      items: 6,
      dots: true,
      nav: true,
      autoplay: true,
      loop: true,
      autoplayTimeout: 5000,
      autoplaySpeed: 2000,
      responsive: {
        320: {
          items: 1
        }
        , 480: {
          items: 2
        }
        , 768: {
          items: 4
        }
        , 992: {
          items: 6
        }
      }
    });

  });

})(jQuery);
