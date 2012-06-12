/**
 * @author sylvia_r
 */

/* VAR */

var xsize_ = 0,
	ysize_ = 0,
	currentTimeUnit_ = 0,
	teams_ = new Array(),
	map_ = new (require("./objects/map.js")),
	player_ = new Array();
	
/* SET */

exports.setMapSize = function(x, y) {
	xsize_ = x;
	ysize_ = y;
	map_.make(x, y);
}

exports.setCurrentTimeUnit = function(t) {
	currentTimeUnit_ = t;
}

exports.addTeam = function(name) {
	teams_.push(name);
}

exports.setCase = function(x, y, ressources) {
	map_.setCase(this, x, y, ressources);
}

exports.addPlayer = function(arg) {
    var Player = require("./objects/player.js");
    player_.push(new Player(arg));
}

/* GET */

exports.getYSize = function() {
	return ysize_;
}

exports.getXSize = function() {
	return xsize_;
}

exports.getCurrentTimeUnit = function() {
	return currentTimeUnit_;
}

exports.getTeams = function() {
	return teams_;
}

exports.getMap = function() {
	return map_;
}

/* OTHER */

exports.isWhole = function() {
	if (teams_.length > 0 && currentTimeUnit_ > 0 &&
		ysize_ > 0 && xsize_ > 0)
			return true;
		return false;
}

exports.dump = function() {
    console.log("x : " + xsize_);
    console.log("y : " + ysize_);
    console.log("currentTimeUnit : " + currentTimeUnit_);
    console.log("teams : " + teams_);
    console.log("player : " + players_);
    // var Case = new (require("./objects/mapCase.js"));
    // if (xsize_ != 0 && ysize_ != 0)
    // {
    	// //console.log("Dump case !" + xsize_ + ysize_);
    	// Case.dump(map_.getCase(this, 2, 2));
    // }
};