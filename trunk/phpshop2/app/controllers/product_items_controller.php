<?php
/* SVN FILE: $Id: product_items_controller.php 414 2008-01-27 23:38:34Z pablo $ */
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
 * @subpackage		phpshop.app.controllers.product_items
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

class ProductItemsController extends AppController {

	var $name = 'ProductItems';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->ProductItem->recursive = 0;
		$this->set('productItems', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid ProductItem.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('productItem', $this->ProductItem->read(null, $id));
	}

	function admin_add() {
		
		if (!empty($this->data)) {
			$this->ProductItem->create();
			if ($this->ProductItem->save($this->data)) {
				$this->Session->setFlash(__('The ProductItem has been saved', true));
				$this->redirect(array('controller' => 'products', 'action'=>'view', $this->data['ProductItem']['product_id']));
			} else {
				$this->Session->setFlash(__('The ProductItem could not be saved. Please, try again.', true));
			}
		}
		$product = $this->ProductItem->Product->read(null, $this->passedArgs['product_id']);
		$this->set('product', $product['Product']);
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid ProductItem', true));
			$this->redirect(array('controller' => 'products', 'action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->ProductItem->save($this->data)) {
				$this->Session->setFlash(__('The ProductItem has been saved', true));
				$this->redirect(array('controller' => 'products', 'action'=>'view', $this->data['ProductItem']['product_id']));
			} else {
				$this->Session->setFlash(__('The ProductItem could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->ProductItem->read(null, $id);
		}
		$product = $this->ProductItem->Product->read(null, $this->data['ProductItem']['product_id']);
		$this->set('product', $product['Product']);
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for ProductItem', true));
			$this->redirect(array('controller' => 'products', 'action'=>'index'));
		}
		if (empty($this->data)) {
			$this->data = $this->ProductItem->read(null, $id);
		}
		if ($this->ProductItem->del($id)) {
			$this->Session->setFlash(__('ProductItem deleted', true));
			$this->redirect(array('controller' => 'products', 'action'=>'view', $this->data['ProductItem']['product_id']));
		}
	}

}
?>