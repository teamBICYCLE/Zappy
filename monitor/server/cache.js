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

// function random_color() {
    // var letters = '0123456789ABCDEF'.split('');
    // var color = '#';
    // for (var i = 0; i < 6; i++ ) {
        // color += letters[Math.round(Math.random() * 15)];
    // }
    // return color;
// }

function random_color(h, s, v) {
	
	h += 0.618033988749895;
	h %= 1;
	
	var h_i = parseInt(h * 6),
		f = h * 6 - h_i,
		p = v * (1 - s),
		q = v * (1 - f * s),
		t = v * (1 - (1 - f) * s),
		ret;
  	
  	if (h_i == 0)
  		{r = v; g = t; v = p;}
  	else if (h_i == 1)
  		{r = q; g = v; b = p;}
  	else if (h_i == 2)
  		{r = p; g = v; b = t;}
  	else if (h_i == 3)
  		{r = p; g = q; b = v;}
  	else if (h_i == 4)
  		{r = t; g = p; b = v;}
  	else if (h_i == 5)
  		{r = v; g = p; b = q;}
  	
  r = parseInt(r * 256);
  g = parseInt(g * 256);
  b = parseInt(b * 256);
  
  console.log(r + " " + g + " " + b);
  ret = b | (g << 8) | (r << 16);
  console.log('#' + ret.toString(16));
  return '#' + ret.toString(16);
}

exports.addTeam = function(name) {
	teams_.push(name);
}

exports.addTeamColor = function() {
	for (var i = 0; i != teams_.length;  i++)
		teamsColor_.push(random_color(((i + 1) / teams_.length), 0.55, 0.99));
	teams_.reverse();
	teamsColor_.reverse();
}

exports.setCase = function(x, y, ressources) {
	map_.setCase(this, x, y, ressources);
}

exports.addPlayer = function(arg) {
    var Player = require("./objects/player.js");
    players_.push(new Player(arg, this.getTeamColor(arg[6])));
    this.addMessage("Team " + arg[6] + " welcomes a new player.");
}

exports.removePlayer = function(argId) {
	
	var id = argId.replace("#", "")
	for (var i = 0; i < players_.length; i++)
		if (id == players_[i].getId())
			players_.splice(i, 1);
			
	this.addMessage("Player " + id + " died (not enough food)");
}

exports.addEgg = function(id, x, y) {
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

exports.getTeamColor = function(team) {
	
	for (var i = 0; i != teams_.length; i++)
		if (team == teams_[i])
			return teamsColor_[i];
			
	console.log("Something wrong in Cache.getTeamColor() : undefined reference to team " + team);
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
			
	console.log("Something wrong in Cache.getPlayer() : undefined reference to id #" + id);
}

exports.getEgg = function(id) {
	
	id = parseInt(id.replace("#", ""));
	
	for (var i = 0; i != eggs_.length; i++)
		if (eggs_[i].getId() == id)
			return eggs_[i];
			
	console.log("Something wrong in Cache.getEgg() : undefined reference to id #" + id);
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