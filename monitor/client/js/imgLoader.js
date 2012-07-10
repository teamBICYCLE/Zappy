/**
 * @author sylvia_r
 */

var imgs_ = new Object();

function ImgLoader() {
	this.load();	
}

ImgLoader.prototype.load = function() {

	[
	    'floor',
	    'highlight',
	    'player-north',
	    'player-south',
	    'player-west',
	    'player-east',
	    'linemate_small',
	    'linemate_medium',
	    'deraumere_small',
	    'deraumere_medium',
	    'sibur_small',
	    'sibur_medium',
	    'mendiane_small',
	    'mendiane_medium',
	    'phiras_small',
	    'phiras_medium',
	    'thystame_small',
	    'thystame_medium',
	    'food_small',
	    'food_medium',
	    'bubble_fork',
	    'bubble_broadcast',
	    'bubble_drop',
	    'bubble_get',
	    'bubble_expulsion',
	    'bubble_incantation',
	    'undefined'
	].forEach(function (name) {
	    var img = new Image;
	    img.src = 'img/' + name + '.png';
	    imgs_[name] = img;
	});
	
	// for (var i = 0; typeof(this.imgs_[i]) != "undefined"; i++)
		// $('<img/>')[0].src = "img/" + this.imgs_[i].name + ".png";
		// //this.imgs_[i].img.src = "img/" + this.imgs_[i].name + ".png";
	
	//this.imgs_[999].img.src = "img/" + this.imgs_[999].name + ".png";
}

ImgLoader.prototype.get = function(name) {
	
	if (imgs_.hasOwnProperty(name))
		return imgs_[name];
		
	return imgs_.undefined;
}