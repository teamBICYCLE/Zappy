/**
 * @author sylvia_r
 */

var imgs_ = new Object();

function ImgLoader() {
	this.load();	
}

ImgLoader.prototype.load = function() {

	[
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
  	    'floor',
	    'bubble_broadcast',
	    'undefined'
	].forEach(function (name) {
	    var img = new Image;
	    img.src = 'img/' + name + '.png';
	    imgs_[name] = img;
	});
}

ImgLoader.prototype.get = function(name) {
	
	if (imgs_.hasOwnProperty(name))
		return imgs_[name];
		
	return imgs_.undefined;
}