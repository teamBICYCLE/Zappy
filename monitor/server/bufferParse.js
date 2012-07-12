/**
 * @author sylvia_r
 */

/* TOUZAI_P */

exports.feed = function(buffer, cache) {
	var arrayBuffer = buffer.split("\n"),
		current;
		
	//console.log(buffer);
	for (var i = 0; i != arrayBuffer.length; i++)
	{
		if (arrayBuffer[i] != "")
		{
			current = arrayBuffer[i].split(" ");
			if (typeof(ptr[current[0]]) != "undefined" && current.length >= ptr[current[0]].nb)
			    ptr[current[0]].ptr(current, cache);
		}	
	}
}

/* PTR FUNCTION */

var mszFct = function(arg, cache){
	cache.setMapSize(arg[1], arg[2]);
}

var sgtFct = function(arg, cache){
	cache.setCurrentTimeUnit(arg[1]);
}

var bctFct = function(arg, cache){
	
	arg = arg.reverse();

	arg.pop();
	
	var x = arg.pop(),
		y = arg.pop();
	
	arg = arg.reverse();
	cache.setCase(x, y, arg);
}

var tnaFct = function(arg, cache){
	cache.addTeam(arg[1]);
}

var pnwFct = function(arg, cache){
    cache.addPlayer(arg);
}

var enwFct = function(arg, cache){
	cache.addEgg(arg);
}

var ppoFct = function(arg, cache){
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
	{
		player.setPosX(arg[2]);
		player.setPosY(arg[3]);
		player.setOrientation(arg[4]);
	}
}

var plvFct = function(arg, cache){
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
	{
		player.setLevel(arg[2]);
		cache.addMessage("Player " + arg[1] + " level'd up.");
	}
}

var pinFct = function(arg, cache){
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
	{
		player.setPosX(arg[2]);
		player.setPosY(arg[3]);
		
		arg = arg.reverse();
		arg.pop();
		arg.pop();
		arg.pop();
		arg.pop();
		arg = arg.reverse();
		player.setInventory(arg);
	}
}

var pexFct = function(arg, cache) {
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
		player.setPex();
}

var pbcFct = function(arg, cache) {
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
	{
		player.setPbc(arg[2]);
		cache.addMessage("Broadcast from player #" + arg[1] + " : " + arg[2] + ".");
	}
}

var picFct = function(arg, cache) {
	
	for (var i = 4; i != arg.length; i++)
	{
		var player = cache.getPlayer(arg[i]);
		
		if (player != -1)
		{
			player.setPic();
			cache.addMessage("Player #" + arg[i] + " is starting an incantation.");
		}
	}
}

var pfkFct = function(arg, cache) {
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
	{
		player.setPfk();
		cache.addMessage("Player #" + arg[1] + " has fork.");
	}
}

var pdrFct = function(arg, cache) {
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
		player.setPdr();
}

var pgtFct = function(arg, cache) {
	
	var player = cache.getPlayer(arg[1]);
	
	if (player != -1)
		player.setPgt();
}

var pdiFct = function(arg, cache) {
	cache.removePlayer(arg[1]);
}

var enwFct = function(arg, cache) {
	cache.addEgg(arg[1], arg[3], arg[4]);
}

var ehtFct = function(arg, cache) {
	
	var egg = cache.getEgg(arg[1]);
	
	if (egg != -1)
	{
		egg.setHatches(true);
		cache.addMessage("An egg has hatched.");
		console.log("An egg has hatched.");
	}
}

var ediFct = function(arg, cache) {
	
	var egg = cache.getEgg(arg[1]);
	
	if (egg != -1)
	{
		egg.setDead(true);
		cache.removeEgg(arg[1]);
		cache.addMessage("An egg has died.");
		console.log("An egg has died.");
	}
}

var eboFct = function(arg, cache) {
	
	var egg = cache.getEgg(arg[1]);
	
	if (egg != -1)
		cache.removeEgg(arg[1]);
}

var smgFct = function(arg, cache) {
	
	arg = arg.reverse();
	arg.pop();
	arg = arg.reverse();
	var msg = arg.join(" ");
	cache.addMessage("Server : " + msg);
}

var pieFct = function(arg, cache) {
	
	var msg = "An incantation has ";
	
	if (arg[3] == "1")
		msg += " succeeded.";
	else
		msg += " failed.";
		
	msg += " (" + arg[1] + ", " + arg[2] + ")";
		
	cache.addMessage(msg);
}

var segFct = function(arg, cache) {
	
	cache.setEndGame(true, arg[1]);
}

var ptr = {
  "msz": {nb: 3, ptr: mszFct},
  "bct": {nb: 10, ptr: bctFct},
  "tna": {nb: 2, ptr: tnaFct},
  "pnw": {nb: 7, ptr: pnwFct}, 
  "ppo": {nb: 5, ptr: ppoFct},
  "plv": {nb: 3, ptr: plvFct},
  "pin": {nb: 11, ptr: pinFct},
  "pex": {nb: 2, ptr: pexFct},
  "pbc": {nb: 3, ptr: pbcFct},
  "pic": {nb: 5, ptr: picFct},
  "pie": {nb: 4, ptr: pieFct},
  "pfk": {nb: 2, ptr: pfkFct},
  "pdr": {nb: 3, ptr: pdrFct},
  "pgt": {nb: 3, ptr: pgtFct},
  "pdi": {nb: 2, ptr: pdiFct},
  "enw": {nb: 5, ptr: enwFct},
  "eht": {nb: 2, ptr: ehtFct},
  "edi": {nb: 2, ptr: ediFct},
  "ebo": {nb: 2, ptr: eboFct},
  "sgt": {nb: 2, ptr: sgtFct},
  "smg": {nb: 2, ptr: smgFct},
  "seg": {nb: 2, ptr: segFct}
};