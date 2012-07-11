/**
 *	@author sylvia_r
 */


function draw_bubble(player, opacity) {
	
	var idx = 0,
		min = player.animationLoop_[idx],
		sprite = ['bubble_expulsion', 'bubble_broadcast', 'bubble_incantation', 'bubble_fork', 'bubble_drop', 'bubble_get'];
		
	for (var i = 0; i != player.animationLoop_.length; i++)
		if (player.animationLoop_[i] > min)
			{
				min = player.animationLoop_[i];
				idx = i;
			}
			
	if (min > -1)
		layers.draw("cPlayers", sprite[idx], player.posx_, player.posy_, opacity);
}

function players_draw(layers) {
    

    var orientation = {
		1: "player-north",
		2: "player-east",
		3: "player-south",
		4: "player-west"
    }

	var opacity;
	
    layers.clear("cPlayers");

	eggs_draw(layers);
	for (var i = 0; i != cache.getPlayers().length; i++)
	{
		var player = cache.getPlayers()[i];

		if (player.team_ == currentTeam || currentTeam == "")
			opacity = false;
		else
			opacity = true;
			
		layers.draw("cPlayers", orientation[player.orientation_], player.posx_, player.posy_, opacity);
		draw_bubble(player, opacity);
	}
}