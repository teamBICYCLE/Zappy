/**
 * @author sylvia_r
 */

/* Najim Production Zappy Connection */

var buffer = '',
	net = require('net'),
	cache = require('./cache.js'),
	parsing = require('./bufferParse.js'),
	util = require('util'),
	ee = require('events').EventEmitter;
	
var ZappyConnection = function (ip, port) {
	
	var socket = new net.createConnection(port, ip);
	var self = this;
	
	socket.on('connect', function(){
		console.log("CONNECTED !!");
		socket.write("GRAPHIC\n");
	});
	
	socket.on('data', function(data){
		buffer += data;
		if (buffer.charCodeAt(buffer.length - 1) == 10)
		{
			parsing.feed(buffer, cache);
			if (cache.isWhole())
				self.emit('cacheWhole');
			buffer = '';
		}
	});
	
	socket.on('error', function(){
		console.log("Error : can't connect to server "+ ip + ":" + port);
		process.exit(0);
	});
	
	ZappyConnection.prototype.getCache = function () {
		return cache;
	};
	
	ZappyConnection.prototype.getSocket = function () {
		return socket;
	};
}

module.exports = ZappyConnection;
util.inherits(ZappyConnection, ee);
