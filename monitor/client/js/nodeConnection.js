/**
 * @author sylvia_r
 */

var socket = io.connect('http://localhost', {
		port: $(".port").text(),
		'connect timeout' : 200,
		'reconnect': true,
  		'reconnection delay': 100,
  		'max reconnection attempts': 5
	}),
	lastTimestamp = 0,
	layers,
	inventoryOpenId = -1,
	currentTeam = "",
	zoom = 10,
	playerFollowed = -1;

socket.on("connect_failed", function(){
	console.log("CONNECTION FAILED");
	$('#overlay').fadeIn('fast', function(){
		$(".error-line1").html("Cannot reach the node server.");
		$(".error-line2").html("Please check the server's status.");
		$('.case-content').fadeOut('fast');
		$('#connectionError').animate({'top':'250px'}, 500);
	});
});

socket.on("disconnect", function(){
	
	$('#overlay').fadeIn('fast', function(){
		$(".error-line1").html("Your connection to the node server has been lost.");
		$(".error-line2").html("We're trying a reconnection, please wait.");
		$('.case-content').fadeOut('fast');
		$('#connectionError').animate({'top':'250px'}, 500);
	});
});

socket.on("reconnect", function(){
	$('#connectionError').animate({'top':'-210px'}, 500, function(){
			$('#overlay').fadeOut('fast');
    });
});

socket.on("reconnect_failed", function(){
	$(".error-line1").html("Connection failure: Maximum attempts exceeded.");
	$(".error-line2").html("Please try to restart the node server then refresh this page.");
});

socket.on('firstConnection', function(data){
	if (lastTimestamp != data.timestamp) {
		cache.setMapSize(data.xsize, data.ysize);
		cache.setTeams(data.teams);
		cache.setTeamsColor(data.teamsColor);
		cache.setMap(data.map);
		cache.setPlayers(setAllInventoryChange(data.players, true));
		cache.setEggs(data.eggs);
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
	
	if (lastTimestamp != data.timestamp) {
		
		if (data.endGame.state)
			display_endGame(data.endGame.name);
		
		prevPlayers = cache.getPlayers();
		prevInfo = cache.getAllTeamInfo();
		
		cache.updateMap(data.changeMap);
		cache.setPlayers(data.players);
		cache.setEggs(data.eggs);
		cache.setCurrentTimeUnit(data.currentTimeUnit);

		detectInventoryChange(prevPlayers);
		
		for (var i = 0; i != data.messages.length; i++)
			addMessage(data.messages[i]);

		nowInfo = cache.getAllTeamInfo();
		
		if (data.changeMap.length > 0)
			ressources_draw(layers);
			
		players_draw(layers);
		update_inventory();
		updateTeamPanel(prevInfo, nowInfo);
		
		lastTimestamp = data.timestamp;
	}
});
