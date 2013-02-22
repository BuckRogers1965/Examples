
var id_global = 10000;
var menudoc;

function monoatomicid(){
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
	

function createContent(){
	insPara("Hello world!");	
	insPara("");	
	insPara("This is content that was inserted into a web page dynamically.");	
	insPara("");	
	insPara("If you view the page source you will not find this text anywhere.");	
}

// Inject a JSON file into the page 

function insertJSON(name, menudoc){

	regcb(name,menudoc)
	var s = document.createElement("script");
	s.setAttribute("type", "text/javascript");
	s.src = name;
	s.id = monoatomicid();
	s.charset = "utf-8";
	document.getElementsByTagName("head")[0].appendChild(s);
}

function Callback (name, JSONFile){

	fx= lookupcb(name)
	try {
		fx = eval (JSONFile);
		fx.go();
	} catch (e){
		unreg(name);
	}
}
