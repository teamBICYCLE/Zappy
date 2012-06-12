/**
 * @author lafont_g
 */

/* OBJECT */

var id_, fromplayer_, posx_, posy_;

var Egg = function(arg) {
    this.id_ = arg[1];
    this.fromplayer_ = arg[2];
    this.posx_ = arg[3];
    this.posy_ = arg[4];
};

/* METHODS */

Egg.prototype.dump = function(obj) {
    console.log("=====Egg=====");
    console.log("id: " + obj.id_);
    console.log("fromplayer: " + obj.fromplayer_);
    console.log("posx: " + posx_);
    console.log("posy: " + posy_);
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