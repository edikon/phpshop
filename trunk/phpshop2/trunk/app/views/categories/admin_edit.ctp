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
<div class="categories form">
<?php echo $form->create('Category');?>
	<fieldset>
 		<legend><?php __('Edit Category');?></legend>
	<?php
		echo $form->input('id');
 		echo $form->input('parent_id', array('type'=>'select', 'options' => $parentCategories, 'selected' => $this->data['Category']['parent_id'], 'empty' => ''));
		echo $form->input('handle');
		echo $form->input('name');
		echo $form->input('description');
		echo $form->input('image');
		echo '<div class="input">';
		echo $form->label('Active');
		echo $form->checkbox('Category.active');
		echo '</div>';
		echo $form->input('Product');
	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Delete', true), array('action'=>'delete', $form->value('Category.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $form->value('Category.id'))); ?></li>
		<li><?php echo $html->link(__('List Categories', true), array('action'=>'index'));?></li>
	</ul>
</div>
