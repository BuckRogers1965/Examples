var id_global = 10000;
var menudoc;

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
	insPara("Hello world!");	
	insPara("");	
	insPara("This is content that was inserted into a web page dynamically.");	
	insPara("");	
	insPara("If you view the page source you will not find this text anywhere.");	
}

