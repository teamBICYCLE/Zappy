/**
 * @author sylvia_r
 */

var socket = io.connect('http://localhost', {
		port: $(".port").text(),
		'reconnect': true,
  		'reconnection delay': 1000,
  		'max reconnection attempts': 15
	}),
	lastTimestamp = 0,
	layers,
	inventoryOpenId = -1,
	currentTeam = "",
	zoom = 10,
	playerFollowed = -1;

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
		cache.setPlayers(setAllInventoryChange(data.players, true));
		cache.setCurrentTimeUnit(data.currentTimeUnit);
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);
		
		// init draw
		layers = new Layers(data.xsize, data.ysize);
		
		// init UI
		initInventory();
		initTeamPanel();
		initPlayersList();
		initSettings();
		
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
		
		if (data.endGame.state)
			console.log("END GAME :) " + data.endGame.name);
		
		prevPlayers = cache.getPlayers();
		prevInfo = cache.getAllTeamInfo();
		
		cache.updateMap(data.changeMap);
		cache.setPlayers(data.players);
		cache.setCurrentTimeUnit(data.currentTimeUnit);

		detectInventoryChange(prevPlayers);		
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);

		nowInfo = cache.getAllTeamInfo();
		
		if (data.changeMap.length > 0)
		{
			console.log("ressources draw ! node");
			ressources_draw(layers);
		}
		players_draw(layers);
		update_inventory();
		updateTeamPanel(prevInfo, nowInfo);
		
		lastTimestamp = data.timestamp;
	}
});
