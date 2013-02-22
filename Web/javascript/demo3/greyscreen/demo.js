var id_global = 10000;

function monoatomicid() {
	id_global++;
	return id_global;
}	

function insPara(text) {
	var bodyRef = document.getElementsByTagName("body").item(0);
	var newText = document.createTextNode(text);
	var newPara = document.createElement("p");
	newPara.id = monoatomicid();
	newPara.appendChild(newText);
	bodyRef.appendChild(newPara);
}

function createContent() {
	insPara("");	
	insPara("The Grey out demo");	
}

function iterObj(myObj) {
	var func_list;
	var num_list;
	var str_list;
	var boo_list;
	var oth_list;

	for (var prop in myObj) {
		switch (typeof myObj[prop]){
		case 'number':
			num_list += prop + " : " + myObj[prop] + "\n";
			break;
		case 'string':
			str_list += prop + " : '" + myObj[prop] + "'\n";
			break;
		case 'boolean':
			boo_list += prop + " : " + myObj[prop] + "\n";
			break;
		case 'function':
			func_list += prop + "\n";
			break;
		default:
			oth_list += prop + " : " + typeof myObj[prop] + "\n";
		}
	}
	alert ("func_list:\n " + func_list );
	alert ("num_list: \n " + num_list );
	alert ("str_list:  \n" + str_list );
	alert ("boo_list:  \n" + boo_list );
	alert ("oth_list:  \n" + oth_list );
}


var srcURI = document.getElementById("CDS10001").src;

var halfURL = srcURI.split('?');
var clientID= halfURL.pop();
var baseURLparts= halfURL[0].split('/');
var baseName= baseURLparts.pop();

if (baseURLparts[0] == 'http:' || baseURLparts[0] == 'https:') {
	var baseURL=baseURLparts.join('/');
// Special fix for IE
} else {
	var basePath = "" + this.location;
	basePath = basePath.split('/');
	basePath.pop();
	var part;
	while(baseURLparts.length > 0){
		part = "" + baseURLparts.shift();
		switch(part){
		case "..":
			basePath.pop();
			break;
		case ".":
			break;
		default:
			basePath.push(part);
		}
	}
	var baseURL=basePath.join('/');
	srcURI = "" + baseURL + "?" + clientID;
}


function findObj(path, nodecount, srchObj, findObj){
	for (var prop in srchObj) {
		nodecount++;
		if (prop === 'parentNode' || prop == 'previousSibling' || prop == '0' || prop == '1'  || prop === 'enabledPlugin' || prop === 'ownerDocument' || prop === 'document' ||  nodecount === 2) {
			continue;
		}
		if (srchObj[prop] === findObj ){
			alert( "Found : " + path + "." + prop + " " + nodecount);
		} else {
			if (typeof srchObj[prop] == 'object') {
				if (nodecount > 200){
					return ;
				}
					
				arguments.callee(path + "." + prop, nodecount, srchObj[prop], findObj);
			}
		}
	}
	return "Not Found," + path + " Checked " + nodecount + " Nodes.";
}

//alert (findObj(" "+this, 0, document, srcScript));
//var srcScript = document.getElementById("CDS10001");
//alert (this.document.defaultView.srcScript);
//iterObj(srcScript);


