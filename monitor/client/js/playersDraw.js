/**
 *	@author sylvia_r
 */

function players_draw(cache, layers) {
    
    layers.clear("cPlayers");
    
	for (var i = 0; i != cache.getPlayers().length; i++)
	{
		var player = cache.getPlayers()[i];

		layers.draw("cPlayers", "player", player.posx_, player.posy_);
	}
}