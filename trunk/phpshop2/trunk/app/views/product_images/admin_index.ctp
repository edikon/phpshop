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
<div class="productImages index">
<h2><?php __('ProductImages');?></h2>
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
	<th><?php echo $paginator->sort('image');?></th>
	<th><?php echo $paginator->sort('priority');?></th>
	<th class="actions"><?php __('Actions');?></th>
</tr>
<?php
$i = 0;
foreach ($productImages as $productImage):
	$class = null;
	if ($i++ % 2 == 0) {
		$class = ' class="altrow"';
	}
?>
	<tr<?php echo $class;?>>
		<td>
			<?php echo $productImage['ProductImage']['id']; ?>
		</td>
		<td>
			<?php echo $html->link($productImage['Product']['name'], array('controller'=> 'products', 'action'=>'view', $productImage['Product']['id'])); ?>
		</td>
		<td>
			<?php echo $productImage['ProductImage']['image']; ?>
		</td>
		<td>
			<?php echo $productImage['ProductImage']['priority']; ?>
		</td>
		<td class="actions">
			<?php echo $html->link(__('View', true), array('action'=>'view', $productImage['ProductImage']['id'])); ?>
			<?php echo $html->link(__('Edit', true), array('action'=>'edit', $productImage['ProductImage']['id'])); ?>
			<?php echo $html->link(__('Delete', true), array('action'=>'delete', $productImage['ProductImage']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $productImage['ProductImage']['id'])); ?>
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
		<li><?php echo $html->link(__('New ProductImage', true), array('action'=>'add')); ?></li>
		<li><?php echo $html->link(__('List Products', true), array('controller'=> 'products', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Product', true), array('controller'=> 'products', 'action'=>'add')); ?> </li>
	</ul>
</div>
