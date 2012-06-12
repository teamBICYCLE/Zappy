/**
 * @author sylvia_r
 */

/* Najim Production Client Connection */

var express = require('express'),
	io = require('socket.io'),
	app = express.createServer();

	io = io.listen(app).set('log level', 1);
	app.listen(24542);
	
var ClientConnection = function() {
	var client = io
	  .sockets
	  .on('connection', function(socket) {
	  	
		socket.on('requestData', function(data) {
			socket.emit('requestDataDone', {data_: "result : " + socket.id});
		});
		
		socket.on('requestDataBroadcast', function(data) {
			socket.broadcast.emit('requestDataBroadcastDone', {data_: "result : " + socket.id});
		});
	        
	  });
}


	