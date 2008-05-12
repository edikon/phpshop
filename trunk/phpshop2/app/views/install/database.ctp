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
<div>
<?php if (isset($errors) && !empty($errors) ) {
      ?><div id="errorMessage" class="message"><?php print_r($errors);?></div>
<?php } ?>

<div class="image-info">

<form method=POST>

<fieldset>
<legend>Your MySQL configuration</legend>
<p>This section requires information on how to access your MySQL database. If you don't know how to fill them, check with your webhost support.</p><br /><br />

<label>MySQL Host</label>(localhost is usually OK)
<br />

<input name="dbserver"  size="30" class="input" value="<?php echo $values['dbserver']; ?>" type="text" id="dbserver" />
&nbsp;&nbsp;&nbsp; <br />

&nbsp;&nbsp;&nbsp; <label>MySQL Database Name</label>&nbsp;&nbsp;&nbsp;<br />
<input name="dbname"  size="30" class="input" value="<?php echo $values['dbname']; ?>" type="text" id="dbname" />
<br />

&nbsp;&nbsp;&nbsp; <label>MySQL Username</label>&nbsp;&nbsp;&nbsp;<br />

<input name="dbuser"  size="30" class="input" value="<?php echo $values['dbuser']; ?>" type="text" id="dbuser" />
<br />

&nbsp;&nbsp;&nbsp; <label>MySQL Password</label>&nbsp;&nbsp;&nbsp;
<br />
<input name="dbpass"  size="30" class="input" value="<?php echo $values['dbpass']; ?>" type="password" id="dbpass" /><br />

&nbsp;&nbsp;&nbsp; <label>MySQL table prefix</label>&nbsp;&nbsp;&nbsp;
<br />
<input name="table_prefix"  size="30" class="input" value="<?php echo $values['table_prefix']; ?>" type="text" id="table_prefix" /><br />
</fieldset>
<p align="center">
<input type="submit" name="submit" value="Submit">
</p>

</form>
</div>
</div>