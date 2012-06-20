/**
 * @author sylvia_r
 */

function highlight_draw(layers) {
    
    $("#cHighLight").click(function(e){
		var pos = getMousePosition(e);
			mapPos = realToMap(pos);
			
		layers.draw("cHighLight", "highlight", mapPos.x, mapPos.y);
	 	console.log(realToMap(pos));
	});
}

/* renverra les positions converties pixel -> map */
// http://www.developpez.net/forums/d788377/applications/developpement-2d-3d-jeux/cherche-formules-2d-isometriques/
function realToMap(pos) {
		
		return ({x: 0, y: 0});
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
