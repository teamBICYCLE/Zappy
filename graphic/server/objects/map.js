/**
 * @author sylvia_r
 */

/* PRIVATE */

var data_ = new Array();

/* METHODS */

exports.addLine = function(line) {
    data_.push(line);
};

exports.make = function(x, y) {
	var line = require('./mapLine.js');
	
	for (var i = 0; i != y; i++)
		data_.push(line.make(x));
};

exports.dump = function() {
	// for (var i = 0; i != data_.length; i++)
	// {
		// data_[i].dump();
	// }
}
