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
<div class="productItems index">
<h2><?php __('ProductItems');?></h2>
<p>
<?php
echo $paginator->counter(array(
'format' => __('Page %page% of %pages%, showing %current% records out of %count% total, starting on record %start%, ending on %end%', true)
));
?></p>
<table cellpadding="0" cellspacing="0">
<tr>
	<th><?php echo $paginator->sort('id');?></th>
	<th><?php echo $paginator->sort('product_id');?></th>
	<th><?php echo $paginator->sort('sku');?></th>
	<th><?php echo $paginator->sort('label');?></th>
	<th><?php echo $paginator->sort('sell_price');?></th>
	<th><?php echo $paginator->sort('regular_price');?></th>
	<th><?php echo $paginator->sort('weight');?></th>
	<th><?php echo $paginator->sort('quantity');?></th>
	<th><?php echo $paginator->sort('track_stock');?></th>
	<th><?php echo $paginator->sort('created');?></th>
	<th><?php echo $paginator->sort('modified');?></th>
	<th class="actions"><?php __('Actions');?></th>
</tr>
<?php
$i = 0;
foreach ($productItems as $productItem):
	$class = null;
	if ($i++ % 2 == 0) {
		$class = ' class="altrow"';
	}
?>
	<tr<?php echo $class;?>>
		<td>
			<?php echo $productItem['ProductItem']['id']; ?>
		</td>
		<td>
			<?php echo $html->link($productItem['Product']['name'], array('controller'=> 'products', 'action'=>'view', $productItem['Product']['id'])); ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['sku']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['label']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['sell_price']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['regular_price']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['weight']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['quantity']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['track_stock']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['created']; ?>
		</td>
		<td>
			<?php echo $productItem['ProductItem']['modified']; ?>
		</td>
		<td class="actions">
			<?php echo $html->link(__('View', true), array('action'=>'view', $productItem['ProductItem']['id'])); ?>
			<?php echo $html->link(__('Edit', true), array('action'=>'edit', $productItem['ProductItem']['id'])); ?>
			<?php echo $html->link(__('Delete', true), array('action'=>'delete', $productItem['ProductItem']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $productItem['ProductItem']['id'])); ?>
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
		<li><?php echo $html->link(__('New ProductItem', true), array('action'=>'add')); ?></li>
		<li><?php echo $html->link(__('List Products', true), array('controller'=> 'products', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Product', true), array('controller'=> 'products', 'action'=>'add')); ?> </li>
	</ul>
</div>
