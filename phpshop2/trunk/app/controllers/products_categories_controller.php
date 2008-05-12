<?php
/* SVN FILE: $Id: products_categories_controller.php 409 2008-01-24 18:04:51Z pablo $ */
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

class ProductsCategoriesController extends AppController {

	var $name = 'ProductsCategories';
	var $helpers = array('Html', 'Form' );

	function admin_index() {
		$this->ProductsCategory->recursive = 0;
		$this->set('productsCategories', $this->paginate());
	}

	function admin_view($id = null) {
		if(!$id) {
			$this->Session->setFlash('Invalid Products Category.');
			$this->redirect(array('action'=>'index'), null, true);
		}
		$this->set('productsCategory', $this->ProductsCategory->read(null, $id));
	}

	function admin_add() {
		if(!empty($this->data)) {
			$this->cleanUpFields();
			$this->ProductsCategory->create();
			if($this->ProductsCategory->save($this->data)) {
				$this->Session->setFlash('The Products Category has been saved');
				$this->redirect(array('action'=>'index'), null, true);
			} else {
				$this->Session->setFlash('The Products Category could not be saved. Please, try again.');
			}
		}
	}

	function admin_edit($id = null) {
		if(!$id && empty($this->data)) {
			$this->Session->setFlash('Invalid Products Category');
			$this->redirect(array('action'=>'index'), null, true);
		}
		if(!empty($this->data)) {
			$this->cleanUpFields();
			if($this->ProductsCategory->save($this->data)) {
				$this->Session->setFlash('The Products Category saved');
				$this->redirect(array('action'=>'index'), null, true);
			} else {
				$this->Session->setFlash('The Products Category could not be saved. Please, try again.');
			}
		}
		if(empty($this->data)) {
			$this->data = $this->ProductsCategory->read(null, $id);
		}
	}

	function admin_delete($id = null) {
		if(!$id) {
			$this->Session->setFlash('Invalid id for Products Category');
			$this->redirect(array('action'=>'index'), null, true);
		}
		if($this->ProductsCategory->del($id)) {
			$this->Session->setFlash('Products Category #'.$id.' deleted');
			$this->redirect(array('action'=>'index'), null, true);
		}
	}

}
?>