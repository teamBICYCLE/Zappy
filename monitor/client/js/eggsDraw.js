function eggs_draw(layers) {
    
    var eggs = cache.getEggs();
	for (var i = 0; i != eggs.length; i++)
	{
		console.log(eggs[i].hatches_, eggs[i].dead_);
		// var player = cache.getPlayers()[i];
// 			
		// layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_, opacity);
		// draw_bubble(player, opacity);
	}
}