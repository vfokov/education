<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?><!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"
<?php print $rdf_namespaces; ?>>

<head>
  <?php print $head; ?>
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <meta name="MobileOptimized" content="width" />
    <meta name="HandheldFriendly" content="true" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta http-equiv="cleartype" content="on" />
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!--[if (gte IE 6)&(lte IE 8)]>
    <script src="<?php print $base_path . $path_to_resbartik; ?>/js/selectivizr-min.js"></script>
  <![endif]-->
  <!--[if lt IE 9]>
    <script src="<?php print $base_path . $path_to_resbartik; ?>/js/html5-respond.js"></script>
  <![endif]-->
</head>
<body class="<?php print $classes; ?> header-sticky" <?php print $attributes;?>>

<script
  src="https://www.paypal.com/sdk/js?client-id=AUV2r-z_ApYr_NFkZBYrSaqPc9eeh88nJUZTxi47OClr38tzMgcvcGRhnHmq_S9lz87vo94P9vrFCM9i"> // Required. Replace SB_CLIENT_ID with your sandbox client ID.
</script>

  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
<div class="boxed">
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</div>

  <script type="text/javascript" src="/sites/all/modules/custom/education_common/js/tooltip.js"></script>

<!-- Javascript -->

<a class="go-top show">
  <i class="fa fa-angle-up"></i>
</a>

<script type="text/javascript" src="/sites/all/themes/education/javascript/bootstrap.min.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.easing.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/imagesloaded.min.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.isotope.min.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/owl.carousel.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.mb.YTPlayer.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery-waypoints.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.flexslider-min.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.cookie.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.fitvids.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery-validate.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.magnific-popup.min.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/parallax.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.countdown.js"></script>
<!--<script type="text/javascript" src="/sites/all/themes/education/javascript/switcher.js"></script>-->
<script type="text/javascript" src="/sites/all/themes/education/javascript/jquery.sticky.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/smoothscroll.js"></script>
<script type="text/javascript" src="/sites/all/themes/education/javascript/main.js"></script>

<!-- Start of LiveChat (www.livechatinc.com) code -->
<script type="text/javascript">
  window.__lc = window.__lc || {};
  window.__lc.license = 11906739;
  (function() {
    var lc = document.createElement('script'); lc.type = 'text/javascript'; lc.async = true;
    lc.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + 'cdn.livechatinc.com/tracking.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(lc, s);
  })();
</script>
<noscript>
  <a href="https://www.livechatinc.com/chat-with/11906739/" rel="nofollow">Chat with us</a>,
  powered by <a href="https://www.livechatinc.com/?welcome" rel="noopener nofollow" target="_blank">LiveChat</a>
</noscript>
<!-- End of LiveChat code -->

</body>
</html>
