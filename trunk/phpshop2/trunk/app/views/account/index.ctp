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
<div class="account index">
<h1><?php  __('Your Account');?></h1>


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
<?php echo $customer['Customer']['email']; ?>
</p>		

<?php echo $html->link(__('Edit', true), array('action'=>'edit', $customer['Customer']['id'])); ?>

</div>

<p>&nbsp;</p>

<div class="related">
	<h2><?php __('Shipping Addresses');?></h2>
	<?php if (!empty($customer['CustomerAddress'])):?>
	<table cellpadding ="0" cellspacing ="0" class="account">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Address'); ?></th>
		<th><?php __('City'); ?></th>
		<th><?php __('Zone'); ?></th>
		<th><?php __('Country'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($customer['CustomerAddress'] as $customerAddress):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $customerAddress['id'];?></td>
			<td><?php echo $customerAddress['shipping_address_1'];?></td>
			<td><?php echo $customerAddress['shipping_city'];?></td>
			<td><?php echo $customerAddress['Zone']['name'];?></td>
			<td><?php echo $customerAddress['Country']['name'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'customer_addresses', 'action'=>'view', $customerAddress['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'customer_addresses', 'action'=>'edit', $customerAddress['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'customer_addresses', 'action'=>'delete', $customerAddress['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $customerAddress['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

<?php echo $html->link(__('New Shipping Address', true), array('controller'=> 'customer_addresses', 'action'=>'add', 'customer_id' => $customer['Customer']['id']));?>
</div>

<p>&nbsp;</p>

<div class="related">
	<h2><?php __('Previous Orders');?></h2>
	<?php if (!empty($customer['Order'])):?>
	<table cellpadding = "0" cellspacing = "0" class="account">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Email'); ?></th>
		<th><?php __('Total'); ?></th>
		<th><?php __('Status'); ?></th>
		<th><?php __('Created'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($customer['Order'] as $order):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}			
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $order['id'];?></td>
			<td><?php echo $order['email'];?></td>
			<td><?php echo $order['total'];?></td>
			<td><?php echo $order['OrderStatus']['name'];?></td>
			<td><?php echo $order['created'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'orders', 'action'=>'view', $order['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

</div>
