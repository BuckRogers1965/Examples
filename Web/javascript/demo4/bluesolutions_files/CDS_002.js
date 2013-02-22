/* Script by: www.jtricks.com
 * Version: 20060925
 * Latest version:
 * www.jtricks.com/javascript/window/box_alone.html
 */
// Moves the box object to be directly beneath an object.
function CDS_Window_move_box(an, box, Width, Height, DisplayMode)
{
    var cleft = 0;
    var ctop = 0;
    var obj = an;

    if (DisplayMode == 0) // Under Link
    {
        while (obj.offsetParent)
        {
            cleft += obj.offsetLeft;
            ctop += obj.offsetTop;
            obj = obj.offsetParent;
        }
        ctop += an.offsetHeight + 8;

        // Handle Internet Explorer body margins,
        // which affect normal document, but not
        // absolute-positioned stuff.
        if (document.body.currentStyle &&
            document.body.currentStyle['marginTop'])
        {
            ctop += parseInt(document.body.currentStyle['marginTop']);
        }
    }
    else if (DisplayMode == 1) // Centered
    {
        var viewPortWidth = CDS.Private.Utility.windowState.getWidth();
        var viewPortHeight = CDS.Private.Utility.windowState.getHeight();
        var horizontalScroll = CDS.Private.Utility.windowState.getScrollX();
        var verticalScroll = CDS.Private.Utility.windowState.getScrollY();

        cleft = Math.round((viewPortWidth - Width)/2) + horizontalScroll;
        ctop = Math.round((viewPortHeight - Height)/2) + verticalScroll;
        cleft = (cleft < horizontalScroll) ? horizontalScroll : cleft;
        ctop = (ctop < verticalScroll) ? verticalScroll:ctop;
    }
    
    box.style.left = cleft + 'px';
    box.style.top = ctop + 'px';
}

// Hides other alone popup boxes that might be displayed
function CDS_Window_hide_other_alone(obj)
{
    if (!document.getElementsByTagName)
        return;
    var window_div = document.getElementById('CDS_Window');
    if(window_div != null)
    {
      document.body.removeChild(window_div);
      return;
    }
}

