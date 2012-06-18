
function monitorCache () {
	this.xsize_ = 0,
	this.ysize_ = 0,
	this.teams_ = new Array(),
	//map_ = new (require("./objects/map.js")),
	this.players_ = new Array();
	this.eggs_ = new Array();
}

monitorCache.prototype.setMapSize = function(x, y) {
	this.xsize_ = x;
	this.ysize_ = y;
	//map_.make(x, y);
}