function grayOut(vis, options) {
  // Pass true to gray out screen, false to ungray
  // options are optional.  This is a JSON object with the following (optional) properties
  // opacity:0-100         // Lower number = less grayout higher = more of a blackout 
  // zindex: #             // HTML elements with a higher zindex appear on top of the gray out
  // bgcolor: (#xxxxxx)    // Standard RGB Hex color code
  // grayOut(true, {'zindex':'50', 'bgcolor':'#0000FF', 'opacity':'70'});
  // Because options is JSON opacity/zindex/bgcolor are all optional and can appear
  // in any order.  Pass only the properties you need to set.
  var options = options || {}; 
  var zindex = options.zindex || 50;
  var opacity = options.opacity || 30;
  //var opaque = (opacity / 100);
  var bgcolor = options.bgcolor || '#000000';
  var dark=document.getElementById('darkenScreenObject');
  if (!dark) {
    // The dark layer doesn't exist, it's never been created.  So we'll
    // create it here and apply some basic styles.
    // If you are getting errors in IE see: http://support.microsoft.com/default.aspx/kb/927917
    var tbody = document.getElementsByTagName("body")[0];
    var tnode = document.createElement('div');           // Create the layer.
        tnode.style.position='absolute';                 // Position absolutely
        tnode.style.top='0px';                           // In the top
        tnode.style.left='0px';                          // Left corner of the page
        tnode.style.overflow='hidden';                   // Try to avoid making scroll bars            
        tnode.style.display='none';                      // Start out Hidden
        tnode.id='darkenScreenObject';                   // Name it so we can find it later
    tbody.appendChild(tnode);                            // Add it to the web page
    dark=document.getElementById('darkenScreenObject');  // Get the object.
  }
  if (vis) {
    // Calculate the page width and height 
/*    if( document.body && ( document.body.scrollWidth || document.body.scrollHeight ) ) {
        var pageWidth = document.body.scrollWidth+'px';
        var pageHeight = document.body.scrollHeight+'px';
    } else if( document.body.offsetWidth ) {
      var pageWidth = document.body.offsetWidth+'px';
      var pageHeight = document.body.offsetHeight+'px';
    } else {
*/       var pageWidth='100%';
       var pageHeight='100%';
//    }   
    //set the shader to cover the entire page and make it visible.
    dark.style.zIndex=zindex;        
    dark.style.backgroundColor=bgcolor;  
    dark.style.width= pageWidth;
    dark.style.height= pageHeight;
    dark.style.display='block';                          

    _set_opacity(dark, 0);
	_fade_in( 'darkenScreenObject', opacity);
       // _set_opacity(dark, opacity);
  } else {
	_fade_out('darkenScreenObject', opacity);
      //  _set_opacity(dark, 0);
  }
	
}

// Global timer table
var timers=new Array();

function _fade_in(element, target_opacity) // private
    {

	var opacity=0;
    // Get object
    var obj = document.getElementById(element);

    // Tidy up timer and register
    stop_timeout(element);

    obj.style.display='block';                          

	step = function (){
    // Fade in one more step
    	if (opacity <= target_opacity) {
        	_set_opacity(obj, opacity);
        	opacity+=10;
        	setTimeout("step()", 50);
        } else {
			alert("Greyed Out!");
			grayOut(false);
		}
	}
    setTimeout("step()", 50);

    }

// Global timer table
var timers=new Array();


function _fade_out(element, opacity) // private 
    {

    // Get object
    obj = document.getElementById(element);

    // If still visible, fade down one further step
    if (opacity > 0) {
        _set_opacity(obj, opacity);
        opacity-=10;
		window.setTimeout("_fade_out(\'"+element+"\',"+opacity+")", 50);
	}

	// If close to invisible, hide object completely
    if (opacity<1) {
     //   obj.style.visibility="hidden";
        obj.style.display='none';                      // Start out Hidden
        }
    }

function _set_opacity(obj, opacity) // private
    {
    opacity=(opacity==100) ? 99.999 : opacity;

    // IE/Win
    obj.style.filter="alpha(opacity:"+opacity+")";

    // Safari<1.2, Konqueror
    obj.style.KHTMLOpacity=opacity/100;

    // Older Mozilla and Firefox
    obj.style.MozOpacity=opacity/100;

    // Safari 1.2, newer Firefox and Mozilla, CSS3
    obj.style.opacity=opacity/100;
    }


function stop_timeout(element) // public
    {
    // Stop timer
    clearTimeout(timers[element]);

    // Clear register
    timers[element]=false;
    }

