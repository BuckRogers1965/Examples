<?php
/** ensure this file is being included by a parent file */
if( !defined( '_JEXEC' ) && !defined( '_VALID_MOS' ) ) die( 'Restricted access' );

$GLOBALS['ext_home'] = 'http://joomlacode.org/gf/project/joomlaxplorer';

define ( "_JX_PATH", $mosConfig_absolute_path."/administrator/components/com_joomlaxplorer" );
define ( "_JX_URL", $mosConfig_live_site."/administrator/components/com_joomlaxplorer" );

$GLOBALS['ERROR'] = '';

$GLOBALS['__GET']	=&$_GET;
$GLOBALS['__POST']	=&$_POST;
$GLOBALS['__SERVER']	=&$_SERVER;
$GLOBALS['__FILES']	=&$_FILES;

if( file_exists(_JX_PATH."/languages/$mosConfig_lang.php"))
  require _JX_PATH."/languages/$mosConfig_lang.php";
else
  require _JX_PATH."/languages/english.php";
  
if( file_exists(_JX_PATH."/languages/".$mosConfig_lang."_mimes.php"))
  require _JX_PATH."/languages/".$mosConfig_lang."_mimes.php";
else
  require _JX_PATH."/languages/english_mimes.php";
  
// the filename of the QuiXplorer script: (you rarely need to change this)
if($_SERVER['SERVER_PORT'] == 443 ) {
	$GLOBALS["script_name"] = "https://".$GLOBALS['__SERVER']['HTTP_HOST'].$GLOBALS['__SERVER']["PHP_SELF"];
}
else {
	$GLOBALS["script_name"] = "http://".$GLOBALS['__SERVER']['HTTP_HOST'].$GLOBALS['__SERVER']["PHP_SELF"];
}
@session_start();
if( !isset( $_REQUEST['dir'] )) {
	$dir = $GLOBALS['dir'] = mosGetParam( $_SESSION,'ext_dir', '' );
}
else {
	$dir = $GLOBALS['dir'] = $_SESSION['ext_dir'] = mosGetParam( $_REQUEST, "dir" );
}


if( strstr( $mosConfig_absolute_path, "/" )) {
	$GLOBALS["separator"] = "/";
}
else {
	$GLOBALS["separator"] = "\\";
}
// Get Sort
$GLOBALS["order"]=mosGetParam( $_REQUEST, 'order', 'name');
// Get Sortorder
$GLOBALS["direction"]=mosGetParam( $_REQUEST, 'direction', 'ASC');
  
// show hidden files in QuiXplorer: (hide files starting with '.', as in Linux/UNIX)
$GLOBALS["show_hidden"] = true;

// filenames not allowed to access: (uses PCRE regex syntax)
$GLOBALS["no_access"] = "^\.ht";

// user permissions bitfield: (1=modify, 2=password, 4=admin, add the numbers)
$GLOBALS["permissions"] = 1;

$GLOBALS['file_mode'] = 'file';

require _JX_PATH."/config/mimes.php";
require _JX_PATH."/application.php";
require _JX_PATH."/libraries/File_Operations.php";
require _JX_PATH."/include/functions.php";
require _JX_PATH."/include/header.php";
require _JX_PATH."/include/footer.php";
require _JX_PATH."/include/result.class.php";

//------------------------------------------------------------------------------
$GLOBALS['ext_File'] = new ext_File();

$abs_dir=get_abs_dir($GLOBALS["dir"]);
if(!file_exists($GLOBALS["home_dir"])) {
  if(!file_exists($GLOBALS["home_dir"].$GLOBALS["separator"])) {
	if(!empty($GLOBALS["require_login"])) {
		$extra="<a href=\"".make_link("logout",NULL,NULL)."\">".
			$GLOBALS["messages"]["btnlogout"]."</A>";
	} 
	else {
		$extra=NULL;
	}
	$GLOBALS['ERROR'] = $GLOBALS["error_msg"]["home"];
  }
}
if(!down_home($abs_dir)) ext_Result::sendResult('', false, $GLOBALS["dir"]." : ".$GLOBALS["error_msg"]["abovehome"]);
if(!is_dir($abs_dir))
  if(!is_dir($abs_dir.$GLOBALS["separator"]))
	$GLOBALS['ERROR'] = $abs_dir." : ".$GLOBALS["error_msg"]["direxist"];
//------------------------------------------------------------------------------
