/**
 * @author sylvia_r
 */

/* OBJECT */

function MapCase() {

	this.ressources_ = [0, 0, 0, 0, 0, 0, 0];
	this.spell_ = -1;
	this.spellAnimation = 5;
}

function MapCase(f, l, d, s, m, p, t) {
	
	this.ressources_ = [f, l, d, s, m, p, t];
}

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

MapCase.prototype.setSpell = function(v) {
	this.speel_ = v;
	this.speelAnimation = 5;
}

MapCase.prototype.getSpell = function() {
	if (this.speelAnimation_ != -1)
		return this.speel_;
	return -1;
}

MapCase.prototype.spellAnimation = function(v) {
	if (this.speelAnimation_ != -1)
		this.speelAnimation_--;
}

module.exports = MapCase;
