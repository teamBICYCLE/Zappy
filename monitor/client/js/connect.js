/* Jquery */

$(function() {

	$("#send").click(function() {
		sendCmd($(".cmd").val());
	});

});

/* Node */

function sendCmd(cmd){
	console.log(cmd);
	// check de la commande 
	var socket = io.connect('http://localhost', {port:24542});
	socket.emit('requestData', {cmd_: cmd});
	socket.on('requestDataDone', function(data){
		$("#result").append(data.data_ + "<br />");
	});
}