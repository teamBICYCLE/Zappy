
var cache = new MonitorCache();

function MonitorCache () {
	this.xsize_ = 0,
	this.ysize_ = 0,
	this.teams_ = new Array();
	//this.map_ = new (require("./objects/map.js"));
	//this.players_ = new Array();
	//this.eggs_ = new Array();
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