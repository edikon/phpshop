<?php
/* SVN FILE: $Id: store_controller.php 416 2008-01-30 20:32:22Z pablo $ */
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

class CheckoutController extends AppController {

	 var $name = 'Checkout';

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
	* Make sure customer is logged in.
	*
	*/
	function beforeFilter() {
		
		// make sure to run parent beforeFilter() method
		AppController::beforeFilter();
		
		$this->checkSession();
	}	
	
	/**
	* Primary purpose of this page is to provide user with option to login or register.
	* If the user logs in, it is handled here, otherwise see register() method.
	*/
  	function index() {
				
		// set page title
		$this->pageTitle = Configure::read('Store.name') .  ' - ' . __('Checkout', true);
				
  		// get cart info
		$this->set('cart_items', $this->Cart->get_contents());		
		$this->set('cart_total', $this->Cart->cart_total());

		// get customer info
		$customer = $this->Session->read('Customer');
		
		// turn off minicart
		$this->set('mini_cart', true);
		
		// TAXES	
		$zone_tax = $this->Tax->zone_tax_total($customer['CustomerAddress'][0]['zone_id'], $this->Cart->cart_total());
		$country_tax = $this->Tax->country_tax_total($customer['CustomerAddress'][0]['country_id'], $this->Cart->cart_total());

		// calculate taxes and total
		$cart_total = $this->Cart->cart_total();
		$order_total = $cart_total + $country_tax + $zone_tax;
		
		// assign selected shipping address
		$customer_address_offset = 0;
		$customer['CustomerShipping'] = $this->CustomerAddress->read(null, $customer['CustomerAddress'][$customer_address_offset]['id']);
		
		// assign totals
		$this->set('country_tax', $country_tax);
		$this->set('zone_tax', $zone_tax);
		$this->set('order_total', $order_total);
		$this->set('customer', $customer);
			
		// get shipping rates
		$this->set('shipping_rates', $this->shipping_rates());

		$this->Session->write('Customer', $customer);
	
  		// save order
		if (!empty($this->data)) {
						
			// assign billing info to order
			$order['Order'] = $customer['Customer'];

			// set order status based on sort order
			$order_statuses = $this->OrderStatus->find('all', array(), 'sort_order');	
			$order['Order']['order_status_id'] = $order_statuses[0]['OrderStatus']['id'];
														
			// assign shipping info to order
			foreach ($customer['CustomerShipping']['CustomerAddress'] as $key => $value) {
				$order['Order'][$key] = $value;
			}
			// need to unset order_id
			unset($order['Order']['id']);
			
			// billing 
			$zone = $this->Zone->findById($customer['Customer']['zone_id']);
			$order['Order']['billing_state'] = $zone['Zone']['code'];
			$order['Order']['billing_country'] = $zone['Country']['iso_code_2'];
			
			// shipping
			$zone = $this->Zone->findById($customer['CustomerShipping']['CustomerAddress']['zone_id']);
			$order['Order']['shipping_state'] = $zone['Zone']['code'];
			$order['Order']['shipping_country'] = $zone['Country']['iso_code_2'];
						
			// save tax info to Order session
			$order['Order']['subtotal'] = $cart_total;
			
			// save shipping information to Order session
			$shipping = $this->ShippingRate->findById($this->data['Payment']['shipping_rate']);
			$shipping_total = $shipping['ShippingRate']['price'];

			$order['Order']['shipping'] = $shipping_total;
			$order['Order']['zone_tax'] = $zone_tax;
			$order['Order']['country_tax'] = $country_tax;

			$order['Order']['total'] = $cart_total + $zone_tax + $country_tax + $shipping_total;
						
			unset($order['Order']['modified']);
			unset($order['Order']['created']);
			$this->Session->write('Order', $order);

			// HOOK for payment processor plugin redirect
			$this->redirect(array('action'=>'confirm'), null, true);		
		}
				
		
	}

	
	/**
	* Confirm method, part 3 of the checkout process.  User confirms data provided.
	* 
	* If user will be redirected to a payment processor, it will happen here.
	*
	*/
  	function confirm() {
				
		// if the cart is empty, redirect to home
		if (!$this->Cart->num_items()) {
			$this->redirect('/');
		}

  		// get cart info
		$this->set('cart_items', $this->Cart->get_contents());		
		$this->set('cart_total', $this->Cart->cart_total());

		// get order info
		$order = $this->Session->read('Order');
								
		// assign totals
		$this->set('shipping', $order['Order']['shipping']);
		$this->set('country_tax', $order['Order']['country_tax']);
		$this->set('zone_tax', $order['Order']['zone_tax']);
		$this->set('order_total', $order['Order']['total']);
		$this->set('order', $order);

		// turn off minicart
		$this->set('mini_cart', true);
					
  		// save order
		if (!empty($this->data)) {
																		
			// HOOK for payment processor plugin redirect
			//$this->redirect('/paypal');
													
			// save the order_item data
			$this->cleanUpFields();
			$this->Order->create();
			if ($this->Order->save($order['Order'])) {
				
				// get order_id so we can now add order_items
				$order_id = $this->Order->id;

				$order['Order']['id'] = $order_id;
				$this->Session->write('Order', $order);
								
				// Order Item
				$cart = $this->Cart->get_contents();
				foreach ($cart as $line) { 

					// create each order item
					$order_item = array();
					$order_item['OrderItem']['order_id'] = $order_id; 
					$order_item['OrderItem']['product_item_id'] = $line['item']['ProductItem']['id']; 
					$order_item['OrderItem']['quantity'] = $line['quantity']; 
					$order_item['OrderItem']['price'] = $line['item']['ProductItem']['sell_price']; 

					$this->OrderItem->create();
					if (!$this->OrderItem->save($order_item)) {				
						$this->Session->setFlash(__('There was an error saving your order. Please, try again.', true));
					}
				}
				
				//$this->Session->setFlash('The Order has been processed successfully.');
				$this->redirect(array('action'=>'thankyou'), null, true);
			} else {
				$this->Session->setFlash('The Order could not be saved. Please, try again.');
			}
		}
				
		
	}

