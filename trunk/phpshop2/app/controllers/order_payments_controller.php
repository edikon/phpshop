<?php
/* SVN FILE: $Id: order_payments_controller.php 414 2008-01-27 23:38:34Z pablo $ */
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
 * @subpackage		phpshop.app.controllers.order_payments
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

class OrderPaymentsController extends AppController {

	var $name = 'OrderPayments';
	var $helpers = array('Html', 'Form', 'Currency');

	function admin_index() {
		$this->OrderPayment->recursive = 0;
		$this->set('orderPayments', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid OrderPayment.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('orderPayment', $this->OrderPayment->read(null, $id));
	}

	function admin_add() {	
		
		if (!empty($this->data)) {
			$this->OrderPayment->create();
			if ($this->OrderPayment->save($this->data)) {
				$this->Session->setFlash(__('The OrderPayment has been saved', true));
				$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderPayment']['order_id']));
			} else {
				$this->Session->setFlash(__('The OrderPayment could not be saved. Please, try again.', true));
			}
		}
		
		$order_id = $this->passedArgs['order_id'];
		$this->set('order_id', $order_id);
	}

	function admin_edit($id = null) {
				
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid OrderPayment', true));
			$this->redirect(array('controller' => 'orders', 'action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->OrderPayment->save($this->data)) {
				$this->Session->setFlash(__('The OrderPayment has been saved', true));
				$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderPayment']['order_id']));
			} else {
				$this->Session->setFlash(__('The OrderPayment could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->OrderPayment->read(null, $id);
		}
		$order_id = $this->data['OrderPayment']['order_id'];
		$this->set('order_id', $order_id);
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for OrderPayment', true));
			$this->redirect(array('controller' => 'orders', 'action'=>'index'));
		}
		if (empty($this->data)) {
			$this->data = $this->OrderPayment->read(null, $id);
		}
		if ($this->OrderPayment->del($id)) {
			$this->Session->setFlash(__('OrderPayment deleted', true));
			$this->redirect(array('controller' => 'orders', 'action'=>'view', $this->data['OrderPayment']['order_id']));
		}
	}

}
?>