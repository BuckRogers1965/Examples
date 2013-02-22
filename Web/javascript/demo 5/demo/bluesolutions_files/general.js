<!--
function clearForm() {
	if(document.search.keywords.value=="Type Here...") 
		document.search.keywords.value="";
}

function fSubmitIt(TheForm,TheElement,TheValue)
{
	var oStatus = document.forms[TheForm].elements[TheElement];
	var oForm = document.forms[TheForm];
	oStatus.value = TheValue;
	oForm.submit();
}

function NewWindow(mypage, myname, w, h, scroll, resize, tool, menu) 
{
	var winl = (screen.width - w) / 2;
	var wint = (screen.height - h) / 2;
	winprops = 'height='+h+',width='+w+',top='+wint+',left='+winl+',scrollbars='+scroll+',resizable='+resize+',toolbar='+tool+',menubar='+menu+''
	win = window.open(mypage, myname, winprops)
	if (parseInt(navigator.appVersion) >= 4) 
	{ 
		win.window.focus(); 
	}
} 

function postback(value)
{
	document.forms["webform"].status.value = value;
    document.forms["webform"].submit()
}

function sort(value)
{
  document.forms["webform"].orderby.value = value;
  document.forms["webform"].submit()
}

    
-->