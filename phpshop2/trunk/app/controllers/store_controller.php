<?php
/* SVN FILE: $Id: store_controller.php 423 2008-05-12 22:28:15Z pablo $ */
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

class StoreController extends AppController {

/**
 * Enter description here...
 *
 * @var unknown_type
 */
	 var $name = 'Store';

/**
 * Enter description here...
 *
 * @var unknown_type
 */
	var $helpers = array('Html', 'Form', 'Javascript', 'Ajax', 'Tree', 'Currency');

	var $layout = 'store';

	var $components = array('Cart', 'Tax', 'RequestHandler');
	
/**
 * This controller uses several models
 *
 * @var $uses
 */
	var $uses = array('Category', 
					  'Product', 
					  'ProductItem', 
					  'Order',
					  'OrderItem',
					  'OrderStatus',
					  'Country',
					  'Zone',
					  'ShippingRate',
					  'Customer',
					  'CustomerAddress'
					  );
	
	/**
	* Index
	*
	*/
	function index($category_handle=null) {
		
		$this->redirect(array('action' => 'browse', 'home'));
	}
	
	/**
	* Browse method handles the browsing of categories
	*
	*/
	function browse($category_handle=null) {
						
		if (isset($category_handle)) {	
			
			// get/set category
			$this->Category->recursive = 2;
			$category = $this->Category->findByHandle($category_handle);
			$this->set(compact('category', $category));
			
			// set page title
			$this->pageTitle = Configure::read('Store.name') .  ' - ' . $category['Category']['name'];
			
			if (isset($this->params['requested'])) {
				$this->render();
			}
		}
		else {
			$this->redirect("/");
		}
	
		
	}
	
	/** 
	* Flypage is the method that shows a product to the viewer.
	*
	*/
	function flypage($product_handle) {
				
		// get product info
		$this->Product->recursive = 2;
		$product = $this->Product->find("Product.handle='$product_handle' AND Product.active='1'");
		$this->set(compact('product', $product));

		// set page title
		$this->pageTitle = Configure::read('Store.name') .  ' - ' . $product['Product']['name'];

	}
	
	/**
	* Cart method handles all shopping cart functions
	* Parameters should contain three things, action, product_item_id, and quantity
	*
	*/
	function cart() {
	
		$url = $this->params['url'];
		
		if (isset($url['action'])) {
			switch ($url['action']) {
				case 'add':
					$this->Cart->add_item($url['product_item_id'], 1);
					break;
				case 'update':
					foreach($url['quantity'] as $item_id=>$quantity) {
						$this->Cart->modify_quantity($item_id, $quantity);
					}
					break;
				case 'delete':
					$this->Cart->delete_item($url['product_item_id'], 1);
					break;
				default:
					break;
			}
		}
		
		$this->set('products', $this->Cart->get_contents());		
		$this->set('cart_total', $this->Cart->cart_total());

		// turn off minicart
		$this->set('mini_cart', true);
		
		// set page title
		$this->pageTitle = Configure::read('Store.name') .  ' - ' . __('Shopping Cart', true);
	}
			
	/**
	* Ajax update of state select box
	*
	*/
	function update_select_state() {
		if (!empty($this->data['Customer']['billing_country_id']) || !empty($this->data['Customer']['shipping_country_id'])) {
			$country_id = $this->data['Customer']['billing_country_id'] ? 
						  $this->data['Customer']['billing_country_id'] : 
						  $this->data['Customer']['shipping_country_id'];
			$options = $this->Zone->find("list", array("country_id='$country_id'"));
			$this->set('options', $options);
		}		
	}
	
	/**
	* RequestActionable mini_cart action
	*
	*/
	function mini_cart() {
		
		$cart = array();
		$cart['cart_total'] = $this->Cart->cart_total();
		$cart['num_items'] = $this->Cart->num_items();
		
		$this->set('cart', $cart);
	
		if(isset($this->params['requested'])) { 
			return $cart; 
		} 	
	}
	
	/**
	 * Returns threaded list of categories for navigation menu
	 *
	 * @return unknown
	 */
	function category_menu() {
		
 		$categories = $this->Category->find('all',  
		     array('fields' => array('name', 'handle', 'lft', 'rght'), 'order' => 'lft ASC', 'conditions' => 'Category.active=1'));   	

		if(isset($this->params['requested'])) { 
			return $categories; 
		}
		$this->set('categories', $categories); 	
  	} 


