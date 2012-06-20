/**
 *	@author sylvia_r
 */

function ressources_draw(cache, layers) {
    
	for (var i = 0; i != cache.getMap().length; i++)
	{
		var aCase = cache.getCase(i);
			
		// le if est temporaire
		if (cache.getSprite(aCase) == "linemate" || cache.getSprite(aCase) == "food")
			layers.draw("cRessources", cache.getSprite(aCase), aCase.x, aCase.y);
	}
}