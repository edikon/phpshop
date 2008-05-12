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
<div class="shippingRates form">
<?php echo $form->create('ShippingRate');?>
	<fieldset>
 		<legend><?php __('Edit ShippingRate');?></legend>
	<?php
		echo $form->input('id');
		echo $form->input('country_id');
 		echo $form->input('zone_id', array('type'=>'select', 'options' => $zones, 'selected' => $this->data['ShippingRate']['zone_id'], 'empty' => ''));
		echo $form->input('name');
		echo $form->input('start');
		echo $form->input('end');
		echo $form->input('price');
	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Delete', true), array('action'=>'delete', $form->value('ShippingRate.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $form->value('ShippingRate.id'))); ?></li>
		<li><?php echo $html->link(__('List ShippingRates', true), array('action'=>'index'));?></li>
		<li><?php echo $html->link(__('List Countries', true), array('controller'=> 'countries', 'action'=>'index')); ?> </li>
	</ul>
</div>
