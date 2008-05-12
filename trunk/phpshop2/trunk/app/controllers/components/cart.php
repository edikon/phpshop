<?php 
/* SVN FILE: $Id: cart.php 416 2008-01-30 20:32:22Z pablo $ */
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


class CartComponent extends Object {

	/**
 	* Place holder for the controller
 	*
 	* @var boolean
 	* @access private
 	*/
    var $controller = true;
    
	/**
 	* Place holder for the sanitize object
 	*
 	* @var boolean
 	* @access private
 	*/
    var $sanitize = true;
    
    var $components = array('Session');
    
    /**
     * Make sure that we can access parent controller models, etc.
     *
     * @param unknown_type $controller
     */
	function startup(&$controller) { 
        $this->Controller =& $controller; 
    } 
    
	/**
	* Checks to see if an item exists in the shopping cart and if so returns the quantity remaining
 	*
 	* @param integer
 	*/
	function check_item($product_item_id) {
	
		$products = $this->Session->read('Cart'); 
		if (isset($products[$product_item_id])) {
			return $products[$product_item_id];
		}
		else {
			return 0;
		}
	}

	/**
	* Adds the provided quantity of the desired product to the shopping cart.
 	*
 	* @param integer
 	* @param integer
	*/
	function add_item($product_item_id, $quantity) {
	
		$products = $this->Session->read('Cart'); 
		$products[$product_item_id] = round($quantity);
		$this->Session->write('Cart', $products);		
	}

	/**
	* Deletes the given item from the shopping cart completely
 	*
 	* @param integer
	*/
	function delete_item($product_item_id) {
		$products = $this->Session->read('Cart'); 
		unset($products[$product_item_id]);
		$this->Session->write('Cart', $products);		
	}

	/**
	* Modifies the total quantity of a given item in the shopping cart. If a quantity of zero 
	* is passed to this function it automatically deletes the item completely.
 	*
 	* @param integer
 	* @param integer
	*/
	function modify_quantity($product_item_id, $quantity) {
	
		$products = $this->Session->read('Cart'); 
		if ($quantity == 0) {
			unset($products[$product_item_id]);
		}
		else {
			$products[$product_item_id] = round($quantity);
		}
		$this->Session->write('Cart', $products);		
	}

	/**
	* Deletes the entire contents of the shopping cart
 	*
	*/
	function clear_cart() {
	
		$this->Session->del('Cart'); 	
	}

	/** 
	* Calculates the total value of the contents of the shopping cart based on the 
	* inventory price specified.
 	*
	*/
	function cart_total() {
	
		$products = $this->Session->read('Cart');
		$total=0;
		if (isset($products)) {
			foreach ($products as $product_item_id => $quantity) {
				$item = $this->Controller->ProductItem->find("ProductItem.id='$product_item_id'");
				$total += $item['ProductItem']['sell_price'] * $quantity;
			}
		}
		return $total;
	}

	/** 
	* Calculates the total weight of the contents of the shopping cart
 	*
	*/
	function cart_weight() {
	
		$products = $this->Session->read('Cart');
		$total=0;
		if (isset($products)) {
			foreach ($products as $product_item_id => $quantity) {
				$item = $this->Controller->ProductItem->find("ProductItem.id='$product_item_id'");
				$total += $item['ProductItem']['weight'] * $quantity;
			}
		}
		return $total;
	}
	
	/**
	* Returns an array containing the details of the entire shopping cart contents.
 	*
	*/
	function get_contents() {
			
		$items = $this->Session->read('Cart'); 

		if (count($items) > 0) {
			foreach ($items as $item_id => $quantity) {
				$item = $this->Controller->ProductItem->find("ProductItem.id='$item_id'");
				$products[] = array('quantity' => $quantity,
								'item' => $item
							 );
			}
			return $products;
		}
		else {
			return null;
		}
	}
	
	/**
	* Returns the total number of unique items in the shopping cart
 	*
	*/
	function num_items() {
	
		$products = $this->Session->read('Cart'); 
		return count($products);
	}

	/** 
	* Returns the total number of items in the shopping cart based on the quantity of 
	* each item rather than the number of unique items
 	*
	*/
	function quant_items() {
	
		$total=0;
		$products = $this->Session->read('Cart'); 
		foreach ($products as $product=>$quantity) {
			$total += $quantity;
		}
		return $total;
	}

}
?>