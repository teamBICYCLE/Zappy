/**
 * @author sylvia_r
 */

function CanvasHandler() {
	
	var fullW = window.innerWidth,
		fullH = window.innerHeight;
		
	this.list_ = {
		0: {name: "cEvents", width: fullW, height: fullH, ctx: null},
		1: {name: "cPlayers", width: fullW, height: fullH, ctx: null},
		2: {name: "cRessources", width: fullW, height: fullH, ctx: null},
		3: {name: "cHighLight", width: fullW, height: fullH, ctx: null},
		4: {name: "cMap", width: fullW, height: fullH, ctx: null},
	};
	
	// init all canvas
	for (var i = 0; typeof(this.list_[i]) != "undefined"; i++)
	{
		var node = document.getElementById(this.list_[i].name);
		
		this.list_[i].ctx = node.getContext("2d");
		this.list_[i].ctx.font = "bold 28px Arial";
		node.width = this.list_[i].width;
		node.height = this.list_[i].height;
	}
}

CanvasHandler.prototype.get = function(name) {
	for (var i = 0; typeof(this.list_[i]) != "undefined"; i++)
		if (this.list_[i].name == name)
			return this.list_[i];
	console.log(name);
	displayError("Something wrong in CanvasHandler.get()");
}