	/**
	* Gather customer information and create customer record.
	*/
  	function register() {
	
		// set page title
		$this->pageTitle = Configure::read('Store.name') .  ' - ' . __('Register', true);

  		if (!$this->Session->read('Cart')) {
			$this->Session->setFlash('Your shopping cart has expired.');
			$this->redirect(array('action'=>'index'), null, true);
		} 
  		
		// get customer information
		$registration = $this->Session->read('Registration');
		
		// build drop down lists		
		$this->set('countries', $this->Country->find("list"));
		$this->set('states', $this->Zone->find("list"));
		$this->set('cart_items', $this->Cart->get_contents());		
		$this->set('cart_total', $this->Cart->cart_total());
	
  		// save order
		if (!empty($this->data)) {
			
			$customer = $this->data;	

			// set email and password from previos page.
			$customer['Customer']['email']= $registration['Customer']['email'];
			$customer['Customer']['password']= $registration['Customer']['password'];
			
			// need to resolve text versions of country and state
			$state = $this->Zone->read(null, $customer['Customer']['billing_state_id']);
			$customer['Customer']['zone_id'] = $customer['Customer']['billing_state_id'];
			$customer['Customer']['country_id'] = $customer['Customer']['billing_country_id'];
						
			// If shipping is the same as billing, let's copy it.
			if ($customer['Customer']['copy']) {
				$customer['CustomerShipping']['shipping_company'] = $customer['Customer']['billing_company'];
				$customer['CustomerShipping']['shipping_last_name'] = $customer['Customer']['billing_last_name'];
				$customer['CustomerShipping']['shipping_first_name'] = $customer['Customer']['billing_first_name'];
				$customer['CustomerShipping']['shipping_phone'] = $customer['Customer']['billing_phone'];
				$customer['CustomerShipping']['shipping_address_1'] = $customer['Customer']['billing_address_1'];
				$customer['CustomerShipping']['shipping_address_2'] = $customer['Customer']['billing_address_2'];
				$customer['CustomerShipping']['shipping_city'] = $customer['Customer']['billing_city'];
				$customer['CustomerShipping']['zone_id'] = $customer['Customer']['billing_state_id'];
				$customer['CustomerShipping']['country_id'] = $customer['Customer']['billing_country_id'];
				$customer['CustomerShipping']['shipping_zip'] = $customer['Customer']['billing_zip'];
			}
			else {
				$customer['CustomerShipping']['shipping_company'] = $customer['Customer']['shipping_company'];
				$customer['CustomerShipping']['shipping_last_name'] = $customer['Customer']['shipping_last_name'];
				$customer['CustomerShipping']['shipping_first_name'] = $customer['Customer']['shipping_first_name'];
				$customer['CustomerShipping']['shipping_phone'] = $customer['Customer']['shipping_phone'];
				$customer['CustomerShipping']['shipping_address_1'] = $customer['Customer']['shipping_address_1'];
				$customer['CustomerShipping']['shipping_address_2'] = $customer['Customer']['shipping_address_2'];
				$customer['CustomerShipping']['shipping_city'] = $customer['Customer']['shipping_city'];
				$customer['CustomerShipping']['country_id'] = $customer['Customer']['shipping_country_id'];
				$customer['CustomerShipping']['zone_id'] = $customer['Customer']['billing_state_id'];
				$customer['CustomerShipping']['shipping_zip'] = $customer['Customer']['shipping_zip'];
			}
			
			// validate order data
			if ($this->Customer->save($customer['Customer'])) {
				
				$customer_id = $this->Customer->id;
				$customer['CustomerShipping']['customer_id'] = $customer_id;
				if ($this->CustomerAddress->save($customer['CustomerShipping'])) {
					
					// Record saved, redirect to payment page.
					$customer = $this->Customer->read(null, $customer_id);

					$this->Session->write('Customer', $customer);
					$this->redirect(array('controller'=>'checkout', 'action'=>'index'), null, true);						
					
				}
				else {
					$this->Session->setFlash(__('There were errors processing your data. Please see below.', true));		
				}
			}
			else {
				$this->Session->setFlash(__('There were errors processing your data. Please see below.', true));
			}
		}
		
	}	

	/**
	* login function
	* 
	*/
	function login() {			
		
		//Don't show the error message if no data has been submitted.
		$this->set('error', false);
				
        // If a user has submitted form data:
        if (!empty($this->data))
        {
			// check if this is a login attempt.
			if (!empty($this->data['Customer']['login'])) {
				
           		// First, let's see if there are any users in the database
            	// with the username supplied by the user using the form:

            	$someone = $this->Customer->findByEmail($this->data['Customer']['login_email']);

            	// At this point, $someone is full of user data, or its empty.
            	// Let's compare the form-submitted password with the one in
            	// the database.

            	if(!empty($someone['Customer']['password']) && 
						$someone['Customer']['password'] == $this->data['Customer']['login_password']) {

						// We do not want to store password in the session. 
						unset($someone['Customer']['login_password']);
                		$this->Session->write('Customer', $someone);

						// login valid
						if ($this->Session->check('Cart')) {
                			$this->redirect(array('controller'=>'checkout', 'action' => 'index'));
						}
						else {
                			$this->redirect(array('controller'=>'account','action' => 'index'));
						}

            	}
            	// Else, they supplied incorrect data:
            	else {
                	$this->set('error', true);
            	}
			}
			else {
				// not a login attempt, redirect to registration
				$registration = $this->data;
				$this->Session->write('Registration', $registration);
				$this->redirect('register');
			}
		}
    }

	/**
	* logout 
	*
	*/
    function logout() {
	
        // Redirect users to this action if they click on a Logout button.
        // All we need to do here is trash the session information:

        $this->Session->delete('Customer');
        $this->Session->delete('Cart');
        $this->Session->delete('Order');

        $this->Session->setFlash('You\'ve successfully logged out.'); 

        // And we should probably forward them somewhere, too...
     
        $this->redirect('/');
    }


}
?>
