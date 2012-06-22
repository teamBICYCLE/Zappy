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
	

    $("#caseContent").click(function(e){
	$("#caseContent").hide();
    });
	// $('#connectionError').click(function(){
		// if (!$("#connectionError").is(":hidden"))
		// {
			// $('#connectionError').animate({'top':'-210px'}, 500, function(){
	            // $('#overlay').fadeOut('fast');
	        // });
		// }
	// });
	// $('#connectionError').click(function(){
		// if (!$("#connectionError").is(":hidden"))
		// {
			// $('#connectionError').animate({'top':'-210px'}, 500, function(){
	            // $('#overlay').fadeOut('fast');
	        // });
		// }
	// });

});

function displayError(msg) {
	$("#errorBox .errorText").text("Error : " + msg);
	$("#errorBox").fadeIn(1500).delay(1000).fadeOut(3000);
}

function displayCaseContent(pos, mapPos, layer, canvas) {
    var ressources = cache.getCaseFromPos(mapPos.x, mapPos.y).ressources;
    
    $("#caseContent .contentText").text("Food: " + ressources[0] + "\n");
    $("#caseContent .contentText").append("Linemate: " + ressources[1] + "\n");
    $("#caseContent").css("left", pos.x + layer.padding(canvas).left);
    $("#caseContent").css("top", pos.y + layer.padding(canvas).top);
    $("#caseContent").fadeIn(800);
}