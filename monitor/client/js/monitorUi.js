/**
 * @author sylvia_r
 */

$(function() {

	/* events */
	
	$(".cmd").keypress(function(e) {
		if (e.keyCode == 13)
		{
			sendCmd($(".cmd").val());
			$(".cmd").val("");
		}
	});
	
	$("#errorBox").click(function(e){
		$("#errorBox").hide();
	});
	
	// $('#connectionError').click(function(){
		// if (!$("#connectionError").is(":hidden"))
		// {
			// $('#connectionError').animate({'top':'-210px'}, 500, function(){
	            // $('#overlay').fadeOut('fast');
	        // });
		// }
	// });

});

function displayError(msg) {
	$("#errorBox .errorText").text("Error : " + msg);
	$("#errorBox").fadeIn(1500).delay(1000).fadeOut(3000);
}