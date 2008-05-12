<?php
/* SVN FILE: $Id: orders_controller.php 416 2008-01-30 20:32:22Z pablo $ */
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

class OrdersController extends AppController {

	var $name = 'Orders';
	var $helpers = array('Html', 'Form', 'Currency');

	function admin_index() {
		$this->Order->recursive = 0;
		$this->set('orders', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid Order.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->Order->recursive = 3;
		$this->set('order', $this->Order->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->Order->create();
			if ($this->Order->save($this->data)) {
				$this->Session->setFlash(__('The Order has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Order could not be saved. Please, try again.', true));
			}
		}
		$orderStatuses = $this->Order->OrderStatus->find('list');
		$customers = $this->Order->Customer->find('list');
		$this->set(compact('orderStatuses', 'customers'));
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid Order', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->Order->save($this->data)) {
				$this->Session->setFlash(__('The Order has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Order could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Order->read(null, $id);
		}
		$orderStatuses = $this->Order->OrderStatus->find('list');
		$customers = $this->Order->Customer->find('list');
		$this->set(compact('orderStatuses','customers'));
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for Order', true));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Order->del($id, $cascade = true)) {
			$this->Session->setFlash(__('Order deleted', true));
			$this->redirect(array('action'=>'index'));
		}
	}

}
?>