/**
 * @author sylvia_r
 */

var socket = io.connect('http://localhost', {port:24542}),
	lastTimestamp = 0;

socket.on('firstConnection', function(data){
	//console.log("receive firstConnection");
	if (lastTimestamp != data.timestamp) {
		cache.setMapSize(data.xsize, data.ysize);
		cache.setTeams(data.teams);
		console.log(data.map);
		map_draw(data.xsize, data.ysize);
	}
});

