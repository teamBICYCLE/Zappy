/**
 * @author lafont_g
 */

/* OBJECT */

var id_, posx_, posy_, hatches_;

var Egg = function(id, x, y) {
	this.id_ = parseInt(id.replace("#", ""));
	this.posx_ = parseInt(x);
	this.posy_ = parseInt(y);
	this.hatches_ = false;
	this.dead_ = false;
};

/* METHODS */

Egg.prototype.dump = function() {
    console.log("=====Egg=====");
    console.log("id: " + this.id_);
    console.log("posx: " + this.posx_);
    console.log("posy: " + this.posy_);
}

Egg.prototype.setId = function(v) {
    this.id_ = v;
}

Egg.prototype.setPosX = function(v) {
    this.posx_ = v;
}

Egg.prototype.setPosY = function(v) {
    this.posy_ = v;
}

Egg.prototype.setHatches = function(v) {
	this.hatches_ = v;
}

Egg.prototype.setDead = function(v) {
	this.dead_ = v;
}

Egg.prototype.getId = function() {
    return this.id_;
}

Egg.prototype.getPosX = function() {
    return this.posx_;
}

Egg.prototype.getPosY = function() {
    return this.posy_;
}

Egg.prototype.isHatches = function() {
	return this.hatches_;	
}

Egg.prototype.isDead = function() {
	return this.dead_;
}

module.exports = Egg;