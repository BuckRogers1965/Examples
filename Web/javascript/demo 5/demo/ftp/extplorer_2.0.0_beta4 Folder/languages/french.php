<?php

// French Language Module for joomlaXplorer (translated by Olivier Pariseau and Alexandre PRIETO)

$GLOBALS["charset"] = "iso-8859-1";
$GLOBALS["text_dir"] = "ltr"; // ('ltr' for left to right, 'rtl' for right to left)
$GLOBALS["date_fmt"] = "d/m/Y H:i";
$GLOBALS["error_msg"] = array(
	// error
	"error"			=> "ERREUR(S)",
	"back"			=> "Page pr�c�dente",
	
	// root
	"home"			=> "Le r�pertoire home n'existe pas, v�rifiez vos pr�f�rences.",
	"abovehome"		=> "Le r�pertoire courant n'a pas l'air d'�tre au-dessus du r�pertoire home.",
	"targetabovehome"	=> "Le r�pertoire cible n'a pas l'air d'�tre au-dessus du r�pertoire home.",
	
	// exist
	"direxist"		=> "Ce r�pertoire n'existe pas.",
	//"filedoesexist"	=> "Ce fichier existe d�j�.",
	"fileexist"		=> "Ce fichier n'existe pas.",
	"itemdoesexist"		=> "Cet item existe d�j�.",
	"itemexist"		=> "Cet item n'existe pas.",
	"targetexist"		=> "Le r�pertoire cible n'existe pas.",
	"targetdoesexist"	=> "L'item cible existe d�j�.",
	
	// open
	"opendir"		=> "Impossible d'ouvrir le r�pertoire.",
	"readdir"		=> "Impossible de lire le r�pertoire.",
	
	// access
	"accessdir"		=> "Vous n'�tes pas autoris� a acc�der � ce r�pertoire.",
	"accessfile"		=> "Vous n'�tes pas autoris� a acc�der � ce fichier.",
	"accessitem"		=> "Vous n'�tes pas autoris� a acc�der � cet item.",
	"accessfunc"		=> "Vous ne pouvez pas utiliser cette fonction.",
	"accesstarget"		=> "Vous n'�tes pas autoris� a acc�der au repertoire cible.",
	
	// actions
	"permread"		=> "Lecture des permissions �chou�e.",
	"permchange"		=> "Changement des permissions �chou�.",
	"openfile"		=> "Ouverture du fichier �chou�e.",
	"savefile"		=> "Sauvegarde du fichier �chou�e.",
	"createfile"		=> "Cr�ation du fichier �chou�e.",
	"createdir"		=> "Cr�ation du r�pertoire �chou�e.",
	"uploadfile"		=> "Envoie du fichier �chou�.",
	"copyitem"		=> "La copie a �chou�e.",
	"moveitem"		=> "Le d�placement a �chou�.",
	"delitem"		=> "La supression a �chou�e.",
	"chpass"		=> "Le changement de mot de passe a �chou�.",
	"deluser"		=> "La supression de l'usager a �chou�e.",
	"adduser"		=> "L'ajout de l'usager a �chou�e.",
	"saveuser"		=> "La sauvegarde de l'usager a �chou�e.",
	"searchnothing"		=> "Vous devez entrez quelquechose � chercher.",
	
	// misc
	"miscnofunc"		=> "Fonctionalit� non disponible.",
	"miscfilesize"		=> "La taille du fichier exc�de la taille maximale autoris�e.",
	"miscfilepart"		=> "L'envoi du fichier n'a pas �t� compl�t�.",
	"miscnoname"		=> "Vous devez entrer un nom.",
	"miscselitems"		=> "Vous n'avez s�lectionn� aucuns item(s).",
	"miscdelitems"		=> "�tes-vous certain de vouloir supprimer ces {0} item(s)?",
	"miscdeluser"		=> "�tes-vous certain de vouloir supprimer l'usager {0}?",
	"miscnopassdiff"	=> "Le nouveau mot de passe est indentique au pr�c�dent.",
	"miscnopassmatch"	=> "Les mots de passe diff�rent.",
	"miscfieldmissed"	=> "Un champs requis n'a pas �t� rempli.",
	"miscnouserpass"	=> "Nom d'usager ou mot de passe invalide.",
	"miscselfremove"	=> "Vous ne pouvez pas supprimer votre compte.",
	"miscuserexist"		=> "Ce nom d'usager existe d�j�.",
	"miscnofinduser"	=> "Usager non trouv�.",
	"extract_noarchive" => "Ce fichier n'est pas une archive extractible.",
	"extract_unknowntype" => "Type Archive Inconnue"
);
$GLOBALS["messages"] = array(
	// links
	"permlink"		=> "CHANGER LES PERMISSIONS",
	"editlink"		=> "�DITER",
	"downlink"		=> "T�L�CHARGER",
	"uplink"		=> "DOSSIER PARENT",
	"homelink"		=> "HOME",
	"reloadlink"		=> "RAFRA�CHIR",
	"copylink"		=> "COPIER",
	"movelink"		=> "D�PLACER",
	"dellink"		=> "SUPPRIMER",
	"comprlink"		=> "ARCHIVER",
	"adminlink"		=> "ADMINISTRATION",
	"logoutlink"		=> "D�CONNECTER",
	"uploadlink"		=> "ENVOYER",
	"searchlink"		=> "RECHERCHER",
	"extractlink"		=> "Extractaction de l'archive",
	'chmodlink'		=> 'Changer (chmod) Droits (R�pertoire/Fichier(s))', // new mic
	'mossysinfolink'	=> $_VERSION->PRODUCT.' Informations Syst�me ('.$_VERSION->PRODUCT.', Server, PHP, mySQL)', // new mic
	'logolink'		=> 'Aller au site web de joomlaXplorer (nouvelle fen�tre)', // new mic
	
	// list
	"nameheader"		=> "Nom",
	"sizeheader"		=> "Taille",
	"typeheader"		=> "Type",
	"modifheader"		=> "Modifi�",
	"permheader"		=> "Perm's",
	"actionheader"		=> "Actions",
	"pathheader"		=> "Chemin",
	
	// buttons
	"btncancel"		=> "Annuler",
	"btnsave"		=> "Sauver",
	"btnchange"		=> "Changer",
	"btnreset"		=> "R�initialiser",
	"btnclose"		=> "Fermer",
	"btncreate"		=> "Cr�er",
	"btnsearch"		=> "Chercher",
	"btnupload"		=> "Envoyer",
	"btncopy"		=> "Copier",
	"btnmove"		=> "D�placer",
	"btnlogin"		=> "Connecter",
	"btnlogout"		=> "D�connecter",
	"btnadd"		=> "Ajouter",
	"btnedit"		=> "�diter",
	"btnremove"		=> "Supprimer",
	
	// user messages, new in joomlaXplorer 1.3.0
	'renamelink'		=> "Renommer",
	'confirm_delete_file' => '�tes-vous s�r de vouloir supprimer ce fichier? \\n%s',
	'success_delete_file' => 'Fichier supprim� avec succes.',
	'success_rename_file' => 'Le r�pertoire/fichier %s a �t� renomm� %s.',
	
	
	// actions
	"actdir"		=> "R�pertoire",
	"actperms"		=> "Changer les permissions",
	"actedit"		=> "�diter le fichier",
	"actsearchresults"	=> "R�sultats de la recherche",
	"actcopyitems"		=> "Copier le(s) item(s)",
	"actcopyfrom"		=> "Copier de /%s � /%s ",
	"actmoveitems"		=> "D�placer le(s) item(s)",
	"actmovefrom"		=> "D�placer de /%s � /%s ",
	"actlogin"		=> "Connecter",
	"actloginheader"	=> "Connecter pour utiliser QuiXplorer",
	"actadmin"		=> "Administration",
	"actchpwd"		=> "Changer le mot de passe",
	"actusers"		=> "Usagers",
	"actarchive"		=> "Archiver le(s) item(s)",
	"actupload"		=> "Envoyer le(s) fichier(s)",
	
	// misc
	"miscitems"		=> "Item(s)",
	"miscfree"		=> "Disponible",
	"miscusername"		=> "Usager",
	"miscpassword"		=> "Mot de passe",
	"miscoldpass"		=> "Ancien mot de passe",
	"miscnewpass"		=> "Nouveau mot de passe",
	"miscconfpass"		=> "Confirmer le mot de passe",
	"miscconfnewpass"	=> "Confirmer le nouveau mot de passe",
	"miscchpass"		=> "Changer le mot de passe",
	"mischomedir"		=> "R�pertoire home",
	"mischomeurl"		=> "URL home",
	"miscshowhidden"	=> "Voir les items cach�s",
	"mischidepattern"	=> "Cacher pattern",
	"miscperms"		=> "Permissions",
	"miscuseritems"		=> "(nom, r�pertoire home, Voir les items cach�s, permissions, actif)",
	"miscadduser"		=> "Ajouter un usager",
	"miscedituser"		=> "�diter l'usager '%s'",
	"miscactive"		=> "Actif",
	"misclang"		=> "Langage",
	"miscnoresult"		=> "Aucun r�sultats.",
	"miscsubdirs"		=> "Rechercher dans les sous-r�pertoires",
	"miscpermnames"		=> array("Lecture seulement","Modifier","Changement le mot de passe","Modifier & Changer le mot de passe",
					"Administrateur"),
	"miscyesno"		=> array("Oui","Non","O","N"),
	"miscchmod"		=> array("Propri�taire", "Groupe", "Publique"),
	// from here all new by mic
	'miscowner'			=> 'Propri�taire',
	'miscownerdesc'		=> '<strong>Description:</strong><br />Propri�taire (UID) /<br />Groupe (GID)<br />Droits actuels:<br /><strong> %s ( %s ) </strong>/<br /><strong> %s ( %s )</strong>',

	// sysinfo (new by mic)
	'simamsysinfo'		=> $_VERSION->PRODUCT.' Informations Syst�me',
	'sisysteminfo'		=> 'Info Syst�me',
	'sibuilton'			=> 'OS',
	'sidbversion'		=> 'Version Base de Donn�es (MySQL)',
	'siphpversion'		=> 'Version PHP',
	'siphpupdate'		=> 'INFORMATION: <span style="color: red;">La version de PHP que vous utilisez n\'est <strong>plus</strong> d\'actualit�!</span><br />Afin de garantir un fonctionnement maximum de '.$_VERSION->PRODUCT.' et addons,<br />Vous devez utiliser au minimum <strong>PHP.Version 4.3</strong>!',
	'siwebserver'		=> 'Webserver',
	'siwebsphpif'		=> 'WebServer - Interface PHP',
	'simamboversion'	=> ' Version'.$_VERSION->PRODUCT,
	'siuseragent'		=> 'Version du Navigateur',
	'sirelevantsettings' => 'Param�tres PHP avanc�s',
	'sisafemode'		=> 'Safe Mode',
	'sibasedir'			=> 'Ouvrir r�pertoire de base',
	'sidisplayerrors'	=> 'Erreurs PHP',
	'sishortopentags'	=> 'Short Open Tags',
	'sifileuploads'		=> 'Date Uploads',
	'simagicquotes'		=> 'Magic Quotes',
	'siregglobals'		=> 'Register Globals',
	'sioutputbuf'		=> 'Output Buffer',
	'sisesssavepath'	=> 'Session Savepath',
	'sisessautostart'	=> 'Session auto start',
	'sixmlenabled'		=> 'XML activ�',
	'sizlibenabled'		=> 'ZLIB activ�',
	'sidisabledfuncs'	=> 'Non enabled functions',
	'sieditor'			=> 'Editeur WYSIWYG',
	'siconfigfile'		=> 'Config file',
	'siphpinfo'			=> 'PHP Info',
	'siphpinformation'	=> 'PHP Information',
	'sipermissions'		=> 'Permissions',
	'sidirperms'		=> 'Permissions R�pertoire',
	'sidirpermsmess'	=> 'Pour obtenir un fonctionnement correcte de '.$_VERSION->PRODUCT.' assurez vous que vous poss�dez les droits en �criture sur l\'ensemble des r�pertoires. [chmod 0777]',
	'sionoff'			=> array( 'On', 'Off' ),
	
	'extract_warning' => "Voulez-vous r�ellement extraire ce fichier Ici?\\nCe fichier �crasera le fichier existant!",
	'extract_success' => "Extraction r�ussi",
	'extract_failure' => "Extraction �chou�e",
	
	'overwrite_files' => '�craser le(s) fichier(s) existant(s)?',
	"viewlink"		=> "APER�U",
	"actview"		=> "Aper�u des sources du fichier",
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_chmod.php file
	'recurse_subdirs'	=> 'R�cursif dans les sous-r�pertoires?',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to footer.php file
	'check_version'	=> 'V�rifier si une version sup�rieure existe',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_rename.php file
	'rename_file'	=>	'Renommer le r�pertoire ou fichier...',
	'newname'		=>	'Nouveau nom',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_edit.php file
	'returndir'	=>	'Retourner au r�pertoire apr�s sauvegarde?',
	'line'		=> 	'Ligne',
	'column'	=>	'Colonne',
	'wordwrap'	=>	'Wordwrap: (IE seulement)',
	'copyfile'	=>	'Copier fichier avec ce nom de fichier',
	
	// Bookmarks
	'quick_jump' => 'Saut rapide vers',
	'already_bookmarked' => 'Ce r�pertoire existe d�j� dans le signet',
	'bookmark_was_added' => 'R�pertoire ajout� � la liste de signet.',
	'not_a_bookmark' => 'Ce r�pertoire n\'est pas un signet.',
	'bookmark_was_removed' => 'Ce r�pertoire � �t� supprim� de la list de signet.',
	'bookmarkfile_not_writable' => "�chec lors de %s dans le signet.\n Le fichier signet '%s' \nn\'est pas accessible en �criture.",
	
	'lbl_add_bookmark' => 'Ajouter ce r�pertoire au signet',
	'lbl_remove_bookmark' => 'Supprimer ce r�pertoire de la liste de signet',
	
	'enter_alias_name' => 'SVP, entrez un alias pour ce signet',
	
	'normal_compression' => 'compression normal',
	'good_compression' => 'compression moyenne',
	'best_compression' => 'compression meilleur',
	'no_compression' => 'pas de compression',
	
	'creating_archive' => 'Cr�ation du Fichier Archive...',
	'processed_x_files' => '%s of %s Fichiers trait�s',
	
	'ftp_header' => 'Authentification FTP Locale',
	'ftp_login_lbl' => 'SVP, entrez un login de connexion pour le serveur FTP',
	'ftp_login_name' => "Nom d'utilisateur FTP",
	'ftp_login_pass' => 'Mot de passe FTP',
	'ftp_hostname_port' => 'Nom du serveur FTP et Port <br />(Le port est optionnel)',
	'ftp_login_check' => 'Test connexion serveur FTP...',
	'ftp_connection_failed' => "Serveur FTP impossible � contacter. \nSVP, v�rifiez que le service FTP est lanc� sur le serveur.",
	'ftp_login_failed' => "Login FTP incorrect. SVP, V�rifiez le nom et mot de passe utilisateur et r�essayez.",
		
	'switch_file_mode' => 'Mode courant: <strong>%s</strong>. Vous pouvez passer en mode %s.',
	'symlink_target' => 'Cible du lien symbolique',
	
	"permchange"		=> "CHMOD r�ussi:",
	"savefile"		=> "Le fichier est sauvegard�.",
	"moveitem"		=> "D�placement r�ussi.",
	"copyitem"		=> "Copie r�ussi.",
	'archive_name' 		=> "Nom de l'archive",
	'archive_saveToDir' 	=> "Sauvez l'archive dans ce r�pertoire",
	
	'editor_simple'	=> 'Simple Editor Mode',
	'editor_syntaxhighlight'	=> 'Syntax-Highlighted Mode',

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
