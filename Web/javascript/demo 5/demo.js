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

	Animate(dark, 0, opacity, 2, 1000, _set_opacity, null);
	//Animate(dark, 255, 0, -2, 1000, _set_bg, null);

  } else 
	Animate(dark, opacity, 0, -2, 1000, _set_opacity, clearblock);
	//Animate(dark, 0, 255, 2, 1000, _set_bg, null);
}

function OpenBoxes(){

	grayOut(true);
    box1=document.getElementById('CDS_Windowtl');  // Get the object.
	Animate(box1, 0, 100, 10, 100, nop, boxopen);

    box2=document.getElementById('CDS_Windowtr');  // Get the object.
	Animate(box2, 0, 100, 10, 100, nop, openboxrd);

    box3=document.getElementById('CDS_Windowc');  // Get the object.
    Animate(box3, 0, 100, 10, 100, nop, openboxc);

    box4=document.getElementById('CDS_Windowbl');  // Get the object.
    Animate(box4, 0, 100, 10, 100, nop, openboxbl);

    box5=document.getElementById('CDS_Windowbr');  // Get the object.
	Animate(box5, 0, 100, 10, 100, nop, openboxlu);
}

function CloseBoxes(){

	grayOut(false);
    box1=document.getElementById('CDS_Windowtl');  // Get the object.
	Animate(box1, 0, 100, 10, 100, nop, boxclose);

    box2=document.getElementById('CDS_Windowtr');  // Get the object.
	Animate(box2, 0, 100, 10, 100, nop, closeboxrd);

    box3=document.getElementById('CDS_Windowc');  // Get the object.
    Animate(box3, 0, 100, 10, 100, nop, closeboxc);

    box4=document.getElementById('CDS_Windowbl');  // Get the object.
    Animate(box4, 0, 100, 10, 100, nop, closeboxbl);

    box5=document.getElementById('CDS_Windowbr');  // Get the object.
	Animate(box5, 0, 100, 10, 100, nop, closeboxlu);
}


//(prop, start, end, step, ms, setval, callback);
function openboxbl(box){
	Animate(box, 0, 50, 1, 1000, changewidth, null);
	Animate(box, 0, 50, 1, 1000, changeheight,null);
	Animate(box, parseInt(box.style.top), parseInt(box.style.top)-50, 1, 1000, changetop, null);
}


function closeboxbl(box){
	Animate(box, 50, 0, -1, 1000, changeheight, null);
	Animate(box, 50, 0, -1, 1000, changewidth, null);
	Animate(box, parseInt(box.style.top), parseInt(box.style.top)+50, 1, 1000, changetop, null);
}


//(prop, start, end, step, ms, setval, callback);
function openboxc(box){
	Animate(box, 0, 300, 1, 1000, changewidth, null);
	Animate(box, 0, 100, 1, 1000, changeheight,null);
	Animate(box, parseInt(box.style.left), parseInt(box.style.left)-75, 1, 1000, changeleft, null);
	Animate(box, parseInt(box.style.top), parseInt(box.style.top)-25, 1, 1000, changetop, null);
}


function closeboxc(box){
	Animate(box, 100, 0, -1, 1000, changeheight, null);
	Animate(box, 300, 0, -1, 1000, changewidth, null);
	Animate(box, parseInt(box.style.top), parseInt(box.style.top)+25, 1, 1000, changetop, null);
	Animate(box, parseInt(box.style.left), parseInt(box.style.left)+75, 1, 1000, changeleft, null);
}


function openboxlu(box){
	Animate(box, 0, 50, 1, 500, changewidth, openboxlu2);
	Animate(box, parseInt(box.style.left), parseInt(box.style.left)-50, 1, 500, changeleft, null);
}

function openboxlu2(box){
	Animate(box, 0, 50, 1, 500, changeheight, null);
	Animate(box, parseInt(box.style.top), parseInt(box.style.top)-50, 1, 500, changetop, null);
}


function closeboxlu(box){
	Animate(box, 50, 0, -1, 500, changeheight, closeboxlu2);
	Animate(box, parseInt(box.style.top), parseInt(box.style.top)+50, 1, 500, changetop, null);
}

