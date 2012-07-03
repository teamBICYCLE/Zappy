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
  			if (isset($_GET['port']) && is_numeric($_GET['port']))
  				$port = $_GET['port'];
  			echo "<script src='http://localhost:".$port."/socket.io/socket.io.js'></script>";
  		?>
  		<script src="js/monitorUi.js"></script>	
  		<script src="js/cmd.js"></script>
  		<script src="js/monitorCache.js"></script>
	</head>
	<body>
		<div id="overlay" style="display:none;"></div>
		<div id="connectionError">
			<h1>Connection error <img src="img/ajax-loader.gif" /></h1>
			<p>Your connection to the node server has been lost.</p>
			<p>Don't panic, I try a reconnection :)</p>
		</div>
		<canvas id="cEvents"></canvas>
		<canvas id="cPlayers"></canvas>
		<canvas id="cRessources"></canvas>
		<canvas id="cHighLight"></canvas>
  		<canvas id="cMap"></canvas>
		<div id="header">
			<i class="zappy-logo"></i>
			<i class="leaf-icon"></i>
			<ul class="topbar-menu">
				<li class="topbar-menu-settings"></li>
				<li class="topbar-menu-userlist"></li>
			</ul>
		</div>
		<div id="cmdResult"></div>
		<div id="errorBox"><span class="errorText"></span></div>
		<div id="caseContent"><span class="contentText"></span></div>
		<input type="text" class="cmd" />
		<div class="latency">latency : <span class="lValue">-</span> ms</div>
		<span class="port" style="display:none;"><? echo $port; ?></span>
		<div class="panel">
			<div class="panel-container">
				<div class="panel-topbar"></div>
				<div class="panel-stats"></div>
			</div>
			<div class="btn-slide"></div>
		</div>
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
		<div class="players-list">
			<span class="players-list">Players List</span>
			<ul class="players-list-content">
				
			</ul>
		</div>
  	</body>
  	<script src="js/canvasHandler.js"></script>
  	<script src="js/imgLoader.js"></script>
  	<script src="js/layers.js"></script>
	<script src="js/mapDraw.js"></script>
	<script src="js/ressourcesDraw.js"></script>
	<script src="js/playersDraw.js"></script>
	<script src="js/highlightDraw.js"></script>
	<script src="js/eventsHandler.js"></script>
	<script src="js/updateInventory.js"></script>
	<script src="js/nodeConnection.js"></script>
</html>
