/* Javascript for OSXL's custom scroll to top by black.dragon74 */

// Basic on document ready fucntion
$(document).ready(function(){
	
	var hideButton = "#scroll-top";
	
	// Hide the button on load (first things first)
	$(hideButton).hide();
	
	// Function to execute whenever window state is scrolling
	$(window).scroll(function(){
		
		// Logging (should be removed after testing)
		console.log($(this).scrollTop());
		
		if ($(this).scrollTop() > 80){
			
			// Scrolled more than 100, show the scroll button (slowly)
			$(hideButton).fadeIn('slow');
			
		}
		
		else {
			// Window is at the top, hide the scroll button (slowly)
			$(hideButton).fadeOut('slow');
		}
		
	});
	
	// Add an on click listener to the hideButton
	$(hideButton).click(function(){
		$('html, body').animate({scrollTop: 0});
	});
	
});