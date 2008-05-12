<?php
/* SVN FILE: $Id: order_items_controller.php 423 2008-05-12 22:28:15Z pablo $ */
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
 * @subpackage		phpshop.app.controllers.order_items
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

class OrderItemsController extends AppController {

	var $name = 'OrderItems';
	var $helpers = array('Html', 'Form', 'Currency');

	var $uses = array('OrderItem', 'ProductItem');
	
	function admin_index() {
		$this->OrderItem->recursive = 0;
		$this->set('orderItems', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid OrderItem.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->OrderItem->recursive = 3;
		$this->set('orderItem', $this->OrderItem->read(null, $id));
	}

	function admin_add($order_id=null) {
		
		
		if (!empty($this->data)) {
			$this->OrderItem->create();
			if ($this->OrderItem->save($this->data)) {
				$this->Session->setFlash(__('The OrderItem has been saved', true));
				$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderItem']['order_id']));
			} else {
				$this->Session->setFlash(__('The OrderItem could not be saved. Please, try again.', true));
				$order_id = $this->data['OrderItem']['order_id'];
			}
		}
		else {
			$order_id = $this->passedArgs['order_id'];			
		}
		$this->set('order_id', $order_id);
		
		$orderShipments = $this->OrderItem->OrderShipment->find('list');
		$productItems = $this->ProductItem->find('list');
		$this->set(compact('orderShipments', 'productItems'));
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid OrderItem', true));
			$this->redirect(array('controller' => 'orders','action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->OrderItem->save($this->data)) {
				$this->Session->setFlash(__('The OrderItem has been saved', true));
				$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderItem']['order_id']));
			} else {
				$this->Session->setFlash(__('The OrderItem could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->OrderItem->read(null, $id);
		}
		$orderShipments = $this->OrderItem->OrderShipment->find('list');
		$order_id = $this->data['OrderItem']['order_id'];
		$this->set('order_id', $order_id);
		$this->set(compact('orderShipments','orders'));
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for OrderItem', true));
			$this->redirect(array('action'=>'index'));
		}
		if (empty($this->data)) {
			$this->data = $this->OrderItem->read(null, $id);
		}
		if ($this->OrderItem->del($id)) {
			$this->Session->setFlash(__('OrderItem deleted', true));
			$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderItem']['order_id']));
		}
	}

}
?>