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
 * @subpackage		phpshop.app.view.products
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<div class="products form">
<?php echo $form->create('Product');?>
	<fieldset>
 		<legend><?php __('Add Product');?></legend>
	<?php
		echo $form->input('name');
		echo $form->input('handle');
		echo $form->input('description', array('id'=>'description'));
		echo '<div class="input">';
		echo $form->label('Active');
		echo $form->checkbox('Product.active');
		echo '</div>';
		echo $form->input('brand_id');
		echo $form->input('product_type_id');
		echo $form->input('tags', array('type'=>'text'));
		echo $form->input('Category');
	?>
	</fieldset>
	<fieldset>
 		<legend><?php __('Default ProductItem');?></legend>
	<?php
		echo $form->input('ProductItem.sku');
		echo $form->input('ProductItem.label');
		echo $form->input('ProductItem.sell_price');
		echo $form->input('ProductItem.regular_price');
		echo $form->input('ProductItem.weight');
		echo $form->input('ProductItem.quantity');
		echo '<div class="input">';
		echo $form->label('Track Stock');
		echo $form->checkbox('ProductItem.track_stock');
		echo '</div>';
	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('List Products', true), array('action'=>'index'));?></li>
		<li><?php echo $html->link(__('List Brands', true), array('controller'=> 'products', 'action'=>'brand_index')); ?> </li>
		<li><?php echo $html->link(__('List Product Types', true), array('controller'=> 'products', 'action'=>'product_type_index')); ?> </li>
	</ul>
</div>
