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
<?php echo $html->docType('xhtml-strict'); ?>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<title>phpShop(tm) : <?php echo $title_for_layout;?></title>
	<link rel="icon" href="<?php echo $this->webroot . 'favicon.ico';?>" type="image/x-icon" />
	<link rel="shortcut icon" href="<?php echo $this->webroot . 'favicon.ico';?>" type="image/x-icon" />

	<?php echo $html->css(array('store')); ?>
	
	<?php if(isset($javascript)) { echo $javascript->link(array('prototype.js','scriptaculous.js?load=effects')); } ?>


</head>

<body>
	<div id="container">
		<div id="header"><h1>&nbsp;</h1></div>
		<div class="accountinfo">
			<?php if ($session->check('Customer')): ?>
				<?php $customer = $session->read('Customer'); ?>
				Logged in as <a href="<?php echo ini_get('session.cookie_path') ?>account/index"><?php echo $customer['Customer']['billing_first_name']; ?> <?php echo $customer['Customer']['billing_last_name']; ?></a>.   
				(Not <a href="<?php echo ini_get('session.cookie_path') ?>store/logout"><?php echo $customer['Customer']['billing_first_name']; ?></a>?)
			<?php endif; ?>
		</div>
		<div class="headermenu">
			<ul>
			<li><a href="<?php echo ini_get('session.cookie_path') ?>">Home</a></li>
			<li><a href="<?php echo ini_get('session.cookie_path') ?>/store/cart">Cart</a></li>
			<li><a href="<?php echo ini_get('session.cookie_path') ?>/checkout/index">Checkout</a></li>
			<?php if ($session->check('Customer')): ?>
			<li><a href="<?php echo ini_get('session.cookie_path') ?>/account/index">My Account</a></li>
			<li><a href="<?php echo ini_get('session.cookie_path') ?>/store/logout">Logout</a></li>
			<?php else: ?>
			<li><a href="<?php echo ini_get('session.cookie_path') ?>/store/login">Login</a></li>	
			<?php endif; ?>
			</ul>	
		</div>
<!--
		<div class="searchform">
			<form>
			<input type="text" size="16">	
			</form>
		</div>
-->	
		
		<div id="content">	

			<?php // only show minicart if this value is not true ?>	
			<?php if (!isset($mini_cart)): ?>
					<?php echo $this->renderElement('store_mini_cart'); ?>	
			<?php endif; ?>
				
			<?php if ($session->check('Message.flash'))
					{
						$session->flash();
					}
					echo $content_for_layout;
			?>
			<br clear="all">
			<br clear="all">
		</div>
		
		<div id="navigation">
			<?php echo $this->renderElement('store_category_menu'); ?>	
		</div>
		<div id="footer">
		<div class="footermenu">
		<ul>
		<li><a href="<?php echo ini_get('session.cookie_path') ?>">Home</a></li>
		<li><a href="<?php echo ini_get('session.cookie_path') ?>/checkout/index">Checkout</a></li>
		<li><a href="<?php echo ini_get('session.cookie_path') ?>/account/index">My Account</a></li>
		<li><a href="<?php echo ini_get('session.cookie_path') ?>">Contact Us</a></li>
		<li><a href="<?php echo ini_get('session.cookie_path') ?>/admin/orders">Administration</a></li>
		</ul>
			<p>
			<a href="http://www.phpshop.org/" target="_new">phpShop(tm) Power</a>
			</p>
		</div>
		</div>
	</div>
</body>
</html>
