/**
 * @author lafont_g
 */

/* OBJECT */

var id_, posx_, posy_, orientation_, level_, team_;

var Player = function(arg) {
    this.id_ = arg[1];
    this.posx_ = arg[2];
    this.posy_ = arg[3];
    this.orientation_ = arg[4];
    this.level_ = arg[5];
    this.team_ = arg[6];
};

/* METHODS */

Player.prototype.dump = function(obj) {
    console.log("====Player====");
    console.log("id: " + obj.id_);
    console.log("posx: " + obj.posx_);
    console.log("posy: " + obj.posy_);
    console.log("ori: " + obj.orientation_);
    console.log("level: " + obj.level_);
    console.log("team: " + obj.team_);
}

Player.prototype.setId = function(v) {
    this.id_ = v;
}

Player.prototype.setPosX = function(v) {
    this.posx_ = v;
}

Player.prototype.setPosY = function(v) {
    this.posy_ = v;
}

Player.prototype.setOrientation = function(v) {
    this.orientation_ = v;
}

Player.prototype.setLevel = function(v) {
    this.level_ = v;
}

Player.prototype.setTeam = function(v) {
    this.team_ = v;
}

Player.prototype.getId = function() {
    return id_;
}

Player.prototype.getPosX = function() {
    return posx_;
}

Player.prototype.getPosY = function() {
    return posy_;
}

Player.prototype.getOrientation = function() {
    return orientation_;
}

Player.prototype.getLevel = function() {
    return level_;
}

Player.prototype.getTeam = function() {
    return team_;
}

module.exports = Player;