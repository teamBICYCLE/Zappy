function checkCmd(cmd){
	var explode = cmd.split(" ");
	
	if (!godMode && (explode[0] == "gkp" || explode[0] == "gsi" ||
		explode[0] == "gsc" || explode[0] == "glp"))
	{
		console.log("yo");
		displayError("Command not found");
		return false;		
	}
	else if (explode[0] == "sst" && parseInt(explode[1]) < 1)
	{
		displayError("Error : sst second argument must be at least 1");
		return false;
	}
	
	if (typeof(ref[explode[0]]) != "undefined" && explode.length >= ref[explode[0]])
		return true;
	displayError("Command not found");
	return false;
}

var lastTimestamp = 0;
	
function cleanCmd(cmd) {
	
	var clean = cmd.split(" "),
		ret = "";
		
	for (var i = 0; i != clean.length; i++)
		if (clean[i] != "")
			ret += clean[i] + " ";
	
	return ret.substring(0, ret.length - 1);
}

function sendCmd(cmd) {
	
	cmd = cleanCmd(cmd);
	
	if (cmd == "help")
		addMessage("Available commands : tna, msz, bct, ppo, plv, pin, sgt, sst, msg, help");
	else if (cmd != "" && checkCmd(cmd))
	{
		socket.emit('requestData', {cmd : cmd});
		socket.on('requestDataDone', function(data){
			if (lastTimestamp != data.timestamp)
			{
				addMessage(data.data_);
				lastTimestamp = data.timestamp;
			}
		});
	}
}

var ref = {
  "tna": 1, 
  "msz": 1,
  "bct": 3,
  "ppo": 2,
  "plv": 2,
  "pin": 2,
  "sgt": 1,
  "sst": 2,
  "gkp": 2,
  "gsi": 9,
  "gsc": 10,
  "glp": 2,
  "msg": 2,
};