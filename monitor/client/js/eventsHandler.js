/**
 * @author sylvia_r
 */

function events_handler(layers) {
		
	$("#cEvents").unbind('click');
	$("#cEvents").unbind('mousemove');
	
	$("#cEvents").click(function(e) {
		
		var pos = getMousePosition(e),
    		mapPos = realToMap(pos, layers, "cHighLight"),
    		players = cache.getPlayers();
    	$("#cHighLight").trigger('click', [mapPos]);

	});

    $("#cEvents").mousemove(function(e) {
    	
    	var pos = getMousePosition(e),
    		mapPos = realToMap(pos, layers, "cHighLight");
    	$("#cHighLight").trigger('mousemove', [mapPos]);
    	
    });
}

function realToMap(pos, layers, canvas) {
    var x = 0, y = 0;

    pos.x -= layers.padding(canvas).left;
    pos.y -= layers.padding(canvas).top;
    x = (pos.y / (layers.tilesSizeLevel[zoom] / 2)) + (pos.x / layers.tilesSizeLevel[zoom]);
    y = (pos.y / (layers.tilesSizeLevel[zoom] / 2)) - (pos.x / layers.tilesSizeLevel[zoom]);
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