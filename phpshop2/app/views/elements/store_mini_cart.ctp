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
<?php $cart = $this->requestAction('/store/mini_cart'); ?>
<?php if (!empty($cart)): ?>
<div class="minicart">
<?php echo $html->link('Shipping Cart:',   array('controller'=>'store', 'action'=>'cart')); ?> <?php echo $cart['num_items'] ?> items totaling <?php echo $currency->format($cart['cart_total']); ?> &raquo; <?php echo $html->link('Checkout',   array('controller'=>'checkout', 'action'=>'index')); ?>
</div>
<?php endif; ?>
