<?php 
/* SVN FILE: $Id: schema.php 6311 2008-01-02 06:33:52Z phpnut $ */
/*App schema generated on: 2008-01-03 13:01:40 : 1199382640*/


class AppSchema extends CakeSchema {

	var $name = 'App';

	function before($event = array()) {
		return true;
	}

	function after($event = array()) {
	}

	var $brands = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'name' => array('type'=>'string', 'null' => false, 'length' => 64),
			'handle' => array('type'=>'string', 'null' => true, 'default' => NULL),
			'image' => array('type'=>'string', 'null' => true, 'default' => NULL),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $categories = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'parent_id' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'handle' => array('type'=>'string', 'null' => false, 'key' => 'unique'),
			'name' => array('type'=>'string', 'null' => false),
			'image' => array('type'=>'string', 'null' => true, 'default' => NULL),
			'active' => array('type'=>'integer', 'null' => false, 'default' => '1', 'length' => 1),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1), 'code_unique' => array('column' => 'handle', 'unique' => 1))
		);

	var $countries = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'key' => 'primary', 'extra' => 'auto_increment'),
			'name' => array('type'=>'string', 'null' => false, 'length' => 64),
			'iso_code_2' => array('type'=>'string', 'null' => false, 'length' => 2, 'key' => 'unique'),
			'iso_code_3' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 3),
			'tax_rate' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'active' => array('type'=>'integer', 'null' => false, 'default' => '0', 'length' => 1),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1), 'code_2_unique' => array('column' => 'iso_code_2', 'unique' => 1))
		);

	var $customer_addresses = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'customer_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'shipping_company' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'shipping_last_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_first_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_phone' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_address_1' => array('type'=>'string', 'null' => false, 'length' => 64),
			'shipping_address_2' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'shipping_city' => array('type'=>'string', 'null' => false, 'length' => 32),
			'zone_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'country_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'shipping_zip' => array('type'=>'string', 'null' => false, 'length' => 32),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $customers = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'email' => array('type'=>'string', 'null' => false),
			'password' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_company' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'billing_last_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_first_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_phone' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_address_1' => array('type'=>'string', 'null' => false, 'length' => 64),
			'billing_address_2' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'billing_city' => array('type'=>'string', 'null' => false, 'length' => 32),
			'zone_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'country_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'billing_zip' => array('type'=>'string', 'null' => false, 'length' => 32),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $customers_orders = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'customer_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'order_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $order_items = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'order_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'product_sku' => array('type'=>'string', 'null' => false, 'length' => 32),
			'quantity' => array('type'=>'integer', 'null' => false),
			'price' => array('type'=>'float', 'null' => false, 'length' => 10),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $order_payments = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'order_id' => array('type'=>'integer', 'null' => false, 'default' => '0000000000', 'length' => 10),
			'reference_number' => array('type'=>'string', 'null' => true, 'default' => NULL),
			'transaction_log' => array('type'=>'text', 'null' => true, 'default' => NULL),
			'amount' => array('type'=>'float', 'null' => false, 'length' => 10),
			'created' => array('type'=>'datetime', 'null' => false),
			'modified' => array('type'=>'datetime', 'null' => false),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $order_shipments = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'order_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'shipping_rate_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'shipping_date' => array('type'=>'date', 'null' => false),
			'reference_number' => array('type'=>'string', 'null' => false, 'length' => 256),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $order_shipments_order_items = array(
			'id' => array('type'=>'integer', 'null' => false, 'length' => 10, 'key' => 'primary'),
			'order_shipment_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'order_item_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $order_status_changes = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'order_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'order_status_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'comment' => array('type'=>'text', 'null' => false),
			'created' => array('type'=>'datetime', 'null' => false),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $order_statuses = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'name' => array('type'=>'string', 'null' => false, 'length' => 64),
			'sort_order' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $orders = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'email' => array('type'=>'string', 'null' => false),
			'billing_company' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'billing_last_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_first_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_phone' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_address_1' => array('type'=>'string', 'null' => false, 'length' => 64),
			'billing_address_2' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'billing_city' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_state' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_country' => array('type'=>'string', 'null' => false, 'length' => 32),
			'billing_zip' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_company' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'shipping_last_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_first_name' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_phone' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_address_1' => array('type'=>'string', 'null' => false, 'length' => 64),
			'shipping_address_2' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'shipping_city' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_state' => array('type'=>'string', 'null' => false, 'length' => 32),
			'shipping_country' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 32),
			'shipping_zip' => array('type'=>'string', 'null' => false, 'length' => 32),
			'subtotal' => array('type'=>'float', 'null' => false, 'length' => 10),
			'zone_tax' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'country_tax' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'shipping' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'shipping_tax' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'total' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'comments' => array('type'=>'text', 'null' => true, 'default' => NULL),
			'order_status_id' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $product_images = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'product_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'image' => array('type'=>'string', 'null' => false),
			'priority' => array('type'=>'integer', 'null' => false),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $product_items = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'product_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'sku' => array('type'=>'string', 'null' => false, 'length' => 32, 'key' => 'unique'),
			'label' => array('type'=>'string', 'null' => false),
			'sell_price' => array('type'=>'float', 'null' => false, 'length' => 10),
			'regular_price' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'weight' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'quantity' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'track_stock' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 1),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1), 'code_key' => array('column' => 'sku', 'unique' => 1))
		);

	var $product_types = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'name' => array('type'=>'string', 'null' => false),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $products = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'name' => array('type'=>'string', 'null' => false),
			'handle' => array('type'=>'string', 'null' => false),
			'description' => array('type'=>'text', 'null' => false),
			'active' => array('type'=>'integer', 'null' => false, 'length' => 1),
			'brand_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'product_type_id' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'tags' => array('type'=>'text', 'null' => false),
			'created' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'modified' => array('type'=>'datetime', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $products_categories = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'product_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'category_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $settings = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'key' => array('type'=>'string', 'null' => false),
			'value' => array('type'=>'text', 'null' => false),
			'description' => array('type'=>'text', 'null' => true, 'default' => NULL),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $shipping_rates = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'country_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'zone_id' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'name' => array('type'=>'string', 'null' => false),
			'start' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'end' => array('type'=>'integer', 'null' => true, 'default' => NULL, 'length' => 10),
			'price' => array('type'=>'float', 'null' => false, 'length' => 10),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $users = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'username' => array('type'=>'string', 'null' => false, 'length' => 250),
			'password' => array('type'=>'string', 'null' => false, 'length' => 32),
			'role' => array('type'=>'string', 'null' => false, 'default' => 'User', 'length' => 50),
			'name' => array('type'=>'string', 'null' => true, 'default' => NULL),
			'email' => array('type'=>'string', 'null' => false, 'length' => 250),
			'created' => array('type'=>'datetime', 'null' => false, 'default' => '0000-00-00 00:00:00'),
			'modified' => array('type'=>'datetime', 'null' => false, 'default' => '0000-00-00 00:00:00'),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1))
		);

	var $zones = array(
			'id' => array('type'=>'integer', 'null' => false, 'default' => NULL, 'length' => 10, 'key' => 'primary', 'extra' => 'auto_increment'),
			'country_id' => array('type'=>'integer', 'null' => false, 'length' => 10),
			'name' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 64),
			'code' => array('type'=>'string', 'null' => true, 'default' => NULL, 'length' => 2, 'key' => 'unique'),
			'tax_rate' => array('type'=>'float', 'null' => true, 'default' => NULL, 'length' => 10),
			'active' => array('type'=>'integer', 'null' => false, 'default' => '1', 'length' => 1),
			'indexes' => array('PRIMARY' => array('column' => 'id', 'unique' => 1), 'code_unique' => array('column' => 'code', 'unique' => 1))
		);

}
?>