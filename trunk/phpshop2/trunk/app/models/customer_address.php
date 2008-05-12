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

class CustomerAddress extends AppModel {

	var $name = 'CustomerAddress';
	var $useTable = 'customer_addresses';
	var $validate = array(
		'shipping_last_name' => VALID_NOT_EMPTY,
		'shipping_first_name' => VALID_NOT_EMPTY,
		'shipping_phone' => VALID_NOT_EMPTY,
		'shipping_address_1' => VALID_NOT_EMPTY,
		'shipping_city' => VALID_NOT_EMPTY,
		'zone_id' => VALID_NOT_EMPTY,
		'country_id' => VALID_NOT_EMPTY,
		'shipping_zip' => VALID_NOT_EMPTY,
	);

	//The Associations below have been created with all possible keys, those that are not needed can be removed
	var $belongsTo = array(
			'Customer' => array('className' => 'Customer',
								'foreignKey' => 'customer_id',
								'conditions' => '',
								'fields' => '',
								'order' => ''
			),
			'Zone' => array('className' => 'Zone',
								'foreignKey' => 'zone_id',
								'conditions' => '',
								'fields' => '',
								'order' => ''
			),
			'Country' => array('className' => 'Country',
								'foreignKey' => 'country_id',
								'conditions' => '',
								'fields' => '',
								'order' => ''
			)
	);

}
?>