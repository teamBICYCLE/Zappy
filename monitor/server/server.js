

var ZappyConnection = require('./zappyConnection.js');
var ClientConnection = require('./clientConnection.js');

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
	    console.log("=================");
	  
		var client = new ClientConnection();

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