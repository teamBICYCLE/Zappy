/**
 * @author sylvia_r
 */

/* OBJECT */

function MapCase() {

	this.ressources_ = [0, 0, 0, 0, 0, 0, 0];
	this.x_ = 0;
	this.y_ = 0;
	this.spell_ = -1;
}

function MapCase(x, y, f, l, d, s, m, p, t) {
	
	this.x_ = x;
	this.y_ = y;
	this.ressources_ = [parseInt(f), parseInt(l), parseInt(d), parseInt(s), parseInt(m), parseInt(p), parseInt(t)];
}

MapCase.prototype.getRessources = function() {
	return this.ressources_;
};

MapCase.prototype.setFood = function(v) {
   this.ressources_[0] = parseInt(v);
};

MapCase.prototype.setLinemate = function(v) {
   this.ressources_[1] = parseInt(v);
};

MapCase.prototype.setDeraumere = function(v) {
   this.ressources_[2] = parseInt(v);
};

MapCase.prototype.setSibur = function(v) {
   this.ressources_[3] = parseInt(v);
};

MapCase.prototype.setMendiane = function(v) {
   this.ressources_[4] = parseInt(v);
};

MapCase.prototype.setPhiras = function(v) {
   this.pressources_[5] = parseInt(v);
};

MapCase.prototype.setThystame = function(v) {
   this.ressources_[6] = parseInt(v);
};

module.exports = MapCase;
