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
<div class="countries form">
<?php echo $form->create('Country');?>
	<fieldset>
 		<legend><?php __('Edit Country');?></legend>
	<?php
		echo $form->input('id');
		echo $form->input('name');
		echo $form->input('iso_code_2');
		echo $form->input('iso_code_3');
		echo $form->input('tax_rate');
		echo '<div class="input">';
		echo $form->label('Active');
		echo $form->checkbox('Country.active');
		echo '</div>';
	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Delete', true), array('action'=>'delete', $form->value('Country.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $form->value('Country.id'))); ?></li>
		<li><?php echo $html->link(__('List Countries', true), array('action'=>'index'));?></li>
	</ul>
</div>
