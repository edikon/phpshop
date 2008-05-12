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
<legend>Your Admin Account</legend>
<p>Please input your personal details - you will need these details to login to your phpshop installation</p>
<br />

&nbsp;&nbsp;&nbsp;<label>Username</label>&nbsp;&nbsp;&nbsp; 
<br />
<input name="username"  size="30" class="input" value="<?php echo $values['username']; ?>" type="text" id="username" /><br />

&nbsp;&nbsp;&nbsp; <label>Password</label>&nbsp;&nbsp;&nbsp;
<br />
<input name="password"  size="30" class="input" value="<?php echo $values['password']; ?>" type="password" id="password" /><br />


&nbsp;&nbsp;&nbsp; <label>Name</label>&nbsp;&nbsp;&nbsp; 
<br />
<input name="name"  size="30" class="input" value="<?php echo $values['name']; ?>" type="text" id="name" />
<br />


&nbsp;&nbsp;&nbsp;<label>Email</label>&nbsp;&nbsp;&nbsp;  
<br />
<input name="email"  size="30" class="input" value="<?php echo $values['email']; ?>" type="text" id="email" /><br />
</fieldset>

<p align="center">
<input type="submit" name="submit" value="Submit">
</p>

</form>
</div>
</div>