function getJobListings(urlToThisTheme) {
	//clear the content in the div for the next feed.
	$("#feed-result").empty();

	var fetch_url = 'http://lindenlab.hrmdirect.com/employment/rss.php';
	var error_msg = '<p>We\'re experiencing some problems displaying our job listings. We do have openings, so please check back with us in a bit.</p>';

	$.ajax({
			url: '/sites/all/themes/lindenlab/ajax_proxy.php?url='+escape(fetch_url),
	    type: 'GET',
	    dataType: 'xml',
	    timeout: 5000,
	    error: function(){
				$('#ajax-loader').css({ display:"none" });
				$('#feed-result').append(error_msg);
	    },
	    success: function(xml){
				$(xml).find('item').each(function() {

					// name the current found item this for this particular loop run
					var $item = $(this);
					// grab the post title
					var title = $item.find('title').text();
					// grab the post's URL
					var link = $item.find('link').text();

					// now create a var 'html' to store the markup we're using to output the feed to the browser window
					var html = "<a href=\"" + link + "\" target=\"_blank\">" + title + "<\/a><br />";
				
					// hide the loading bar
					$('#ajax-loader').css({ display:"none" });

					// put that feed content on the screen!
					$('#feed-result').append($(html));
				});

	    }
	});
}
