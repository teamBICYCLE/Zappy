/**
 * @author sylvia_r
 */

$(function() {

	$(".cmd").keypress(function(e) {
		if (e.keyCode == 13)
		{
			sendCmd($(".cmd").val());
			$(".cmd").val("");
		}
	});
});