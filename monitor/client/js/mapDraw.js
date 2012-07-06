/**
 *	@author lafont_g
 */

function map_draw(map_width, map_height, layers) {
    
    layers.clear("cMap");
    for (var i = 0; i != map_height; i++)
    	for (var j = 0; j != map_width; j++)
    	    layers.draw("cMap", "floor", j, i, false);
}