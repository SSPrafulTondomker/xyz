$(document).ready(function(){
	
	//hide message_body after the first one
	$(".message_list .message_body").hide();
	
	


	
	//toggle message_body

	//collapse all messages
	$(".collpase_all_message").click(function(){
		$(".message_body").slideUp(500)
		return false;
	});

	

});