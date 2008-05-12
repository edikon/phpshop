<?php
/* SVN FILE: $Id: categories_controller.php 423 2008-05-12 22:28:15Z pablo $ */
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

class CategoriesController extends AppController {

	var $name = 'Categories';
	var $helpers = array('Html', 'Form');
	
	var $spacer = '-';

	var $paginate = array('order'=>array('ParentCategory.name' => 'asc')); 

	function admin_index() {
		$this->Category->recursive = 0;
		$this->set('categories', $this->paginate());
		$this->Category->getPaths( $this->viewVars['categories'] ); 	
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid Category.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->Category->recursive = 2;
		$this->set('category', $this->Category->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->Category->create();
			if ($this->Category->save($this->data)) {
				$this->Session->setFlash(__('The Category has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Category could not be saved. Please, try again.', true));
			}
		}
		$products = $this->Category->Product->find('list');
		$parentCategories = $this->Category->generatetreelist(null, null, null, $this->spacer);
		$this->set(compact('products', 'parentCategories'));
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid Category', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->Category->save($this->data)) {
				$this->Session->setFlash(__('The Category has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Category could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Category->read(null, $id);
		}
		$products = $this->Category->Product->find('list');
		$parentCategories = $this->Category->generatetreelist(null, null, null, $this->spacer);
		$this->set(compact('products','parentCategories'));
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for Category', true));
			$this->redirect(array('action'=>'index'));
		}
		
		$category = $this->Category->read(null, $id);
		if ($category['Category']['handle'] == 'home') {
			$this->Session->setFlash(__('Category \'home\' must not be deleted.', true));
			$this->redirect(array('action'=>'index'));			
		}
		if ($this->Category->del($id)) {
			$this->Session->setFlash(__('Category deleted', true));
			$this->redirect(array('action'=>'index'));
		}
	}

}
?>