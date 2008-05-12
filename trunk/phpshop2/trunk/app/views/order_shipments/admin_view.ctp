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
<div class="orderShipments view">
<h2><?php  __('OrderShipment');?></h2>
	<dl><?php $i = 0; $class = ' class="altrow"';?>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Id'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $orderShipment['OrderShipment']['id']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Order'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($orderShipment['Order']['id'], array('controller'=> 'orders', 'action'=>'view', $orderShipment['Order']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Shipping Rate'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($orderShipment['ShippingRate']['name'], array('controller'=> 'shipping_rates', 'action'=>'view', $orderShipment['ShippingRate']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Shipping Date'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $orderShipment['OrderShipment']['shipping_date']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Reference Number'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $orderShipment['OrderShipment']['reference_number']; ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Edit OrderShipment', true), array('action'=>'edit', $orderShipment['OrderShipment']['id'])); ?> </li>
		<li><?php echo $html->link(__('Delete OrderShipment', true), array('action'=>'delete', $orderShipment['OrderShipment']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $orderShipment['OrderShipment']['id'])); ?> </li>
	</ul>
</div>
<div class="related">
	<h3><?php __('Related Order Items');?></h3>
	<?php if (!empty($orderShipment['OrderItem'])):?>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Product Item Id'); ?></th>
		<th><?php __('Quantity'); ?></th>
		<th><?php __('Price'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($orderShipment['OrderItem'] as $orderItem):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $orderItem['id'];?></td>
			<td><?php echo $orderItem['product_item_id'];?></td>
			<td><?php echo $orderItem['quantity'];?></td>
			<td><?php echo $orderItem['price'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'order_items', 'action'=>'view', $orderItem['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'order_items', 'action'=>'edit', $orderItem['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'order_items', 'action'=>'delete', $orderItem['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $orderItem['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('New Order Item', true), array('controller'=> 'order_items', 'action'=>'add'));?> </li>
		</ul>
	</div>
</div>
