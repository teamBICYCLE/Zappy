/**
 *	@author sylvia_r
 */


function players_draw(layers) {
    

    var orientation = {
		1: "player-north",
		2: "player-east",
		3: "player-south",
		4: "player-west"
    }

    layers.clear("cPlayers");

	for (var i = 0; i != cache.getPlayers().length; i++)
	{
		var player = cache.getPlayers()[i];

		console.log(player.animationLoop_);
		if (player.team_ == currentTeam || currentTeam == "")
			layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_, false);
		else
			layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_, true);
			
		if (player.animationLoop_[1] > -1)
			layers.draw("cPlayers", "bubble_broadcast", player.posx_, player.posy_, false);
	}
}