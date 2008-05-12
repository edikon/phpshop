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

class AccountController extends AppController {

	var $name = 'Account';

	var $helpers = array('Html', 'Form', 'Javascript', 'Ajax', 'Tree', 'Currency');

	var $components = array('Cart','RequestHandler');
		
	var $layout = 'store';

	var $uses = array('Category', 
					  'Product', 
					  'ProductItem', 
					  'Order',
					  'OrderItem',
					  'OrderStatus',
					  'Country',
					  'Zone',
					  'ShippingRate',
					  'Customer',
					  'CustomerAddress'
					  );
	

	/**
	* Make sure customer is logged in.
	*
	*/
	function beforeFilter() {
		// make sure to run parent beforeFilter() method
		AppController::beforeFilter();
		
		$this->checkSession();
	}	


	function index() {
				
		$customer = $this->Session->read('Customer');
		
		$id = $customer['Customer']['id'];
		
		if (!$id) {
			$this->Session->setFlash(__('Invalid Customer.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->Customer->recursive = 2;
		$this->set('customer', $this->Customer->read(null, $id));
	}

	function edit($id = null) {
		
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid Customer', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->Customer->save($this->data)) {
				$this->Session->setFlash(__('The Customer has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Customer could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Customer->read(null, $id);
		}
		$orders = $this->Customer->Order->find('list');
		$zones = $this->Customer->Zone->find('list');
		$countries = $this->Customer->Country->find('list');
		$this->set(compact('orders','zones','countries'));
	}

}
?>