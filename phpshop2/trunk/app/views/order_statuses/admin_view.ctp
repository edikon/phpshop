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
<div class="orderStatuses view">
<h2><?php  __('OrderStatus');?></h2>
	<dl><?php $i = 0; $class = ' class="altrow"';?>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Id'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $orderStatus['OrderStatus']['id']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Name'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $orderStatus['OrderStatus']['name']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Sort Order'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $orderStatus['OrderStatus']['sort_order']; ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Edit OrderStatus', true), array('action'=>'edit', $orderStatus['OrderStatus']['id'])); ?> </li>
		<li><?php echo $html->link(__('Delete OrderStatus', true), array('action'=>'delete', $orderStatus['OrderStatus']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $orderStatus['OrderStatus']['id'])); ?> </li>
		<li><?php echo $html->link(__('List OrderStatuses', true), array('action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New OrderStatus', true), array('action'=>'add')); ?> </li>
	</ul>
</div>

<?php if (!empty($orderStatus['Order'])):?>
<div class="related">
	<h3><?php __('Related Orders');?></h3>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Customer Id'); ?></th>
		<th><?php __('Total'); ?></th>
		<th><?php __('Order Status Id'); ?></th>
		<th><?php __('Created'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($orderStatus['Order'] as $order):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $order['id'];?></td>
			<td><?php echo $order['customer_id'];?></td>
			<td><?php echo $order['total'];?></td>
			<td><?php echo $order['order_status_id'];?></td>
			<td><?php echo $order['created'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'orders', 'action'=>'view', $order['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'orders', 'action'=>'edit', $order['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'orders', 'action'=>'delete', $order['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $order['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
</div>
<?php endif; ?>
