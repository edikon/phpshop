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
<h1>Shopping Cart</h1>

<?php if (isset($products)): ?>

<form action="<?php echo $html->url("/store/cart"); ?>" method="get">

<table id="cart" cellspacing="0" cellpadding="0">
<tr>
<th>Quantity</th>
<th width="50%">Product</th>
<th>Product Price</th>
<th>Amount</th>
<th>Action</th>
</tr>
<?php $i=0;foreach($products as $product): ?>
<tr align="center">
<td width="10"><input type="text" value="<?php echo $product['quantity'] ?>" name="quantity[<?php echo $product['item']['ProductItem']['id'] ?>]" size="2"></td>
<td><?php echo $product['item']['Product']['name'] ?>
	<?php // show item handle if not the same as name ?>
<?php if($product['item']['Product']['name'] != $product['item']['ProductItem']['label']): ?>	
	 (<?php echo $product['item']['ProductItem']['label'] ?>)
<?php endif; ?></td>
<td><?php echo $currency->format($product['item']['ProductItem']['sell_price']) ?></td>
<td><?php echo $currency->format(($product['quantity'] * $product['item']['ProductItem']['sell_price'])) ?></td>
<td><a href="<?php echo $html->url("/store/cart?action=delete&product_item_id={$product['item']['ProductItem']['id']}"); ?>">Remove</a></td>
</tr>
<?php endforeach; ?>

<tr class="action">
<td colspan="2"><input type="submit" name="update" value="Update Quantities"></td>
<td align="right"><strong>Subtotal:</strong></td>
<td align="center"><strong><?php echo $currency->format($cart_total) ?></strong></td>
<td>&nbsp;</td>
</tr>

<tr class="action">
<td colspan="3" align="right"><strong>Shipping Estimate:</strong></td>
<td align="center"><strong>0.00</strong></td>
<td>&nbsp;</td>
</tr>

</table>
<input type="hidden" name="action" value="update">
</form>

<p>&nbsp;</p>
<form action="<?php echo $html->url("/checkout/index"); ?>" method="get">
<input type="submit" name="checkout" value="Proceed to Checkout">
</form>

<?php else: ?>
Your shopping cart is currently empty.
<?php endif; ?>