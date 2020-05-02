"use strict";

var ge = function (elName) {return document.getElementById(elName)},
  gc = function (elName) {return document.getElementsByClassName(elName)},
  hardHide = function (elName) {ge(elName).style.display = "none"},
  hardShow = function (elName) {ge(elName).style.display = "block"},
  html = function(elName,val) {ge(elName).innerHTML = val},
  htmlEl = function(el,val) {el.innerHTML = val},

  clickEvent = ((document.ontouchstart!==null) ? 'click':'touchstart'),

  device = function(){
    var w = Math.max(document.documentElement.clientWidth, window.innerWidth || 0);
    if(w>=992){
      return "desctop";
    }else if(w<992 && w>768){
      return "ipad";
    }else if(w<768){
      return "mobile";
    }
  };


if (!Element.prototype.remove) {
  Element.prototype.remove = function remove() {
    if (this.parentNode) {
      this.parentNode.removeChild(this);
    }
  };
}






// contact.js

// feedback.js
// form.js
(function(){

  var count = gc("form__count");
  var countArr = [];

  var CountBlock = function(el){
    var _this = this;
    this.el = el;
    this.num = 1;
    this.input = el.getElementsByClassName("form__count-input")[0];
    if(this.input.value){
      this.num = this.input.value;
    }else{
      this.input.value = 1;
    }
    this.plus = el.getElementsByClassName("form__count-btn_plus")[0];
    this.minus = el.getElementsByClassName("form__count-btn_minus")[0];

    this.minus.onclick = function(){
      if(_this.num<=1){return false}
      _this.input.value = --_this.num;
      return false;
    }
    this.plus.onclick = function(){
      _this.input.value = ++_this.num;
      return false;
    }
    this.input.onkeypress = function(){
      var charCode = (event.which) ? event.which : event.keyCode
      if (charCode > 31 && (charCode < 48 || charCode > 57)){
        return false;
      }
      return true;
    }
    this.input.onkeyup = function(){ _this.num = this.value; }
  };

  if(count.length){
    for(var i = 0; i<count.length; i++){
      countArr.push(new CountBlock(count[i]));
    }
  }


})();

(function(){



})();
// main.js
var mainBanner = function(){

};

document.addEventListener("DOMContentLoaded", mainBanner, false);


function getCookie(name) {
  var matches = document.cookie.match(new RegExp(
    "(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"
  ));
  return matches ? decodeURIComponent(matches[1]) : undefined;
}
function setCookie(name, value, options) {
  options = options || {};
  var expires = options.expires;

  if(typeof expires == "number" && expires){
    var d = new Date();
    d.setTime(d.getTime() + expires * 1000);
    expires = options.expires = d;
  }
  if(expires && expires.toUTCString){
    options.expires = expires.toUTCString();
  }

  value = encodeURIComponent(value);
  var updatedCookie = name + "=" + value;

  for(var propName in options){
    updatedCookie += "; " + propName;
    var propValue = options[propName];
    if(propValue !== true){
      updatedCookie += "=" + propValue;
    }
  }
  document.cookie = updatedCookie;
}


var old18 = function(){

};
//document.addEventListener("DOMContentLoaded", old18, false);

// popup.js



// (function(){ })();

