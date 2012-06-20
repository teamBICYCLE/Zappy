/**
 * @author sylvia_r
 */

$(function() {

	/* events */
	
	$(".cmd").keypress(function(e) {
		if (e.keyCode == 13)
		{
			sendCmd($(".cmd").val());
			$(".cmd").val("");
		}
	});
	
	$("#errorBox").click(function(e){
		$("#errorBox").hide();
	});
	
	// http://www.developpez.net/forums/d788377/applications/developpement-2d-3d-jeux/cherche-formules-2d-isometriques/
	
	$("#cHighLight").mousemove(getMousePosition);
	var canvasHL = document.getElementById("cHighLight");  
 	var ctx = canvasHL.getContext("2d");
	$("#cHighLight").click(function(e){
		var pos = getMousePosition(e);
		ctx.clearRect(0, 0, canvasHL.width, canvasHL.height);
		ctx.fillStyle = "rgb(200,0,0)";  
	 	ctx.fillRect (pos.x, pos.y, 10, 10);
	 	console.log(realToMap(pos));
	});
	
	/* utils */
	
	function realToMap(pos) {
		var mapx, mapy;
		
		pos.x = pos.x - (canvasMap.width / 2) - ((cache.getWidth() / 2) * tile_width);
		pos.y = pos.y - (canvasMap.height / 2);
		mapx = (pos.y / tile_height) + (pos.x / tile_width);
		mapx = (parseInt(mapx) + parseInt(cache.getWidth()) - 1);
		mapy = (pos.y / tile_height) - (pos.x / tile_width);
		console.log(mapy);
		//mapy = (parseInt(mapy) - parseInt(cache.getHeight()));
		return ({x: mapx, y: mapy});
		//return mapx;
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
	}
});

function displayError(msg) {
	$("#errorBox .errorText").text("Error : " + msg);
	$("#errorBox").fadeIn(1500).delay(1000).fadeOut(3000);
}