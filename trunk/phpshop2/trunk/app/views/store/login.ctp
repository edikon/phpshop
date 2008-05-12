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
<h1>Login</h1>


<p>&nbsp;</p>
<?php if ($error): ?>
<p>The login credentials you supplied could not be recognized. Please try again.</p>
<?php endif; ?>

<table width="100%">
	<tr><td width="50%" valign="top">
<h3><?php __('Customer Login') ?></h3>
<p><?php __('If you are an existing customer, please login below.') ?></p>
<?php echo $form->create('Customer', array('url'=>'/store/login'));?>
<?php echo $form->hidden('login', array('value'=> '1'));?>
<?php echo $form->input('login_email', array('class' => 'required', 'label'=> __('Email', true)));?>
<?php echo $form->input('login_password', array('class' => 'required', 'label'=> __('Password', true)));?>
<?php echo $form->checkbox('lost_password');?><?php __('Email Lost Password'); ?>
<p>&nbsp;</p>
<?php echo $form->submit('Login');?>
</form>
</td>

<td valign="top">
<h3><?php __('Create Account'); ?></h3>
<p><?php __('If you are a new customer, please fill in the form below.') ?></p>
<?php echo $form->create('Customer', array('url'=>'/store/login'));?>
<?php echo $form->hidden('login', array('value'=> '0'));?>
<?php echo $form->input('email', array('class' => 'required'));?>
<?php echo $form->input('password', array('class' => 'required'));?>
<?php echo $form->input('password2', array('class' => 'required', 'type' => 'password', 'label' => __('Confirm Password', true)));?>
<?php echo $form->submit('Create');?>

</td></tr></table>
