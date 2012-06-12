//var express = require('express');
//var io = require('socket.io');

var ZappyConnection = require('./zappyConnection.js');
//var app = express.createServer();

//io = io.listen(app);
//app.listen(4242);

if (process.argv.length >= 3)
{
	var ip = process.argv[2],
		port = "4242",
		buffer = '';
		
	if (process.argv.length >= 4)
		port = process.argv[3];

	var zappy = new ZappyConnection(ip, port);
	
	zappy.on('cacheWhole', function(){
		console.log("done !");
		zappy.getCache().dump();
		var Case = new (require("./objects/mapCase.js"));
		Case.dump(zappy.getCache().getMap().getCase(zappy.getCache(), 2, 2));
		//zappy.getCache().getMap().getCase(zappy.getCache(), 19, 19).dump();
	    // test creation player
	    console.log("=================");
		//update();
	});
}
else
{
	console.log("Usage : ./node server.js ip [port]");
	process.exit(0);
}

function update() {
	console.log("update at " + zappy.getCache().getCurrentTimeUnit());
	setTimeout(update, zappy.getCache().getCurrentTimeUnit());
}