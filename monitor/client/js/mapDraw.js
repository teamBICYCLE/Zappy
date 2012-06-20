/**
 *	@author lafont_g
 */

function map_draw(map_width, map_height, layers) {
    
    for (var i = 0; i != map_height; i++)
    	for (var j = map_width - 1; j >= 0; j--)
    		layers.draw("cMap", "floor", j, i);
}