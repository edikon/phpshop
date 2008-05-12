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

class OrderItem extends AppModel {

	var $name = 'OrderItem';
	var $useTable = 'order_items';

	//The Associations below have been created with all possible keys, those that are not needed can be removed
	var $belongsTo = array(
		'Order' => array('className' => 'Order',
							'foreignKey' => 'order_id',
							'conditions' => '',
							'fields' => '',
							'order' => ''
		),
		'ProductItem' => array('className' => 'ProductItem',
							'foreignKey' => 'product_item_id',
							'conditions' => '',
							'fields' => '',
							'order' => ''
		)
	);

	var $hasAndBelongsToMany = array(
			'OrderShipment' => array('className' => 'OrderShipment',
						'joinTable' => 'order_shipments_order_items',
						'foreignKey' => 'order_item_id',
						'associationForeignKey' => 'order_shipment_id',
						'unique' => true,
						'conditions' => '',
						'fields' => '',
						'order' => '',
						'limit' => '',
						'offset' => '',
						'finderQuery' => '',
						'deleteQuery' => '',
						'insertQuery' => ''
			)
	);

}
?>