/**
 * @author sylvia_r
 */

function ImgLoader() {
	
	this.imgs_ = {
		0 : {name: "floor", img: new Image()},
		1 : {name: "food", img: new Image()},
		2 : {name: "highlight", img: new Image()},
		3 : {name: "player-north", img: new Image()},
		4 : {name: "player-south", img: new Image()},
		5 : {name: "player-west", img: new Image()},
		6 : {name: "player-east", img: new Image()},
		7 : {name: "linemate_small", img: new Image()},
		8 : {name: "linemate_medium", img: new Image()},
		9 : {name: "linemate_large", img: new Image()},
		10 : {name: "deraumere_small", img: new Image()},
		11 : {name: "deraumere_medium", img: new Image()},
		12 : {name: "deraumere_large", img: new Image()},
		13 : {name: "sibur_small", img: new Image()},
		14 : {name: "sibur_medium", img: new Image()},
		15 : {name: "sibur_large", img: new Image()},
		16 : {name: "mendiane_small", img: new Image()},
		17 : {name: "mendiane_medium", img: new Image()},
		18 : {name: "mendiane_large", img: new Image()},
		19 : {name: "phiras_small", img: new Image()},
		20 : {name: "phiras_medium", img: new Image()},
		21 : {name: "phiras_large", img: new Image()},
		22 : {name: "thystame_small", img: new Image()},
		23 : {name: "thystame_medium", img: new Image()},
		24 : {name: "thystame_large", img: new Image()},
		25 : {name: "food_small", img: new Image()},
		26 : {name: "food_medium", img: new Image()},
		27 : {name: "food_large", img: new Image()},
		999 : {name: "undefined", img: new Image()}
	};
	
	for (var i = 0; typeof(this.imgs_[i]) != "undefined"; i++)
		this.imgs_[i].img.src = "img/" + this.imgs_[i].name + ".png";
		
	this.imgs_[999].img.src = "img/" + this.imgs_[999].name + ".png";
}

ImgLoader.prototype.get = function(name) {
	
	for (var i = 0; typeof(this.imgs_[i]) != "undefined"; i++)
		if (this.imgs_[i].name == name)
			return this.imgs_[i].img;
			
	// undefined
	//displayError("Undefined reference to " + name + ".png.");
	return this.imgs_[999].img;
}