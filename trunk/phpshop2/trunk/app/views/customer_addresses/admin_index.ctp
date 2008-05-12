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
<div class="customerAddresses index">
<h2><?php __('CustomerAddresses');?></h2>
<p>
<?php
echo $paginator->counter(array(
'format' => __('Page %page% of %pages%, showing %current% records out of %count% total, starting on record %start%, ending on %end%', true)
));
?></p>
<table cellpadding="0" cellspacing="0">
<tr>
	<th><?php echo $paginator->sort('id');?></th>
	<th><?php echo $paginator->sort('customer_id');?></th>
	<th><?php echo $paginator->sort('shipping_company');?></th>
	<th><?php echo $paginator->sort('shipping_last_name');?></th>
	<th><?php echo $paginator->sort('shipping_first_name');?></th>
	<th><?php echo $paginator->sort('shipping_phone');?></th>
	<th><?php echo $paginator->sort('shipping_address_1');?></th>
	<th><?php echo $paginator->sort('shipping_address_2');?></th>
	<th><?php echo $paginator->sort('shipping_city');?></th>
	<th><?php echo $paginator->sort('zone_id');?></th>
	<th><?php echo $paginator->sort('country_id');?></th>
	<th><?php echo $paginator->sort('shipping_zip');?></th>
	<th><?php echo $paginator->sort('created');?></th>
	<th><?php echo $paginator->sort('modified');?></th>
	<th class="actions"><?php __('Actions');?></th>
</tr>
<?php
$i = 0;
foreach ($customerAddresses as $customerAddress):
	$class = null;
	if ($i++ % 2 == 0) {
		$class = ' class="altrow"';
	}
?>
	<tr<?php echo $class;?>>
		<td>
			<?php echo $customerAddress['CustomerAddress']['id']; ?>
		</td>
		<td>
			<?php echo $html->link($customerAddress['Customer']['id'], array('controller'=> 'customers', 'action'=>'view', $customerAddress['Customer']['id'])); ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_company']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_last_name']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_first_name']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_phone']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_address_1']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_address_2']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_city']; ?>
		</td>
		<td>
			<?php echo $html->link($customerAddress['Zone']['name'], array('controller'=> 'zones', 'action'=>'view', $customerAddress['Zone']['id'])); ?>
		</td>
		<td>
			<?php echo $html->link($customerAddress['Country']['name'], array('controller'=> 'countries', 'action'=>'view', $customerAddress['Country']['id'])); ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['shipping_zip']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['created']; ?>
		</td>
		<td>
			<?php echo $customerAddress['CustomerAddress']['modified']; ?>
		</td>
		<td class="actions">
			<?php echo $html->link(__('View', true), array('action'=>'view', $customerAddress['CustomerAddress']['id'])); ?>
			<?php echo $html->link(__('Edit', true), array('action'=>'edit', $customerAddress['CustomerAddress']['id'])); ?>
			<?php echo $html->link(__('Delete', true), array('action'=>'delete', $customerAddress['CustomerAddress']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $customerAddress['CustomerAddress']['id'])); ?>
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
		<li><?php echo $html->link(__('New CustomerAddress', true), array('action'=>'add')); ?></li>
		<li><?php echo $html->link(__('List Customers', true), array('controller'=> 'customers', 'action'=>'index')); ?> </li>
	</ul>
</div>
