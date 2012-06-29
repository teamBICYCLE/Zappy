/**
 * @author sylvia_r
 */

var socket = io.connect('http://localhost', {
		port: $(".port").text(),
		'reconnect': true,
  		'reconnection delay': 500,
  		'max reconnection attempts': 10
	}),
	lastTimestamp = 0,
	layers,
	inventoryOpenId = -1;
	
socket.on("disconnect", function(){
	
	$('#overlay').fadeIn('fast', function(){
		$('#connectionError').animate({'top':'160px'}, 500);
	});
});

socket.on("reconnect", function(){
	$('#connectionError').animate({'top':'-200px'}, 500, function(){
        $('#overlay').fadeOut('fast');
    });
});

socket.on("reconnect_failed", function(){
	console.log("GROS FAIL DE RECONNECTION !!!");
});

socket.on('firstConnection', function(data){
	if (lastTimestamp != data.timestamp) {
		cache.setMapSize(data.xsize, data.ysize);
		cache.setTeams(data.teams);
		cache.setTeamsColor(data.teamsColor);
		cache.setMap(data.map);
		cache.setPlayers(data.players);
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);
		
		// init draw
		layers = new Layers(data.xsize, data.ysize);
		
		map_draw(data.xsize, data.ysize, layers);
		ressources_draw(layers);
		players_draw(layers);
		
		// event & draw
		highlight_draw(layers);
		events_handler(layers);
		
		// init UI
		initInventory();
		
		// init teamPanel
		initTeamPanel();		
		
		lastTimestamp = data.timestamp;
	}
});

socket.on('cacheUpdate', function(data){

	var latency = (parseInt(new Date().getTime()) - parseInt(data.timestamp));
	$(".latency .lValue").text(latency);
	
	/* faudra seter eggs */
	if (lastTimestamp != data.timestamp) {
		cache.setMapSize(data.xsize, data.ysize);
		
		cache.setMap(data.map);
		cache.setPlayers(data.players);
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);

		update_inventory();
		ressources_draw(layers);
		players_draw(layers);
		
		lastTimestamp = data.timestamp;
	}
});
