/**
 * @author lafont_g
 */

/* OBJECT */

var id_, fromplayer_, posx_, posy_;

var Egg = function(arg) {
	if (arg.length >= 5)
	{
		this.id_ = arg[1].replace("#", "");
    	this.fromplayer_ = arg[2].replace("#", "");
    	this.posx_ = arg[3];
    	this.posy_ = arg[4];
	}
};

/* METHODS */

Egg.prototype.dump = function() {
    console.log("=====Egg=====");
    console.log("id: " + this.id_);
    console.log("fromplayer: " + this.fromplayer_);
    console.log("posx: " + this.posx_);
    console.log("posy: " + this.posy_);
}

Egg.prototype.setId = function(v) {
    this.id_ = v;
}

Egg.prototype.setFromPlayer = function(v) {
    this.fromplayer_ = v;
}

Egg.prototype.setPosX = function(v) {
    this.posx_ = v;
}

Egg.prototype.setPosY = function(v) {
    this.posy_ = v;
}

Egg.prototype.getId = function() {
    return id_;
}

Egg.prototype.getFromPlayer = function() {
    return fromplayer_;
}

Egg.prototype.getPosX = function() {
    return posx_;
}

Egg.prototype.getPosY = function() {
    return posy_;
}

module.exports = Egg;