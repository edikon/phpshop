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
 * @subpackage		phpshop.app.controllers.customer_addresses
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

class CustomerAddressesController extends AppController {

	var $name = 'CustomerAddresses';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->CustomerAddress->recursive = 0;
		$this->set('customerAddresses', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid CustomerAddress.', true));
			$this->redirect(array('controller' => 'customers', 'action'=>'index'));
		}
		$this->set('customerAddress', $this->CustomerAddress->read(null, $id));
	}

	function admin_add() {
		
		if (!empty($this->data)) {
			$this->CustomerAddress->create();
			if ($this->CustomerAddress->save($this->data)) {
				$this->Session->setFlash(__('The CustomerAddress has been saved', true));
				$this->redirect(array('controller' => 'customers', 'action'=>'view', $this->data['CustomerAddress']['customer_id']));
			} else {
				$this->Session->setFlash(__('The CustomerAddress could not be saved. Please, try again.', true));
				$customer_id = $this->data['CustomerAddress']['customer_id'];		
			}
		}
		else {
			$customer_id = $this->passedArgs['customer_id'];		
		}

		$this->set('customer_id', $customer_id);
		
		$zones = $this->CustomerAddress->Zone->find('list');
		$countries = $this->CustomerAddress->Country->find('list');
		$this->set(compact('zones', 'countries'));
	}

	function admin_edit($id = null) {
		
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid CustomerAddress', true));
			$this->redirect(array('controller' => 'customers', 'action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->CustomerAddress->save($this->data)) {
				$this->Session->setFlash(__('The CustomerAddress has been saved', true));
				$this->redirect(array('controller' => 'customers', 'action'=>'view', $this->data['CustomerAddress']['customer_id']));
			} else {
				$this->Session->setFlash(__('The CustomerAddress could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->CustomerAddress->read(null, $id);
		}
		$zones = $this->CustomerAddress->Zone->find('list');
		$countries = $this->CustomerAddress->Country->find('list');
		$this->set(compact('zones','countries'));

		$customer_id = $this->data['CustomerAddress']['customer_id'];
		$this->set('customer_id', $customer_id);
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for CustomerAddress', true));
			$this->redirect(array('action'=>'index'));
		}
		if (empty($this->data)) {
			$this->data = $this->CustomerAddress->read(null, $id);
		}
		if ($this->CustomerAddress->del($id)) {
			$this->Session->setFlash(__('CustomerAddress deleted', true));
			$this->redirect(array('controller' => 'customers', 'action'=>'view', $this->data['CustomerAddress']['customer_id']));
		}
	}

}
?>