function eggs_draw(layers) {
    
    var eggs = cache.getEggs(),
    	sprite = "";
    	
	for (var i = 0; i != eggs.length; i++)
	{
		console.log(eggs[i].hatches_, eggs[i].dead_);
		if (eggs[i].hatches_)
			sprite = "hatched_";
		else if (eggs[i].dead_)
			sprite = "dead_";
			
		layers.draw("cPlayers", (sprite + "egg"), eggs[i].posx_, eggs[i].posy_, false);
	}
}