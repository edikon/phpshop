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
<div class="login">

<?php echo $form->create('User', array('action'=> 'login')); ?>
<h2><?php echo _("Username"); ?></h2>
<input name="data[User][username]" size="16" maxlength="64" type="text" /><br />

<h2><?php echo _("Password"); ?></h2>
<input name="data[User][password]" size="16" maxlength="64" type="password" /><br />

<p><strong>Help:</strong> <a href="#">I forgot my username or password</a></p>
<input type="submit" value="Sign in" class="button" /><br /><br />
</form>

</div>
