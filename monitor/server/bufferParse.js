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
			if (typeof(ptr[current[0]]) != "undefined" && ptr[current[0]].nb >= current.length)
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
	cache.getPlayer(arg[1]).setPosX(arg[2]);
	cache.getPlayer(arg[1]).setPosY(arg[3]);
}

var plvFct = function(arg, cache){
	cache.getPlayer(arg[1]).setLevel(arg[2]);
	cache.addMessage("Player " + arg[1] + " level'd up");
}

var pinFct = function(arg, cache){
	
	var player = cache.getPlayer(arg[1]);
	
	//console.log(player);
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

var pexFct = function(arg, cache) {
	cache.getPlayer(arg[1]).setPex();
}

var pbcFct = function(arg, cache) {
	cache.getPlayer(arg[1]).setPbc(arg[2]);
}

var picFct = function(arg, cache) {
	cache.getPlayer(arg[1]).setPic();
	cache.addMessage("Player " + arg[1] + " is starting a spell");
}

var pfkFct = function(arg, cache) {
	cache.getPlayer(arg[1]).setPfk();
}

var pdrFct = function(arg, cache) {
	cache.getPlayer(arg[1]).setPdr();
}

var pgtFct = function(arg, cache) {
	cache.getPlayer(arg[1]).setPgt();
}

var pdiFct = function(arg, cache) {
	cache.removePlayer(arg[1]);
}

var ptr = {
  "msz": {nb: 3, ptr: mszFct}, 
  "sgt": {nb: 2, ptr: sgtFct},
  "bct": {nb: 10, ptr: bctFct},
  "tna": {nb: 2, ptr: tnaFct},
  "pnw": {nb: 7, ptr: pnwFct},
  "enw": {nb: 5, ptr: enwFct},
  "ppo": {nb: 5, ptr: ppoFct},
  "plv": {nb: 3, ptr: plvFct},
  "pin": {nb: 11, ptr: pinFct},
  "pex": {nb: 2, ptr: pexFct},
  "pbc": {nb: 3, ptr: pbcFct},
  "pic": {nb: 5, ptr: picFct},
  // faire pie
  "pfk": {nb: 2, ptr: pfkFct},
  "pdr": {nb: 2, ptr: pdrFct},
  "pgt": {nb: 2, ptr: pgtFct},
  "pdi": {nb: 2, ptr: pdiFct},
  // faire pdi
};