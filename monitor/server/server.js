

var ZappyConnection = require('./zappyConnection.js');
var ClientConnection = require('./clientConnection.js');

if (process.argv.length >= 3)
{
	var ip = process.argv[2],
		port = "4242",
		buffer = '';
		
	if (process.argv[3] == "24542")
	{
		console.log("This port is reserved for browser <-> node server connection.");
		process.exit(0);
	}
	if (process.argv.length >= 4)
		port = process.argv[3];

	var zappy = new ZappyConnection(ip, port),
		client;
	
	zappy.on('cacheWhole', function(){
		
		client = new ClientConnection();
		
		var ref = {
		  "tna": zappy.getCache().getTeams(), 
		  "msz": zappy.getCache().getMapSize(),
		  "mct": zappy.getCache().getMap(),
		  "sgt": zappy.getCache().getCurrentTimeUnit()
		};
		
		zappy.getCache().dump();
	    console.log("=================");
	  
	  	client.on('requestData', function(obj){
	  		var data = getCmd(obj.cmd, ref);
			obj.socket.emit('requestDataDone', {data_: data, timestamp: new Date().getTime()});
		});
		
		client.on('firstConnection', function(obj){
			
			console.log("send firstConnection !");
			var cache = zappy.getCache();
			
			obj.socket.emit('firstConnection', {
				xsize: cache.getXSize(),
				ysize: cache.getYSize(),
				teams: cache.getTeams(),
				map: cache.getFormatedMap(),
				players: cache.getPlayers(),
				eggs: cache.getEggs(),
				timestamp: new Date().getTime()
			});
		});
		
		// client.on('requestDataBroadcast', function(obj){
			// obj.socket.emit('requestDataBroadcast', {data_: data, timestamp: new Date().getTime()});
		// });
		
		update();
	});
}
else
{
	console.log("Usage : ./node server.js ip [port]");
	process.exit(0);
}

function update() {
	/* reset */
	//cache.getPlayers() = [];
	zappy.getSocket().write("mct\n");
	zappy.getSocket().write("sgt\n");
	
	client.getClientSocket().emit('cacheUpdate', {
		map: zappy.getCache().getFormatedMap(),
		players: zappy.getCache().getPlayers(),
		eggs: zappy.getCache().getEggs(),
		timestamp: new Date().getTime()
	});
	
	console.log("update at " + zappy.getCache().getCurrentTimeUnit());
	setTimeout(update, zappy.getCache().getCurrentTimeUnit());
}

function playerCmd(explode) {
	
	var player = zappy.getCache().getPlayer(explode[1].replace("#", ""));
	
	var playerPtr = {
		"ppo": player.getPos(),
		"plv": player.getLevel(),
		"pin": player.getInventory()
	};
	
	if (typeof(playerPtr[explode[0]]) != "undefined")
		return playerPtr[explode[0]];
}

function getCmd(cmd, ref) {
	
	var explode = cmd.split(" ");
		
	if (typeof(ref[explode[0]]) != "undefined")
		return ref[explode[0]];
	else if (cmd.search("#") != -1)
		return playerCmd(explode);
	else if (explode[0] == "bct" && explode[1] >= 0 && explode[2] >=0 &&
			explode[1] < zappy.getCache().getXSize() && explode[2] < zappy.getCache().getYSize())
		return "Case content in (" + explode[1] + ", " + explode[2] + ") : " +
		zappy.getCache().getMap().getCase(zappy.getCache(), explode[1], explode[2]).ressources;
	else if (explode[0] == "sst")
	{
		zappy.getSocket().write(explode[0] + " " + explode[1] + "\n");
		return "Server current time unit is now set at " + explode[1];
	}
	return explode[0] + " : Command Error";
}


