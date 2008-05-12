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
<div class="orderItems index">
<h2><?php __('OrderItems');?></h2>
<p>
<?php
echo $paginator->counter(array(
'format' => __('Page %page% of %pages%, showing %current% records out of %count% total, starting on record %start%, ending on %end%', true)
));
?></p>
<table cellpadding="0" cellspacing="0">
<tr>
	<th><?php echo $paginator->sort('id');?></th>
	<th><?php echo $paginator->sort('order_id');?></th>
	<th><?php echo $paginator->sort('product_item_id');?></th>
	<th><?php echo $paginator->sort('quantity');?></th>
	<th><?php echo $paginator->sort('price');?></th>
	<th><?php echo $paginator->sort('created');?></th>
	<th><?php echo $paginator->sort('modified');?></th>
	<th class="actions"><?php __('Actions');?></th>
</tr>
<?php
$i = 0;
foreach ($orderItems as $orderItem):
	$class = null;
	if ($i++ % 2 == 0) {
		$class = ' class="altrow"';
	}
?>
	<tr<?php echo $class;?>>
		<td>
			<?php echo $orderItem['OrderItem']['id']; ?>
		</td>
		<td>
			<?php echo $html->link($orderItem['Order']['id'], array('controller'=> 'orders', 'action'=>'view', $orderItem['Order']['id'])); ?>
		</td>
		<td>
			<?php echo $html->link($orderItem['ProductItem']['label'], array('controller'=> 'product_items', 'action'=>'view', $orderItem['ProductItem']['id'])); ?>
		</td>
		<td>
			<?php echo $orderItem['OrderItem']['quantity']; ?>
		</td>
		<td>
			<?php echo $orderItem['OrderItem']['price']; ?>
		</td>
		<td>
			<?php echo $orderItem['OrderItem']['created']; ?>
		</td>
		<td>
			<?php echo $orderItem['OrderItem']['modified']; ?>
		</td>
		<td class="actions">
			<?php echo $html->link(__('View', true), array('action'=>'view', $orderItem['OrderItem']['id'])); ?>
			<?php echo $html->link(__('Edit', true), array('action'=>'edit', $orderItem['OrderItem']['id'])); ?>
			<?php echo $html->link(__('Delete', true), array('action'=>'delete', $orderItem['OrderItem']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $orderItem['OrderItem']['id'])); ?>
		</td>
	</tr>
<?php endforeach; ?>
</table>
</div>
<div class="paging">
	<?php echo $paginator->prev('<< '.__('previous', true), array(), null, array('class'=>'disabled'));?>
 | 	<?php echo $paginator->numbers();?>
	<?php echo $paginator->next(__('next', true).' >>', array(), null, array('class'=>'disabled'));?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('New OrderItem', true), array('action'=>'add')); ?></li>
		<li><?php echo $html->link(__('List Orders', true), array('controller'=> 'orders', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Order', true), array('controller'=> 'orders', 'action'=>'add')); ?> </li>
		<li><?php echo $html->link(__('List Product Items', true), array('controller'=> 'product_items', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Product Item', true), array('controller'=> 'product_items', 'action'=>'add')); ?> </li>
		<li><?php echo $html->link(__('List Order Shipments', true), array('controller'=> 'order_shipments', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Order Shipment', true), array('controller'=> 'order_shipments', 'action'=>'add')); ?> </li>
	</ul>
</div>
