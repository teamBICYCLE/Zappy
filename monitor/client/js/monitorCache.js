
var cache = new MonitorCache();

function MonitorCache () {
	this.xsize_ = 0,
	this.ysize_ = 0,
	this.teams_ = new Array();
	this.teamsColor_ = new Array();
	this.map_ = new Array();
	this.players_ = new Array();
	this.currentTimeUnit_ = 0;
	this.eggs_ = new Array();
	
	this.ref = {
		0: "food",
		1: "linemate",
		2: "deraumere",
		3: "sibur",
		4: "mendiane",
		5: "phiras",
		6: "thystame"
	};
}

/* SET */

MonitorCache.prototype.setMapSize = function(x, y) {
	this.xsize_ = x;
	this.ysize_ = y;
	//map_.make(x, y);
}

MonitorCache.prototype.setTeams = function(teams) {
	this.teams_ = teams;
}

MonitorCache.prototype.setTeamsColor = function(color) {
	this.teamsColor_ = color;
}

MonitorCache.prototype.setMap = function(map) {
	this.map_ = map;
}

MonitorCache.prototype.setPlayers = function(players) {
	this.players_ = players;
	
	if (playerFollowed != -1)
	{
		var playerFollowedFind = false;
		
		for (var i = 0; i != this.players_.length; i++)
			if (this.players_[i].id_ == playerFollowed)
			{
				playerFollowedFind = true;
				break;
			}
			
		if (!playerFollowedFind)
		{
			playerFollowed = -1;
			if (typeof(layers) != "undefined")
				layers.resetAndRedraw();
		}
	}
}

MonitorCache.prototype.setCurrentTimeUnit = function(v) {
	this.currentTimeUnit_ = parseInt(v);
}

MonitorCache.prototype.setEggs = function(v) {
	this.eggs_ = v;
}

/* GET */

MonitorCache.prototype.getWidth = function() {
	return this.xsize_;
}

MonitorCache.prototype.getHeight = function() {
	return this.ysize_;
}

MonitorCache.prototype.getTeams = function() {
	return this.teams_;
}

MonitorCache.prototype.getTeamsColor = function() {
	return this.teamsColor_;
}

MonitorCache.prototype.updateMap = function(data) {
	
	var target, x, y;
	
	for (var i = 0; i != data.length; i++)
		{
		    x = parseInt(data[i].x_);
		    y = parseInt(data[i].y_);
		    target = (y * this.xsize_) + x;
		    if (this.ysize_ != 0 && this.xsize_ != 0 &&
			x < this.xsize_ && y < this.ysize_ && x >= 0 && y >= 0)
				this.map_[target] = data[i];
		    else
				displayError("Something wrong in MonitorCache.updateMap()");
		}
}

MonitorCache.prototype.getCaseFromPos = function(x, y) {
    var target = (parseInt(y) * this.xsize_) + parseInt(x);
    
	if (this.ysize_ != 0 && this.xsize_ != 0 &&
		x < this.xsize_ && y < this.ysize_ && x >= 0 && y >= 0)
		return this.map_[target];
	displayError("Something wrong in MonitorCache.getCase()");
}

MonitorCache.prototype.getCase = function(target) {
	
	if (target >= 0 && target < this.map_.length)
		return this.map_[target];
	displayError("Something wrong in MonitorCache.getCase()");
}

MonitorCache.prototype.getSpriteBase = function(aCase) {
	
	var sprite = 0,
   		value = aCase.ressources_[0];
   	   	
   	for (var i = 1; i != aCase.ressources_.length; i++)
   	{
   		if (aCase.ressources_[i] > value)
   		{
   			sprite = i;
   			value = aCase.ressources_[i];
   		}
   	}
   	
   	if (value != 0)
   		return ({name: this.ref[sprite], nb: value});
   	return ({name: null, nb: 0}); // empty !
}

MonitorCache.prototype.getSprite = function(aCase) {
	
	var sprite = this.getSpriteBase(aCase);
	
	if (sprite.name == null)
		return sprite.name;
	else if (sprite.nb <= 2)
		sprite.name += "_small";
	else
		sprite.name += "_medium";

	return sprite.name;
}

MonitorCache.prototype.getMap = function() {
	return this.map_;
}

MonitorCache.prototype.getPlayers = function() {
	return this.players_;
}

MonitorCache.prototype.getTeamInfo = function(teamId) {
	
	var ret = {
			name: "", 
			maxLevel: 1, 
			number: 0, 
			stats: [{label: "Level 1", data: 0, color: "#3266cc"},
					{label: "Level 2", data: 0, color: "#db3711"},
					{label: "Level 3", data: 0, color: "#ff9900"},
					{label: "Level 4", data: 0, color: "#990099"},
					{label: "Level 5", data: 0, color: "#0098c4"},
					{label: "Level 6", data: 0, color: "#dd4578"},
					{label: "Level 7", data: 0, color: "#65a900"},
					{label: "Level 8", data: 0, color: "#958453"}], 
			color: "#FF0000"
		};
	
	if (teamId <= this.teams_.length)
	{
		ret.name = this.teams_[teamId - 1];
		ret.color = this.teamsColor_[teamId - 1];
		for (var i = 0;  i != this.players_.length; i++)
			if (this.players_[i].team_ == ret.name)
			{
				if (this.players_[i].level_ > ret.maxLevel)
					ret.maxLevel = this.players_[i].level_;
				
				ret.stats[this.players_[i].level_ - 1].data += 1;
				ret.number += 1;
			}
	}
	else
		displayError("Something wrong in Cache.getTeamInfo() : undefined reference to team id " + teamId);
	return ret;
}

MonitorCache.prototype.getAllTeamInfo = function() {
	
	var ret = new Array();
	
	for (var i = 0; i != this.teams_.length; i++)
		ret[i] = this.getTeamInfo(i + 1);
		
	return ret;
}

MonitorCache.prototype.playerExist = function(id) {
	
	for (var i = 0; i != this.players_.length; i++)
		if (this.players_[i].id_ == id)
			return true;
	return false;
}

MonitorCache.prototype.getPlayer = function(id) {
		
	for (var i = 0; i != this.players_.length; i++)
		if (this.players_[i].id_ == id)
			return this.players_[i];
			
	displayError("Something wrong in Cache.getPlayer() : undefined reference to id #" + id);
}

MonitorCache.prototype.playerHere = function(x, y) {
	
	for (var i = 0; i != this.players_.length; i++)
		if (this.players_[i].posx_ == x && this.players_[i].posy_ == y)
			return true;
	return false;
}

MonitorCache.prototype.setInventoryChange = function(id, v, lastInventory) {
		
	this.getPlayer(id).inventoryChange_ = v;
	this.getPlayer(id).lastInventory_ = lastInventory;
}

MonitorCache.prototype.getCurrentTimeUnit = function() {
	return this.currentTimeUnit_;
}

MonitorCache.prototype.getEggs = function() {
	return this.eggs_;
}
