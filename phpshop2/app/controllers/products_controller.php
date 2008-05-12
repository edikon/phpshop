<?php
/* SVN FILE: $Id: products_controller.php 416 2008-01-30 20:32:22Z pablo $ */
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

class ProductsController extends AppController {

	var $name = 'Products';
	var $uses = array('Product','Brand','ProductType','Category', 'ProductItem');
	var $helpers = array('Html', 'Form');
    
	var $spacer = '-';

	function admin_index() {
		$this->Product->recursive = 1;
		$this->set('products', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid Product.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('product', $this->Product->read(null, $id));
		// get images by priority
		$this->set('productImages', $this->Product->ProductImage->find('all', array('conditions' => array('product_id'=>$id), 
																					'order' => 'priority ASC')));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->Product->create();
			if ($this->Product->save($this->data)) {
				
				// this is the product id we just created
				$product_id = $this->Product->id;

				// Product Item
				$this->ProductItem->create();
				$this->data['ProductItem']['product_id'] = $product_id;
				if ($this->ProductItem->save($this->data)) {				
					$this->Session->setFlash(__('The Product has been saved', true));
					$this->redirect(array('action'=>'view', $product_id));
				}
				else {
					$this->Session->setFlash(__('The ProductItem could not be saved. Please, try again.', true));
				}
			} else {
				$this->Session->setFlash(__('The Product could not be saved. Please, try again.', true));
			}
		}
		$categories = $this->Product->Category->generatetreelist(null, null, null, $this->spacer);
		$brands = $this->Product->Brand->find('list');
		$productTypes = $this->Product->ProductType->find('list');
		$this->set(compact('categories', 'brands', 'productTypes'));	
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid Product', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->Product->save($this->data)) {
				$this->Session->setFlash(__('The Product has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Product could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Product->read(null, $id);
		}
	
		$categories = $this->Product->Category->generatetreelist(null, null, null, $this->spacer);
		$brands = $this->Product->Brand->find('list');
		$productTypes = $this->Product->ProductType->find('list');
		$this->set(compact('categories','brands','productTypes'));
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for Product', true));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Product->del($id, $cascade = true)) {
			$this->Session->setFlash(__('Product deleted', true));
			$this->redirect(array('action'=>'index'));
		}
	}	
}
?>