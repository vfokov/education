<div class="dropdown b-topnav__icon box">
  <span class="dropbtn">&nbsp;</span>
  <div class="dropdown-content">
    <?php foreach($menu_items as $key => $menu_item):?>
      <?php if ($key == 0) {
        $class = 'first';
      } elseif ($key == count($menu_items) - 1) {
        $class = 'last';
      }else {$class = 'item';} ?>
    <a class="<?php print $class; ?>" href="/<?php print drupal_get_path_alias($menu_item['href']); ?>"><?php print $menu_item['title']; ?></a>
    <?php endforeach; ?>
  </div>
</div>

<!--
<ul class="b-topnav__dropdown-menu" style="height: 118px; overflow-y: scroll;">
  <ul class="hideshow" style="display: none;"></ul>
  <ul>
    <li><a href="https://www.tutoronline.ru/pupil/scheduledlessons">Запланированные уроки</a></li>
    <li><a href="https://www.tutoronline.ru/pupil/homeworks">Домашние задания</a></li>
    <li><a href="https://www.tutoronline.ru/pupil/sessions">История занятий</a></li>
    <li><a href="https://www.tutoronline.ru/pupil/billing">История баланса</a></li>
    <li><a href="https://www.tutoronline.ru/pupil/tutor-requests">Мои заявки</a></li>

    <li><a href="/repetitory?online=1">Репетиторы сейчас онлайн</a></li>
    <li><a href="https://www.tutoronline.ru/pupil/chat">Чат</a></li>
  </ul>

  <ul>
    <li><a href="https://www.tutoronline.ru/biblioteka">Библиотека</a></li>
    <li><a href="https://www.tutoronline.ru/faqs">Вопросы - ответы</a></li>
    <li><a href="https://www.tutoronline.ru/tests">Тесты</a></li>
  </ul>


  <ul>
    <li>
      <a href="/pupil/profile" id="ContentPlaceHolderDefault_MainNavigation_2_teacherProfileMenu_lnkProfile">Профиль</a>
    </li>
    <li>
      <a id="ContentPlaceHolderDefault_MainNavigation_2_teacherProfileMenu_exitBtn" href="javascript:__doPostBack('ctl00$ctl00$ctl00$ctl00$ContentPlaceHolderDefault$MainNavigation_2$teacherProfileMenu$exitBtn','')">Выйти</a>
    </li>
  </ul>
</ul>
-->
