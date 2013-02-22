<?php
/**
* @version $Id: install.extplorer.php 57 2007-07-08 18:05:52Z soeren $
* @package eXtplorer
* @copyright (C) 2005-2007 Soeren
* @license GNU / GPL
* @author soeren
* joomlaXplorer is Free Software
*/
function com_install(){
	global $database;
	
	if( is_callable( array( 'JFactory', 'getDBO' ))) {
		$database = JFactory::getDBO();
	}
	$mypath = dirname(__FILE__);
	require_once($mypath . "/include/functions.php");
	require_once($mypath . "/libraries/Archive.php");
	
	ext_RaiseMemoryLimit( '16M' );
	error_reporting( E_ALL ^ E_NOTICE );
	
	$archive_name = $mypath.'/scripts.zip';
	$archive_as_dir = $archive_name.'/';
	$extract_dir = $mypath.'/';
	
	$result = File_Archive::extract( $archive_as_dir, $extract_dir );
	if( !PEAR::isError( $result )) {
		unlink( $archive_name );
	}
	$database->setQuery( "SELECT id FROM #__components WHERE admin_menu_link = 'option=com_extplorer'" );
	$id = $database->loadResult();

	//add new admin menu images
	$database->setQuery( "UPDATE #__components SET admin_menu_img = '../administrator/components/com_extplorer/images/joomla_x_icon.png', admin_menu_link = 'option=com_extplorer' WHERE id=$id");
	$database->query();
}
?>