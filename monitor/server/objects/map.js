/**
 * @author sylvia_r
 */

var data_ = new Array();
var Case = require("./mapCase.js")

var Map = function()
{
};

Map.prototype.dump = function() {
	
	var tmpCase = new Case();
	
	for (var i = 0; i != data_.length; i++)
		tmpCase.dump(data_[i]);
}

Map.prototype.make = function(x, y) {
	for (var i = 0; i != y; i++)
	{
		for (var j = 0; j != x; j++)
		{
			var nowCase = new Case();
			data_.push(nowCase);
		}
	}
}

Map.prototype.getCase = function(cache, x, y) {
	var target = parseInt(y * cache.getYSize()) + parseInt(x);

	if (cache.getYSize() != 0 && cache.getXSize() != 0 &&
		x < cache.getXSize() && y < cache.getYSize() && x >= 0 && y >= 0)
	{
		for (var i = 0; i != data_.length; i++)
		{
			if (i == target)
				return ({x: x, y: y, ressources: data_[i]});
		}
	}
	console.log("Something wrong in Map.getCase()");
}

Map.prototype.setCase = function(cache, x, y, ressources) {
	var target = parseInt(y * cache.getYSize()) + parseInt(x);
	
	if (cache.getYSize() != 0 && cache.getXSize() != 0 &&
		x < cache.getXSize() && y < cache.getYSize() && x >= 0 && y >= 0)
	{
		for (var i = 0; i != data_.length; i++)
		{
			if (i == target)
			{
				data_[i] = new Case(ressources[0], ressources[1],
									ressources[2], ressources[3], 
									ressources[4], ressources[5], ressources[6]);
			}
		}
		
	}
	else
		console.log("Something wrong in Cache.setCase()");
}

Map.prototype.length = function() {
	return data_.length;
}

module.exports = Map;
