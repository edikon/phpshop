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

<script language="JavaScript" type="text/javascript">
<!--

function showhide (id)
{
var style = document.getElementById(id).style
if (style.visibility == "hidden")
	style.visibility = "visible";
else
	style.visibility = "hidden";
}

// -->
</script> 

<h1>Shipping</h1>

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
<td align="center"><strong><?php echo $currency->format($cart_total) ?></strong></td>
</tr>
</table>

<p>&nbsp;</p>
<h2>Confirm Your Address</h2>
<?php echo $form->create('Customer', array('url'=>'/store/register'));?>

<table width="100%" id="checkout">
<tr>
<td width="50%" valign="top">
		<h3><?php __('Billing Information'); ?></h3>
		<?php echo $form->input('billing_company');?>
		<?php echo $form->input('billing_last_name', array('class' => 'required'));?>
		<?php echo $form->input('billing_first_name', array('class' => 'required'));?>
		<?php echo $form->input('billing_address_1', array('class' => 'required'));?>
		<?php echo $form->input('billing_address_2');?>
		<?php echo $form->checkbox('residential', array('checked'=>'checked'));?><?php __('This is a residence'); ?><br><br>
		<?php echo $form->input('billing_city', array('class' => 'required'));?>
		<div class="input"><label for="CustomerBillingCountry">Billing Country</label>
		<?php echo $form->select('billing_country_id', $countries, null, 
								  array('class' => 'required', 'id' => 'billing_country_id')); ?>
		</div>
		<div class="input"><label for="CustomerBillingState">Billing State</label>
		<?php echo $form->select('billing_state_id', $states, null, 
								  array('class' => 'required', 'id' => 'billing_state_id')); ?>
		</div>
		<?php echo $form->input('billing_zip', array('class' => 'required'));?>
		<?php $options = array('url' => 'update_select_state', 'update' => 'billing_state_id');
		      echo $ajax->observeField('billing_country_id', $options); ?>
			<?php echo $form->input('billing_phone', array('class' => 'required'));?>
</td>

<td valign="top">
	<h3><?php __('Shipping Information'); ?></h3>
	<?php echo $form->checkbox('copy', array('checked'=>'checked', 'onclick'=>"showhide('shippingForm');"));?><?php __('Shipping same as Billing') ?><br /><br />
		<div id="shippingForm" style="visibility: hidden">
		<?php echo $form->input('shipping_company');?>
		<?php echo $form->input('shipping_last_name', array('class' => 'required'));?>
		<?php echo $form->input('shipping_first_name', array('class' => 'required'));?>
		<?php echo $form->input('shipping_address_1', array('class' => 'required'));?>
		<?php echo $form->input('shipping_address_2');?>
		<?php echo $form->checkbox('residential', array('checked'=>'checked'));?><?php __('This is a residence'); ?><br><br>
		<?php echo $form->input('shipping_city', array('class' => 'required'));?>
		<div class="input"><label for="CustomerShippingCountry">Shipping Country</label>
		<?php echo $form->select('shipping_country_id', $countries, null, 
								  array('class' => 'required', 'id' => 'shipping_country_id')); ?>
		</div>
		<div class="input"><label for="CustomerShippingState">Shipping State</label>
		<?php echo $form->select('shipping_state_id', $states, null, 
								  array('class' => 'required', 'id' => 'shipping_state_id')); ?>
		</div>
		<?php echo $form->input('shipping_zip', array('class' => 'required'));?>
		<?php $options = array('url' => 'update_select_state', 'update' => 'shipping_state_id');
		      echo $ajax->observeField('shipping_country_id', $options); ?>
			<?php echo $form->input('shipping_phone', array('class' => 'required'));?>
</div>

</td>
</tr>
<tr>
<td colspan="2">		
		<?php echo $form->submit('Continue');?>
</td>
</tr>
</table>
</form>



