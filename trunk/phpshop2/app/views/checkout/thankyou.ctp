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
<?php
/*
* Checkout page is meant to be easy to use.  Using JS we either show or hide the shipping address fields.
*
*/
?>
<h1>Thank You for Your Order</h1>

<?php if (isset($cart_items)): ?>

<table width="100%">
<tr>
	<td width="50%" valign="top">
		<h2>Billing Address</h2>
<p>
<?php echo $order['Order']['billing_first_name'] ?> <?php echo $order['Order']['billing_last_name'] ?><br  />
<?php if(!empty($order['Order']['billing_company'])):?>
<?php echo $order['Order']['billing_company'] ?><br />
<?php endif; ?>
<?php echo $order['Order']['billing_address_1'] ?><br />
<?php if (!empty($order['Order']['billing_address_2'])): ?>
<?php echo $order['Order']['billing_address_2'] ?><br />
<?php endif; ?>
<?php echo $order['Order']['billing_city'] ?>, <?php echo $order['Order']['billing_state'] ?> <?php echo $order['Order']['billing_zip'] ?><br />
</p>
<p>&nbsp;</p>
</td>
<td valign="top">
<h2>Shipping Address</h2>
<p>
<?php echo $order['Order']['shipping_first_name'] ?> <?php echo $order['Order']['shipping_last_name'] ?><br  />
<?php if (!empty($order['Order']['shipping_company'])): ?>
<?php echo $order['Order']['shipping_company'] ?><br />
<?php endif; ?>
<?php echo $order['Order']['shipping_address_1'] ?><br />
<?php if(!empty($order['Order']['shipping_address_2'])): ?>
<?php echo $order['Order']['shipping_address_2'] ?><br />
<?php endif; ?>
<?php echo $order['Order']['shipping_city'] ?>, <?php echo $order['Order']['shipping_state'] ?> <?php echo $order['Order']['shipping_zip'] ?><br />
</p>
</td>
</tr></table>


<p>&nbsp;</p>

<table id="cart" cellspacing="0" cellpadding="0">
<tr>
<th>Quantity</th>
<th width="50%">Product</th>
<th>Product Price</th>
<th>Amount</th>
</tr>

<?php $i=0;foreach($cart_items as $product): ?>
<tr align="center">
<td width="10"><?php echo $product['quantity'] ?></td>
<td><?php echo $product['item']['Product']['name'] ?>
	<?php // show item handle if not the same as name ?>
<?php if($product['item']['Product']['name'] != $product['item']['ProductItem']['label']): ?>	
	 (<?php echo $product['item']['ProductItem']['label'] ?>)
<?php endif; ?></td>
<td><?php echo $currency->format($product['item']['ProductItem']['sell_price']) ?></td>
<td><?php echo $currency->format(($product['quantity'] * $product['item']['ProductItem']['sell_price'])) ?></td>
</tr>
<?php endforeach; ?>

<tr class="action">
<td colspan="2"></td>
<td align="right"><strong>Subtotal:</strong></td>
<td align="center"><strong><?php echo $currency->format($cart_total); ?></strong></td>
</tr>

<?php if ($country_tax > 0): ?>
<tr class="action">
<td colspan="2"></td>
<td align="right"><strong>Federal Tax:</strong></td>
<td align="center"><strong><?php echo $currency->format($country_tax); ?></strong></td>
</tr>
<?php endif; ?>

<?php if ($zone_tax > 0): ?>
<tr class="action">
<td colspan="2"></td>
<td align="right"><strong>Sales Tax:</strong></td>
<td align="center"><strong><?php echo $currency->format($zone_tax) ?></strong></td>
</tr>
<?php endif; ?>

<?php if ($shipping > 0): ?>
<tr class="action">
<td colspan="2"></td>
<td align="right"><strong>Shipping:</strong></td>
<td align="center"><strong><?php echo $currency->format($shipping) ?></strong></td>
</tr>
<?php endif; ?>

<tr class="action">
<td colspan="2"></td>
<td align="right"><strong>Grand Total:</strong></td>
<td align="center"><strong><?php echo $currency->format($order_total) ?></strong></td>
</tr>

</table>

<p>&nbsp;</p>



<?php else: ?>
Your shopping cart is currently empty.
<?php endif; ?>
