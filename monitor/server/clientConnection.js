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
	
var ClientConnection = function(port) {
	
	app.listen(port);
	var self = this;
	
	var client = io.sockets;
	
	client.on('connection', function(socket) {
		
		self.emit('firstConnection', {socket: socket});
	  	
		socket.on('requestData', function(obj) {
			self.emit('requestData', {socket: socket, cmd: obj.cmd});
		});
		
	});
	  
	ClientConnection.prototype.getClientSocket = function() {
		return client;
	}
}

module.exports = ClientConnection;
util.inherits(ClientConnection, ee);

	