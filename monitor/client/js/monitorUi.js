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
	
	$(".cmd").focusin(function() {
		$("#cmdResult").fadeIn(200);
	});
	
	$(".cmd").focusout(function() {
		$("#cmdResult").fadeOut(1000);
	})
	
	$("#errorBox").click(function(e){
		$("#errorBox").hide();
	});
	
	
	$(".case-content").click(function() {
		$(this).fadeOut(300);
		$("#overlay").fadeOut(300);
	});
	
	$("body").mousewheel(function(event, delta) {
		
		previousZoom = zoom;
		
		if (playerFollowed == -1)
		{
			if (delta > 0)
			{
				zoom = ((zoom == 10) ? (10) : (zoom + 1));
				layers.setCenter(lastMapPos.x, lastMapPos.y);
			}
			else
				zoom = ((zoom == 1) ? (1) : (zoom - 1));
	
			var tileSize = layers.getTileSize();
			//layers.setTileSize(layers.getTileLevel(zoom), layers.getTileLevel(zoom));
			
			if (previousZoom != zoom)
			{
				layers.clear("cHighLight");
				map_draw(cache.getWidth(), cache.getHeight(), layers);
				ressources_draw(layers);
				players_draw(layers);
			}
		}
	});
	
	Mousetrap.bind('up up down down left right left right b a', function() {
	    console.log("Konami Code !");
	});
	
	Mousetrap.bind('i', function() {
	    if (playerFollowed != -1)
	    {
	    	if ($("#inventory").is(':hidden'))
	    		showInventory(playerFollowed);
	    	else
	    		closeInventory();
	    }
	});
	
	Mousetrap.bind('p', function() {
		$(".player-list").toggle();
	});
	
	Mousetrap.bind('t', function() {

		if ($(".panel").css("margin-right") == "-500px")
			$(".panel").animate({marginRight: "0px"}, 200);
		else
			$(".panel").animate({marginRight: "-500px"}, 200);
	});
	
	/*
	$("#overlay").click(function() {
		$(this).fadeOut(300);
		$(".case-content").fadeOut(300);
	});
	*/
	
	$(".topbar-menu-players").toggle(function() {
		$(".player-list").fadeIn(300);
	}, function() {
		$(".player-list").fadeOut(300);
	});

});

function displayError(msg) {
	$("#errorBox .errorText").text("Error : " + msg);
	$("#errorBox").fadeIn(500).delay(1000).fadeOut(1500);
}

function displayCaseContent(mapPos, layer, canvas) {
    var ressources = cache.getCaseFromPos(mapPos.x, mapPos.y).ressources_;
    
    	$(".case-content-position").text("Position ("+mapPos.x+", "+mapPos.y + ")");
		$(".tiny-food .count").text(ressources[0]);
		$(".tiny-linemate .count").text(ressources[1]);
		$(".tiny-deraumere .count").text(ressources[2]);
		$(".tiny-sibur .count").text(ressources[3]);
		$(".tiny-mendiane .count").text(ressources[4]);
		$(".tiny-phiras .count").text(ressources[5]);
		$(".tiny-thystame .count").text(ressources[6]);
		$("#overlay").fadeIn(300);
		$(".case-content").fadeIn(300);    
}

function fadeAndRemove() {
	
	$("#cmdResult span:first-child").fadeOut(1000, function(){
		$("#cmdResult span:first-child").remove();
		if ($("#cmdResult .entry").length > 5)
			fadeAndRemove();
	})
}

