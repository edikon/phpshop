<?php
/* SVN FILE: $Id: brands_controller.php 409 2008-01-24 18:04:51Z pablo $ */
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
class BrandsController extends AppController {

	var $name = 'Brands';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->Brand->recursive = 0;
		$this->set('brands', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid Brand.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->Brand->recursive = 2;
		$this->set('brand', $this->Brand->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->Brand->create();
			if ($this->Brand->save($this->data)) {
				$this->Session->setFlash(__('The Brand has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Brand could not be saved. Please, try again.', true));
			}
		}
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid Brand', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->Brand->save($this->data)) {
				$this->Session->setFlash(__('The Brand has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The Brand could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Brand->read(null, $id);
		}
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for Brand', true));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Brand->del($id)) {
			$this->Session->setFlash(__('Brand deleted', true));
			$this->redirect(array('action'=>'index'));
		}
	}

}
?>