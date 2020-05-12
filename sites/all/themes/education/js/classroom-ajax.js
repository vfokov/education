(function ($) {

  Drupal.ajax.prototype.commands.reloadPage = function() {
    window.location.reload();
  };

})(jQuery);
