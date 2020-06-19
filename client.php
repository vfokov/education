<?php
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
    <script>

      (function ($) {
        var user_id = Math.random().toString(36).substr(2, 5);




      ///////////ws = new WebSocket("wss://echo.websocket.org/");
        //ws = new WebSocket("ws://127.0.0.1:8000/?user=tester01");
        //ws = new WebSocket("wss://127.0.0.1:8000/?user=tester01");
        //ws = new WebSocket("wss://158.69.24.72:8000/?user=tester01");
        //ws = new WebSocket("wss://158.69.24.72:8000/?user=tester01");   // https://158.69.24.72:8443/
        //ws = new WebSocket("ws://localhost/?user=tester01");   // https://158.69.24.72:8443/
        //ws = new Worker('websocket://0.0.0.0:8000', $context);
        //ws = new Worker('websocket://0.0.0.0:8000');
        //ws = new WebSocket("ws://education.designseonweb.com:8000/?user=tester01");
        //ws = new WebSocket("wss://education.designseonweb.com:8000/?user=tester01");
        //ws = new WebSocket("wss://education.designseonweb.com:8000");
        //console.log(ws);
        //ws.onmessage = function(evt) {alert(evt.data);};
        //ws.onmessage = function(evt) {console.log(evt.data);};


        // Tell the server this is client 1 (swap for client 2 of course)
        function Send(user_id, mess) {
          // Tell the server we want to send something to the other client

          console.log(user_id);

          var data = {user: user_id, message: mess};
          $.ajax({
            type: 'POST',
            url: '/send.php',
            data: data,
            success: function (msg) {
              console.log(msg);
              console.log('succ');
            },
            error: function () {
              console.log('err');
            }
          });

          /*
          websocket.send(JSON.stringify({
            data
          }));
          */

        }


        $(document).ready(function($) {

          var user_to_send = '';

          ws = new WebSocket("ws://127.0.0.1:8000/?user=tester01");
          //ws = new WebSocket("ws://127.0.0.1:8000/?user=tester" + user_id);
          console.log(ws);
          //ws.onmessage = function(evt) {alert(evt.data);};
          ws.onmessage = function(evt) {
            console.log(evt.data);

            //if (evt.data.message == 'init') {
              user_to_send = evt.data.user;
            //}
          };

          ws.onopen = function(event) {
            ws.send("соединение с сервером установлено");
            // отправляем определенные данные в формате JSON
            //var data = {'test':'test'}
            var data = {user: "tester" + user_id, message: 'init'};
            console.log('open');
            console.log(data);
            //var data = 'test data';
            //ws.send(JSON.stringify(data));
            Send("tester" + user_id, 'some message');
          };

          /*
          ws.send(JSON.stringify({
            id: "client1"
          }));
          */



          $('.test-send').click(function(){
            Send("tester" + user_id, 'some message');

          })
        })

      })(jQuery);
    </script>
</head>

<body>
  <div class="test-socket">Test socket</div>

  <a class="test-send" href="#" >Test send</a>

</body>

</html>
