<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
  		<title>Zappy</title>
		<link rel="stylesheet" type="text/css" href="style.css" />
  		<script src="js/libs/jquery.min.js"></script>
  		<script src="js/libs/jquery-ui.min.js"></script>
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
		<div id="header"></div>
		<div id="cmdResult"></div>
		<div id="errorBox"><span class="errorText"></span></div>
		<div id="caseContent"><span class="contentText"></span></div>
		<input type="text" class="cmd" />
		<div class="latency">latency : <span class="lValue">-</span> ms</div>
		<span class="port" style="display:none;"><? echo $port; ?></span>
		<div id="panel">
			<div id="panel-container">
				<div id="panel-topbar"></div>
				<div id="panel-stats"></div>
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
