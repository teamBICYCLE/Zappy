/**
 * @author sylvia_r
 */

function highlight_draw(layers) {
    
    $("#cHighLight").click(function(e){
	var pos = getMousePosition(e),
	mapPos = realToMap(pos, layers, "cHighLight");
    	if ((mapPos.x >= 0 && mapPos.x < layers.getMapSize().width)
	    && (mapPos.y >= 0 && mapPos.y < layers.getMapSize().height))
	{
	    layers.clear("cHighLight");
	    layers.draw("cHighLight", "highlight", mapPos.x, mapPos.y);
	}
	});

    $("#cHighLight").mousemove(function(e){
    	var pos = getMousePosition(e),
    	mapPos = realToMap(pos, layers, "cHighLight");
    	if ((mapPos.x >= 0 && mapPos.x < layers.getMapSize().width)
	    && (mapPos.y >= 0 && mapPos.y < layers.getMapSize().height))
	{		
	    layers.clear("cHighLight");
    	    layers.draw("cHighLight", "highlight", mapPos.x, mapPos.y);
	}
    	});
}

/* renverra les positions converties pixel -> map */
// http://www.developpez.net/forums/d788377/applications/developpement-2d-3d-jeux/cherche-formules-2d-isometriques/
function realToMap(pos, layers, canvas) {
    var x = 0, y = 0;

    pos.x -= layers.padding(canvas).left;
    pos.y -= layers.padding(canvas).top;
    x = (pos.y / (layers.getTileSize().height / 2)) + (pos.x / layers.getTileSize().width);
    y = (pos.y / (layers.getTileSize().height / 2)) - (pos.x / layers.getTileSize().width);
    return ({x: parseInt(x - 1), y: parseInt(y)});
};
	
function getMousePosition(e) {

	var targ;
    if (!e)
        e = window.event;
    if (e.target)
        targ = e.target;
    else if (e.srcElement)
        targ = e.srcElement;
    if (targ.nodeType == 3) // Safari
        targ = targ.parentNode;

    var x = e.pageX - $(targ).offset().left;
    var y = e.pageY - $(targ).offset().top;
    
    return ({x: x, y: y});
};
