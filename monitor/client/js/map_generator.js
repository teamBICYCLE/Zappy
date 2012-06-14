/**
 *	@author lafont_g
 */

 $(function() {
	MapGenerate(200, 200);
});

function MapGenerate(map_width, map_height) {
	var x, y;
	var tile_width = 64, tile_height = 32;
	
	for (y = 0; y < map_height; y++) {
		for (x = 0; x < map_width; x++) {
			img = new Image();
			img.src = "img/0.gif";
			img.style.position = 'absolute';
			img.style.left = ((x * tile_width / 2) + (y * tile_width / 2)) + 'px';
			img.style.top = ((y * tile_height / 2) - (x * tile_height / 2)) + 'px';
			$('#container').append(img);
		}
	}
	
}