<?php
/**
 * PaymentController for phpShop
 *
 * @copyright Edikon Corporation, http://www.edikon.com
 * @license http://opensource.org/licenses/gpl-license.php GNU General Public License V2
 * @package phpShop
 * @version $Id$
 *
 * This plugin must be included in PAYMENT_PROCESSORS
 * 
 * This plugins depends on the following global settings:
 * 
 * PAYMENT_PAYPAL_EMAIL: Should specify the email address of your PayPal account.
 * 
 */
class PaypalController extends PaypalAppController
{
  	var $helpers = array('Html', 'Form');

  	var $uses = array();
  	

	/**
	 * Returns information about this payment processor.
	 * This is meant to be shown to the user on the payment screen, so that they can select this payment method.
	 *
	 */
	 function info() {
	 	
	 }

	/**
	 * Called by the checkout routine for payment processing.
	 * 
	 *
	 */
	function index() {
		// get order information from session
		$order = $this->Session->read('Order');
	
		loadModel('ProductItem');
		$productItem =& new ProductItem();
		
		$i = 1;
		foreach ($order['OrderItems'] as $item_id=>$quantity) {
			$item = $productItem->findById($item_id);
			$items['item_name_'. $i] = $item['Product']['name'];
			$items['item_number_'. $i] = $item['ProductItem']['sku'];
			$items['amount_' . $i++] = $item['ProductItem']['sell_price'];
		}
		
		// prepare order for sending to PayPal
		$this->set('order', $order);
		$this->set('items', $items);
	}
	
	/**
	 * Method called by the PayPal IPN return function.
	 * 
	 * This method should update the order status so that we know it's been paid.
	 * 
	 * You must set your PayPal settings to use IPN
	 * The URL should be your URL/paypal/payment/ipn
	 *
	 * @param unknown_type $result
	 */
	function ipn($result=null) {
		
	}
	

}
