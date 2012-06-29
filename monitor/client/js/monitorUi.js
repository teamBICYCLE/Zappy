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
	
});

function displayError(msg) {
	$("#errorBox .errorText").text("Error : " + msg);
	$("#errorBox").fadeIn(1500).delay(1000).fadeOut(3000);
}

function displayCaseContent(pos, mapPos, layer, canvas) {
    var ressources = cache.getCaseFromPos(mapPos.x, mapPos.y).ressources;

    $("#caseContent").hide();
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

function fadeAndRemove() {
	
	$("#cmdResult span:first-child").fadeOut(2000, function(){
		$("#cmdResult span:first-child").remove();
		if ($("#cmdResult .entry").length > 5)
			fadeAndRemove();
	})
}

// function addMessage(msg) {
	// if ($("#cmdResult .entry").length >= 5)
		// $("#cmdResult span:first-child").remove();
	// $("#cmdResult").append("<span class='entry'>"+ msg + "</span>");
	// $('#cmdResult span:last-child').fadeOut(7000);
// }

function addMessage(msg) {
	
	if ($("#cmdResult .entry").length >= 5)
		fadeAndRemove();
		
	$("#cmdResult").append("<span class='entry'>"+ msg + "</span>");
}

/* INVENTORY */

function initInventory() {
	src = null;
	
	options = {
		revert:true,
		opacity: 0.8,
		zIndex: 100,
		start: function() {
			src = $(this).parent();
		}
	};
		
	$("#inventory").draggable();
	$(".item").draggable(options);
	
	$(".container").droppable({
		drop: function(event, ui) {
			src.append($('.item', this).remove()
							.removeClass().addClass("item")
							.css({"left": '',"opacity": '',"z-index": '',"top": ''})
							.draggable(options)
			);
		/* if drop != case de depart */
			$(this).append(ui.draggable.remove().clone()
							.removeClass().addClass("item")
							.css({"left": '',"opacity": '',"z-index": '',"top": ''})
							.draggable(options)
			);
		}
	});
	
	$(".inventory-close").click(function() {
		closeInventory();
	});
}

function closeInventory() {
	$("#inventory").hide();
	inventoryOpenId = -1;
}

function showInventory(id) {
	$("#inventory").show();
	inventoryOpenId = id;
}

/* TEAMSTATS PANEL*/

function addTeamsToPanel() {
	var nbTeams = cache.getTeams().length;

	for (var i = 1; i <= nbTeams; i++) {
		var infos = cache.getTeamInfo(i);

		$("#panel-stats").append("<div class='teambox'><div class='teamstats'><div class='team-picture' style='background-color:"+infos.color+"'></div>"
										+ "<span class='team-name'>Name: "
										+ infos.name + "</span><span class='team-effective'>Effective: " + infos.number + "</span>"
										+ "<span class='team-maxlvl'>Max level: <span class='team-maxlvl-number'>" + infos.maxLevel + "</span></span></div>"
										+ "<div class='chart'></div></div>");
	}
}

function initTeamPanel() {	
	
	addTeamsToPanel();	
	
   $(".btn-slide").toggle(function() {
		$("#panel").animate({marginRight: "0px"}, 200);
		$(this).toggleClass("active");
   }, function() {
		$("#panel").animate({marginRight: "-500px"}, 200);
		$(this).toggleClass("active");
   });
    
   $(".teambox").click(function() {
		if ($(".chart", this).is(':hidden')) {
	   	$(".chart").slideUp("slow");
		}
		$(".chart", this).slideToggle("slow");
   });
}