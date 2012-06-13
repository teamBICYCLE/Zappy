/* Jquery */

$(function() {

	$("#send").click(function() {
		sendCmd($(".cmd").val());
	});

});

/* function */

function checkCmd(cmd){
	var explode = cmd.split(" ");
	
	if (typeof(ref[explode[0]]) != "undefined")
		return true;	
	return false;
}

var socket = io.connect('http://localhost', {port:24542});
var lastTimestamp = 0;

function sendCmd(cmd){
	if (checkCmd(cmd))
	{
		socket.emit('requestData', cmd);
		socket.on('requestDataDone', function(data){
			if (lastTimestamp != data.timestamp)
			{
				$("#result").append(data.data_ + "<br />");
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
  "sst": 2
};