var MLpopupObj = {};
function initPopup(){
  "use strict";
  var popupLinkArr = gc("popup__link");
  MLpopupObj.popupCur = "";
  MLpopupObj.overlay = ge("popup__overlay");

  function popupOpen(){
    arguments[0].preventDefault();
    var name = this.getAttribute("data-popup");
    MLpopupObj[name].open();
  }

  for(var i=0;i<popupLinkArr.length;i++){
    var popupName = popupLinkArr[i].getAttribute("data-popup");
    var popupType = popupLinkArr[i].getAttribute("data-type");
    var cookieCheck = popupLinkArr[i].getAttribute("data-cookiecheck");
    var overlayStop = popupLinkArr[i].getAttribute("data-overlaystop");
    if(!!popupType && popupType == "youtube"){
      var link = popupLinkArr[i].getAttribute("data-link");
    }
    MLpopupObj[popupName] = new MLpopup(popupName, {"type": popupType, "link": link, "cookieCheck": cookieCheck, "overlayStop": overlayStop});
    popupLinkArr[i].addEventListener("click", popupOpen);
  }
  function closePopup(){
    if(!!MLpopupObj.popupCur){
      MLpopupObj[MLpopupObj.popupCur].close();
    }
  }
  function closeOverlay(){
    if(MLpopupObj[MLpopupObj.popupCur].overlayStop){
      return false;
    }
    closePopup();
  }
  function closePopupX(){
    // if(MLpopupObj[MLpopupObj.popupCur].cookieCheck){
    // 	setCookie(MLpopupObj.popupCur,"true",{expires: 10000000});
    // }
    closePopup();
  }
  MLpopupObj.overlay.addEventListener("click", closeOverlay);
  var hide = function(el){
    el.classList.remove('popup_show');
    setTimeout(function(){
      el.style.display="none";
    },200);
  };
  var show = function(el){
    el.style.display="block";
    setTimeout(function(){
      el.classList.add("popup_show");
    },100);
  };


  document.addEventListener('keydown',function(e){
    if(e.which==27){
      closePopup()
    }
  }, false);

  function MLpopup(element, options) {
    this.popupName = element;
    this.popup = ge(element);

    if(options.type == "youtube"){
      this.type = "youtube";
      this.content = '<iframe width="630" height="390" src="'+options.link+'" frameborder="0" allowfullscreen></iframe>';
    }else{
      this.closeEl = this.popup.getElementsByClassName("popup__close")[0];
      if(this.closeEl){
        this.closeEl.addEventListener("click", closePopupX, false);
      }
    }
    if(options.cookieCheck){
      this.cookieCheck = true;
      setTimeout(function(){
        if(getCookie(element) != "true"){
          MLpopupObj[element].open();
        }
      },100);
    }
    if(options.overlayStop == "true"){
      this.overlayStop = true;
    }else{
      this.overlayStop = false;
    }
  }

  MLpopup.prototype.open = function() {
    MLpopupObj.popupCur = this.popupName;
    show(this.popup);
    show(MLpopupObj.overlay);
    if(this.type == "youtube"){
      this.popup.innerHTML = this.content;
    }
  };

  MLpopup.prototype.close = function() {
    hide(this.popup);
    hide(MLpopupObj.overlay);
    if(this.type == "youtube"){
      this.popup.innerHTML = "";
    }
    MLpopupObj.popupCur = "";
  };
};


document.addEventListener("DOMContentLoaded", initPopup, false);






var initInfo = function(){
  var infoArr = gc("info__close");
  for(var i=0; i<infoArr.length; i++){
    infoArr[i].addEventListener("click", function(){
      var infoEl = this.parentNode;
      infoEl.parentNode.removeChild(infoEl);
    });
  }
}
document.addEventListener("DOMContentLoaded", initInfo, false);
// product.js

function getOffsetRect(elem) {
  var box = elem.getBoundingClientRect();
  var body = document.body;
  var docElem = document.documentElement;
  var scrollTop = window.pageYOffset || docElem.scrollTop || body.scrollTop;
  var scrollLeft = window.pageXOffset || docElem.scrollLeft || body.scrollLeft;

  var clientTop = docElem.clientTop || body.clientTop || 0;
  var clientLeft = docElem.clientLeft || body.clientLeft || 0;

  var top  = box.top +  scrollTop - clientTop;
  var left = box.left + scrollLeft - clientLeft;

  return { top: Math.round(top), left: Math.round(left) }
}


(function(){





  //document.addEventListener("DOMContentLoaded", Zoom.init, false);

})();



(function(){

})();

(function(){

})();


