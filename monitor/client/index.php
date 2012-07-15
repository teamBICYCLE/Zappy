<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
  		<title>Zappy</title>
		<link rel="stylesheet" type="text/css" href="style.css" />
		<link href="img/favicon.ico" rel="icon" type="image/x-icon" />
  		<script src="js/libs/jquery.min.js"></script>
  		<script src="js/libs/jquery-ui.min.js"></script>
  		<script src="js/libs/jquery.flot.min.js"></script>
		<script src="js/libs/jquery.flot.pie.min.js"></script>
		<script src="js/libs/jquery.mousewheel.js"></script>
  		<?php
  			$port = "24542";
			$ip = "localhost";
  			
  			if (isset($_GET['port']) && is_numeric($_GET['port']))
  				$port = $_GET['port'];
			
			if (isset($_GET['ip']))
				$ip = $_GET['ip'];
			
  			echo "<script src='http://".$ip.":".$port."/socket.io/socket.io.js'></script>";
  		?>
  		<script src="js/libs/mousetrap.min.js"></script>
  		<script src="js/monitorUi.js"></script>	
  		<script src="js/cmd.js"></script>
  		<script src="js/monitorCache.js"></script>
	</head>
	<body>
		<div id="overlay" style="display:none;"></div>
		<div id="connectionError">
			<h1>Connection error<img src="img/ajax-loader.gif"/></h1>
			<p class="error-line1">Your connection to the node server has been lost.</p>
			<p class="error-line2">We're trying a reconnection, please wait.</p>
		</div>
		<div id="canvasContainer">
			<canvas id="cEvents"></canvas>
			<canvas id="cPlayers"></canvas>
			<canvas id="cRessources"></canvas>
			<canvas id="cHighLight"></canvas>
	  		<canvas id="cMap"></canvas>
	  	</div>
		<div id="header">
			<i class="zappy-logo"></i>
			<i class="leaf-icon"></i>
			<ul class="topbar-menu">
				<li class="topbar-menu-settings"></li>
				<li class="topbar-menu-players"></li>
				<li class="topbar-menu-centermap"></li>
				<li class="topbar-menu-godmode"></li>
			</ul>
		</div>
		<div id="cmdResult"></div>
		<div id="errorBox"><img src="img/warning_icon.png" alt="error icon" style="float:left;"><span class="errorText"></span></div>
		<input type="text" class="cmd" />
		<div class="latency">latency : <span class="lValue">-</span> ms</div>
		<span class="port" style="display:none;"><? echo $port; ?></span>
		<span class="ip" style="display:none;"><? echo $ip; ?></span>
		<div class="panel">
			<div class="panel-topbar"></div>
			<div class="panel-stats"></div>
		</div>
		<span class="pieNumber"></span>
		<div class="endGame">
				<span class="winner"></span>
				<img src="img/end.gif" />
				<span class="newGame">New Game in <span class="timer">10</span> seconds</span>
		</div>
		<div class="btn-slide"></div>
		<div id="inventory">
			<div id="inventory-header">
				<div class="inventory-close"></div>
			</div>
			<div id="inventory-containers">
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<br style="clear: both;"/>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<br style="clear: both;"/>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<br style="clear: both;"/>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
				<div class="container"></div>
			</div>
		</div>
		<div class="case-content">
			<div class="case-content-topbar"><span class="case-content-position"></span></div>
			<span class="case-content-title">Ressources:</span>
			<ul class="case-content-itemlist">
				<li class="case-content-item tiny-food">Food: <span class="count">15</span></li>
				<li class="case-content-item tiny-linemate">Linemate: <span class="count">21</span></li>
				<li class="case-content-item tiny-deraumere">Deraumere: <span class="count">5</span></li>
				<li class="case-content-item tiny-sibur">Sibur: <span class="count">7</span></li>
				<li class="case-content-item tiny-mendiane">Mendiane: <span class="count">19</span></li>
				<li class="case-content-item tiny-phiras">Phiras: <span class="count">12</span></li>
				<li class="case-content-item tiny-thystame">Thystame: <span class="count">14</span></li>
			</ul>
		</div>
		<div class="player-list button-display">
			<div class="player-list-topbar"></div>
			
			<div class="labels">
				<span class="label">ID</span><span class="label">Level</span><span class="label">Team</span>
			</div>	
			<div class="player-list-container">
			<ul></ul>
			</div>
		</div>
		<div class="settings button-display">
			<div class="settings-topbar"></div>
			<div class="settings-container">
				<h2>Settings</h2>
				<span class="setting-showres-label setting-label">Display ressources:</span><span class="setting-showres-button setting-enabled"></span><br />
				<span class="setting-music-label setting-label">Turn up the music:</span><span class="setting-music-button setting-disabled"></span><br /><br />
				<span class="setting-timer-label setting-label">Set time unit:</span><span class="setting-timer-value">1000</span><br />
				<input id="setting-timer-slider" type="range" min="1" max="200" step="1" />
			</div>
		</div>
		<div class="godmode button-display">
			<div class="godmode-topbar"></div>
			<div class="godmode-container">
				<h2>G0DM0D3!</h2>
				<p class="godmode-cmd"><b>gkp [player_id]:</b> Kick a player.</p>
				<p class="godmode-cmd"><b>gsi [player_id] [ressources]:</b> Set player inventory.</p>
				<p class="godmode-cmd"><b>gsc [x_pos] [y_pos] [ressources]:</b> Set case content.</p>
				<p class="godmode-cmd"><b>glp [player_id]:</b> Level up a player.</p>
			</div>
		</div>
  	</body>
  	<script src="js/canvasHandler.js"></script>
  	<script src="js/imgLoader.js"></script>
  	<script src="js/layers.js"></script>
	<script src="js/mapDraw.js"></script>
	<script src="js/ressourcesDraw.js"></script>
	<script src="js/eggsDraw.js"></script>
	<script src="js/playersDraw.js"></script>
	<script src="js/highlightDraw.js"></script>
	<script src="js/eventsHandler.js"></script>
	<script src="js/updateInventory.js"></script>
	<script src="js/nodeConnection.js"></script>
</html>
