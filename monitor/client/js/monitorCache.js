
var cache = new MonitorCache();

function MonitorCache () {
	this.xsize_ = 0,
	this.ysize_ = 0,
	this.teams_ = new Array();
	this.map_ = new Array();
	//this.players_ = new Array();
	//this.eggs_ = new Array();
	
	this.ref = {
		0: "food",
		1: "linemate",
		2: "deraumere",
		3: "sibur",
		4: "mendiane",
		5: "phiras",
		6: "thystame",
		7: "empty"
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

MonitorCache.prototype.setMap = function(map) {
	this.map_ = map;
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

MonitorCache.prototype.getCaseFromPos = function(x, y) {
    var target = (parseInt(y) * this.ysize_) + parseInt(x);
    console.log(x + " " + y);
    console.log(this.xsize_);
    console.log(this.ysize_);
    console.log(target);
	if (this.ysize_ != 0 && this.xsize_ != 0 &&
		x < this.xsize_ && y < this.ysize_ && x >= 0 && y >= 0)
	{
		for (var i = 0; i != this.map_.length; i++)
		{
			if (i == target)
				return this.map_[i];
		}
	}
	console.log("Something wrong in MonitorCache.getCase()");
}

MonitorCache.prototype.getCase = function(target) {
	
	for (var i = 0; i != this.map_.length; i++)
		if (i == target)
			return this.map_[i];
	displayError("Something wrong in MonitorCache.getCase()");
}

MonitorCache.prototype.getSprite = function(aCase) {
	
	var sprite = 0,
   		value = aCase.ressources[0];
   		
   	for (var i = 0; i != aCase.ressources.length; i++)
   		if (aCase.ressources[i] > value)
   		{
   			sprite = i;
   			value = aCase.ressources[i];
   		}
   	if (value != 0)
   		return (this.ref[sprite]);
   	return (this.ref[7]);
}

MonitorCache.prototype.getMap = function() {
	return this.map_;
}
