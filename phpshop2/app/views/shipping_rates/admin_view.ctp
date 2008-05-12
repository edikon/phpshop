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
<div class="shippingRates view">
<h2><?php  __('ShippingRate');?></h2>
	<dl><?php $i = 0; $class = ' class="altrow"';?>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Id'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $shippingRate['ShippingRate']['id']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Country'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($shippingRate['Country']['name'], array('controller'=> 'countries', 'action'=>'view', $shippingRate['Country']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Zone'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($shippingRate['Zone']['name'], array('controller'=> 'zones', 'action'=>'view', $shippingRate['Zone']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Name'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $shippingRate['ShippingRate']['name']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Start'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $shippingRate['ShippingRate']['start']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('End'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $shippingRate['ShippingRate']['end']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Price'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $shippingRate['ShippingRate']['price']; ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Edit ShippingRate', true), array('action'=>'edit', $shippingRate['ShippingRate']['id'])); ?> </li>
		<li><?php echo $html->link(__('Delete ShippingRate', true), array('action'=>'delete', $shippingRate['ShippingRate']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $shippingRate['ShippingRate']['id'])); ?> </li>
		<li><?php echo $html->link(__('List ShippingRates', true), array('action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New ShippingRate', true), array('action'=>'add')); ?> </li>
	</ul>
</div>
<div class="related">
	<h3><?php __('Related Order Shipments');?></h3>
	<?php if (!empty($shippingRate['OrderShipment'])):?>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Order Id'); ?></th>
		<th><?php __('Shipping Rate Id'); ?></th>
		<th><?php __('Shipping Date'); ?></th>
		<th><?php __('Reference Number'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($shippingRate['OrderShipment'] as $orderShipment):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $orderShipment['id'];?></td>
			<td><?php echo $orderShipment['order_id'];?></td>
			<td><?php echo $orderShipment['shipping_rate_id'];?></td>
			<td><?php echo $orderShipment['shipping_date'];?></td>
			<td><?php echo $orderShipment['reference_number'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'order_shipments', 'action'=>'view', $orderShipment['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'order_shipments', 'action'=>'edit', $orderShipment['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'order_shipments', 'action'=>'delete', $orderShipment['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $orderShipment['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('New Order Shipment', true), array('controller'=> 'order_shipments', 'action'=>'add'));?> </li>
		</ul>
	</div>
</div>