function addMessage(msg) {
	
	$("#cmdResult").fadeIn(200);
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

function initItem(item) {
	src = null;
	
	options = {
		revert:true,
		opacity: 0.8,
		zIndex: 100,
		start: function() {
			src = $(this).parent();
		}
	};
	
	$(".item").draggable(options);
}

function closeInventory() {
	
	$("#inventory").hide();
	inventoryOpenId = -1;
}

function showInventory(id) {
	
	$("#inventory").show();
	inventoryOpenId = id;
}

function emptyInventoryContent() {
	var container = $("#inventory-containers .container");
	
	for (var i = 0; i != container.length; i++)
		$(container[i]).children().remove();
}

function updateInventoryContent(inventory) {
	
	var ref = ["food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"];
	
	emptyInventoryContent();
	for (var i = 0; i != inventory.length; i++)
		if (inventory[i] > 0)
			{
				var container = $("#inventory-containers .container");
				
				for (var j = 0; j != container.length; j++)
					if ($(container[j]).children().length == 0)
					{
						$(container[j]).append("<div id='"+ref[i]+"-item' class='item'><span class='"+ref[i]+"-count item-count'>"+inventory[i]+"</span></div>");
						
						break;
					}
				//console.log($("#inventory-containers .container"));
			}
			
	initItem();
}

/* TEAMSTATS PANEL*/

function addTeamsToPanel() {
	var nbTeams = cache.getTeams().length;

	for (var i = 1; i <= nbTeams; i++) {
		var infos = cache.getTeamInfo(i);

		$(".panel-stats").append("<div class='teambox' id='teamid-" + infos.name + "'><div class='teamstats'><div class='team-picture' style='background-color:"+infos.color+"'></div>"
										+ "<span class='team-name'>Name: "
										+ infos.name + "</span><span class='team-effective'>Effective: " + infos.number + "</span>"
										+ "<span class='team-maxlvl'>Max level: <span class='team-maxlvl-number'>" + infos.maxLevel + "</span></span></div>"
										+ "<div class='chart'><div class='chart-content'></div></div></div>");
	
		if (infos.number > 0)		
			$.plot($(".chart-content:last"), infos.stats,
			{
		        series: {
		            pie: { 
		                show: true,
		                radius: 3/4,
		                label : {
		                	radius: 3/4,
		                }
		            }
		        },
			});
		else
			$(".chart-content:last").append("<p style='text-align: center; font-size: 18px; margin-top: 100px;'>Statistics are currently unavailable for this team.</p>");									
	}
	// $("#interactive").bind("plothover", pieHover);
	// $("#interactive").bind("plotclick", pieClick);
}

function initTeamPanel() {	
	
	$(".panel-stats").children().remove();
	
	addTeamsToPanel();
	
	$(".btn-slide").toggle(function() {
			$(".panel").animate({marginRight: "0px"}, 200);
			$(".btn-slide").toggleClass("active");
		}, function() {
			$(".panel").animate({marginRight: "-500px"}, 200);
			$(".btn-slide").toggleClass("active");
	});
    
   $(".teambox").click(function() {
		if ($(".chart", this).is(':hidden')) {
			$(".chart").slideUp("slow");
		}
		$(".chart", this).slideToggle("slow");
   });
   
   $(".teambox").mouseover(function(e) {
   		//console.log(e.currentTarget.id.split("-")[1] + "currentTeam");
		if (e.currentTarget.id.split("-")[1] != currentTeam)
			currentTeam = e.currentTarget.id.split("-")[1];
	});
	
	$(".teambox").mouseout(function(e) {
			currentTeam = "";
	});
}

function detectTeamPanelChange(prev, now) {
	
	for (var i = 0; i != prev.length; i++)
	{
		if (prev[i].number != now[i].number || prev[i].maxLevel != now[i].maxLevel)
			return true;
		for (var j = 0; j != prev[i].stats.length; j++)
			if (prev[i].stats[j].data != now[i].stats[j].data)
				return true;
	}
	return false;
}

function updateTeamPanel(prev, now) {
	
	if (detectTeamPanelChange(prev, now))
		{
			$(".panel-stats").children().remove();
			initTeamPanel();
			updatePlayerList();
		}	
}

/* PLAYERS LIST */

function initPlayersList() {
	var players = cache.getPlayers();

	for (var i = 0; i < players.length; i++) {
		$(".player-list-container ul").append("<li>" +
								"<span class='player-id'>" + players[i].id_ + "</span>" +
								"<span class='player-lvl'>" + players[i].level_ + "</span>" +
								"<span class='player-team'>" + players[i].team_ + "</span>" +
								"<span class='player-follow-button' style='margin-left:0;'>Follow</span>" +
								"</li>");
	}
	
	$(".player-follow-button").click(function() {
		if ($(this).text() == "Follow") {
			$(".player-follow-button").text("Follow");
			$(this).text("Unfollow");
			
			var id = parseInt($(this).parent().children().html());
			playerFollowed = id;
			showInventory(id);
			layers.resetAndRedraw();
		}
		else {
			$(this).text("Follow");
			playerFollowed = -1;
			layers.resetAndRedraw();
			closeInventory();
		}
	});
}

function updatePlayerList() {
	$(".player-list-container ul").children().remove();
	initPlayersList();
}
