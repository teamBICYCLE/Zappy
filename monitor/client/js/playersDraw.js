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
    //var c = layers.get("cPlayers");
    
    //c.ctx.globalAlpha = 1;
	for (var i = 0; i != cache.getPlayers().length; i++)
	{
		var player = cache.getPlayers()[i];

		if (player.team_ == currentTeam || currentTeam == "")
			layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_, false);
		else
			layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_, true);
	}
}