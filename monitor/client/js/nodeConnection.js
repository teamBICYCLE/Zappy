/**
 * @author sylvia_r
 */

var socket = io.connect('http://localhost', {port:24542}),
	lastTimestamp = 0,
	layers;

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
