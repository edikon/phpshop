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

<h1>Checkout</h1>

<?php if (isset($cart_items)): ?>

<?php echo $form->create('Payment', array('url'=>'index'));?>

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

<tr class="action">
<td colspan="2"></td>
<td align="right"><strong>Grand Total:</strong></td>
<td align="center"><strong><?php echo $currency->format($order_total) ?></strong></td>
</tr>

</table>


<p>&nbsp;</p>

<table width="100%">
<tr>
	<td width="50%" valign="top">
		<h2>Billing Address</h2>
<p>
<?php echo $customer['Customer']['billing_first_name'] ?> <?php echo $customer['Customer']['billing_last_name'] ?><br  />
<?php if (!empty($customer['Customer']['billing_company'])): ?>
<?php echo $customer['Customer']['billing_company'] ?><br />
<?php endif; ?>
<?php echo $customer['Customer']['billing_address_1'] ?><br />
<?php if (!empty($customer['Customer']['billing_address_2'])): ?>
<?php echo $customer['Customer']['billing_address_2'] ?><br />
<?php endif; ?>
<?php echo $customer['Customer']['billing_city'] ?>, <?php echo $customer['Zone']['name'] ?> <?php echo $customer['Customer']['billing_zip'] ?><br />
</p>
<?php echo $html->link(_('Edit'), array('action' => 'update_billing')); ?>
<p>&nbsp;</p>
</td>
<td valign="top">
<h2>Shipping Address</h2>
<p>
<?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_first_name'] ?> <?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_last_name'] ?><br  />
<?php if (!empty($customer['CustomerShipping']['CustomerAddress']['shipping_company'])): ?>
<?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_company'] ?><br />
<?php endif; ?>
<?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_address_1'] ?><br />
<?php if (!empty($customer['CustomerShipping']['CustomerAddress']['shipping_address_2'])): ?>
<?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_address_2'] ?><br />
<?php endif; ?>
<?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_city'] ?>, <?php echo $customer['CustomerShipping']['Zone']['name'] ?> <?php echo $customer['CustomerShipping']['CustomerAddress']['shipping_zip'] ?><br />
</p>
<?php echo $html->link(_('Edit'), array('action' => 'update_shipping')); ?>
</td>
</tr></table>

<h2>Shipping Method</h2>

<p>Please select a shipping method for delivery of your products.</p>
<?php echo $form->radio('shipping_rate', $shipping_rates, null, array('class' => 'required')); ?>

<p>&nbsp;</p>

<?php // decide if we want to capture payment information right here, or redirect to a plugin after the confirm page ?>



	
<?php echo $form->submit('Continue');?>
</form>


<?php else: ?>
Your shopping cart is currently empty.
<?php endif; ?>


