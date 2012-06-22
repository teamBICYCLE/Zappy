/**
 * @author sylvia_r
 */

var socket = io.connect('http://localhost', {
		port:24542,
		'reconnect': true,
  		'reconnection delay': 1000,
  		'max reconnection attempts': 10
	}),
	lastTimestamp = 0,
	layers;
	
console.log(socket);

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
		cache.setMap(data.map);
		layers = new Layers(data.xsize, data.ysize);
		map_draw(data.xsize, data.ysize, layers);
		ressources_draw(cache, layers);
		highlight_draw(layers);
		lastTimestamp = data.timestamp;
	}
});

socket.on('cacheUpdate', function(data){
	//console.log("receive firstConnection");
	console.log("cacheUpdate");
	var latency = (parseInt(new Date().getTime()) - parseInt(data.timestamp));
	$(".latency .lValue").text(latency);
	
	
	if (lastTimestamp != data.timestamp) {
		cache.setMapSize(data.xsize, data.ysize);
		cache.setTeams(data.teams);
		cache.setMap(data.map);
		//console.log(cache.getSprite(cache.getCase(1, 1)));
		//console.log(data.map);
		//map_draw(data.xsize, data.ysize, layers);
		ressources_draw(cache, layers);
		//highlight_draw(layers);
		lastTimestamp = data.timestamp;
	}
});
