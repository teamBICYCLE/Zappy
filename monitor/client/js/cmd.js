function checkCmd(cmd){
	var explode = cmd.split(" ");
	
	if (explode[0] == "sst" && parseInt(explode[1]) < 1)
	{
		alert("Error : sst second argument must be at least 1");
		return false;
	}
	if (typeof(ref[explode[0]]) != "undefined" && explode.length == ref[explode[0]])
		return true;
	displayError("Command not found");
	return false;
}

var lastTimestamp = 0;
	
function sendCmd(cmd){
	if (cmd == "help")
	{
		$("#cmdResult").append("<span class='entry'>" + "Available commands : tna, msz, bct, mct, ppo, plv, pin, sgt, sst, help" + "</span>");
		$('#cmdResult span:last-child').fadeOut(7000);
	}
	else if (checkCmd(cmd))
	{
		socket.emit('requestData', {cmd : cmd});
		socket.on('requestDataDone', function(data){
			if (lastTimestamp != data.timestamp)
			{
				if ($("#cmdResult .entry").length >= 5)
		 			$("#cmdResult span:first-child").remove();
		 		$("#cmdResult").append("<span class='entry'>"+ data.data_ + "</span>");
		 		$('#cmdResult span:last-child').fadeOut(7000);
				lastTimestamp = data.timestamp;
			}
		});
	}
}

var ref = {
  "tna": 1, 
  "msz": 1,
  "bct": 3,
  "mct": 1,
  "ppo": 2,
  "plv": 2,
  "pin": 2,
  "sgt": 1,
  "sst": 2,
  "help": 0
};