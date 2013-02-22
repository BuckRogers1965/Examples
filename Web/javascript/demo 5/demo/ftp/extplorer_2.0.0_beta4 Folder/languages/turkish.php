<?php

// Turkish Language for joomlaXplorer (Translated by Sinan Ata 'From Turkey'(contact@mambo.gen.tr))

$GLOBALS["charset"] = "iso-8859-9";
$GLOBALS["text_dir"] = "ltr"; // ('ltr' for left to right, 'rtl' for right to left)
$GLOBALS["date_fmt"] = "Y/m/d H:i";
$GLOBALS["error_msg"] = array(
	// error
	"error"			=> "HATA(LAR)",
	"back"			=> "Geri Gel",
	
	// root
	"home"			=> "Ana klasör oluþturulmamýþ ayarlarýnýzý kontrol edin.",
	"abovehome"		=> "Bu klasör ana klasörün üstünde olmamalýdýr.",
	"targetabovehome"	=> "Hedef klasör ana klasörün üstünde olmamalýdýr.",
	
	// exist
	"direxist"		=> "Bu klasör oluþturulamadý.",
	//"filedoesexist"	=> "Bu dosya zaten var.",
	"fileexist"		=> "Bu dosya oluþturulamadý.",
	"itemdoesexist"		=> "Bu madde zaten var.",
	"itemexist"		=> "Bu madde oluþturulamadý.",
	"targetexist"		=> "Hedef klasör oluþturulmamýþ.",
	"targetdoesexist"	=> "Hedef madde zaten oluþturumuþ.",
	
	// open
	"opendir"		=> "Klasör Açýlamaz.",
	"readdir"		=> "Klasör Okunamaz.",
	
	// access
	"accessdir"		=> "Bu klasöre ulaþmak için izinleriniz yetersiz.",
	"accessfile"		=> "Bu dosyaya ulaþmak için izinleriniz yetersiz.",
	"accessitem"		=> "Bu maddeye ulaþmak için izinleriniz yetersiz.",
	"accessfunc"		=> "Bu fonksiyonu kullanmak için izinleriniz yetersiz.",
	"accesstarget"		=> "Hedef klasöre ulaþmak için izinleriniz yetersiz.",
	
	// actions
	"permread"		=> "Ýzin gösterimi baþarýsýz.",
	"permchange"		=> "Ýzin deðiþtirme baþarýsýz.",
	"openfile"		=> "Dosya açýlmasý baþarýsýz.",
	"savefile"		=> "Dosya kaydý baþarýsýz.",
	"createfile"		=> "Dosya oluþumu baþarýsýz.",
	"createdir"		=> "Klasör oluþumu baþarýsýz.",
	"uploadfile"		=> "Dosya yüklemesi baþarýsýz.",
	"copyitem"		=> "Kopyalama baþarýsýz.",
	"moveitem"		=> "Taþýma baþarýsýz.",
	"delitem"		=> "Silme baþarýsýz.",
	"chpass"		=> "Þifre deðiþtirme baþarýsýz.",
	"deluser"		=> "Kullanýcý kaldýrma baþarýsýz.",
	"adduser"		=> "Kullanýcý ekleme baþarýsýz.",
	"saveuser"		=> "Kullanýcý deðiþiklik kaydý baþarýsýz.",
	"searchnothing"		=> "Aramak için bir deðer girmelisiniz.",
	
	// misc
	"miscnofunc"		=> "Fonksiyon kullanýlabilir.",
	"miscfilesize"		=> "Dosya maksimum boyutu aþtý.",
	"miscfilepart"		=> "Dosyanýn yalnýzca bir kýsmý yüklenebildi.",
	"miscnoname"		=> "Bir isim girmelisiniz.",
	"miscselitems"		=> "Hiçbir madde(ler) seçmediniz.",
	"miscdelitems"		=> " {0} maddelerini silmek istediðinizden eminmisiniz?",
	"miscdeluser"		=> "'{0}' kullanýcýsýný silmek istediðinizden eminmisiniz?",
	"miscnopassdiff"	=> "Yeni þifre eskisinden farklý deðil.",
	"miscnopassmatch"	=> "Þifreler eþleþmiyor.",
	"miscfieldmissed"	=> "Gerekli bir boþluðu atladýnýz.",
	"miscnouserpass"	=> "Kullanýcý adý yada þifreniz yanlýþ.",
	"miscselfremove"	=> "Kendinizi silemezsiniz.",
	"miscuserexist"		=> "Kullanýcý zaten var.",
	"miscnofinduser"	=> "Kullanýcý bulunamadý.",
	"extract_noarchive" => "The File is no extractable Archive.",
	"extract_unknowntype" => "Unknown Archive Type"
);
$GLOBALS["messages"] = array(
	// links
	"permlink"		=> "Ýzinleri Deðiþtir",
	"editlink"		=> "Deðiþtir",
	"downlink"		=> "Aþaðý",
	"uplink"		=> "Yukarý",
	"homelink"		=> "Baþa Dön",
	"reloadlink"		=> "Yenile",
	"copylink"		=> "Kopyala",
	"movelink"		=> "Taþý",
	"dellink"		=> "Sil",
	"comprlink"		=> "Depola",
	"adminlink"		=> "Yönetici",
	"logoutlink"		=> "Çýkýþ",
	"uploadlink"		=> "Yükle",
	"searchlink"		=> "Ara",
	"extractlink"	=> "Extract Archive",
	'chmodlink'		=> 'Change (chmod) Rights (Folder/File(s))', // new mic
	'mossysinfolink'	=> $_VERSION->PRODUCT.' System Information ('.$_VERSION->PRODUCT.', Server, PHP, mySQL)', // new mic
	'logolink'		=> 'Go to the joomlaXplorer Website (new window)', // new mic
	
	// list
	"nameheader"		=> "Ýsim",
	"sizeheader"		=> "Boyut",
	"typeheader"		=> "Tip",
	"modifheader"		=> "Deðiþtirme",
	"permheader"		=> "Ýzinler",
	"actionheader"		=> "Hareketler",
	"pathheader"		=> "Yol",
	
	// buttons
	"btncancel"		=> "Çýkýþ",
	"btnsave"		=> "Kaydet",
	"btnchange"		=> "Deðiþtir",
	"btnreset"		=> "Sýfýrla",
	"btnclose"		=> "Kapat",
	"btncreate"		=> "Oluþtur",
	"btnsearch"		=> "Ara",
	"btnupload"		=> "Yükle",
	"btncopy"		=> "Kopyala",
	"btnmove"		=> "Taþý",
	"btnlogin"		=> "Giriþ",
	"btnlogout"		=> "Çýkýþ",
	"btnadd"		=> "Ekle",
	"btnedit"		=> "Deðiþtir",
	"btnremove"		=> "Kaldýr",
	
	// user messages, new in joomlaXplorer 1.3.0
	'renamelink'	=> 'RENAME',
	'confirm_delete_file' => 'Are you sure you want to delete this file? \\n%s',
	'success_delete_file' => 'Item(s) successfully deleted.',
	'success_rename_file' => 'The directory/file %s was successfully renamed to %s.',
	
	// actions
	"actdir"		=> "Klasör",
	"actperms"		=> "Ýzinleri Deðiþtir",
	"actedit"		=> "Dosyayý Deðiþtir",
	"actsearchresults"	=> "Arama Sonuçlarý",
	"actcopyitems"		=> "Madde(ler)i kopyala",
	"actcopyfrom"		=> " /%s dan /%s ya ",
	"actmoveitems"		=> "Madde(ler)i taþý",
	"actmovefrom"		=> " /%s dan /%s ya taþý ",
	"actlogin"		=> "Giriþ",
	"actloginheader"	=> "QuiXplorer kullanýmý için giriþ yap",
	"actadmin"		=> "Yönetim",
	"actchpwd"		=> "Þifre Deðiþtir",
	"actusers"		=> "Kullanýcýlar",
	"actarchive"		=> "Madde(ler)i Yedekle",
	"actupload"		=> "Dosya(lar)i Yükle",
	
	// misc
	"miscitems"		=> "Madde(ler)",
	"miscfree"		=> "Serbest",
	"miscusername"		=> "Kullanýcý Adý",
	"miscpassword"		=> "Þifre",
	"miscoldpass"		=> "Eski Þifre",
	"miscnewpass"		=> "Yeni Þifre",
	"miscconfpass"		=> "Þifreyi Onayla",
	"miscconfnewpass"	=> "Yeni Þifeyi Onayla",
	"miscchpass"		=> "Þifre Deðiþtir",
	"mischomedir"		=> "Ana Klasör",
	"mischomeurl"		=> "Baþ URL",
	"miscshowhidden"	=> "Gizli Maddeleri Göster",
	"mischidepattern"	=> "Resim Gizle",
	"miscperms"		=> "Ýzinler",
	"miscuseritems"		=> "(isim, ana klasör, gizli maddeleri göster, izinler, Aktif)",
	"miscadduser"		=> "Kullanýcý ekle",
	"miscedituser"		=> "'%s' kullanýcýsýný deðiþtir",
	"miscactive"		=> "Aktif",
	"misclang"		=> "Dil",
	"miscnoresult"		=> "Hiç sonuç yok.",
	"miscsubdirs"		=> "Alt kategorileri de ara",
	"miscpermnames"		=> array("Sadece bakýlabilir","Modifiye","Þifre deðiþtir","Modifiye & Þifre Deðiþtir",
					"Yönetici"),
	"miscyesno"		=> array("Evet","Hayýr","E","H"),
	"miscchmod"		=> array("Sahip", "Grup", "Halk"),
	// from here all new by mic
	'miscowner'			=> 'Owner',
	'miscownerdesc'		=> '<strong>Description:</strong><br />User (UID) /<br />Group (GID)<br />Current rights:<br /><strong> %s ( %s ) </strong>/<br /><strong> %s ( %s )</strong>',

	// sysinfo (new by mic)
	'simamsysinfo'		=> $_VERSION->PRODUCT.' System Info',
	'sisysteminfo'		=> 'System Info',
	'sibuilton'			=> 'Operating System',
	'sidbversion'		=> 'Database Version (MySQL)',
	'siphpversion'		=> 'PHP Version',
	'siphpupdate'		=> 'INFORMATION: <span style="color: red;">The PHP version you use is <strong>not</strong> actual!</span><br />To guarantee all functions and features of '.$_VERSION->PRODUCT.' and addons,<br />you should use as minimum <strong>PHP.Version 4.3</strong>!',
	'siwebserver'		=> 'Webserver',
	'siwebsphpif'		=> 'WebServer - PHP Interface',
	'simamboversion'	=> $_VERSION->PRODUCT.' Version',
	'siuseragent'		=> 'Browser Version',
	'sirelevantsettings' => 'Important PHP Settings',
	'sisafemode'		=> 'Safe Mode',
	'sibasedir'			=> 'Open basedir',
	'sidisplayerrors'	=> 'PHP Errors',
	'sishortopentags'	=> 'Short Open Tags',
	'sifileuploads'		=> 'Datei Uploads',
	'simagicquotes'		=> 'Magic Quotes',
	'siregglobals'		=> 'Register Globals',
	'sioutputbuf'		=> 'Output Buffer',
	'sisesssavepath'	=> 'Session Savepath',
	'sisessautostart'	=> 'Session auto start',
	'sixmlenabled'		=> 'XML enabled',
	'sizlibenabled'		=> 'ZLIB enabled',
	'sidisabledfuncs'	=> 'Non enabled functions',
	'sieditor'			=> 'WYSIWYG Editor',
	'siconfigfile'		=> 'Config file',
	'siphpinfo'			=> 'PHP Info',
	'siphpinformation'	=> 'PHP Information',
	'sipermissions'		=> 'Permissions',
	'sidirperms'		=> 'Directory permissions',
	'sidirpermsmess'	=> 'To be shure that all functions and features of '.$_VERSION->PRODUCT.' are working correct, following folders should have permission to write [chmod 0777]',
	'sionoff'			=> array( 'On', 'Off' ),
	
	'extract_warning' => "Do you really want to extract this file? Here?\\nThis will overwrite existing files when not used carefully!",
	'extract_success' => "Extraction was successful",
	'extract_failure' => "Extraction failed",
	
	'overwrite_files' => 'Overwrite existing file(s)?',
	"viewlink"		=> "VIEW",
	"actview"		=> "Showing source of file",
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_chmod.php file
	'recurse_subdirs'	=> 'Recurse into subdirectories?',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to footer.php file
	'check_version'	=> 'Check for latest version',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_rename.php file
	'rename_file'	=>	'Rename a directory or file...',
	'newname'		=>	'New Name',
	
	// added by Paulino Michelazzo (paulino@michelazzo.com.br) to fun_edit.php file
	'returndir'	=>	'Return to directory after saving?',
	'line'		=> 	'Line',
	'column'	=>	'Column',
	'wordwrap'	=>	'Wordwrap: (IE only)',
	'copyfile'	=>	'Copy file into this filename',
	
	// Bookmarks
	'quick_jump' => 'Quick Jump To',
	'already_bookmarked' => 'This directory is already bookmarked',
	'bookmark_was_added' => 'This directory was added to the bookmark list.',
	'not_a_bookmark' => 'This directory is not a bookmark.',
	'bookmark_was_removed' => 'This directory was removed from the bookmark list.',
	'bookmarkfile_not_writable' => "Failed to %s the bookmark.\n The Bookmark File '%s' \nis not writable.",
	
	'lbl_add_bookmark' => 'Add this Directory as Bookmark',
	'lbl_remove_bookmark' => 'Remove this Directory from the Bookmark List',
	
	'enter_alias_name' => 'Please enter the alias name for this bookmark',
	
	'normal_compression' => 'normal compression',
	'good_compression' => 'good compression',
	'best_compression' => 'best compression',
	'no_compression' => 'no compression',
	
	'creating_archive' => 'Creating Archive File...',
	'processed_x_files' => 'Processed %s of %s Files',
	
	'ftp_header' => 'Local FTP Authentication',
	'ftp_login_lbl' => 'Please enter the login credentials for the FTP server',
	'ftp_login_name' => 'FTP User Name',
	'ftp_login_pass' => 'FTP Password',
	'ftp_hostname_port' => 'FTP Server Hostname and Port <br />(Port is optional)',
	'ftp_login_check' => 'Checking FTP connection...',
	'ftp_connection_failed' => "The FTP server could not be contacted. \nPlease check that the FTP server is running on your server.",
	'ftp_login_failed' => "The FTP login failed. Please check the username and password and try again.",
		
	'switch_file_mode' => 'Current mode: <strong>%s</strong>. You could switch to %s mode.',
	'symlink_target' => 'Target of the Symbolic Link',
	
	"permchange"		=> "CHMOD Success:",
	"savefile"		=> "The File was saved.",
	"moveitem"		=> "Moving succeeded.",
	"copyitem"		=> "Copying succeeded.",
	'archive_name' 	=> 'Name of the Archive File',
	'archive_saveToDir' 	=> 'Save the Archive in this directory',
	
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
