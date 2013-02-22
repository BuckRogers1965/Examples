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
	insPara("	Print where the script loaded from.");	
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
