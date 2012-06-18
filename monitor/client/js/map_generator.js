/**
 *	@author lafont_g
 */

var canvasMap = document.getElementById("c"),
	context = canvasMap.getContext("2d"),
	highLight = document.getElementById("cHighLight"),
	tile_width = 64,
	tile_height = 64;
	
canvasMap.width = window.innerWidth,
canvasMap.height = window.innerHeight;

function map_draw(map_width, map_height) {

	console.log("draw");
	console.log(cache.getTeams());
	img = new Image();

	highLight.width = window.innerWidth;
	highLight.height = window.innerHeight;
	
    img.onload = function() {
    
    	for (var i = 0; i != map_height; i++)
    	{
    		for (var j = map_width - 1; j >= 0; j--)
    		{
    			leftH = ((j * tile_width / 2) + (i * tile_width / 2));
				topH = ((i * tile_height / 4) - (j * tile_height / 4));

				// pour centrer
				//console.log((canvasMap.width / 2) - ((map_width / 2) * tile_width));
				leftH += (canvasMap.width / 2) - ((map_width / 2) * tile_width);
				topH += (canvasMap.height / 2);
				context.drawImage(img, leftH, topH);
    		}
    			
    	}
    };
    img.src = "img/floor.png";
}