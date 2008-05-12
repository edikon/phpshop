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

class Order extends AppModel {

	var $name = 'Order';
	var $useTable = 'orders';
	var $validate = array(
		'email' => array('rule' => array('email', false), 
						 'message' => 'Please supply a valid email address.',
						), 
		'password' => array(VALID_NOT_EMPTY),
		'billing_last_name' => array(VALID_NOT_EMPTY),
		'billing_first_name' => array(VALID_NOT_EMPTY),
		'billing_phone' => array(VALID_NOT_EMPTY),
		'billing_address_1' => array(VALID_NOT_EMPTY),
		'billing_city' => array(VALID_NOT_EMPTY),
		'billing_state' => array(VALID_NOT_EMPTY),
		'billing_country' => array(VALID_NOT_EMPTY),
		'billing_zip' => array(VALID_NOT_EMPTY),

		'shipping_last_name' => array(VALID_NOT_EMPTY),
		'shipping_first_name' => array(VALID_NOT_EMPTY),
		'shipping_phone' => array(VALID_NOT_EMPTY),
		'shipping_address_1' => array(VALID_NOT_EMPTY),
		'shipping_city' => array(VALID_NOT_EMPTY),
		'shipping_state' => array(VALID_NOT_EMPTY),
		'shipping_country' => array(VALID_NOT_EMPTY),
		'shipping_zip' => array(VALID_NOT_EMPTY),
	);
	

	//The Associations below have been created with all possible keys, those that are not needed can be removed
	var $belongsTo = array(
			'OrderStatus' => array('className' => 'OrderStatus',
								'foreignKey' => 'order_status_id',
								'conditions' => '',
								'fields' => '',
								'order' => ''
			),
			'Customer' => array('className' => 'Customer',
								'foreignKey' => 'customer_id',
								'conditions' => '',
								'fields' => '',
								'order' => ''
			)
	);

	var $hasMany = array(
			'OrderItem' => array('className' => 'OrderItem',
								'foreignKey' => 'order_id',
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
			'OrderShipment' => array('className' => 'OrderShipment',
								'foreignKey' => 'order_id',
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
			'OrderPayment' => array('className' => 'OrderPayment',
								'foreignKey' => 'order_id',
								'dependent' => true,
								'conditions' => '',
								'fields' => '',
								'order' => ''
			),
	);

}
?>