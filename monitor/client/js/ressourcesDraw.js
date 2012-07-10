/**
 *	@author sylvia_r
 */

function ressources_draw(layers) {
    
    layers.clear("cRessources");

    //console.log("DRAW ressources");
	for (var i = 0; i != cache.getMap().length; i++)
	{
		var aCase = cache.getCase(i),
			sprite = cache.getSprite(aCase);
			
		if (sprite != null)
			layers.draw("cRessources", cache.getSprite(aCase), aCase.x_, aCase.y_, false);
	}
	return;
}