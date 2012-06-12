/* Jquery */

$(function() {

	$("#connect").click(function() {
		var ip = $("#ip").val();
		
		exp = new RegExp("([0-9]{1,3}.){3}([0-9]{1,3})", "g");
		if (exp.test(ip))
			connect_initNodeServer($("#ip").val());
		else
			alert("Bad ip !");
	});

});

/* Node */

function connect_initNodeServer(ip){
	//console.log(ip);
	var socket = io.connect('http://localhost', {port:4242});
	socket.emit('initNodeServer', {ip_: ip});
}