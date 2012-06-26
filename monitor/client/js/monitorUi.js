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
    
    $("#caseContent .contentText").text("Food: " + ressources[0] + " ");
    $("#caseContent .contentText").append("Linemate: " + ressources[1] + " ");
    $("#caseContent .contentText").append("Deraumere: " + ressources[2] + " ");
    $("#caseContent .contentText").append("Sibur: " + ressources[3] + " ");
    $("#caseContent .contentText").append("Mendiane: " + ressources[4] + " ");
    $("#caseContent .contentText").append("Phiras: " + ressources[5] + " ");
    $("#caseContent .contentText").append("Thystame: " + ressources[6]);
    $("#caseContent").css("left", pos.x + layer.padding(canvas).left);
    $("#caseContent").css("top", pos.y + layer.padding(canvas).top);
    $("#caseContent").fadeIn(800);
}

function addMessage(msg) {
	if ($("#cmdResult .entry").length >= 5)
		$("#cmdResult span:first-child").remove();
	$("#cmdResult").append("<span class='entry'>"+ msg + "</span>");
	$('#cmdResult span:last-child').fadeOut(7000);
}