// Shows a box if it wasn't shown yet or is hidden
// or hides it if it is currently shown
function CDS_Window_show_hide_box(an, Title, URL, width, height, borderStyle, DisplayMode)
{
    var href = URL;
    var boxdiv = null;

    CDS_Window_hide_other_alone(null);

    // Create box object through DOM
    boxdiv = document.createElement('div');

    // Assign id equalling to the document it will show
    boxdiv.setAttribute('id','CDS_Window');

    // Add object identification variable
    boxdiv.alonePopupBox = 1;
    
    var viewPortWidth = CDS.Private.Utility.windowState.getWidth() - 80;
    var viewPortHeight = CDS.Private.Utility.windowState.getHeight() - 80;
    
    width = Math.min(viewPortWidth,width);  
    height = Math.min(viewPortHeight,height);
    // Add the magical 17 pixel to width for IE to avoid horizontal scroll bar
    // DF: 5/17/07 - not sure why this was here - I think the 2px adjustment at the bottom
    // internal vs. external is enough
    if(CDS.Private.Utility.IsIE())
    {
      // width = Math.min(viewPortWidth,width + 17);  
    }
    
    boxdiv.style.width = width + 'px';
    boxdiv.style.height = height + 'px';
    //alert( " boxdiv.style.height: "  + boxdiv.style.height);
    var offsetX = 0;
    var offsetY = 0;

    // Remove the following code if 'Close' hyperlink
    // is not needed.
    /*
    var close_href = document.createElement('a');
    close_href.href = 'javascript:void(0);';
    close_href.onclick = function()
        { CDS_Window_show_hide_box(an, Title, URL, width, height, borderStyle, DisplayMode); }
    close_href.appendChild(document.createTextNode('Close'));
    boxdiv.appendChild(close_href);
    offset = close_href.offsetHeight;
    */
    // DF: set a title bar, hardcode off set for now, figure out dynamic later.
    
    boxdiv.innerHTML = "<table name='CDS_Window_Titlebar' id='CDS_Window_Titlebar' cellpadding='0' cellspacing='0'>"
                     + "<tr>"
                     + "<td width='90%' align='left'>"
                     + Title 
                     + "</td>"
                     + "<td width='10%' align='right' valign='middle' onclick='CDS_Window_hide_other_alone()'"
                     + " style='cursor:pointer;background-position:right center;background-repeat:no-repeat;background-image:url(" 
                     + CDS.Private.gCloseButtonWindowImageUri 
                     + ");'>"
                     + "</td>"
                     + "</tr>"
                     + "</table>";
                     
    // Show the box now instead of earlier, so the innerHTML is exists in Safari for the following getElementbyID call
    document.body.appendChild(boxdiv);
        
    // prevent hyperlink navigation.
    boxdiv.style.display = 'block';
        
    oCDS_Window_Titlebar = document.getElementById('CDS_Window_Titlebar');

    // End of 'Close' hyperlink code.
    
    /* DF 5/17/2007 - I think borders are outside and we didn't notice b/c the microsite is white 
    offsetX = parseInt(CDS_Window_getStyle(boxdiv,"border-left-width"));
    offsetX += parseInt(CDS_Window_getStyle(boxdiv,"border-right-width"));
    
    offsetY = parseInt(CDS_Window_getStyle(boxdiv,"border-top-width"));
    offsetY += parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"height"));
    offsetY += parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"border-bottom-width"));
    */
    // DF 5/17 - as far as I can tell it's the titlebar info (height/borders)
    offsetX = 0;
    
    // Added a check here for NaN because if the first step blows up the offsetY will always be NaN
    offsetY = isNaN(parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"height")))? 0: parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"height"));
    
    offsetY += isNaN(parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"border-top-width"))) ? 0 : parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"border-top-width"));
    offsetY += isNaN(parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"border-bottom-width")))? 0 : parseInt(CDS_Window_getStyle(oCDS_Window_Titlebar,"border-bottom-width"));
    
    // JMR Had to add 2 pixels here so it wouldn't eat the bottom of the windows display box
    offsetY += 2;
        
    // JMR approximate/punt if the above fails
    if (offsetY == 2) {
        offsetY=22;
        }
    
    var contents = document.createElement('iframe');
    contents.scrolling = 'auto';
    //contents.id="CDSIF";
    //contents.name="CDSIF";
    contents.overflowX = 'hidden';
    contents.overflowY = 'scroll';
    contents.frameBorder = '0';
    contents.style.width = (width - offsetX) + 'px';
    contents.style.height = (height - offsetY) + 'px';
    //CDS.Private.AddEventListener(contents, "load", CDS_IFrame_Loaded); 
    
    boxdiv.appendChild(contents);

    CDS_Window_move_box(an, boxdiv, width, height, DisplayMode);

    if (contents.contentWindow)
        contents.contentWindow.document.location.replace(href);
    else
        contents.src = href;
    
    return false;
}

function CDS_IFrame_Loaded()
{
   alert((window.frames["CDSIF"].document.body.scrollWidth + 4) + " : " + (window.frames["CDSIF"].document.body.scrollHeight + 23));
}

function CDS_Window_getStyle(element, prop) {

    if (typeof element == 'string') element = document.getElementById(element);
	
	if (prop == null) {
	    return null;
	} else if (element.style[prop]) {
		// inline style property
		return element.style[prop];
	} else if (element.currentStyle) {
		// external stylesheet for Explorer
		return element.currentStyle[prop];
	} else if (document.defaultView && document.defaultView.getComputedStyle && document.defaultView.getComputedStyle(element,"")) {
		// external stylesheet for Mozilla and Safari 1.3+
		prop = prop.replace(/([A-Z])/g, "-$1");
		prop = prop.toLowerCase();
		return document.defaultView.getComputedStyle(element,"").getPropertyValue(prop);
	} else {
		return null;
	}
}