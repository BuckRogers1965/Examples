<?php
// ensure this file is being included by a parent file
if( !defined( '_JEXEC' ) && !defined( '_VALID_MOS' ) ) die( 'Restricted access' );
/**
 * @version $Id: $
 * @package eXtplorer
 * @copyright soeren 2007
 * @author The eXtplorer project (http://sourceforge.net/projects/extplorer)
 * @author The  The QuiX project (http://quixplorer.sourceforge.net)
 * @license
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU General Public License Version 2 or later (the "GPL"), in
 * which case the provisions of the GPL are applicable instead of
 * those above. If you wish to allow use of your version of this file only
 * under the terms of the GPL and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting  the provisions above and replace  them with the notice and
 * other provisions required by the GPL.  If you do not delete
 * the provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL."
 * 
*/
/**
 * Uploads file(s)
 *
 */
class ext_Upload extends ext_Action {
	
	function execAction($dir) {	
	
		if(($GLOBALS["permissions"]&01)!=01) {
			ext_Result::sendResult('upload', false, $GLOBALS["error_msg"]["accessfunc"]);
		}
		
		// Execute
		if(isset($GLOBALS['__POST']["confirm"]) && $GLOBALS['__POST']["confirm"]=="true") {	
			
			$cnt=count($GLOBALS['__FILES']['userfile']['name']);
			$err=false;
			$err_available=isset($GLOBALS['__FILES']['userfile']['error']);
		
			// upload files & check for errors
			for($i=0;$i<$cnt;$i++) {
				$errors[$i]=NULL;
				$tmp = $GLOBALS['__FILES']['userfile']['tmp_name'][$i];
				$items[$i] = stripslashes($GLOBALS['__FILES']['userfile']['name'][$i]);
				if($err_available) $up_err = $GLOBALS['__FILES']['userfile']['error'][$i];
				else $up_err=(file_exists($tmp)?0:4);
				$abs = get_abs_item($dir,$items[$i]);
			
				if($items[$i]=="" || $up_err==4) continue;
				if($up_err==1 || $up_err==2) {
					$errors[$i]=$GLOBALS["error_msg"]["miscfilesize"];
					$err=true;	continue;
				}
				if($up_err==3) {
					$errors[$i]=$GLOBALS["error_msg"]["miscfilepart"];
					$err=true;	continue;
				}
				if(!@is_uploaded_file($tmp)) {
					$errors[$i]=$GLOBALS["error_msg"]["uploadfile"];
					$err=true;	continue;
				}
				if(@file_exists($abs) && empty( $_REQUEST['overwrite_files'])) {
					$errors[$i]=$GLOBALS["error_msg"]["itemdoesexist"];
					$err=true;	continue;
				}
				
				// Upload
				$ok = @$GLOBALS['ext_File']->move_uploaded_file($tmp, $abs);
				if($ok===false || PEAR::isError( $ok )) {
					$errors[$i]=$GLOBALS["error_msg"]["uploadfile"];
					if( PEAR::isError( $ok ) ) $errors[$i].= ' ['.$ok->getMessage().']';
					$err=true;	continue;
				}
				else {
					$mode = ext_isFTPMode() ? 755 : 0755;
				  	@$GLOBALS['ext_File']->chmod( $abs, $mode );
				}
			}
			
			if($err) {			// there were errors
				$err_msg="";
				for($i=0;$i<$cnt;$i++) {
					if($errors[$i]==NULL) continue;
					$err_msg .= $items[$i]." : ".$errors[$i]."\n";
				}
				ext_Result::sendResult('upload', false, $err_msg);
			}
			
			ext_Result::sendResult('upload', true, 'Upload successful!');
			return;
		}
		
	?>
	<div style="width:auto;">
	    <div class="x-box-tl"><div class="x-box-tr"><div class="x-box-tc"></div></div></div>
	    <div class="x-box-ml"><div class="x-box-mr"><div class="x-box-mc">
	
	        <h3 style="margin-bottom:5px;"><?php echo $GLOBALS["messages"]["actupload"] ?></h3>
	        <?php echo '<br />
	        Maximum File Size = <strong>'. ((get_max_file_size() / 1024) / 1024).' MB</strong><br />
			Maximum Upload Limit = <strong>'. ((get_max_upload_limit() / 1024) / 1024).' MB</strong><br />';
			?>
	        <div id="adminForm">
	
	        </div>
	    </div></div></div>
	    <div class="x-box-bl"><div class="x-box-br"><div class="x-box-bc"></div></div></div>
	</div>
	<script type="text/javascript">
	var simple = new Ext.form.Form({
	    labelWidth: 125, // label settings here cascade unless overridden
	    url:'index3.php',
	    fileUpload: true
	});
	simple.add(
		<?php
		for($i=0;$i<10;$i++) {
		    echo "new Ext.form.TextField({
		        fieldLabel: '{$GLOBALS["messages"]["newname"]}',
		        name: 'userfile[$i]',
		        width:275,
		        inputType: 'file'
		    }),";
		}
		?>
		new Ext.form.Checkbox({
			fieldLabel: '<?php echo $GLOBALS["messages"]["overwrite_files"] ?>',
			name: 'overwrite_files',
			checked: true
		})
	    );
	
	simple.addButton('Save', function() {
		statusBarMessage( 'Processing Upload, please wait...', true );
	    simple.submit({
	        //reset: true,
	        reset: false,
	        success: function(form, action) {
	        	datastore.reload();
	        	statusBarMessage( action.result.message, false, true );
	        	dialog.destroy();
	        },
	        failure: function(form, action) {
	        	if( !action.result ) return;
	        	Ext.MessageBox.alert('Error!', action.result.error);
	        	statusBarMessage( action.result.error, false, false );
	        },
	        scope: simple,
	        // add some vars to the request, similar to hidden fields
	        params: {option: 'com_extplorer', 
	        		action: 'upload', 
	        		dir: datastore.directory,
	        		requestType: 'xmlhttprequest',
	        		confirm: 'true'}
	    });
	});
	simple.addButton('<?php echo ext_Lang::msg( 'btncancel', true ) ?>', function() { dialog.destroy(); } );
	simple.render('adminForm');
	</script>
	<?php
		
	}
}
?>