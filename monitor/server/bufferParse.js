/**
 * @author sylvia_r
 */

/* TOUZAI_P */

exports.feed = function(buffer, cache) {
	var arrayBuffer = buffer.split("\n"),
		current;
		
	for (var i = 0; i != arrayBuffer.length; i++)
	{
		if (arrayBuffer[i] != "")
		{
			current = arrayBuffer[i].split(" ");
			if (typeof(ptr[current[0]]) != "undefined")
			    ptr[current[0]](current, cache);
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

var ptr = {
  "msz": mszFct, 
  "sgt": sgtFct,
  "bct": bctFct,
  "tna": tnaFct,
  "pnw": pnwFct,
  "enw": enwFct
};