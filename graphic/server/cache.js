/**
 * @author sylvia_r
 */

/* VAR */

var xsize_ = 0,
	ysize_ = 0,
	currentTimeUnit_ = 0,
	teams_ = new Array();
	map_ = require('./objects/map.js');
	
/* PUBLIC VAR */

exports.xsize_ = xsize_;
exports.ysize_ = ysize_;
exports.currentTimeUnit_ = currentTimeUnit_;
exports.teams_ = teams_;

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

/* OTHER */

exports.dump = function() {
    console.log("x : " + xsize_);
    console.log("y : " + ysize_);
    console.log("currentTimeUnit : " + currentTimeUnit_);
    console.log("teams : " + teams_);
    map_.dump();
};