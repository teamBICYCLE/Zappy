/**
 * @author sylvia_r
 */

/* VAR */

var xsize_ = 0,
	ysize_ = 0,
	currentTimeUnit_ = 0,
	teams_ = new Array(),
	teamsColor_ = new Array(),
	map_ = new (require("./objects/map.js")),
	players_ = new Array(),
	eggs_ = new Array(),
	cmdMessages_ = new Array();
	
/* SET */

exports.setMapSize = function(x, y) {
	xsize_ = x;
	ysize_ = y;
	map_.make(x, y);
}

exports.setCurrentTimeUnit = function(t) {
	currentTimeUnit_ = t;
}

function random_color() {
    var letters = '0123456789ABCDEF'.split('');
    var color = '#';
    for (var i = 0; i < 6; i++ ) {
        color += letters[Math.round(Math.random() * 15)];
    }
    return color;
}

exports.addTeam = function(name) {
	teams_.push(name);
	teamsColor_.push(random_color());
}

exports.setCase = function(x, y, ressources) {
	map_.setCase(this, x, y, ressources);
}

exports.addPlayer = function(arg) {
    var Player = require("./objects/player.js");
    players_.push(new Player(arg));
    this.addMessage("Team " + arg[6] + " welcomes a new player.");
}

exports.removePlayer = function(argId) {
	
	var id = argId.replace("#", "")
	for (var i = 0; i < players_.length; i++)
		if (id == players_[i].getId())
			players_.splice(i, 1);
			
	this.addMessage("Player " + id + " died (not enough food)");
}

exports.addEggs = function(id, x, y) {
	var Egg = require("./objects/egg.js");
	eggs_.push(new Egg(id, x, y));
}

exports.removeEgg = function(argId) {
	
	var id = argId.replace("#", "")
	for (var i = 0; i < eggs_.length; i++)
		if (id == eggs_[i].getId())
			eggs_.splice(i, 1);
}

exports.addMessage = function(msg) {
	cmdMessages_.push(msg);
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

exports.getTeamsColor = function() {
	return teamsColor_;
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
	
	id = parseInt(id.replace("#", ""));
	
	for (var i = 0; i != players_.length; i++)
		if (players_[i].getId() == id)
			return players_[i];
			
	displayError("Something wrong in Cache.getPlayer() : undefined reference to id #" + id);
}

exports.getEgg = function(id) {
	
	id = parseInt(id.replace("#", ""));
	
	for (var i = 0; i != eggs_.length; i++)
		if (eggs_[i].getId() == id)
			return eggs_[i];
			
	displayError("Something wrong in Cache.getEgg() : undefined reference to id #" + id);
}

exports.getPlayers = function() {
	return players_;
}

exports.getEggs = function() {
	return eggs_;
}

exports.getCmdMessages = function() {
	return cmdMessages_;
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

exports.cmdMessagesEmpty = function() {
	cmdMessages_ = [];
}
