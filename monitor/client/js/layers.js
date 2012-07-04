/**
 * @author sylvia_r
 */

function Layers(xsize, ysize){
	
	this.imgs = new ImgLoader();
	
	this.canvasHandler = new CanvasHandler();
	
	this.tilesSizeLevel = [0, 12, 25, 38, 51, 64, 76, 89, 102, 115, 128];
	
	this.tileWidth = 128;
	this.tileHeight = 128;
	this.mapWidth = xsize;
	this.mapHeight = ysize;
}

/* GET */

Layers.prototype.getTileLevel = function(level) {
	
    return (this.tilesSizeLevel[level]);	
}

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

Layers.prototype.setTileSize = function(w, h) {
	
    this.tileWidth = w;
    this.tileHeight = h;
}

/* DRAWING */

function abs(nb) {
	return ((nb < 0) ? (-nb) : (nb));
}

Layers.prototype.centerAt = function(x, y) {
	
	var left, top, ox, oy, medx, medy, multx, multy;
	
	medx = parseInt(this.mapWidth / 2);
	medy = parseInt(this.mapHeight / 2);
	multx = 1;
	multy = 1;
	
	ox = abs(x - medx);
	oy = abs(y - medy);
	if (x > medx)
		multx = -1;	
	if (y > medy)
		multy = -1;	
	
	left = ox * this.tileWidth;
	left *= multx;
	top = oy * (this.tileHeight / 2);
	top *= multy;
	//top = (this.mapHeight / 2) * (this.tileHeight / 2) - (this.tileHeight / 4);
	//console.log(left);
	return ({left: left, top: top});
}

Layers.prototype.padding = function(canvas) {
	
	var c = this.canvasHandler.get(canvas),
		topOffset = (c.height / 2) - ((this.mapHeight / 2) * (this.tileHeight / 2)),
		leftOffset = (c.width / 2) - (this.tileWidth / 2),
		center = this.centerAt(parseInt(this.mapHeight / 2), parseInt(this.mapWidth / 2));
	
	//leftOffset += (this.mapWidth / 2) * this.tileWidth - (this.tileWidth / 2);
	//topOffset += (this.mapHeight / 2) * (this.tileHeight / 2) - (this.tileHeight / 4);
	//console.log(leftOffset + " " + topOffset);
	return ({left: leftOffset + center.left, top: topOffset + center.top});
}

Layers.prototype.draw = function(canvas, img, x, y, alpha) {
	
	x = parseInt(x);
	y = parseInt(y);
	var c = this.canvasHandler.get(canvas),
		//leftD = this.padding(canvas).left + ((x - y) * this.tileWidth / 2),
		//topD = this.padding(canvas).top + ((x + y) * this.tileHeight / 4);
		leftD = ((x - y) * this.tileWidth / 2),
		topD = ((x + y) * this.tileHeight / 4);
		
	c.ctx.save();
	//c.ctx.translate(this.padding(canvas).left, this.padding(canvas).top);
	c.ctx.translate(this.padding(canvas).left, this.padding(canvas).top);
	if (alpha)
		c.ctx.globalAlpha = 0.4;
	
	if (zoom != 10)
		c.ctx.scale(zoom / (this.tilesSizeLevel.length - 1), zoom / (this.tilesSizeLevel.length - 1));
	c.ctx.drawImage(this.imgs.get(img), leftD, topD);
	c.ctx.restore();
}

Layers.prototype.drawFromPixel = function(canvas, img, x , y) {
	
	x = parseInt(x);
	y = parseInt(y);
	var c = this.canvasHandler.get(canvas);
	
	c.ctx.drawImage(this.imgs.get(img), x, y);
}

Layers.prototype.clear = function(canvas) {
	
	var c = this.canvasHandler.get(canvas);
	
	c.ctx.clearRect(0, 0, c.width, c.height);
}