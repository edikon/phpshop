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

class Category extends AppModel {

	var $name = 'Category';
	var $actsAs = array('Tree');
  	
	var $validate = array(
		'handle' => VALID_NOT_EMPTY,
		'name' => VALID_NOT_EMPTY,
		'active' => VALID_NOT_EMPTY,
	);

	//The Associations below have been created with all possible keys, those that are not needed can be removed
	var $belongsTo = array(
			'ParentCategory' => array('className' => 'Category',
								'foreignKey' => 'parent_id',
								'conditions' => '',
								'fields' => '',
								'order' => '',
								'counterCache' => ''),
	);

	var $hasAndBelongsToMany = array(
			'Product' => array('className' => 'Product',
						'joinTable' => 'products_categories',
						'foreignKey' => 'category_id',
						'associationForeignKey' => 'product_id',
						'conditions' => '',
						'fields' => '',
						'order' => '',
						'limit' => '',
						'offset' => '',
						'unique' => '',
						'finderQuery' => '',
						'deleteQuery' => '',
						'insertQuery' => ''),
	);


	
	
	function getPaths( & $categories = null ) {

			$i = 0;

			foreach ( $categories as $category ) {

				$pathTemp 	= '';
				$paths 		= array();

				$paths = $this->getpath( $category['Category']['id'], 'name' );

				foreach ( $paths as $path ) {

					$pathTemp .= $path['Category']['name'] . '/';

				}

				$categories[$i]['Category']['path'] = $pathTemp;

				$i++;

			}

		}
	
}
?>
