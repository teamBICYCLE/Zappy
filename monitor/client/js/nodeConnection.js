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
		cache.setPlayers(setInventoryChange(data.players, true));
		//cache.setPlayers(data.players);
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);
		
		// init draw
		layers = new Layers(data.xsize, data.ysize);
		
		// init UI
		initInventory();
		initTeamPanel();
		
		map_draw(data.xsize, data.ysize, layers);
		ressources_draw(layers);
		players_draw(layers);
		update_inventory();
		
		// event & draw
		highlight_draw(layers);
		events_handler(layers);
		update_inventory();
		
		lastTimestamp = data.timestamp;
	}
});

socket.on('cacheUpdate', function(data){

	var latency = (parseInt(new Date().getTime()) - parseInt(data.timestamp)),
		prevPlayers;
	$(".latency .lValue").text(latency);
	
	/* faudra seter eggs */
	if (lastTimestamp != data.timestamp) {
		cache.setMapSize(data.xsize, data.ysize);
		
		prevPlayers = cache.getPlayers();
		
		cache.setMap(data.map);
		//cache.setPlayers(setInventoryChange(data.players, true));
		cache.setPlayers(data.players);

		//console.log((cache.getPlayers()[0]).inventoryChange_);
		detectInventoryChange(prevPlayers);		
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);

		ressources_draw(layers);
		players_draw(layers);
		update_inventory();
		layers.zoom("cMap");
		
		lastTimestamp = data.timestamp;
	}
});
