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

class Country extends AppModel {

	var $name = 'Country';
	var $validate = array(
		'name' => VALID_NOT_EMPTY,
		'iso_code_2' => VALID_NOT_EMPTY,
    					array( 
         						'rule' => array('maxLength', 2) 
     						),
		'iso_code_3' => VALID_NOT_EMPTY,
					    array( 
					         	'rule' => array('maxLength', 3) 
					     	),
		'active' => VALID_NOT_EMPTY,
	);

	//The Associations below have been created with all possible keys, those that are not needed can be removed
	var $hasMany = array(
			'ShippingRate' => array('className' => 'ShippingRate',
								'foreignKey' => 'country_id',
								'conditions' => '',
								'fields' => '',
								'order' => '',
								'limit' => '',
								'offset' => '',
								'dependent' => true,
								'exclusive' => '',
								'finderQuery' => '',
								'counterQuery' => ''),
			'Zone' => array('className' => 'Zone',
								'foreignKey' => 'country_id',
								'conditions' => '',
								'fields' => '',
								'order' => '',
								'limit' => '',
								'offset' => '',
								'dependent' => true,
								'exclusive' => '',
								'finderQuery' => '',
								'counterQuery' => ''),
	);

}
?>