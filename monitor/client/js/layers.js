/**
 * @author sylvia_r
 */

var layers = new Layers();

function Layers(xsize, ysize){
	
	this.imgs = new ImgLoader();
	
	this.canvasHandler = new CanvasHandler();
	
	this.tileWidth = 128;
	this.tileHeight = 128;
	this.mapWidth = xsize;
	this.mapHeight = ysize;
}

/* GET */

Layers.prototype.getMapSize = function() {
	
    return ({width: parseInt(this.mapWidth), height: parseInt(this.mapHeight)});	
}

Layers.prototype.getTileSize = function() {
	
    return ({width: parseInt(this.tileWidth), height: parseInt(this.tileHeight)});	
}

/* SET */

Layers.prototype.setMapSize = function(x, y) {
	
    this.mapWidth = parseInt(x);
    this.mapHeight = parseInt(y);	
}

/* DRAWING */

Layers.prototype.padding = function(canvas) {
	var c = this.canvasHandler.get(canvas),
	topOffset = (c.height / 2) - ((this.mapHeight / 2) * (this.tileHeight / 2));
	leftOffset = (c.width / 2) - (this.tileWidth / 2);

	return ({left: leftOffset, top: topOffset});
}

Layers.prototype.draw = function(canvas, img, x, y) {
	
	x = parseInt(x);
	y = parseInt(y);
	var c = this.canvasHandler.get(canvas),
		leftD = this.padding(canvas).left + ((x - y) * this.tileWidth / 2),
		topD = this.padding(canvas).top + ((x + y) * this.tileHeight / 4);

	c.ctx.drawImage(this.imgs.get(img), leftD, topD);
}

Layers.prototype.drawFromPixel = function(canvas, img, x , y) {
	
	x = parseInt(x);
	y = parseInt(y);
	var c = this.canvasHandler.get(canvas);
	
	c.ctx.drawImage(this.imgs.get(img), x, y);
}

Layers.prototype.drawSocle = function(canvas, color, x, y) {
	
	x = parseInt(x);
	y = parseInt(y);
	var c = this.canvasHandler.get(canvas),
		leftD = this.padding(canvas).left + ((x - y) * this.tileWidth / 2) + this.tileWidth / 2,
		topD = this.padding(canvas).top + this.tileHeight + (32 * 3) + 24;
		
	c.ctx.save();
	c.ctx.scale(1, 0.58);
	c.ctx.beginPath();
	c.ctx.fillStyle = color;
	c.ctx.arc(leftD, topD, 32, 0, Math.PI * 2, true);
	c.ctx.fill();
	c.ctx.closePath();
	c.ctx.restore();
}

Layers.prototype.clear = function(canvas) {
	
	var c = this.canvasHandler.get(canvas);
	
	c.ctx.clearRect(0, 0, c.width, c.height);
}

Layers.prototype.zoom = function(canvas) {


	var c = this.canvasHandler.get(canvas);
	// c.ctx.scale(10, 10);
	// c.ctx.scale(0.5, 0.5);
	// c.ctx.scale(-10, -10);
	console.log('eeee');
	this.draw(canvas, "floor", 150, 150);
}
