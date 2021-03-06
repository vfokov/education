<?php

/**
 * @file
 * Bartik's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head, and body tags are not in this template. Instead
 * they can be found in the html.tpl.php template normally located in the
 * core/modules/system directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on
 *   the menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node entity, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['featured']: Items for the featured region.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['triptych_first']: Items for the first triptych.
 * - $page['triptych_middle']: Items for the middle triptych.
 * - $page['triptych_last']: Items for the last triptych.
 * - $page['footer_firstcolumn']: Items for the first footer column.
 * - $page['footer_secondcolumn']: Items for the second footer column.
 * - $page['footer_thirdcolumn']: Items for the third footer column.
 * - $page['footer_fourthcolumn']: Items for the fourth footer column.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see bartik_process_page()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<div id="page-wrapper"><div id="page">


    <div class="top">
      <div class="container">
        <div class="row">
          <div class="col-md-6">
            <div class="language">
              <ul class="flat-information">
                <li class="email"><a href="mailto:AlitStudios@gmail.com">mystudio@gmaill.com</a></li>
                <li class="phone"><a href="699999999">+61 9 9999 9999</a></li>
              </ul>
            </div><!-- /.language -->
          </div><!-- /.col-md-6 -->
          <div class="col-md-6">
            <div class="top-navigator">
              <ul>
               <!-- <li><a href="/">Register</a></li> -->
                <?php if (user_is_anonymous()) : ?>
               <!-- <li><a href="/user">Login</a></li> -->
                <?php endif; ?>
              </ul>
            </div><!-- /.top-navigator -->
          </div><!-- /.col-md-6 -->
        </div><!-- /.row -->
      </div><!-- /.container -->
    </div>


    <header id="header" role="banner" class="<?php print $secondary_menu ? 'with-secondary-menu': 'without-secondary-menu'; ?> header">
      <div class="header-wrap clearfix">
        <div class="container">
        <div class="row">

        <?php if (user_is_anonymous()): ?>
          <?php if ($secondary_menu): ?>
            <nav id="secondary-menu" role="navigation" class="navigation">
              <?php /*print theme('links__system_secondary_menu', array(
                'links' => $secondary_menu,
                'attributes' => array(
                  'id' => 'secondary-menu-links',
                  'class' => array('links', 'inline', 'clearfix'),
                ),
                'heading' => array(
                  'text' => t('Secondary menu'),
                  'level' => 'h2',
                  'class' => array('element-invisible'),
                ),
              ));*/ ?>
            </nav> <!-- /#secondary-menu -->
          <?php endif; ?>
        <?php endif; ?>


        <div class="col-md-2">
          <?php if ($logo): ?>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          <?php endif; ?>

          <?php if ($site_name || $site_slogan): ?>
            <div id="name-and-slogan"<?php if ($hide_site_name && $hide_site_slogan) { print ' class="element-invisible"'; } ?>>

              <?php if ($site_name): ?>
                <?php if ($title): ?>
                  <div id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
                    <strong>
                      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                    </strong>
                  </div>
                <?php else: /* Use h1 when the content title is empty */ ?>
                  <h1 id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                  </h1>
                <?php endif; ?>
              <?php endif; ?>

              <?php if ($site_slogan): ?>
                <div id="site-slogan"<?php if ($hide_site_slogan) { print ' class="element-invisible"'; } ?>>
                  <?php print $site_slogan; ?>
                </div>
              <?php endif; ?>

            </div> <!-- /#name-and-slogan -->
          <?php endif; ?>
        </div>

        <?php print render($page['header']); ?>

          <div class="col-md-10">
            <?php if ($main_menu): ?>
              <nav id="main-menu" role="navigation" class="navigation <?php print user_is_anonymous() ? 'shown' : ''; ?>">
                <?php print theme('links__system_main_menu', array(
                  'links' => $main_menu,
                  'attributes' => array(
                    'id' => 'main-menu-links',
                    'class' => array('links', 'clearfix'),
                  ),
                  'heading' => array(
                    'text' => t('Main menu'),
                    'level' => 'h2',
                    'class' => array('element-invisible'),
                  ),
                )); ?>
              </nav> <!-- /#main-menu -->
            <?php endif; ?>
          </div>

        <?php if ($show_user_menu): ?>
          <!--<div class="b-topnav__icon"><span>&nbsp;</span></div>-->
          <?php print $education_pupil_pupil_menu; ?>
        <?php endif; ?>

        <?php if ($show_tutor_menu): ?>
          <!--<div class="b-topnav__icon"><span>&nbsp;</span></div>-->
          <?php print $education_tutor_tutor_menu; ?>
        <?php endif; ?>

        <?php if ($show_anonymous_menu): ?>
          <!--<div class="b-topnav__icon"><span>&nbsp;</span></div>-->
          <?php print $education_common_anonymous_menu; ?>
        <?php endif; ?>

      </div>
      </div>
      </div>
    </header> <!-- /.section, /#header -->

    <?php if ($messages): ?>
      <div id="messages"><div class="section clearfix">
          <?php print $messages; ?>
        </div></div> <!-- /.section, /#messages -->
    <?php endif; ?>

    <?php if ($page['featured']): ?>
      <div id="featured"><div class="section clearfix">
          <?php print render($page['featured']); ?>
        </div></div> <!-- /.section, /#featured -->
    <?php endif; ?>

    <div id="main-wrapper" class="clearfix"><div id="main" role="main" class="clearfix">

        <?php print $breadcrumb; ?>

        <div id="content" class="column"><div class="section">
            <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
            <a id="main-content"></a>
            <?php print render($title_prefix); ?>
            <?php if ($title): ?>
              <h1 class="title" id="page-title">
                <?php print $title; ?>
              </h1>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php if ($tabs && $show_tabs): ?>
              <div class="tabs">
                <?php print render($tabs); ?>
              </div>
            <?php endif; ?>
            <?php print render($page['help']); ?>
            <?php if ($action_links): ?>
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
            <?php endif; ?>
            <?php print render($page['content']); ?>
            <?php print $feed_icons; ?>

          </div></div> <!-- /.section, /#content -->

        <?php if ($page['sidebar_first']): ?>
          <div id="sidebar-first" class="column sidebar"><div class="section">
              <?php print render($page['sidebar_first']); ?>
            </div></div> <!-- /.section, /#sidebar-first -->
        <?php endif; ?>

        <?php if ($page['sidebar_second']): ?>
          <div id="sidebar-second" class="column sidebar"><div class="section">
              <?php print render($page['sidebar_second']); ?>
            </div></div> <!-- /.section, /#sidebar-second -->
        <?php endif; ?>

      </div></div> <!-- /#main, /#main-wrapper -->

    <?php if ($page['triptych_first'] || $page['triptych_middle'] || $page['triptych_last']): ?>
      <div id="triptych-wrapper"><div id="triptych" class="clearfix">
          <?php print render($page['triptych_first']); ?>
          <?php print render($page['triptych_middle']); ?>
          <?php print render($page['triptych_last']); ?>
        </div></div> <!-- /#triptych, /#triptych-wrapper -->
    <?php endif; ?>

    <div id="footer-wrapper">
      <div class="container">

        <div class="row">
          <div class="col-md-12 text-center">
            <div class="widget widget-text">
              <img class="logo-footer" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </div>
          </div><!-- /.col-md-12 -->
        </div>

        <div class="row">
          <div class="col-md-12 text-center">
            <div class="sidebar-inner-footer">
              <div class="widget widget-infomation">
                <ul class="flat-information">
                  <li class="email"><a href="mailto:education@gmail.com">education@gmaill.com</a></li>
                  <li class="phone"><a href="699999999">+69 9 9999 9999</a></li>
                  <li class="address">999 King Street, Toronto 9999 Canada</li>

                </ul>
              </div>
            </div><!-- /.sidebar-inner-footer -->
          </div><!-- /.col-md-12 -->
        </div>

        <?php if ($page['footer_firstcolumn'] || $page['footer_secondcolumn'] || $page['footer_thirdcolumn'] || $page['footer_fourthcolumn']): ?>
          <div id="footer-columns" class="clearfix">
            <?php print render($page['footer_firstcolumn']); ?>
            <?php print render($page['footer_secondcolumn']); ?>
            <?php print render($page['footer_thirdcolumn']); ?>
            <?php print render($page['footer_fourthcolumn']); ?>
          </div> <!-- /#footer-columns -->
        <?php endif; ?>

        <?php if ($page['footer']): ?>
          <footer id="footer" role="contentinfo" class="clearfix">
            <?php print render($page['footer']); ?>
          </footer> <!-- /#footer -->
        <?php endif; ?>

      </div>
    </div> <!-- /.section, /#footer-wrapper -->


    <!-- BOTTOM -->
    <div class="bottom">
      <div class="container">
        <div class="row">
          <div class="col-md-12">
            <div class="line-top"></div>
          </div>
        </div>
        <div class="row">
          <div class="container-bottom">
            <div class="col-md-6">
              <div class="copyright">
                <!--
                <p>© Copyright <a href="#">Alitstudio</a> 2015. All Rights Reserved.</p>
                -->
              </div>
            </div><!-- /.col-md-6 -->

            <div class="col-md-6">
              <ul class="flat-socials text-right">
                <li class="facebook">
                  <a href="#"><i class="fa fa-facebook"></i></a>
                </li>
                <li class="twitter">
                  <a href="#"><i class="fa fa-twitter"></i></a>
                </li>
                <li class="instagram">
                  <a href="#"><i class="fa fa-instagram"></i></a>
                </li>
                <li class="linkedin">
                  <a href="#"><i class="fa fa-linkedin"></i></a>
                </li>
              </ul>
            </div><!-- /.col-md-6 -->
          </div><!-- /.container-bottom -->
        </div><!-- /.row -->
      </div><!-- /.container -->
    </div>
    <!-- END BOTTOM -->


    <div id="popup__overlay" class="popup__overlay" style="display: none;"></div>

    <!--------------------------------------->
    <?php if (isset($quick_order_form)): ?>
      <?php print $quick_order_form; ?>
    <?php endif; ?>

    <?php if (isset($lesson_date_close_form)): ?>
      <?php print $lesson_date_close_form; ?>
    <?php endif; ?>

    <?php if (isset($lesson_date_disable_form)): ?>
      <?php print $lesson_date_disable_form; ?>
    <?php endif; ?>

    <?php if (isset($lesson_date_enable_form)): ?>
      <?php print $lesson_date_enable_form; ?>
    <?php endif; ?>

    <?php if (isset($lesson_pay_form)): ?>
      <?php print $lesson_pay_form; ?>
    <?php endif; ?>

    <?php if (isset($form_balance_recharge)): ?>
      <?php print $form_balance_recharge; ?>
    <?php endif; ?>
    <!--------------------------------------->

  </div></div> <!-- /#page, /#page-wrapper -->
