/**
 *	@author lafont_g
 */

var canvas = document.getElementById("c"),
	context = canvas.getContext("2d");
	
function map_draw(map_width, map_height) {

	console.log("draw");
	tile_width = 64, tile_height = 64,
	img = new Image();

	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;
	$("#c").click(getMousePosition);
	$("#c").mousemove(getMousePosition);
	
    img.onload = function() {
    
    	for (var i = 0; i != map_height; i++)
    	{
    		for (var j = map_width - 1; j >= 0; j--)
    		{
    			leftH = ((j * tile_width / 2) + (i * tile_width / 2));
				topH = ((i * tile_height / 4) - (j * tile_height / 4));

				// pour centrer
				leftH += (canvas.width / 2) - ((map_width / 2) * tile_width);
				topH += (canvas.height / 2);
				context.drawImage(img, leftH, topH);
    		}
    			
    	}
    };
    img.src = "img/floor.png";
}
	
function getMousePosition(e) {
	//var x = event.x;
	//var y = event.y;
	
	var rect = e.target.getBoundingClientRect();
	var x = e.offsetX || e.pageX - rect.left - window.scrollX;
	var y = e.offsetY || e.pageY - rect.top - window.scrollY;
	
}