	/**
	* Thank you method.  Simply says thank you and shows order receipt.
	* 
	*
	*/
  	function thankyou() {
		
		// if the cart is empty, redirect to home
		if (!$this->Cart->num_items()) {
			$this->redirect('/');
		}		
		
  		// get cart info
		$this->set('cart_items', $this->Cart->get_contents());		
		$this->set('cart_total', $this->Cart->cart_total());

		// get order info
		$order = $this->Session->read('Order');
				
		// assign totals
		$this->set('shipping', $order['Order']['shipping']);
		$this->set('country_tax', $order['Order']['country_tax']);
		$this->set('zone_tax', $order['Order']['zone_tax']);
		$this->set('order_total', $order['Order']['total']);
		$this->set('order', $order);
		
		// turn off minicart
		$this->set('mini_cart', true);

		// let's get rid of session info
		$this->Session->delete('Cart');
		$this->Session->delete('Order');
									
	}


	/**
	* Shipping calculator.  Returns a list of shipping rates that are within the given range and zone/country.
	* First checks if the customer's shipping zone is defined with a rate, otherwise, check the country's shipping.
	* The basis for the range can be based on one of the following three options:  order_weight, order_total, order_quantity
	* default: order_weight
	*/
	function shipping_rates() {
		
		// get customer info
		$customer = $this->Session->read('Customer');

		// calculate shipping.
		
		switch (Configure::read('Shipping.method')) {
		
			case 'order_weight':
				$basis = $this->Cart->cart_weight();
				break;
			case 'order_quantity':
				$basis = $this->Cart->num_items();
				break;
			case 'order_total':
				$basis = $this->Cart->cart_total();
				break;
			default:
				$basis = $this->Cart->cart_weight();
				break;	
		}
		
		// lookup shipping rates for given weight
		$conditions = array('ShippingRate.start' => "< $basis", 
							'ShippingRate.end' => ">= $basis", 
							'ShippingRate.country_id' => $customer['CustomerAddress'][0]['country_id']
							);
		$shipping_rates = $this->ShippingRate->find('all', array('conditions' => $conditions, 
													'sort' => 'ShippingRate.price ASC'));
		
		//build select list
		$rates=array();
		foreach ($shipping_rates as $shipping_rate) {
			$rates[$shipping_rate['ShippingRate']['id']] = $shipping_rate['ShippingRate']['name'] 
												. " - " . $shipping_rate['ShippingRate']['price'];
		}
		return $rates;

	}
}
?>
