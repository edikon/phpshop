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
<div class="orderShipments form">
<?php echo $form->create('OrderShipment');?>
	<fieldset>
 		<legend><?php __('Add OrderShipment for Order: ' . $order_id);?></legend>
	<?php
		echo $form->input('order_id', array('type'=>'hidden', 'value' => $order_id));
		echo $form->input('shipping_rate_id');
		echo $form->input('shipping_date');
		echo $form->input('reference_number');
		echo $form->input('OrderItem');
	?>
	</fieldset>
<?php echo $form->end('Submit');?>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('View Order', true), array('controller'=> 'orders', 'action'=>'view', $order_id)); ?> </li>
	</ul>
</div>
