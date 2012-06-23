/**
 *	@author sylvia_r
 */

function ressources_draw(cache, layers) {
    
    layers.clear("cRessources");
    
	for (var i = 0; i != cache.getMap().length; i++)
	{
		var aCase = cache.getCase(i);
			
		layers.draw("cRessources", cache.getSprite(aCase), aCase.x, aCase.y);
	}
}