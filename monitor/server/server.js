

var ZappyConnection = require('./zappyConnection.js');
var ClientConnection = require('./clientConnection.js');

var cmdPtr = {
  "msz": {nb: 1, ptr: mszCmd},
  "tna": {nb: 1, ptr: tnaCmd},
  "bct": {nb: 3, ptr: bctCmd},
  "ppo": {nb: 2, ptr: ppoCmd},
  "plv": {nb: 2, ptr: plvCmd},
  "pin": {nb: 2, ptr: pinCmd},
  "sgt": {nb: 1, ptr: sgtCmd},
  "sst": {nb: 2, ptr: sstCmd},
  "gkp": {nb: 2, ptr: gkpCmd},
  "gsi": {nb: 9, ptr: gsiCmd},
  "gsc": {nb: 10, ptr: gscCmd},
  "glp": {nb: 2, ptr: glpCmd}
};

if (process.argv.length >= 3)
{
	var ip = process.argv[2],
		port = "4242",
		buffer = '',
		portClient = "24542";
	
	if (typeof(process.argv[4]) != "undefined")
		portClient = process.argv[4];
	
	if (process.argv[3] == portClient)
	{
		console.log("This port is reserved for browser <-> node server connection.");
		process.exit(0);
	}
	if (process.argv.length >= 4)
		port = process.argv[3];

	var zappy = new ZappyConnection(ip, port),
		client;
	
	zappy.on('cacheWhole', function(){
		
		//process.exit(0);
		client = new ClientConnection(portClient);
		
		zappy.getCache().dump();
	    console.log("=================");
	  
	  	client.on('requestData', function(obj){
	  		var data = getCmd(obj.cmd);
			obj.socket.emit('requestDataDone', {data_: data, timestamp: new Date().getTime()});
		});
		
		client.on('firstConnection', function(obj){
			
			console.log("send firstConnection !");
			var cache = zappy.getCache();
			
			obj.socket.emit('firstConnection', {
				xsize: cache.getXSize(),
				ysize: cache.getYSize(),
				teams: cache.getTeams(),
				teamsColor: cache.getTeamsColor(),
				map: cache.getFormatedMap(),
				players: cache.getPlayers(),
				eggs: cache.getEggs(),
				messages: cache.getCmdMessages(),
				timestamp: new Date().getTime(),
				currentTimeUnit: cache.getCurrentTimeUnit(),
				endGame: cache.getEndGame()
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
	
	var cache = zappy.getCache(),
		players = cache.getPlayers();
		
	client.getClientSocket().emit('cacheUpdate', {
		changeMap: cache.getChangeMap(),
		players: cache.getPlayers(),
		eggs: cache.getEggs(),
		messages: cache.getCmdMessages(),
		timestamp: new Date().getTime(),
		currentTimeUnit: cache.getCurrentTimeUnit(),
		endGame: cache.getEndGame()
	});
	
	console.log(cache.getEggs());
	
	if (cache.getEndGame().state)
		{
			zappy.getSocket().write("mct\n");
			cache.setEndGame(false, "");
		}
	cache.cmdMessagesEmpty();
	cache.changeMapEmpty();
	cache.updateBubbleAnimation();
	setTimeout(update, calcTimeOut(cache.getCurrentTimeUnit()));
}

function calcTimeOut(t) {
	if ((1000 / t) > 50)
		return (1000 / t);
	return 50;
}

/* CMD */

function mszCmd(arg) {
	return zappy.getCache().getMapSize();
}

function tnaCmd(arg) {
	return "Teams : " + zappy.getCache().getTeams();
}

function bctCmd(arg) {
	if (parseInt(arg[1]) >= 0 && parseInt(arg[2]) >= 0 && 
		parseInt(arg[1]) < zappy.getCache().getXSize() &&
		parseInt(arg[2]) < zappy.getCache().getYSize())
	{
		return "Case content in (" + arg[1] + ", " + arg[2] + ") : " +
		zappy.getCache().getMap().getCase(zappy.getCache(), parseInt(arg[1]), parseInt(arg[2])).ressources_;
	}
	else
		return ("Bct Error : X or Y is not valid");
}

function ppoCmd(arg) {
	if (zappy.getCache().playerExist(arg[1].replace("#", "")))
		return "Player position : " + zappy.getCache().getPlayer(arg[1]).getPos();
	else
		return ("Ppo Error : player doesn't exist !");
}

function plvCmd(arg) {
	if (zappy.getCache().playerExist(arg[1].replace("#", "")))
		return "Player level : " + zappy.getCache().getPlayer(arg[1]).getLevel();
	else
		return ("Plv Error : player doesn't exist !");
}

function pinCmd(arg) {
	if (zappy.getCache().playerExist(arg[1].replace("#", "")))
	{
		var inv = zappy.getCache().getPlayer(arg[1]).getInventory(),
			ret = "Player inventory :"
		
		ret += " [food " + inv.food + "] [linemate " + inv.linemate + "] [deraumere " + inv.deraumere;
		ret += "] [sibur " + inv.sibur + "] [mendiane " + inv.mendiane + "] [phiras " + inv.phiras;
		ret += "] [thystame " + inv.thystame + "]"; 

		return ret; 
	}
	else
		return ("Pin Error : player doesn't exist !");
}

function sgtCmd(arg) {
	return zappy.getCache().getCurrentTimeUnitText();
}

function sstCmd(arg) {
	
	zappy.getSocket().write(arg[0] + " " + arg[1] + "\n");
	zappy.getCache().setCurrentTimeUnit(arg[1]);
	return "Server current time unit is now set at " + arg[1];
}

function gkpCmd(arg) {
	
	var id = parseInt(arg[1].replace("#", ""));
	if (zappy.getCache().playerExist(id))
	{
		zappy.getSocket().write(arg[0] + " " + id + "\n");
		return ("Player #" + id + " successfully kicked");
	}
	else
		return ("Gkp Error : player doesn't exist !");
}

function gsiCmd(arg) {
	
	var id = parseInt(arg[1].replace("#", ""));
	if (zappy.getCache().playerExist(id))
	{
		zappy.getSocket().write(arg[0] + " " + id + " " + arg[2] + " " + arg[3] +
										 " " + arg[4] + " " + arg[5] + " " + arg[6] + 
										 " " + arg[7] + " " + arg[8] + "\n");
		return ("New inventory successfully setted for player #" + id);
	}
	else
		return ("Gsi Error : player doesn't exist !");
}

function gscCmd(arg) {
	
	if (parseInt(arg[1]) >= 0 && parseInt(arg[2]) >= 0 && 
		parseInt(arg[1]) < zappy.getCache().getXSize() &&
		parseInt(arg[2]) < zappy.getCache().getYSize())
	{
		zappy.getSocket().write(arg[0] + " " + arg[1] + " " + arg[2] + " " + arg[3] +
										 " " + arg[4] + " " + arg[5] + " " + arg[6] + 
										 " " + arg[7] + " " + arg[8] + " " + arg[9] + "\n");
										 
		return ("New content successfully setted for case (" + arg[1] + ", " + arg[2] + ")");
	}
	else
		return ("Gsc Error : X or Y is not valid");
}

function glpCmd(arg) {
	
	var id = parseInt(arg[1].replace("#", ""));
	if (zappy.getCache().playerExist(id))
	{
		zappy.getSocket().write(arg[0] + " " + id + "\n");
		return ("Player #" + id + " successfully level'd up");
	}
	else
		return ("Glp Error : player doesn't exist !");
}

function getCmd(cmd) {
	
	var arg = cmd.split(" ");
	
	if (typeof(cmdPtr[arg[0]]) != "undefined" && arg.length >= cmdPtr[arg[0]].nb)
		return cmdPtr[arg[0]].ptr(arg);
	else
		return ("Undefined reference to command : " + arg[0] + " with " + (arg.length - 1) + " parameters");
}