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
			if (match.indexOf(current[0]) != -1)
				matchPtr[match.indexOf(current[0])](current, cache);
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
	//console.log("bctFct call !");
}

var tnaFct = function(arg, cache){
	cache.addTeam(arg[1]);
}

var match = ["msz", "sgt", "bct", "tna"];
var matchPtr = [mszFct, sgtFct, bctFct, tnaFct];