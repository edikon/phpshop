<?php
/* SVN FILE: $Id: shipping_rates_controller.php 409 2008-01-24 18:04:51Z pablo $ */
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

class ShippingRatesController extends AppController {

	var $name = 'ShippingRates';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->ShippingRate->recursive = 0;
		$this->set('shippingRates', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid ShippingRate.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('shippingRate', $this->ShippingRate->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->ShippingRate->create();
			if ($this->ShippingRate->save($this->data)) {
				$this->Session->setFlash(__('The ShippingRate has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The ShippingRate could not be saved. Please, try again.', true));
			}
		}
		$countries = $this->ShippingRate->Country->find('list');
		$zones = $this->ShippingRate->Zone->find('list');
		$this->set(compact('countries', 'zones'));
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid ShippingRate', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->ShippingRate->save($this->data)) {
				$this->Session->setFlash(__('The ShippingRate has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The ShippingRate could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->ShippingRate->read(null, $id);
		}
		$countries = $this->ShippingRate->Country->find('list');
		$zones = $this->ShippingRate->Zone->find('list');
		$this->set(compact('countries','zones'));
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for ShippingRate', true));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->ShippingRate->del($id)) {
			$this->Session->setFlash(__('ShippingRate deleted', true));
			$this->redirect(array('action'=>'index'));
		}
	}

}
?>