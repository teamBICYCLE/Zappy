/**
 * @author sylvia_r
 */

/* VAR */

var xsize_ = 0,
	ysize_ = 0,
	currentTimeUnit_ = 0,
	teams_ = new Array(),
	map_ = new (require("./objects/map.js")),
	players_ = new Array();
	eggs_ = new Array();
	
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
    players_.push(new Player(arg));
}

exports.addEggs = function(arg) {
	var Egg = require("./objects/egg.js");
	eggs_.push(new Egg(arg));
}

/* GET */

exports.getYSize = function() {
	return ysize_;
}

exports.getXSize = function() {
	return xsize_;
}

exports.getMapSize = function() {
	return "x : " + xsize_ + " | y : " + ysize_;
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

exports.getFormatedMap = function() {
	var array = new Array();
	
	for (var j = 0; j != ysize_; j++)
		for (var i = 0; i != xsize_; i++)
			array.push(map_.getCase(this, i, j));
	return array;
}

exports.getPlayer = function(id) {
	for (var i = 0; i != players_.length; i++)
		if (players_[i].getId() == id)
			return players_[i];
			
	console.log("Something wrong in Cache.getPlayer() : undefined reference to id #" + id);
}

exports.getPlayers = function() {
	return players_;
}

exports.getEggs = function() {
	return eggs_;
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
};