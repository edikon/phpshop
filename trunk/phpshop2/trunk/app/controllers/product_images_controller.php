<?php
/* SVN FILE: $Id: product_images_controller.php 422 2008-02-03 23:34:08Z yurin $ */
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

class ProductImagesController extends AppController {

	var $name = 'ProductImages';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->ProductImage->recursive = 0;
		$this->set('productImages', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid ProductImage.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('productImage', $this->ProductImage->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->ProductImage->create();
			$filename = time().'_'.$this->data['ProductImage']['image']['name']; 
			$dest_file = WWW_ROOT . "img/products/" . $filename;
			if (move_uploaded_file($this->data['ProductImage']['image']['tmp_name'],$dest_file )) {				 
				$this->data['ProductImage']['image'] = $filename; 
			}
			
			if ($this->ProductImage->save($this->data)) {
				$this->Session->setFlash(__('The ProductImage has been saved', true));
				$this->redirect(array('controller' => 'products', 'action'=>'view', $this->data['ProductImage']['product_id']));
			} else {
				$this->Session->setFlash(__('The ProductImage could not be saved. Please, try again.', true));
			}
		}
		$products = $this->ProductImage->Product->find('list');
		$this->set(compact('products'));
		
		$product = $this->ProductImage->Product->read(null, $this->passedArgs['product_id']);
		$this->set('product', $product['Product']);
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid ProductImage', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->ProductImage->save($this->data)) {
				$this->Session->setFlash(__('The ProductImage has been saved', true));
				$this->redirect(array('controller' => 'products', 'action'=>'view', $this->data['ProductImage']['product_id']));
			} else {
				$this->Session->setFlash(__('The ProductImage could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->ProductImage->read(null, $id);
		}
		$products = $this->ProductImage->Product->find('list');
		$this->set(compact('products'));
		
		$product = $this->ProductImage->Product->read(null, $this->data['ProductImage']['product_id']);
		$this->set('product', $product['Product']);
		
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for ProductImage', true));
			$this->redirect(array('action'=>'index'));
		}
		if (empty($this->data)) {
			$this->data = $this->ProductImage->read(null, $id);
		}
		
		if ($this->ProductImage->del($id)) {
			$this->Session->setFlash(__('ProductImage deleted', true));
			$this->redirect(array('controller' => 'products', 'action'=>'view', $this->data['ProductImage']['product_id']));
		}
	}

}
?>