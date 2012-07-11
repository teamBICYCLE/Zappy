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
	
	x = parseInt(x);
	y = parseInt(y);
	var target = parseInt(y * cache.getXSize()) + parseInt(x);
	
	if (cache.getYSize() != 0 && cache.getXSize() != 0 &&
		x < cache.getXSize() && y < cache.getYSize() && x >= 0 && y >= 0)
		return ({x_: x, y_: y, ressources_: data_[target].getRessources()});
	console.log("Something wrong in Map.getCase()");
}

Map.prototype.getRealCase = function(cache, x, y) {
	
	x = parseInt(x);
	y = parseInt(y);
	var target = parseInt(y * cache.getXSize()) + parseInt(x);
	
	if (cache.getYSize() != 0 && cache.getXSize() != 0 &&
		x < cache.getXSize() && y < cache.getYSize() && x >= 0 && y >= 0)
		return data_[target];
	console.log("Something wrong in Map.getRealCase()");
}

Map.prototype.setCase = function(cache, x, y, ressources) {
	
	x = parseInt(x);
	y = parseInt(y);
	var target = y * cache.getXSize() + x;
	
	if (cache.getYSize() != 0 && cache.getXSize() != 0 &&
		x < cache.getXSize() && y < cache.getYSize() && x >= 0 && y >= 0)
	{
		data_[target] = new Case(x, y, ressources[0], ressources[1],
							ressources[2], ressources[3], 
							ressources[4], ressources[5], ressources[6]);
	}
	else
		console.log("Something wrong in Cache.setCase()");
}

Map.prototype.length = function() {
	return data_.length;
}

module.exports = Map;
