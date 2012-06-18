/**
 * @author sylvia_r
 */

/* OBJECT */

function MapCase() {
	// this.food_ = 0;
	// this.linemate_ = 0;
	// this.deraumere_ = 0;
	// this.sibur_ = 0;
	// this.mendiane_ = 0;
	// this.phiras_ = 0;
	// this.thystame_ = 0;
	this.ressources_ = [0, 0, 0, 0, 0, 0, 0];
	
	var ref = {
		0: "food",
		1: "linemate",
		2: "deraumere",
		3: "sibur",
		4: "mendiane",
		5: "phiras",
		6: "thystame"
	};
}

function MapCase(f, l, d, s, m, p, t) {
	// this.food_ = f;
	// this.linemate_ = l;
	// this.deraumere_ = d;
	// this.sibur_ = s;
	// this.mendiane_ = m;
	// this.phiras_ = p;
	// this.thystame_ = t;
	this.ressources_ = [f, l, d, s, m, p, t];
	
	var ref = {
		0: "food",
		1: "linemate",
		2: "deraumere",
		3: "sibur",
		4: "mendiane",
		5: "phiras",
		6: "thystame"
	};
}

/* METHODS */

MapCase.prototype.getSprite = function(night) {
	
   	var sprite = 0,
   		value = ressources_[0];
   		
   	for (var i = 0; i != ressources_.length; i++)
   		if (ressources_[i] > value)
   		{
   			sprite = i;
   			value = ressources_[i];
   		}
   	return ref[sprite];
};

MapCase.prototype.getRessources = function() {
	return this.ressources_;
};

MapCase.prototype.dump = function(obj) {
	console.log(obj.ressources_[0]);
	console.log(obj.ressources_[1]);
	console.log(obj.ressources_[2]);
	console.log(obj.ressources_[3]);
	console.log(obj.ressources_[4]);
	console.log(obj.ressources_[5]);
	console.log(obj.ressources_[6]);
}

MapCase.prototype.setFood = function(v) {
   this.ressources_[0] = v;
};

MapCase.prototype.setLinemate = function(v) {
   this.ressources_[1] = v;
};

MapCase.prototype.setDeraumere = function(v) {
   this.ressources_[2] = v;
};

MapCase.prototype.setSibur = function(v) {
   this.ressources_[3] = v;
};

MapCase.prototype.setMendiane = function(v) {
   this.ressources_[4] = v;
};

MapCase.prototype.setPhiras = function(v) {
   this.pressources_[5] = v;
};

MapCase.prototype.setThystame = function(v) {
   this.ressources_[6] = v;
};

module.exports = MapCase;
