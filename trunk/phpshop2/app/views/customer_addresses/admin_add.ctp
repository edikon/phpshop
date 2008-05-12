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
 * @subpackage		phpshop.app.views.customer_address
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<div class="customerAddresses form">
<?php echo $form->create('CustomerAddress');?>
	<fieldset>
 		<legend><?php __('Add CustomerAddress');?></legend>
	<?php
		echo $form->input('customer_id', array('type'=>'hidden', 'value' => $customer_id));
		echo $form->input('shipping_company');
		echo $form->input('shipping_last_name');
		echo $form->input('shipping_first_name');
		echo $form->input('shipping_phone');
		echo $form->input('shipping_address_1');
		echo $form->input('shipping_address_2');
		echo $form->input('shipping_city');
		echo $form->input('zone_id');
		echo $form->input('country_id');
		echo $form->input('shipping_zip');
		echo '<div class="input">';
		echo $form->label('Residential?');
		echo $form->checkbox('CustomerAddress.residential');
		echo '</div>';
	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('View Customer', true), array('controller'=> 'customers', 'action'=>'view', $customer_id)); ?> </li>
		<li><?php echo $html->link(__('List Customers', true), array('controller'=> 'customers', 'action'=>'index')); ?> </li>
	</ul>
</div>
