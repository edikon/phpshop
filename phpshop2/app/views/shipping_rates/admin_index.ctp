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
<div class="shippingRates index">
<h2><?php __('ShippingRates');?></h2>
<p>
<?php
echo $paginator->counter(array(
'format' => __('Page %page% of %pages%, showing %current% records out of %count% total, starting on record %start%, ending on %end%', true)
));
?></p>
<table cellpadding="0" cellspacing="0">
<tr>
	<th><?php echo $paginator->sort('id');?></th>
	<th><?php echo $paginator->sort('country_id');?></th>
	<th><?php echo $paginator->sort('zone_id');?></th>
	<th><?php echo $paginator->sort('name');?></th>
	<th><?php echo $paginator->sort('start');?></th>
	<th><?php echo $paginator->sort('end');?></th>
	<th><?php echo $paginator->sort('price');?></th>
	<th class="actions"><?php __('Actions');?></th>
</tr>
<?php
$i = 0;
foreach ($shippingRates as $shippingRate):
	$class = null;
	if ($i++ % 2 == 0) {
		$class = ' class="altrow"';
	}
?>
	<tr<?php echo $class;?>>
		<td>
			<?php echo $shippingRate['ShippingRate']['id']; ?>
		</td>
		<td>
			<?php echo $html->link($shippingRate['Country']['name'], array('controller'=> 'countries', 'action'=>'view', $shippingRate['Country']['id'])); ?>
		</td>
		<td>
			<?php echo $html->link($shippingRate['Zone']['name'], array('controller'=> 'zones', 'action'=>'view', $shippingRate['Zone']['id'])); ?>
		</td>
		<td>
			<?php echo $shippingRate['ShippingRate']['name']; ?>
		</td>
		<td>
			<?php echo $shippingRate['ShippingRate']['start']; ?>
		</td>
		<td>
			<?php echo $shippingRate['ShippingRate']['end']; ?>
		</td>
		<td>
			<?php echo $shippingRate['ShippingRate']['price']; ?>
		</td>
		<td class="actions">
			<?php echo $html->link(__('View', true), array('action'=>'view', $shippingRate['ShippingRate']['id'])); ?>
			<?php echo $html->link(__('Edit', true), array('action'=>'edit', $shippingRate['ShippingRate']['id'])); ?>
			<?php echo $html->link(__('Delete', true), array('action'=>'delete', $shippingRate['ShippingRate']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $shippingRate['ShippingRate']['id'])); ?>
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
		<li><?php echo $html->link(__('New ShippingRate', true), array('action'=>'add')); ?></li>
	</ul>
</div>
