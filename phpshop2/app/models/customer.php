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

class Customer extends AppModel {

	var $name = 'Customer';
	var $useTable = 'customers';
	
	var $displayField = 'email';
	
	var $validate = array(
		'email' => array(
        	'rule' => array('email', false),
        	'message' => 'Please supply a valid email address.'
    	), 
		'password' => array(
			'rule' => 'alphaNumeric',
            'required' => true
    	), 
		'billing_last_name' => VALID_NOT_EMPTY,
		'billing_first_name' => VALID_NOT_EMPTY,
		'billing_phone' => VALID_NOT_EMPTY,
		'billing_address_1' => VALID_NOT_EMPTY,
		'billing_city' => VALID_NOT_EMPTY,
		'billing_zip' => VALID_NOT_EMPTY,
	);

	//The Associations below have been created with all possible keys, those that are not needed can be removed
	var $belongsTo = array(
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

	var $hasMany = array(
			'CustomerAddress' => array('className' => 'CustomerAddress',
								'foreignKey' => 'customer_id',
								'dependent' => true,
								'conditions' => '',
								'fields' => '',
								'order' => '',
								'limit' => '',
								'offset' => '',
								'exclusive' => '',
								'finderQuery' => '',
								'counterQuery' => ''
			),
			'Order' => array('className' => 'Order',
								'foreignKey' => 'customer_id',
								'dependent' => false,
								'conditions' => '',
								'fields' => '',
								'order' => '',
								'limit' => '',
								'offset' => '',
								'exclusive' => '',
								'finderQuery' => '',
								'counterQuery' => ''
			)
	);

}
?>