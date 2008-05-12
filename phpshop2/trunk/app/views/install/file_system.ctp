<?php
/* SVN FILE: $Id:$ */
/**
 *
 * PHP versions 4 and 5
 *
 * phpShop(tm) :  A Simple Shopping Cart <http://www.phpshop.org/>
 * Copyright 1998-2008, 	Edikon Corporation
 *							3455 Peachtree Road Suite 500
 *							Atlanta, Georgia 30326
 *
 * Licensed under The GNU General Public License
 * Redistributions of files must retain the above copyright notice.
 *
 * @filesource
 * @copyright		Copyright 1998-2008, Edikon Corporation
 * @link			http://www.edikon.com/ phpShop(tm) Project
 * @package			phpshop
 * @subpackage		phpshop.app.controllers
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<form method="post">
<div class="image-info">
Before you continue with phpShop installation, there are some problems that need to be fixed.<br /><br/>
<?php foreach($areNotWriteable as $dir){ ?>
<div id="errorMessage" class="message" >The <?php echo $dir; ?> directory should be writable so that cheesecake can work properly. Use your FTP program to change its mode to 777.</div>
<br />
<?php } ?>
<br />
Note: in case of tmp/ directory all the subdirectories need to be writeable as well
<br />
<br />
Once you are done, hit the "Try again" button.<br />
<p align=center >
<input type="Submit" name="again" value="Try again">
</p>
</div>
</form>