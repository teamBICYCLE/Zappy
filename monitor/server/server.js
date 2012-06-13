

var ZappyConnection = require('./zappyConnection.js');
var ClientConnection = require('./clientConnection.js');
var client = new ClientConnection();

if (process.argv.length >= 3)
{
	var ip = process.argv[2],
		port = "4242",
		buffer = '';
		
	if (process.argv.length >= 4)
		port = process.argv[3];

	var zappy = new ZappyConnection(ip, port);
	
	zappy.on('cacheWhole', function(){
		
		var ref = {
		  "tna": zappy.getCache().getTeams(), 
		  "msz": zappy.getCache().getMapSize(),
		  "bct": 3,
		  "mct": zappy.getCache().getMap(),
		  "ppo": 2,
		  "plv": 2,
		  "pin": 2,
		  "sgt": zappy.getCache().getCurrentTimeUnit(),
		  "sst": 2
		};
		
		zappy.getCache().dump();
	    console.log("=================");
	  
	  	client.on('requestData', function(obj){
	  		var data = getCmd(obj.cmd, ref);
			obj.socket.emit('requestDataDone', {data_: data, timestamp: new Date().getTime()});
		});
		
		// client.on('requestDataBroadcast', function(obj){
			// obj.socket.emit('requestDataBroadcast', {data_: zappy.getCache().getTeams(), times});
		// });
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

function getCmd(cmd, ref) {
	
	var explode = cmd.split(" ");
		
	if (typeof(ref[explode[0]]) != "undefined")
		return ref[explode[0]];
}


