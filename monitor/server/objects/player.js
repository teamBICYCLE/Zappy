/**
 * @author lafont_g
 */

/* OBJECT */

var Player = function(arg, color) {
	if (arg.length >= 7)
	{
		//console.log("new player !!!!!!! ====> " + parseInt(arg[1].replace("#", "")));
		this.id_ = parseInt(arg[1].replace("#", ""));
	    this.posx_ = parseInt(arg[2]);
	    this.posy_ = parseInt(arg[3]);
	    this.orientation_ = parseInt(arg[4]);
	    this.level_ = parseInt(arg[5]);
	    this.team_ = arg[6];
	    this.color_ = color;
	    this.inventory_ = [0, 0, 0, 0, 0, 0, 0];
	    this.animationLoop_ = [-1, -1, -1, -1, -1, -1];
		this.inventoryChange_ = false;
		this.broadcast_ = "";
		//piex pbc pic pfk pdr pgt
	} 
};

/* METHODS */

Player.prototype.dump = function() {
    console.log("====Player====");
    console.log("id: " + this.id_);
    console.log("posx: " + this.posx_);
    console.log("posy: " + this.posy_);
    console.log("ori: " + this.orientation_);
    console.log("level: " + this.level_);
    console.log("team: " + this.team_);
    console.log("Food: " + this.inventory_[0]);
    console.log("Linemate: " + this.inventory_[1]);
    console.log("Deraumere: " + this.inventory_[2]);
    console.log("Sibur: " + this.inventory_[3]);
    console.log("Mendiane: " + this.inventory_[4]);
    console.log("Phiras: " + this.inventory_[5]);
    console.log("Thystame: " + this.inventory_[6]);
}

/* SET */

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

Player.prototype.setInventory = function(elems) {
	
	for (var i = 0; i != elems.length; i++)
		this.inventory_[i] = parseInt(elems[i]);
}

/* GET */

Player.prototype.getId = function() {
    return this.id_;
}

Player.prototype.getPos = function() {
	return "x : " + this.posx_ + " | y : " + this.posy_;
}

Player.prototype.getPosX = function() {
    return this.posx_;
}

Player.prototype.getPosY = function() {
    return this.posy_;
}

Player.prototype.getOrientation = function() {
    return this.orientation_;
}

Player.prototype.getLevel = function() {
    return this.level_;
}

Player.prototype.getTeam = function() {
    return this.team_;
}

Player.prototype.getInventory = function() {
	var inventory = {
		food: this.inventory_[0],
		linemate: this.inventory_[1],
		deraumere: this.inventory_[2],
		sibur: this.inventory_[3],
		mendiane: this.inventory_[4],
		phiras: this.inventory_[5],
		thystame: this.inventory_[6]
	};
	
	return inventory;
}

Player.prototype.getBubbleAnimation = function() {
		
	var ret = {
		pex: this.animationLoop_[0],
		pbc: this.animationLoop_[1],
		pic: this.animationLoop_[2],
		pfk: this.animationLoop_[3],
		pdr: this.animationLoop_[4],
		pgt: this.animationLoop_[5]
	}
	return ret;
}

/* animation set */

Player.prototype.setPex = function() {
	this.animationLoop_[0] += 10;
}

Player.prototype.setPbc = function(msg) {
	this.animationLoop_[1] += 40;
	this.broadcast_ = msg;
}

Player.prototype.setPic = function() {
	this.animationLoop_[2] += 20;
}

Player.prototype.setPfk = function() {
	this.animationLoop_[3] += 10;
}

Player.prototype.setPdr = function() {
	this.animationLoop_[4] += 5;
}

Player.prototype.setPgt = function() {
	this.animationLoop_[5] += 5;
}

/* other */

Player.prototype.bubbleAnimation = function() {
	for (var i = 0; i != this.animationLoop_.length; i++)
		if (this.animationLoop_[i] != -1)
			this.animationLoop_[i] -= 1;
}

module.exports = Player;