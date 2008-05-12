<?php
/* SVN FILE: $Id: order_shipments_controller.php 412 2008-01-25 02:11:47Z pablo $ */
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

class OrderShipmentsController extends AppController {

	var $name = 'OrderShipments';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->OrderShipment->recursive = 0;
		$this->set('orderShipments', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid OrderShipment.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('orderShipment', $this->OrderShipment->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->OrderShipment->create();
			if ($this->OrderShipment->save($this->data)) {
				$this->Session->setFlash(__('The OrderShipment has been saved', true));
				$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderShipment']['order_id']));
			} else {
				$this->Session->setFlash(__('The OrderShipment could not be saved. Please, try again.', true));
			}
		}
		$orderItems = $this->OrderShipment->OrderItem->find('list');
		$shippingRates = $this->OrderShipment->ShippingRate->find('list');
		$this->set(compact('orderItems', 'shippingRates'));

		$order_id = $this->passedArgs['order_id'];
		$this->set('order_id', $order_id);
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid OrderShipment', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->OrderShipment->save($this->data)) {
				$this->Session->setFlash(__('The OrderShipment has been saved', true));
				$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderShipment']['order_id']));
			} else {
				$this->Session->setFlash(__('The OrderShipment could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->OrderShipment->read(null, $id);
		}
		$orderItems = $this->OrderShipment->OrderItem->find('list');
		$shippingRates = $this->OrderShipment->ShippingRate->find('list');
		$this->set(compact('orderItems','shippingRates'));

		$order_id = $this->data['OrderShipment']['order_id'];
		$this->set('order_id', $order_id);
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for OrderShipment', true));
			$this->redirect(array('action'=>'index'));
		}
		if (empty($this->data)) {
			$this->data = $this->OrderShipment->read(null, $id);
		}
		if ($this->OrderShipment->del($id)) {
			$this->Session->setFlash(__('OrderShipment deleted', true));
			$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderShipment']['order_id']));
		}
	}

}
?>