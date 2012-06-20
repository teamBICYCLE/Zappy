/**
 * @author lafont_g
 */

/* OBJECT */

var id_, posx_, posy_, orientation_, level_, team_,
	inventoryFood_, inventoryLinemate_, inventoryDeraumere_, 
	inventorySibur_, inventoryMendiane_, inventoryPhiras_,
	inventoryThystame_;

var Player = function(arg) {
	if (arg.length >= 7)
	{
		this.id_ = arg[1].replace("#", "");
	    this.posx_ = arg[2];
	    this.posy_ = arg[3];
	    this.orientation_ = arg[4];
	    this.level_ = arg[5];
	    this.team_ = arg[6];
	    this.inventoryFood_ = 0;
	    this.inventoryLinemate_ = 0,
		this.inventoryDeraumere_ = 0,
		this.inventorySibur_ = 0,
		this.inventoryMendiane_ = 0,
		this.inventoryPhiras_ = 0,
		this.inventoryThystame_ = 0;
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
    console.log("Food: " + this.inventoryFood_);
    console.log("Linemate: " + this.inventoryLinemate_);
    console.log("Deraumere: " + this.inventoryDeraumere_);
    console.log("Sibur: " + this.inventorySibur_);
    console.log("Mendiane: " + this.inventoryMendiane_);
    console.log("Phiras: " + this.inventoryPhiras_);
    console.log("Thystame: " + this.inventoryThystame_);
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

/* GET */

Player.prototype.getId = function() {
    return id_;
}

Player.prototype.getPos = function() {
	return "x : " + posx_ + " | y : " + posy_;
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

Player.prototype.getInventory = function() {
	var inventory = {
		food: this.inventoryFood_,
		linemate: this.inventoryLinemate_,
		deraumere: this.inventoryDeraumere_,
		sibur: this.inventorySibur_,
		mendiane: this.inventoryMendiane_,
		mendiane: this.inventoryPhiras_,
		thystame: this.inventoryThystame_
	};
	
	return inventory;
}

module.exports = Player;