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
	this.centerX = (this.mapWidth / 2);
	this.centerY = (this.mapHeight / 2);
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

Layers.prototype.setCenter = function(x, y) {
	
	this.centerX = x;
	this.centerY = y;
}

Layers.prototype.resetAndRedraw = function() {
	this.centerX = (this.mapWidth / 2);
	this.centerY = (this.mapHeight / 2);
	this.zoom = 10;
	this.tileWidth = 128;
	this.tileHeight = 128;
	
	this.clear("cHighLight");
	this.clear("cMap");
	ressources_draw(this);
	players_draw(this);
	map_draw(this.mapWidth, this.mapHeight, this);
}

/* DRAWING */

Layers.prototype.centerAt = function(x, y) {
	
	var alignTop, alignLeft;
	
	alignTop = ((this.mapHeight - 1) - (x + y)) * (this.tileHeight / 4);
		
	if (x <= y)
		alignLeft = ((y - x) * (this.tileWidth / 2));
	else if (x > y)
	{
		alignLeft = ((x - y) * (this.tileWidth / 2));
		alignLeft *= -1;
	}
	
	return ({left: alignLeft, top: alignTop});
}

Layers.prototype.padding = function(canvas) {
	
	var c = this.canvasHandler.get(canvas),
		topOffset = (c.height / 2) - ((this.mapHeight / 2) * (this.tileHeight / 2)),
		leftOffset = (c.width / 2) - (this.tileWidth / 2);
		
	if (playerFollowed == -1)	
		center = this.centerAt(this.centerX, this.centerY);
	else
	{
		var player = cache.getPlayer(playerFollowed),
			oldCenter = {x: this.centerX, y: this.centerY},
			pPos = {x: parseInt(player.posx_), y: parseInt(player.posy_)};
		
		this.setCenter(pPos.x, pPos.y);
		if (oldCenter.x != this.centerX || oldCenter.y != this.centerY)
			{
				zoom = 10;
				this.tileWidth = 128;
				this.tileHeight = 128;
				console.log("draw");
				center = this.centerAt(pPos.x, pPos.y);
				this.clear("cHighLight");
				ressources_draw(this);
				map_draw(this.mapWidth, this.mapHeight, this);
			}
	}
		
	return ({left: leftOffset + center.left , top: topOffset + center.top});
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
		c.ctx.globalAlpha = 0.6;
	
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