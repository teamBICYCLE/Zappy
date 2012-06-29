/**
 * @author sylvia_r
 */

function highlight_draw(layers) {
    
    $("#cHighLight").click(function(e, pos, mapPos){
	
    	if ((mapPos.x >= 0 && mapPos.x < layers.getMapSize().width)
	    && (mapPos.y >= 0 && mapPos.y < layers.getMapSize().height))
		{
		    layers.clear("cHighLight");
		    layers.draw("cHighLight", "highlight", mapPos.x, mapPos.y);
		    displayCaseContent(pos, mapPos, layers, "cHighLight");
		}
	});

    $("#cHighLight").mousemove(function(e, mapPos){
    		
		if ((mapPos.x >= 0 && mapPos.x < layers.getMapSize().width)
	    && (mapPos.y >= 0 && mapPos.y < layers.getMapSize().height))
		{		
		    layers.clear("cHighLight");
	    	layers.draw("cHighLight", "highlight", mapPos.x, mapPos.y);
		}
    });
}
