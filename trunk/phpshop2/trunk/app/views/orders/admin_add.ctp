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
<div class="orders form">
<?php echo $form->create('Order');?>
	<fieldset>
 		<legend><?php __('Add Order');?></legend>
	<?php
 		echo $form->input('customer_id', array('type'=>'select', 'options' => $customers, 'selected' => $this->data['Order']['customer_id'], 'empty' => ''));		echo $form->input('email');
		echo $form->input('billing_company');
		echo $form->input('billing_last_name');
		echo $form->input('billing_first_name');
		echo $form->input('billing_phone');
		echo $form->input('billing_address_1');
		echo $form->input('billing_address_2');
		echo $form->input('billing_city');
		echo $form->input('billing_state');
		echo $form->input('billing_country');
		echo $form->input('billing_zip');
		echo $form->input('shipping_company');
		echo $form->input('shipping_last_name');
		echo $form->input('shipping_first_name');
		echo $form->input('shipping_phone');
		echo $form->input('shipping_address_1');
		echo $form->input('shipping_address_2');
		echo $form->input('shipping_city');
		echo $form->input('shipping_state');
		echo $form->input('shipping_country');
		echo $form->input('shipping_zip');
		echo '<div class="input">';
		echo $form->label('Residential?');
		echo $form->checkbox('CustomerAddress.residential');
		echo '</div>';
		echo $form->input('subtotal');
		echo $form->input('zone_tax');
		echo $form->input('country_tax');
		echo $form->input('shipping');
		echo $form->input('shipping_tax');
		echo $form->input('total');
		echo $form->input('comments');
 		echo $form->input('order_status_id', array('type'=>'select', 'options' => $orderStatuses, 'selected' => $this->data['Order']['order_status_id'], 'empty' => ''));	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('List Orders', true), array('action'=>'index'));?></li>
	</ul>
</div>
