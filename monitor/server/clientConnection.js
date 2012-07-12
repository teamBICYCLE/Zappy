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
	
	//console.log(client);
	  client.on('connection', function(socket) {
	  	
	  	self.emit('firstConnection', {socket: socket});
	  	
		socket.on('requestData', function(obj) {
			self.emit('requestData', {socket: socket, cmd: obj.cmd});
		});
		
		// socket.on('requestDataBroadcast', function(obj) {
			// if (lastTimestamp != obj.timestamp)
			// {
				// self.emit('requestDataBroadcast', {socket: socket, cmd: obj.data});
				// lastTimestamp = obj.timestamp;
			// }
		// });
	        
	  });
	  
	  ClientConnection.prototype.getClientSocket = function() {
		return client;
	}
}

module.exports = ClientConnection;
util.inherits(ClientConnection, ee);

	