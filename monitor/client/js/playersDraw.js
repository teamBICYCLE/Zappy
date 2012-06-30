/**
 *	@author sylvia_r
 */

function players_draw(layers) {
    

    var orientation = {
		1: "player-south",
		2: "player-west",
		3: "player-north",
		4: "player-east"
    }

    layers.clear("cPlayers");    
	for (var i = 0; i != cache.getPlayers().length; i++)
	{
		var player = cache.getPlayers()[i];

		layers.drawSocle("cPlayers", player.color_, player.posx_, player.posy_);
		//layers.draw("cPlayers", orientation[player.orientation_], 1, 0);
		layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_);
	}
}