(function ($) {

  //
  Drupal.behaviors.book_button = {
    attach: function (context, settings) {
      $('.btn.product__card-fast').bind('click', function(){
        $('#popup__overlay').addClass('popup_show');
        var product_id = $(this).attr('data-product-id');
        var product_price = $(this).attr('data-product-price');
        //<a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="1" data-date="2020-04-08 23:00:00" data-teacher-uid="3">Book a lesson</a>
        var teacher_uid = $(this).attr('data-teacher-uid');
        var date = $(this).attr('data-date');
        $('input[name="product_id"]').val(product_id);
        $('input[name="product_price"]').val(product_price);
        $('input[name="teacher_uid"]').val(teacher_uid);
        $('input[name="lesson_date"]').val(date);

        //PP TRY
        var amount_value = product_price.substr(1);
        //console.log('pp price' + amount_value);

        //if (!paypal.Buttons)

        paypal.Buttons({
          createOrder: function(data, actions) {
            // This function sets up the details of the transaction, including the amount and line item details.
            return actions.order.create({
              purchase_units: [{
                amount: {
                  value: amount_value
                }
              }]
            });
          },
          onApprove: function(data, actions) {
            // This function captures the funds from the transaction.
            return actions.order.capture().then(function(details) {
              // This function shows a transaction success message to your buyer.
              //TODO чтобы делать заказ paid
              //alert('Transaction completed by ' + details.payer.name.given_name);

              $('input[name="is_paid"]').val(1);
              $('#edit-submit').click();
              $('#edit-submit').trigger('click');
              $('#edit-submit').mousedown();

              window.setTimeout(
                function () {
                  //$('#edit-submit').click();
                  $('.form-submit').click();
                }, 200);


            });
          }
        }).render('#paypal-button-container');

        // PP


      });

      $('.btn.lesson_date_close').bind('click', function(){
        $('#popup__overlay').addClass('popup_show');
        var product_id = $(this).attr('data-product-id');
        //<a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="1" data-date="2020-04-08 23:00:00" data-teacher-uid="3">Book a lesson</a>
        var teacher_uid = $(this).attr('data-teacher-uid');
        var date = $(this).attr('data-date');
        var lesson_nid = $(this).attr('data-lesson-nid');
        $('input[name="close_product_id"]').val(product_id);
        $('input[name="close_teacher_uid"]').val(teacher_uid);
        $('input[name="close_lesson_date"]').val(date);
        $('input[name="close_lesson_nid"]').val(lesson_nid);
      });

      // Disable popup form
      $('.btn.lesson_date_disable').bind('click', function(){
        $('#popup__overlay').addClass('popup_show');
        var product_id = $(this).attr('data-product-id');
        //<a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="1" data-date="2020-04-08 23:00:00" data-teacher-uid="3">Book a lesson</a>
        var teacher_uid = $(this).attr('data-teacher-uid');
        var date = $(this).attr('data-date');
        var lesson_nid = $(this).attr('data-lesson-nid');
        $('input[name="disable_product_id"]').val(product_id);
        $('input[name="disable_teacher_uid"]').val(teacher_uid);
        $('input[name="disable_lesson_date"]').val(date);
        $('input[name="disable_lesson_nid"]').val(lesson_nid);
      });
      // Enable popup form
      // TODO
      $('.btn.lesson_date_enable').bind('click', function(){
        $('#popup__overlay').addClass('popup_show');
        //var product_id = $(this).attr('data-product-id');
        //<a href="#" class="btn product__card-fast popup__link" data-popup="fast_cart" data-product-id="1" data-date="2020-04-08 23:00:00" data-teacher-uid="3">Book a lesson</a>
        var teacher_uid = $(this).attr('data-teacher-uid');
        var date = $(this).attr('data-date');
        //var lesson_nid = $(this).attr('data-lesson-nid');
        //$('input[name="enable_product_id"]').val(product_id);
        $('input[name="enable_teacher_uid"]').val(teacher_uid);
        //$('input[name="enable_lesson_date"]').val(date);
        $('input[name="enable_lesson_date[date]"]').val(date);
        //$('input[name="enable_time[time]"]').val('00:00');
        //$('input[name="enable_lesson_nid"]').val(lesson_nid);
      });


      $('.popup__close').click(function(){
        $('.popup_show').removeClass('popup_show');
        $('#popup__overlay').removeClass('mlpopup__show');

        $('#paypal-button-container').html('');

        if ($(this).hasClass('close_reload')) {
          window.setTimeout(
            function () {
              window.location.reload();
            }, 500);
        }

      });

      $('.form__submit.cancel').click(function(e){
        e.preventDefault();
        $('.popup_show').removeClass('popup_show');
        $('#popup__overlay').removeClass('mlpopup__show');
        $('#popup__overlay').hide();
      });


      $('#views-exposed-form-lesson-calendar-page-1 .form-item select').bind('change', function(){
        console.log('selected');
        $('.views-submit-button input').trigger('click');
      })

    }

  };

  $(document).ready(function($) {
    console.log('bokk sdafaf');



  });

})(jQuery);
