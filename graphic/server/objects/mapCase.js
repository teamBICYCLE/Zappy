/**
 * @author sylvia_r
 */

/* OBJECT */

function MapCase() {
	this.food_ = 0;
	this.linemate_ = 0;
	this.deraumere_ = 0;
	this.sibur_ = 0;
	this.mendiane_ = 0;
	this.phiras_ = 0;
	this.thystame_ = 0;
}

function MapCase(f, l, d, s, m, p, t) {
	this.food_ = f;
	this.linemate_ = l;
	this.deraumere_ = d;
	this.sibur_ = s;
	this.mendiane_ = m;
	this.phiras_ = p;
	this.thystame_ = t;
}

/* METHODS */

MapCase.prototype.getSprite = function(night) {
	
	var plus = "_day.png";
	if (night)
		plus = "_night.png"
   	
   	// TODO
   	var sprite = "food";
   	return sprite.concat(plus);
};

MapCase.prototype.getRessources = function() {
	var ret = [this.food_, this.linemate_, this.deraumere_, this.sibur_, this.mendiane_, this.phiras_, this.thystame_];
	return ret;
};

MapCase.prototype.dump = function(obj) {
	console.log("============");
	console.log(obj.food_);
	console.log(obj.linemate_);
	console.log(obj.deraumere_);
	console.log(obj.sibur_);
	console.log(obj.mendiane_);
	console.log(obj.phiras_);
	console.log(obj.thystame_);
}

MapCase.prototype.setFood = function(v) {
   this.food_ = v;
};

MapCase.prototype.setLinemate = function(v) {
   this.linemate_ = v;
};

MapCase.prototype.setDeraumere = function(v) {
   this.deraumere_ = v;
};

MapCase.prototype.setSibur = function(v) {
   this.sibur_ = v;
};

MapCase.prototype.setMendiane = function(v) {
   this.mendiane_ = v;
};

MapCase.prototype.setPhiras = function(v) {
   this.phiras_ = v;
};

MapCase.prototype.setThystame = function(v) {
   this.thystame_ = v;
};

module.exports = MapCase;