function closeboxlu2(box){
	Animate(box, 50, 0, -1, 500, changewidth, null);
	Animate(box, parseInt(box.style.left), parseInt(box.style.left)+50, 1, 500, changeleft, null);
}

function openboxrd(box){
	Animate(box, 0, 50, 1, 500, changewidth, openboxrd2);
}

function openboxrd2(box){
	Animate(box, 0, 50, 1, 500, changeheight, null);
}


function closeboxrd(box){
	Animate(box, 50, 0, -1, 500, changeheight, closeboxrd2);
}

function closeboxrd2(box){
	Animate(box, 50, 0, -1, 500, changewidth, null);
}

function boxopen(box){
	Animate(box, 0, 50, 1, 1000, changeheight, null);
	Animate(box, 0, 50, 1, 1000, changewidth, null);
}

function boxclose(box){
	Animate(box, 50, 0, -1, 1000, changeheight, null);
	Animate(box, 50, 0, -1, 1000, changewidth, null);
}

function changeleft(obj, value){
	obj.style.left = "" + value + "px";
}

function changetop(obj, value){
	obj.style.top = "" + value + "px";
}

function changeheight(obj, value){
	obj.style.height = "" + value + "pt";
}

function changewidth(obj, value){
	obj.style.width = "" + value +"pt";
}

function clearblock (){
    dark=document.getElementById('darkenScreenObject');  // Get the object.
	dark.style.display='none';
}

x=1;
function flash(dark){

	if (x){
		x=0;
    	_set_opacity(dark, 60);
	}else{
		x=1;
    	_set_opacity(dark, 70);
	}
}

function nop () {

}

function pausefive (){
    dark=document.getElementById('darkenScreenObject');  // Get the object.
	Animate(dark, 0, 1000, 200, 5000, flash, fade_in);
}

function fade_in (){
    dark=document.getElementById('darkenScreenObject');  // Get the object.
	Animate(dark, 70, 0, -2, 1000, _set_opacity, clearblock);
	Animate(dark, 0, 255, 8, 500, _set_bg, null);
}

function _set_bg(obj, bg)
{

    dark=document.getElementById('darkenScreenObject');  // Get the object.
	var hexval = from10toradix(bg, 16);
    dark.style.backgroundColor="#"+hexval+"0000";  
    //dark.style.display='block';                          
}

function from10toradix(value,radix)
{
	var retval = '';
	var ConvArray = [0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','F'];
	var intnum;
	var tmpnum;
	var i = 0;
	intnum = parseInt(value,10);
	if (isNaN(intnum))
		{ retval = 'NaN';
	}else{
		while (intnum > 0.9){
			i++; tmpnum = intnum;
			// cancatinate return string with new digit:
			retval = ConvArray[tmpnum % radix] + retval;
			intnum = Math.floor(tmpnum / radix);
			if (i > 100){ 
				// break infinite loops
				retval = 'NaN'; 
				break;
			}
		}
	}
	if (retval.length == 1)
		retval = "0" + retval;
	return retval;
} 


function _set_opacity(obj, opacity)
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

var register = [];
var count=[];

function Animate (prop, start, end, step, ms, setval, callback){

	//if (prop == null || start == null || end == null || step == null || ms == null || setval == null)
		//return;
/*
	if ((start-end) < 0) {
		if(step < (start-end))
			step = -1;
	} else {
		if(step > (start-end))
			step = 1;
	}
*/

	var delay=0;
	while (delay < 50){
		delay = Math.abs (ms / ((start - end)/step));
		((start-end) < 0)?step++:step--;
	}
	((start-end) < 0)?step--:step++;

	// just set to end if time is too short 
	//if (ms < 30) {
	//	setval(prop, end);
	//	return;
	//}

	if ((start>end)?(step>0):(step<0)){
		setval(prop, end);
		return;
	}

	var current = start;
	setval(prop, current);

	count++;
	var mycount = count;
	function stepfunc (){
		current += step;
    	if ((start>end)?(current>end):(current<end)) {
			setval(prop, current);
       		setTimeout(stepfunc, delay);
        } else {
			setval(prop, end);
			//register[mycount]=null;
			if (callback)
				callback(prop, start, end, step, ms, setval, callback);
		}
	}

    setTimeout(stepfunc, delay); 
}
