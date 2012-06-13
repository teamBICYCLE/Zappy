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
	  	
		socket.on('requestData', function(data) {
			self.emit('requestData', {socket: socket, cmd: data});
		});
		
		socket.on('requestDataBroadcast', function(data) {
			self.emit('requestDataBroadcast', {socket: socket, cmd: data});
		});
	        
	  });
}

module.exports = ClientConnection;
util.inherits(ClientConnection, ee);

	