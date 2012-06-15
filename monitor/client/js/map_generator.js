/**
 *	@author lafont_g
 */

var map_width = 20;
var map_height = 20;

$(function() {
	
	var canvas = document.getElementById("c"),
		context = canvas.getContext("2d");
	
	draw();
	function draw() {

		console.log("draw");
		tile_width = 64, tile_height = 64,
    	img = new Image();

		canvas.width = 1300;
		canvas.height = 690;
		
	    img.onload = function() {
	    
	    	for (var i = 0; i != map_height; i++)
	    	{
	    		for (var j = 0; j != map_width; j++)
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
	    img.src = "img/0.gif";
	   	//setTimeout(draw, 100);
	}

	$("#plus").on("click", function(){
		console.log("Eeeee");
	});
});