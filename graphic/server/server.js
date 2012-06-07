var express = require('express');
var io = require('socket.io');
var net = require('net');
var cache = require('./cache.js');
var parsing = require('./bufferParse.js');
var app = express.createServer();

io = io.listen(app);
app.listen(4242);

if (process.argv.length >= 3)
{
	var ip = process.argv[2];
	var port = "24542";
	var buffer = '';
	
	if (process.argv.length >= 4)
		port = process.argv[3];
	
	var socketZappy = new net.createConnection(port, ip);
	
	socketZappy.on('connect', function(){
		console.log("CONNECTED !!");
		socketZappy.write("GRAPHIC\n");
	});
	
	socketZappy.on('data', function(data){
		buffer += data;
		if (buffer.charCodeAt(buffer.length - 1) == 10)
		{
			parsing.feed(buffer, cache);
			cache.dump();
			buffer = '';
		}
	});
	
	socketZappy.on('error', function(){
		console.log("Error : can't connect to server "+ ip + ":" + port);
		process.exit(0);
	});
	
}
else
{
	console.log("Usage : ./node server.js ip [port]");
	process.exit(0);
}