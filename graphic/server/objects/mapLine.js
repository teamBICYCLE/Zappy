/**
 * @author sylvia_r
 */

/* PRIVATE */

var data_ = new Array();

/* METHODS */

exports.make = function(length) {
	for (var i = 0; i != length; i++)
		data_.push(0);
};

exports.setY = function(mapCase) {
    for (var i = 0; i != data_.length; i++)
    {
    	if (i == y)
    		data_[i] = mapCase;
    }
};

exports.dump = function() {
	console.log(data_);
};