/**
 * @author sylvia_r
 */

var layers = new Layers();

function Layers(xsize, ysize){
	
	this.imgs = {
		0 : {name: "food", img: new Image()},
		1 : {name: "linemate", img: new Image()},
		2 : {name: "floor", img: new Image()},
		3 : {name: "highlight", img: new Image()},
		999 : {name: "undefined", img: new Image()}
	};
	
	this.canvasHandler = new CanvasHandler();
	
	this.tileWidth = 64;
	this.tileHeight = 64;
	this.mapWidth = xsize;
	this.mapHeight = ysize;
	
	/* Image preload */
	
	for (var i = 0; typeof(this.imgs[i]) != "undefined"; i++)
		this.imgs[i].img.src = "img/" + this.imgs[i].name + ".png";
		
	this.imgs[999].img.src = "img/" + this.imgs[999].name + ".png";
}

/* GET */

Layers.prototype.getMapSize = function() {
	
	return ({width: this.mapWidth, height: this.mapHeight});	
}

Layers.prototype.getTileSize = function() {
	
	return ({width: this.tileWidth, height: this.tileHeight});	
}

Layers.prototype.getImg = function(name) {
	
	for (var i = 0; typeof(this.imgs[i]) != "undefined"; i++)
		if (this.imgs[i].name == name)
			return this.imgs[i].img;
			
	// undefined
	displayError("Undefined reference to " + name + ".png.");
	return this.imgs[999].img;
}

/* DRAWING */

Layers.prototype.draw = function(canvas, img, x, y) {
	
	//console.log("Drawing on canvas : " + canvas);
	//console.log(this.getImg(img));
	var c = this.canvasHandler.get(canvas),
		leftD = ((x * this.tileWidth / 2) + (y * this.tileWidth / 2)),
		topD = ((y * this.tileHeight / 4) - (x * this.tileHeight / 4));
		
	/* pour center */
	
	leftD += (c.width / 2) - ((this.mapWidth / 2) * this.tileWidth);
	topD += (c.height / 2);

	c.ctx.drawImage(this.getImg(img), leftD, topD);
}

Layers.prototype.drawFromPixel = function(canvas, img, x , y) {
	
	var c = this.canvasHandler.get(canvas);
	
	c.ctx.drawImage(this.getImg(img), x, y);
}
