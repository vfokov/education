<?php
$localsocket = 'tcp://127.0.0.1:1234';
$user = 'tester01';
$message = 'test';

// соединяемся с локальным tcp-сервером


//var_dump($instance);

/*
if (isset($_POST['user'])) {
  $message = 'dssafdafs message';
  $instance = stream_socket_client($localsocket);
  $user = $_POST['user'];
  fwrite($instance, json_encode(['user' => $user, 'message' => $message]) . "\n");
  echo 'dfsffsdfsdfdsfsdfsd ' . $_POST['user'];
}
*/

//else {
// отправляем сообщение
  ///////$message = $_POST['message'];
  ////////$user = $_POST['user'];
  $instance = stream_socket_client($localsocket);
  fwrite($instance, json_encode(['user' => $user, 'message' => $message]) . "\n");
//}
