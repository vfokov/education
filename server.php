<?php
require_once __DIR__ . '/vendor/autoload.php';
use Workerman\Worker;

// массив для связи соединения пользователя и необходимого нам параметра
$users = [];

// создаём ws-сервер, к которому будут подключаться все наши пользователи
$ws_worker = new Worker("websocket://0.0.0.0:8000");



/*
$ws_worker->onConnect = function($connection) use(&$connections)
{
  // Эта функция выполняется при подключении пользователя к WebSocket-серверу
  $connection->onWebSocketConnect = function($connection) use (&$connections) {

  };
};
*/


// создаём обработчик, который будет выполняться при запуске ws-сервера
$ws_worker->onWorkerStart = function() use (&$users)
{
    // создаём локальный tcp-сервер, чтобы отправлять на него сообщения из кода нашего сайта
    $inner_tcp_worker = new Worker("tcp://127.0.0.1:1234");
    // создаём обработчик сообщений, который будет срабатывать,
    // когда на локальный tcp-сокет приходит сообщение
    $inner_tcp_worker->onMessage = function($connection, $data) use (&$users) {
        $data = json_decode($data);



        // отправляем сообщение пользователю по userId
        if (isset($users[$data->user])) {
          //$log = date('d.m.Y H:i:s') . "\n Check send: ";
          //file_put_contents('check_send.log', $log . "\n", FILE_APPEND | LOCK_EX);

            $webconnection = $users[$data->user];
            $webconnection->send($data->message);

        }
    };
    $inner_tcp_worker->listen();
};

$ws_worker->onConnect = function($connection) use (&$users)
{
    $connection->onWebSocketConnect = function($connection) use (&$users)
    {
        // при подключении нового пользователя сохраняем get-параметр, который же сами и передали со страницы сайта
        $users[$_GET['user']] = $connection;
        // вместо get-параметра можно также использовать параметр из cookie, например $_COOKIE['PHPSESSID']
    };
};

$ws_worker->onClose = function($connection) use(&$users)
{
    // удаляем параметр при отключении пользователя
    $user = array_search($connection, $users);
    unset($users[$user]);
};


////////////////////////////////

/*
$ws_worker->onMessage = function($connection, $message) use (&$users) {
  // распаковываем json
  $messageData = json_decode($message, true);

  foreach ($users as $c) {
    $c->send(json_encode($messageData));
  }

  //$connection->send(json_encode($messageData));
  //$users->send(json_encode($messageData));
};
*/



// Run worker
Worker::runAll();
