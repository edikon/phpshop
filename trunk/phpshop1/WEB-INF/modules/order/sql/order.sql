CREATE TABLE order_item (
  order_item_id int(11) DEFAULT '0' NOT NULL auto_increment,
  order_id int(11),
  user_info_id int(11),
  vendor_id int(11),
  product_id int(11),
  product_quantity int(11),
  product_item_price decimal(10,2),
  order_item_currency varchar(16),
  order_status char(1),
  cdate int(11),
  mdate int(11),
  PRIMARY KEY (order_item_id)
);


#
# Table structure for table 'orders'
#
CREATE TABLE orders (
  order_id int(11) DEFAULT '0' NOT NULL auto_increment,
  user_id varchar(32) DEFAULT '' NOT NULL,
  vendor_id int(11) DEFAULT '0' NOT NULL,
  order_number varchar(32),
  user_info_id int(11),
  order_subtotal decimal(10,2),
  order_tax decimal(10,2),
  order_shipping decimal(10,2),
  order_shipping_tax decimal(10,2),
  order_currency varchar(16),
  order_status char(1),
  cdate int(11),
  mdate int(11),
  ship_method_id int(11),
  PRIMARY KEY (order_id)
);


#
# Table structure for table 'payment_method'
#
CREATE TABLE payment_method (
  order_id int(11) DEFAULT '0' NOT NULL,
  payment_method_type varchar(8),
  payment_method_number varchar(128),
  payment_method_expire int(11),
  payment_method_name varchar(128)
);

