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
<div class="products form">
<?php echo $form->create('Product');?>
	<fieldset>
 		<legend><?php __('Edit Product');?></legend>
	<?php
		echo $form->input('id');
		echo $form->input('name');
		echo $form->input('handle');
		echo $form->input('description', array('id' => 'editor'));
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
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Delete', true), array('action'=>'delete', $form->value('Product.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $form->value('Product.id'))); ?></li>
		<li><?php echo $html->link(__('List Products', true), array('action'=>'index'));?></li>
	</ul>
</div>
