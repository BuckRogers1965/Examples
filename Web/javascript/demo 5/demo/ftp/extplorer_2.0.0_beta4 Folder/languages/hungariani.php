<?php

// Hungarian Language Module for v2.3 (translated by Jozsef Tamas Herczeg a.k.a LocaLiceR www.joomlandia.hu)
global $_VERSION;

$GLOBALS["charset"] = "iso-8859-2";
$GLOBALS["text_dir"] = "ltr"; // ('ltr' for left to right, 'rtl' for right to left)
$GLOBALS["date_fmt"] = "Y.m.d. H:i";
$GLOBALS["error_msg"] = array(
	// error
	"error"			=> "HIB�(K)",
	"message"			=> "�ZENET(EK)",
	"back"			=> "Vissza",
	
	// root
	"home"			=> "A kiindul�si k�nyvt�r nem l�tezik, ellen�rizd a be�ll�t�sokat.",
	"abovehome"		=> "A jelenlegi k�nyvt�r nem lehet f�ljebb a kiindul�si k�nyvt�rn�l.",
	"targetabovehome"	=> "A c�lk�nyvt�r nem lehet f�ljebb a kiindul�si k�nyvt�rn�l.",
	
	// exist
	"direxist"		=> "Ez a k�nyvt�r nem l�tezik.",
	//"filedoesexist"	=> "Ez a f�jl m�r l�tezik.",
	"fileexist"		=> "Ez a f�jl nem l�tezik.",
	"itemdoesexist"		=> "Ez az elem m�r l�tezik.",
	"itemexist"		=> "Ez az elem nem l�tezik.",
	"targetexist"		=> "A c�lk�nyvt�r nem l�tezik.",
	"targetdoesexist"	=> "A c�lelem m�r l�tezik.",
	
	// open
	"opendir"		=> "Nem nyithat� meg a k�nyvt�r.",
	"readdir"		=> "Nem olvashat� a k�nyvt�r.",
	
	// access
	"accessdir"		=> "Nem enged�lyezett a sz�modra az ehhez a k�nyvt�rhoz val� hozz�f�r�s.",
	"accessfile"		=> "Nem enged�lyezett a sz�modra az ehhez a f�jlhoz val� hozz�f�r�s.",
	"accessitem"		=> "Nem enged�lyezett a sz�modra az ehhez az elemhez val� hozz�f�r�s.",
	"accessfunc"		=> "Ennek a funkci�nak a haszn�lata nem enged�lyezett a sz�modra.",
	"accesstarget"		=> "Nem enged�lyezett a c�lk�nyvt�rhoz val� hozz�f�r�s.",
	
	// actions
	"permread"		=> "Az enged�lyek lek�r�se nem siker�lt.",
	"permchange"		=> "Az enged�lym�dos�t�s nem siker�lt.",
	"openfile"		=> "Nem lehet megnyitni a f�jlt.",
	"savefile"		=> "Nem lehet menteni a f�jlt.",
	"createfile"		=> "Nem lehet l�trehozni a f�jlt.",
	"createdir"		=> "Nem lehet l�trehozni a k�nyvt�rt.",
	"uploadfile"		=> "A f�jl felt�lt�se nem siker�lt.",
	"copyitem"		=> "A m�sol�s nem siker�lt.",
	"moveitem"		=> "Az �thelyez�s nem siker�lt.",
	"delitem"		=> "A t�rl�s nem siker�lt.",
	"chpass"		=> "Nem siker�lt megv�ltoztatni a jelsz�t.",
	"deluser"		=> "A felhaszn�l� elt�vol�t�sa nem siker�lt.",
	"adduser"		=> "A felhaszn�l� hozz�ad�sa nem siker�lt.",
	"saveuser"		=> "A felhaszn�l� ment�se nem siker�lt.",
	"searchnothing"		=> "Meg kell adnod a keresend� kulcssz�t.",
	
	// misc
	"miscnofunc"		=> "Ez a funkci� nem m�k�dik.",
	"miscfilesize"		=> "A f�jl m�rete nagyobb a megengedettn�l.",
	"miscfilepart"		=> "Csak r�szben siker�lt felt�lteni a f�jlt.",
	"miscnoname"		=> "Meg kell adnod egy nevet.",
	"miscselitems"		=> "Nem v�lasztott�l ki egy elemet sem.",
	"miscdelitems"		=> "Biztosan t�r�lni akarod ezt a(z) \"+num+\" elemet?",
	"miscdeluser"		=> "Biztosan t�r�lni akarod a k�vetkez� felhaszn�l�t: '\"+user+\"'?",
	"miscnopassdiff"	=> "Az �j jelsz� ugyanaz, mint a jelenlegi.",
	"miscnopassmatch"	=> "Elt�r�ek a jelszavak.",
	"miscfieldmissed"	=> "Kihagyt�l egy fontos mez�t.",
	"miscnouserpass"	=> "�rv�nytelen a felhaszn�l�n�v vagy a jelsz�.",
	"miscselfremove"	=> "Saj�t magadat nem t�vol�thatod el.",
	"miscuserexist"		=> "A felhaszn�l� m�r l�tezik.",
	"miscnofinduser"	=> "Nem tal�lhat� a felhaszn�l�.",
	"extract_noarchive" => "A f�jl nem kibonthat� arch�vum.",
	"extract_unknowntype" => "Ismeretlen t�pus� arch�vum"
);
$GLOBALS["messages"] = array(
	// links
	"permlink"		=> "ENGED�LYEK M�DOS�T�SA",
	"editlink"		=> "SZERKESZT�S",
	"downlink"		=> "LET�LT�S",
	"uplink"		=> "FEL",
	"homelink"		=> "KIINDUL�SI K�NYVT�R",
	"reloadlink"		=> "FRISS�T�S",
	"copylink"		=> "M�SOL�S",
	"movelink"		=> "�THELYEZ�S",
	"dellink"		=> "T�RL�S",
	"comprlink"		=> "ARCHIV�L�S",
	"adminlink"		=> "ADMIN",
	"logoutlink"		=> "KIL�P�S",
	"uploadlink"		=> "FELT�LT�S",
	"searchlink"		=> "KERES�S",
	"extractlink"	=> "Arch�vum kibont�sa",
	'chmodlink'		=> 'Enged�lyek m�dos�t�sa (chmod) (K�nyvt�r/F�jl(ok))', // new mic
	'mossysinfolink'	=> $_VERSION->PRODUCT.' Rendszerinform�ci� ('.$_VERSION->PRODUCT.', Kiszolg�l�, PHP, mySQL)', // new mic
	'logolink'		=> 'Ugr�s a joomlaXplorer webhely�re (�j ablak)', // new mic
	
	// list
	"nameheader"		=> "N�v",
	"sizeheader"		=> "M�ret",
	"typeheader"		=> "T�pus",
	"modifheader"		=> "M�dos�tva",
	"permheader"		=> "Enged�lyek",
	"actionheader"		=> "M�veletek",
	"pathheader"		=> "�tvonal",
	
	// buttons
	"btncancel"		=> "M�gse",
	"btnsave"		=> "Ment�s",
	"btnchange"		=> "M�dos�t�s",
	"btnreset"		=> "Alaphelyzet",
	"btnclose"		=> "Bez�r�s",
	"btncreate"		=> "L�trehoz�s",
	"btnsearch"		=> "Keres�s",
	"btnupload"		=> "Felt�lt�s",
	"btncopy"		=> "M�sol�s",
	"btnmove"		=> "�thelyez�s",
	"btnlogin"		=> "Bejelentkez�s",
	"btnlogout"		=> "Kijelentkez�s",
	"btnadd"		=> "Hozz�ad�s",
	"btnedit"		=> "Szerkeszt�s",
	"btnremove"		=> "�thelyez�s",
	
	// user messages, new in joomlaXplorer 1.3.0
	'renamelink'	=> '�TNEVEZ�S',
	'confirm_delete_file' => 'Biztosan t�r�lni akarod ezt a f�jlt? \\n%s',
	'success_delete_file' => 'Az elem(ek) t�rl�se siker�lt.',
	'success_rename_file' => 'A(z) %s k�nyvt�r/f�jl �tnevez�se %s n�vre siker�lt.',
	
	// actions
	"actdir"		=> "K�nyvt�r",
	"actperms"		=> "Enged�lyek m�dos�t�sa",
	"actedit"		=> "F�jl szerkeszt�se",
	"actsearchresults"	=> "A keres�s eredm�nye",
	"actcopyitems"		=> "Elem(ek) m�sol�sa",
	"actcopyfrom"		=> "M�sol�s a(z) /%s mapp�b�l a(z) /%s mapp�ba ",
	"actmoveitems"		=> "Elem(ek) �thelyez�se",
	"actmovefrom"		=> "�thelyez�s a(z) /%s mapp�b�l a(z) /%s mapp�ba ",
	"actlogin"		=> "Bejelentkez�s",
	"actloginheader"	=> "Bejelentkez�s a QuiXplorer haszn�lat�ra",
	"actadmin"		=> "Adminisztr�l�s",
	"actchpwd"		=> "A jelsz� megv�ltoztat�sa",
	"actusers"		=> "Felhaszn�l�k",
	"actarchive"		=> "Elem(ek) archiv�l�sa",
	"actupload"		=> "F�jl(ok) felt�lt�se",
	
	// misc
	"miscitems"		=> "elem",
	"miscfree"		=> "Szabad ter�let",
	"miscusername"		=> "Felhaszn�l�n�v",
	"miscpassword"		=> "Jelsz�",
	"miscoldpass"		=> "A r�gi jelsz�",
	"miscnewpass"		=> "Az �j jelsz�",
	"miscconfpass"		=> "A jelsz� meger�s�t�se",
	"miscconfnewpass"	=> "Az �j jelsz� meger�s�t�se",
	"miscchpass"		=> "Jelsz�csere",
	"mischomedir"		=> "Kiindul�si k�nyvt�r",
	"mischomeurl"		=> "Kezd� URL",
	"miscshowhidden"	=> "A rejtett elemek l�that�k",
	"mischidepattern"	=> "Minta elrejt�se",
	"miscperms"		=> "Enged�lyek",
	"miscuseritems"		=> "(n�v, kiindul�si k�nyvt�r, rejtett elemek megjelen�t�se, enged�lyek, akt�v)",
	"miscadduser"		=> "�j felhaszn�l�",
	"miscedituser"		=> "'%s' felhaszn�l� m�dos�t�sa",
	"miscactive"		=> "Akt�v",
	"misclang"		=> "Nyelv",
	"miscnoresult"		=> "A keres�s eredm�nytelen.",
	"miscsubdirs"		=> "Keres�s az alk�nyvt�rakban",
	"miscpermnames"		=> array("Csak n�zet","M�dos�t�s","Jelsz�csere","M�dos�t�s �s jelsz�csere",
					"Adminisztr�tor"),
	"miscyesno"		=> array("Igen","Nem","I","N"),
	"miscchmod"		=> array("Tulajdonos", "Csoport", "K�z�ns�g"),

	// from here all new by mic
	'miscowner'			=> 'Tulajdonos',
	'miscownerdesc'		=> '<strong>Le�r�s:</strong><br />Felhaszn�l� (UID) /<br />Csoport (GID)<br />Jelenlegi enged�lyek:<br /><strong> %s ( %s ) </strong>/<br /><strong> %s ( %s )</strong>',

	// sysinfo (new by mic)
	'simamsysinfo'		=> $_VERSION->PRODUCT." rendszerinform�ci�",
	'sisysteminfo'		=> 'Rendszer',
	'sibuilton'			=> 'Oper�ci�s rendszer',
	'sidbversion'		=> 'Adatb�zis verzi�sz�ma (MySQL)',
	'siphpversion'		=> 'PHP verzi�sz�ma',
	'siphpupdate'		=> 'INFORM�CI�: <span style="color: red;">Az �ltalad haszn�lt PHP verzi� <strong>elavult</strong>!</span><br />A Mambo �s kieg�sz�t�i valamennyi funkci�inak �s szolg�ltat�sainak biztos�t�s�hoz<br />legal�bb <strong>PHP 4.3-as verzi�t</strong> kell haszn�lnod!',
	'siwebserver'		=> 'Webkiszolg�l�',
	'siwebsphpif'		=> 'Webkiszolg�l� - PHP fel�let',
	'simamboversion'	=> $_VERSION->PRODUCT.' verzi�sz�ma',
	'siuseragent'		=> 'B�ng�sz� verzi�sz�ma',
	'sirelevantsettings' => 'Fontos PHP be�ll�t�sok',
	'sisafemode'		=> 'Biztons�gos m�d',
	'sibasedir'			=> 'Open basedir',
	'sidisplayerrors'	=> 'PHP hib�k',
	'sishortopentags'	=> 'Short Open Tags',
	'sifileuploads'		=> 'F�jlfelt�lt�s',
	'simagicquotes'		=> 'M�gikus id�z�jelek',
	'siregglobals'		=> 'Register Globals',
	'sioutputbuf'		=> 'Kimeneti puffer',
	'sisesssavepath'	=> 'Munkamenet ment�si �tvonal',
	'sisessautostart'	=> 'Munkamenet automatikus ind�t�sa',
	'sixmlenabled'		=> 'XML enged�lyezett',
	'sizlibenabled'		=> 'ZLIB enged�lyezett',
	'sidisabledfuncs'	=> 'Nem enged�lyezett funkci�k',
	'sieditor'			=> 'WYSIWYG szerkeszt�',
	'siconfigfile'		=> 'Konfigur�ci�s f�jl',
	'siphpinfo'			=> 'PHP',
	'siphpinformation'	=> 'PHP tulajdons�gai',
	'sipermissions'		=> 'Enged�lyek',
	'sidirperms'		=> 'K�nyvt�renged�lyek',
	'sidirpermsmess'	=> 'Ha azt akarod, hogy a '.$_VERSION->PRODUCT.' �sszes funkci�ja �s szolg�ltat�sa megfelel�en m�k�dj�n, akkor �rhat�v� kell tenned a k�vetkez� k�nyvt�rakat [chmod 0777]',
	'sionoff'			=> array( 'Be', 'Ki' ),
	
	'extract_warning' => "Val�ban ki akarod bontani ezt a f�jlt? Ide?\\nFel�l fogja �rni a l�tez� f�jlokat, ha nem k�r�ltekint�en haszn�lod!",
	'extract_success' => "A kibont�s siker�lt",
	'extract_failure' => "A kibont�s nem siker�lt",
	
	'overwrite_files' => 'A l�tez� f�jlok fel�l�r�sa',
	"viewlink"		=> "N�ZET",
	"actview"		=> "A f�jl forr�s�nak megtekint�se",
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_chmod.php file
	'recurse_subdirs'	=> 'V�grehajt�s az alk�nyvt�rakon is',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to footer.php file
	'check_version'	=> '�j verzi� ellen�rz�se',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_rename.php file
	'rename_file'	=>	'F�jl vagy k�nyvt�r �tnevez�se...',
	'newname'		=>	'�j n�v',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_edit.php file
	'returndir'	=>	'Visszat�r�s a k�nyvt�rhoz ment�s ut�n?',
	'line'		=> 	'Sor',
	'column'	=>	'Oszlop',
	'wordwrap'	=>	'Sort�rdel�s: (csak IE)',
	'copyfile'	=>	'A f�jl m�sol�sa ezen a n�ven',
	
	// Bookmarks
	'quick_jump' => 'Gyors ugr�s ide:',
	'already_bookmarked' => 'Ehhez a k�nyvt�rhoz m�r helyezt�l el k�nyvjelz�t',
	'bookmark_was_added' => 'Ez a k�nyvt�r hozz�ad�sra ker�lt a k�nyvjelz�kbe.',
	'not_a_bookmark' => 'Ez a k�nyvt�r nem k�nyvjelz�.',
	'bookmark_was_removed' => 'Ez a k�nyvt�r elt�vol�t�sra ker�lt a k�nyvjelz�k k�z�l.',
	'bookmarkfile_not_writable' => "Nem siker�lt %s a k�nyvjelz�t.\n A(z) '%s' k�nyvjelz�f�jl \nnem �rhat�.",
	
	'lbl_add_bookmark' => 'K�nyvjelz� k�sz�t�se ehhez a k�nyvt�rhoz',
	'lbl_remove_bookmark' => 'A k�nyvt�r k�nyvjelz�j�nek elt�vol�t�sa',
	
	'enter_alias_name' => 'K�rj�k, hogy �rd be a k�nyvt�r aliasnev�t',
	
	'normal_compression' => 'norm�l t�m�r�t�s',
	'good_compression' => 'j� t�m�r�t�s',
	'best_compression' => 'legjobb t�m�r�t�s',
	'no_compression' => 'nincs t�m�r�t�s',
	
	'creating_archive' => 'Arch�v f�jl l�trehoz�sa...',
	'processed_x_files' => 'Feldolgozva %s a(z) %s f�jlb�l',
	
	'ftp_header' => 'Helyi FTP hiteles�t�s',
	'ftp_login_lbl' => 'K�rj�k, hogy �rd be az FTP kiszolg�l� hiteles�t�si adatait',
	'ftp_login_name' => 'FTP felhaszn�l�n�v',
	'ftp_login_pass' => 'FTP jelsz�',
	'ftp_hostname_port' => 'Az FTP kiszolg�l� neve �s portja <br />(A port elhagyhat�)',
	'ftp_login_check' => 'FTP kapcsolat ellen�rz�se...',
	'ftp_connection_failed' => "Nem lehet kapcsol�dni az FTP kiszolg�l�hoz. \nK�rj�k, ellen�rizd, hogy m�k�dik-e az FTP kiszolg�l� a szerveren.",
	'ftp_login_failed' => "Sikertelen az FTP bejelentkez�s. K�rj�k, hogy ellen�rizd a felhaszn�l�nevet �s a jelsz�t, majd pr�b�ld �jra.",
		
	'switch_file_mode' => 'Jelenlegi m�d: <strong>%s</strong>. �tv�lt�s %s m�dba.',
	'symlink_target' => 'A szimbolikus hivatkoz�s c�lja',
	
	"permchange"		=> "CHMOD siker:",
	"savefile"		=> "A f�jl ment�se k�sz.",
	"moveitem"		=> "Az �thelyez�s siker�lt.",
	"copyitem"		=> "A m�sol�s siker�lt.",
	'archive_name' 	=> 'Az arch�vumf�jl neve',
	'archive_saveToDir' 	=> 'Az arch�vum ment�se a k�nyvt�rban',
	
	'editor_simple'	=> 'Egyszer� szerkeszt� m�d',
	'editor_syntaxhighlight'	=> 'Szintaxis-kiemel�ses m�d',
	
	'newlink'	=> 'New File/Directory',
	'show_directories' => 'Show Directories',
	'actlogin_success' => 'Login successful!',
	'actlogin_failure' => 'Login failed, try again.',
	'directory_tree' => 'Directory Tree',
	'browsing_directory' => 'Browsing Directory',
	'filter_grid' => 'Filter',
	'paging_page' => 'Page',
	'paging_of_X' => 'of {0}',
	'paging_firstpage' => 'First Page',
	'paging_lastpage' => 'Last Page',
	'paging_nextpage' => 'Next Page',
	'paging_prevpage' => 'Previous Page',
	
	'paging_info' => 'Displaying Items {0} - {1} of {2}',
	'paging_noitems' => 'No items to display',
	'aboutlink' => 'About...',
	'password_warning_title' => 'Important - Change your Password!',
	'password_warning_text' => 'The user account you are logged in with (admin with password admin) corresponds to the default eXtplorer priviliged account. Your eXtplorer installation is open to intrusion and you should immediately fix this security hole!',
	'change_password_success' => 'Your Password has been changed!',
	'success' => 'Success',
	'failure' => 'Failure',
	'dialog_title' => 'Website Dialog'
);
?>
