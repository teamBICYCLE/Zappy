/**
 * @author sylvia_r
 */

/* Najim Production Client Connection */

var express = require('express'),
	io = require('socket.io'),
	app = express.createServer(),
	util = require('util'),
	ee = require('events').EventEmitter;

	io = io.listen(app).set('log level', 1);
	app.listen(24542);
	
var ClientConnection = function() {
	
	var self = this;
	
	var client = io
	  .sockets
	  .on('connection', function(socket) {
	  	
		socket.on('requestData', function(obj) {
			self.emit('requestData', {socket: socket, cmd: obj.cmd});
		});
		
		socket.on('requestDataBroadcast', function(obj) {
			if (lastTimestamp != obj.timestamp)
			{
				self.emit('requestDataBroadcast', {socket: socket, cmd: obj.data});
				lastTimestamp = obj.timestamp;
			}
		});
	        
	  });
}

module.exports = ClientConnection;
util.inherits(ClientConnection, ee);

	