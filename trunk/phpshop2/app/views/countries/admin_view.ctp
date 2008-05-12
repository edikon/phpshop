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
<div class="countries view">
<h2><?php  __('Country');?></h2>
	<dl><?php $i = 0; $class = ' class="altrow"';?>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Id'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $country['Country']['id']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Name'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $country['Country']['name']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Iso Code 2'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $country['Country']['iso_code_2']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Iso Code 3'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $country['Country']['iso_code_3']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Tax Rate'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $country['Country']['tax_rate']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Active'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $country['Country']['active']; ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Edit Country', true), array('action'=>'edit', $country['Country']['id'])); ?> </li>
		<li><?php echo $html->link(__('Delete Country', true), array('action'=>'delete', $country['Country']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $country['Country']['id'])); ?> </li>
		<li><?php echo $html->link(__('List Countries', true), array('action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Country', true), array('action'=>'add')); ?> </li>
	</ul>
</div>
<div class="related">
	<h3><?php __('Related Shipping Rates');?></h3>
	<?php if (!empty($country['ShippingRate'])):?>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Zone'); ?></th>
		<th><?php __('Name'); ?></th>
		<th><?php __('Start'); ?></th>
		<th><?php __('End'); ?></th>
		<th><?php __('Price'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($country['ShippingRate'] as $shippingRate):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $shippingRate['id'];?></td>
			<td><?php echo $shippingRate['zone_id'];?></td>
			<td><?php echo $shippingRate['name'];?></td>
			<td><?php echo $shippingRate['start'];?></td>
			<td><?php echo $shippingRate['end'];?></td>
			<td><?php echo $shippingRate['price'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'shipping_rates', 'action'=>'view', $shippingRate['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'shipping_rates', 'action'=>'edit', $shippingRate['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'shipping_rates', 'action'=>'delete', $shippingRate['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $shippingRate['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('New Shipping Rate', true), array('controller'=> 'shipping_rates', 'action'=>'add'));?> </li>
		</ul>
	</div>
</div>
<div class="related">
	<h3><?php __('Related Zones');?></h3>
	<?php if (!empty($country['Zone'])):?>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Name'); ?></th>
		<th><?php __('Code'); ?></th>
		<th><?php __('Tax Rate'); ?></th>
		<th><?php __('Active'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($country['Zone'] as $zone):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $zone['id'];?></td>
			<td><?php echo $zone['name'];?></td>
			<td><?php echo $zone['code'];?></td>
			<td><?php echo $zone['tax_rate'];?></td>
			<td><?php echo $zone['active'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'zones', 'action'=>'view', $zone['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'zones', 'action'=>'edit', $zone['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'zones', 'action'=>'delete', $zone['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $zone['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('New Zone', true), array('controller'=> 'zones', 'action'=>'add'));?> </li>
		</ul>
	</div>
</div>
