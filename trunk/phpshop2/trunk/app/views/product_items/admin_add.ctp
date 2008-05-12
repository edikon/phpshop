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
 * @subpackage		phpshop.app.views.product_items
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<div class="productItems form">
<?php echo $form->create('ProductItem');?>
	<fieldset>
 		<legend><?php __('Add ProductItem to: ' . $product['name']);?></legend>
	<?php
		echo $form->input('product_id', array('type' => 'hidden', 'value' => $product['id']));
		echo $form->input('sku');
		echo $form->input('label');
		echo $form->input('sell_price');
		echo $form->input('regular_price');
		echo $form->input('weight');
		echo $form->input('quantity');
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
		<li><?php echo $html->link(__('List ProductItems', true), array('action'=>'index'));?></li>
		<li><?php echo $html->link(__('List Products', true), array('controller'=> 'products', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Product', true), array('controller'=> 'products', 'action'=>'add')); ?> </li>
	</ul>
</div>
