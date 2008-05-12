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
 * @subpackage		phpshop.app.views.products
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<div class="products view">
<h2><?php  __('Product');?></h2>
	<dl><?php $i = 0; $class = ' class="altrow"';?>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Id'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['id']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Name'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['name']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Handle'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['handle']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Description'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['description']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Active'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['active']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Brand'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($product['Brand']['name'], array('controller'=> 'brands', 'action'=>'view', $product['Brand']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Product Type'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($product['ProductType']['name'], array('controller'=> 'product_types', 'action'=>'view', $product['ProductType']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Tags'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['tags']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Created'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['created']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Modified'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $product['Product']['modified']; ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Edit Product', true), array('action'=>'edit', $product['Product']['id'])); ?> </li>
		<li><?php echo $html->link(__('Delete Product', true), array('action'=>'delete', $product['Product']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $product['Product']['id'])); ?> </li>
		<li><?php echo $html->link(__('List Products', true), array('action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Product', true), array('action'=>'add')); ?> </li>
	</ul>
</div>

<div class="related">
	<h3><?php __('Related Product Items');?></h3>
	<?php if (!empty($product['ProductItem'])):?>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Sku'); ?></th>
		<th><?php __('Label'); ?></th>
		<th><?php __('Sell Price'); ?></th>
		<th><?php __('Regular Price'); ?></th>
		<th><?php __('Weight'); ?></th>
		<th><?php __('Quantity'); ?></th>
		<th><?php __('Track Stock'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($product['ProductItem'] as $productItem):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $productItem['id'];?></td>
			<td><?php echo $productItem['sku'];?></td>
			<td><?php echo $productItem['label'];?></td>
			<td><?php echo $productItem['sell_price'];?></td>
			<td><?php echo $productItem['regular_price'];?></td>
			<td><?php echo $productItem['weight'];?></td>
			<td><?php echo $productItem['quantity'];?></td>
			<td><?php echo $productItem['track_stock'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'product_items', 'action'=>'view', $productItem['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'product_items', 'action'=>'edit', $productItem['id'])); ?>
				<?php echo $html->link(__('Delete', true), array('controller'=> 'product_items', 'action'=>'delete', $productItem['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $productItem['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('New Product Item', true), array('controller'=> 'product_items', 'action'=>'add', 'product_id' => $product['Product']['id']));?> </li>
		</ul>
	</div>
</div>

<div class="related">
	<h3><?php __('Related Categories');?></h3>
	<?php if (!empty($product['Category'])):?>
	<table cellpadding = "0" cellspacing = "0">
	<tr>
		<th><?php __('Id'); ?></th>
		<th><?php __('Name'); ?></th>
		<th><?php __('Handle'); ?></th>
		<th><?php __('Active'); ?></th>
		<th class="actions"><?php __('Actions');?></th>
	</tr>
	<?php
		$i = 0;
		foreach ($product['Category'] as $category):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<tr<?php echo $class;?>>
			<td><?php echo $category['id'];?></td>
			<td><?php echo $category['name'];?></td>
			<td><?php echo $category['handle'];?></td>
			<td><?php echo $category['active'];?></td>
			<td class="actions">
				<?php echo $html->link(__('View', true), array('controller'=> 'categories', 'action'=>'view', $category['id'])); ?>
				<?php echo $html->link(__('Edit', true), array('controller'=> 'categories', 'action'=>'edit', $category['id'])); ?>
			</td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('Manage', true), array('action'=>'edit', $product['Product']['id'])); ?> </li>
		</ul>
	</div>
</div>



<div class="related">
	<h3><?php __('Related Product Images');?></h3>
	<?php if (!empty($product['ProductImage'])):?>
	<div id="productimages">
	<ul>
	<?php
		$i = 0;
		foreach ($productImages as $image):
			$class = null;
			if ($i++ % 2 == 0) {
				$class = ' class="altrow"';
			}
		?>
		<li>
		<?php echo $html->link($html->image('products/' . $image['ProductImage']['image']), 
								array('controller'=> 'product_images', 'action'=>'edit', $image['ProductImage']['id'])
							   ,null, null,false); ?>
			<br>
			<?php echo $html->link(__('Delete', true), array('controller'=> 'product_images', 'action'=>'delete', $image['ProductImage']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $image['ProductImage']['id'])); ?>
		</li>
	<?php endforeach; ?>
</ul>
</div>
<?php endif; ?>

	<div class="actions">
		<ul>
			<li><?php echo $html->link(__('New Product Image', true), array('controller'=> 'product_images', 'action'=>'add', 'product_id' => $product['Product']['id']));?> </li>
		</ul>
	</div>
</div>
