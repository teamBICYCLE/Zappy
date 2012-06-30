/**
 * @author sylvia_r
 */

function ImgLoader() {
	
	this.imgs_ = {
		0 : {name: "floor", img: new Image()},
		1 : {name: "food", img: new Image()},
		2 : {name: "linemate", img: new Image()},
		3 : {name: "highlight", img: new Image()},
		4 : {name: "empty", img: new Image()},
		5 : {name: "deraumere", img: new Image()},
		6 : {name: "sibur", img: new Image()},
		7 : {name: "mendiane", img: new Image()},
		8 : {name: "phiras", img: new Image()},
		9 : {name: "thystame", img: new Image()},
		10 : {name: "player-north", img: new Image()},
		11 : {name: "player-south", img: new Image()},
		12 : {name: "player-west", img: new Image()},
		13 : {name: "player-east", img: new Image()},
		14 : {name: "linemate_small", img: new Image()},
		15 : {name: "linemate_medium", img: new Image()},
		16 : {name: "linemate_large", img: new Image()},
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