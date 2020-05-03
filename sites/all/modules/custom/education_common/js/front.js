(function ($) {
  $(document).ready(function($) {
    console.log('front');

    $('.e-form-tab').click(function(){
      if ($(this).hasClass('sign-up-lesson')) {
        $(this).addClass('m-active');
        $('.select-tutor').removeClass('m-active');

        $('.b-main__jumbotron-form__next_steps__group .sign-up-lesson-step').addClass('m-active');
        $('.b-main__jumbotron-form__next_steps__group .select-tutor-step').removeClass('m-active');

        $('#block-education-common-front-tutors-search .views-exposed-widget.views-submit-button .container-inline-date').show();
        var field_grade_subject = $('.front #block-education-common-front-tutors-search .views-widget-filter-field_grade_subject').width();
        field_grade_subject -= 150;
        $('.front #block-education-common-front-tutors-search .views-widget-filter-field_grade_subject').width(field_grade_subject);
      }
      if ($(this).hasClass('select-tutor')) {
        $(this).addClass('m-active');
        $('.sign-up-lesson').removeClass('m-active');

        $('.b-main__jumbotron-form__next_steps__group .sign-up-lesson-step').removeClass('m-active');
        $('.b-main__jumbotron-form__next_steps__group .select-tutor-step').addClass('m-active');

        $('#block-education-common-front-tutors-search .views-exposed-widget.views-submit-button .container-inline-date').hide();

        var field_grade_subject = $('.front #block-education-common-front-tutors-search .views-widget-filter-field_grade_subject').width();
        field_grade_subject += 150;
        $('.front #block-education-common-front-tutors-search .views-widget-filter-field_grade_subject').width(field_grade_subject);
      }
    })
  });

})(jQuery);
