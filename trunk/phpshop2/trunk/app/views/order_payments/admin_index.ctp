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
<div class="orderPayments index">
<h2><?php __('OrderPayments');?></h2>
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
	<th><?php echo $paginator->sort('reference_number');?></th>
	<th><?php echo $paginator->sort('transaction_log');?></th>
	<th><?php echo $paginator->sort('amount');?></th>
	<th><?php echo $paginator->sort('created');?></th>
	<th><?php echo $paginator->sort('modified');?></th>
	<th class="actions"><?php __('Actions');?></th>
</tr>
<?php
$i = 0;
foreach ($orderPayments as $orderPayment):
	$class = null;
	if ($i++ % 2 == 0) {
		$class = ' class="altrow"';
	}
?>
	<tr<?php echo $class;?>>
		<td>
			<?php echo $orderPayment['OrderPayment']['id']; ?>
		</td>
		<td>
			<?php echo $html->link($orderPayment['Order']['id'], array('controller'=> 'orders', 'action'=>'view', $orderPayment['Order']['id'])); ?>
		</td>
		<td>
			<?php echo $orderPayment['OrderPayment']['reference_number']; ?>
		</td>
		<td>
			<?php echo $orderPayment['OrderPayment']['transaction_log']; ?>
		</td>
		<td>
			<?php echo $orderPayment['OrderPayment']['amount']; ?>
		</td>
		<td>
			<?php echo $orderPayment['OrderPayment']['created']; ?>
		</td>
		<td>
			<?php echo $orderPayment['OrderPayment']['modified']; ?>
		</td>
		<td class="actions">
			<?php echo $html->link(__('View', true), array('action'=>'view', $orderPayment['OrderPayment']['id'])); ?>
			<?php echo $html->link(__('Edit', true), array('action'=>'edit', $orderPayment['OrderPayment']['id'])); ?>
			<?php echo $html->link(__('Delete', true), array('action'=>'delete', $orderPayment['OrderPayment']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $orderPayment['OrderPayment']['id'])); ?>
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
		<li><?php echo $html->link(__('New OrderPayment', true), array('action'=>'add')); ?></li>
		<li><?php echo $html->link(__('List Orders', true), array('controller'=> 'orders', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Order', true), array('controller'=> 'orders', 'action'=>'add')); ?> </li>
	</ul>
</div>
