-- phpMyAdmin SQL Dump
-- version 2.11.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 31, 2008 at 10:16 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `phpshop2`
--

-- --------------------------------------------------------

--
-- Table structure for table `ps_brands`
--

CREATE TABLE IF NOT EXISTS `ps_brands` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(64) NOT NULL,
  `handle` varchar(255) default NULL,
  `image` varchar(255) default NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `ps_brands`
--

INSERT INTO `ps_brands` (`id`, `name`, `handle`, `image`, `created`, `modified`) VALUES
(3, 'ACME', 'acme', '', NULL, '2007-07-26 20:08:14');

-- --------------------------------------------------------

--
-- Table structure for table `ps_categories`
--

CREATE TABLE IF NOT EXISTS `ps_categories` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `parent_id` int(10) unsigned default NULL,
  `handle` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` text,
  `image` varchar(255) default NULL,
  `active` int(1) NOT NULL default '1',
  `lft` int(10) default NULL,
  `rght` int(10) default NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `code_unique` (`handle`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1000000014 ;

--
-- Dumping data for table `ps_categories`
--

INSERT INTO `ps_categories` (`id`, `parent_id`, `handle`, `name`, `description`, `image`, `active`, `lft`, `rght`, `created`, `modified`) VALUES
(7, 5, 'handtools', 'Hand Tools', NULL, '', 1, 6, 7, '2007-06-08 00:22:18', '2008-01-24 12:43:30'),
(2, 5, 'powertools', 'Power Tools', NULL, '', 1, 4, 5, '2007-06-08 00:22:18', '2008-01-24 12:43:21'),
(3, 4, 'gardentools', 'Garden Tools', NULL, '', 1, 10, 11, '2007-06-08 00:22:19', '2008-01-24 14:39:56'),
(4, 1, 'outdoortools', 'Outdoor Tools', NULL, '', 1, 9, 12, '2007-06-08 00:22:19', '2008-01-24 12:42:52'),
(5, 1, 'indoortools', 'Indoor Tools', NULL, '', 1, 3, 8, '2007-06-08 00:22:19', '2008-01-24 12:42:38'),
(6, 1, 'specials', 'Specials', '', '', 1, 13, 14, '2007-07-27 14:49:34', '2008-01-31 08:43:25'),
(1, NULL, 'home', 'Home', 'Welcome to Washupito''s Tiendita. \r\n\r\nWe carry the products that you need! We are proud to bring you the best line of tools and equipment for your use and enjoyment. If you need any assistance with your purchase, please do not hesitate to contact us.', '', 0, 2, 15, '2008-01-24 12:42:12', '2008-01-27 20:03:23');

-- --------------------------------------------------------

--
-- Table structure for table `ps_countries`
--

CREATE TABLE IF NOT EXISTS `ps_countries` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(64) NOT NULL,
  `iso_code_2` char(2) NOT NULL,
  `iso_code_3` varchar(3) default NULL,
  `tax_rate` decimal(10,4) default NULL,
  `active` int(1) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `code_2_unique` (`iso_code_2`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=242 ;

--
-- Dumping data for table `ps_countries`
--

INSERT INTO `ps_countries` (`id`, `name`, `iso_code_2`, `iso_code_3`, `tax_rate`, `active`) VALUES
(1, 'United States', 'US', 'USA', 0.0000, 1);

-- --------------------------------------------------------

--
-- Table structure for table `ps_customers`
--

CREATE TABLE IF NOT EXISTS `ps_customers` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `email` varchar(255) NOT NULL,
  `password` varchar(32) NOT NULL,
  `billing_company` varchar(64) default NULL,
  `billing_last_name` varchar(32) NOT NULL,
  `billing_first_name` varchar(32) NOT NULL,
  `billing_phone` varchar(32) NOT NULL,
  `billing_address_1` varchar(64) NOT NULL,
  `billing_address_2` varchar(64) default NULL,
  `billing_city` varchar(32) NOT NULL,
  `zone_id` int(10) NOT NULL,
  `country_id` int(10) NOT NULL,
  `billing_zip` varchar(32) NOT NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `ps_customers`
--

INSERT INTO `ps_customers` (`id`, `email`, `password`, `billing_company`, `billing_last_name`, `billing_first_name`, `billing_phone`, `billing_address_1`, `billing_address_2`, `billing_city`, `zone_id`, `country_id`, `billing_zip`, `created`, `modified`) VALUES
(1, 'demo@phpshop.org', 'password', NULL, 'Customer', 'Demo', '555-555-1212', 'Address 1', NULL, 'City', 132, 1, '00000', NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `ps_customer_addresses`
--

CREATE TABLE IF NOT EXISTS `ps_customer_addresses` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `customer_id` int(10) NOT NULL,
  `shipping_company` varchar(64) default NULL,
  `shipping_last_name` varchar(32) NOT NULL,
  `shipping_first_name` varchar(32) NOT NULL,
  `shipping_phone` varchar(32) NOT NULL,
  `shipping_address_1` varchar(64) NOT NULL,
  `shipping_address_2` varchar(64) default NULL,
  `shipping_city` varchar(32) NOT NULL,
  `zone_id` int(10) NOT NULL,
  `country_id` int(10) NOT NULL,
  `shipping_zip` varchar(32) NOT NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `ps_customer_addresses`
--

INSERT INTO `ps_customer_addresses` (`id`, `customer_id`, `shipping_company`, `shipping_last_name`, `shipping_first_name`, `shipping_phone`, `shipping_address_1`, `shipping_address_2`, `shipping_city`, `zone_id`, `country_id`, `shipping_zip`, `created`, `modified`) VALUES
(1, 1, 'Home', 'Customer', 'Demo', '555-555-1212', 'Shipping Address 1', '', 'City', 132, 1, '00000', NULL, '2008-01-25 10:13:22');

-- --------------------------------------------------------

--
-- Table structure for table `ps_orders`
--

CREATE TABLE IF NOT EXISTS `ps_orders` (
  `id` int(10) unsigned zerofill NOT NULL auto_increment,
  `customer_id` int(10) NOT NULL,
  `email` varchar(255) NOT NULL,
  `billing_company` varchar(64) default NULL,
  `billing_last_name` varchar(32) NOT NULL,
  `billing_first_name` varchar(32) NOT NULL,
  `billing_phone` varchar(32) NOT NULL,
  `billing_address_1` varchar(64) NOT NULL,
  `billing_address_2` varchar(64) default NULL,
  `billing_city` varchar(32) NOT NULL,
  `billing_state` varchar(32) NOT NULL,
  `billing_country` varchar(32) NOT NULL,
  `billing_zip` varchar(32) NOT NULL,
  `shipping_company` varchar(64) default NULL,
  `shipping_last_name` varchar(32) NOT NULL,
  `shipping_first_name` varchar(32) NOT NULL,
  `shipping_phone` varchar(32) NOT NULL,
  `shipping_address_1` varchar(64) NOT NULL,
  `shipping_address_2` varchar(64) default NULL,
  `shipping_city` varchar(32) NOT NULL,
  `shipping_state` varchar(32) NOT NULL,
  `shipping_country` varchar(32) default NULL,
  `residential` int(1) default '0',
  `shipping_zip` varchar(32) NOT NULL,
  `subtotal` decimal(10,2) NOT NULL,
  `zone_tax` decimal(10,2) default NULL,
  `country_tax` decimal(10,2) default NULL,
  `shipping` decimal(10,2) default NULL,
  `shipping_tax` decimal(10,2) default NULL,
  `total` decimal(10,2) default NULL,
  `comments` text,
  `order_status_id` int(10) unsigned default NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `ps_orders`
--

INSERT INTO `ps_orders` (`id`, `customer_id`, `email`, `billing_company`, `billing_last_name`, `billing_first_name`, `billing_phone`, `billing_address_1`, `billing_address_2`, `billing_city`, `billing_state`, `billing_country`, `billing_zip`, `shipping_company`, `shipping_last_name`, `shipping_first_name`, `shipping_phone`, `shipping_address_1`, `shipping_address_2`, `shipping_city`, `shipping_state`, `shipping_country`, `shipping_zip`, `residential`, `subtotal`, `zone_tax`, `country_tax`, `shipping`, `shipping_tax`, `total`, `comments`, `order_status_id`, `created`, `modified`) VALUES
(0000000001, 1, 'root@localhost', 'Company', 'Last Name', 'First Name', '555-555-1212', 'Street Address 1', 'Street Address 2', 'City', 'State', 'Country', '00000', 'Shipping Company', 'Last Name', 'First Name', '555-555-1212', 'Address 1', 'Address 2', 'City', 'State', 'Country', '00000', NULL, 80.97, 2.54, 0.00, 0.00, 0.00, 83.51, 'Please send in a hurry.', 1, '2007-04-24 22:14:56', '2008-01-23 17:47:18');

-- --------------------------------------------------------

--
-- Table structure for table `ps_order_items`
--

CREATE TABLE IF NOT EXISTS `ps_order_items` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `order_id` int(10) unsigned zerofill NOT NULL,
  `product_item_id` int(10) NOT NULL,
  `quantity` int(11) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=19 ;

--
-- Dumping data for table `ps_order_items`
--

INSERT INTO `ps_order_items` (`id`, `order_id`, `product_item_id`, `quantity`, `price`, `created`, `modified`) VALUES
(1, 0000000001, 5, 2, 4.99, '2007-04-24 22:15:32', '2008-01-16 13:01:17'),
(17, 0000000001, 5, 4, 4.99, '2008-01-24 21:46:33', '2008-01-24 21:46:33'),
(15, 0000000001, 7, 4, 69.99, '2008-01-16 18:27:08', '2008-01-16 21:56:36');

-- --------------------------------------------------------

--
-- Table structure for table `ps_order_payments`
--

CREATE TABLE IF NOT EXISTS `ps_order_payments` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `order_id` int(10) unsigned zerofill NOT NULL default '0000000000',
  `reference_number` varchar(255) default NULL,
  `transaction_log` text,
  `amount` float(10,2) NOT NULL,
  `created` datetime NOT NULL,
  `modified` datetime NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `ps_order_payments`
--

INSERT INTO `ps_order_payments` (`id`, `order_id`, `reference_number`, `transaction_log`, `amount`, `created`, `modified`) VALUES
(3, 0000000001, '12345', '', 550.00, '2008-01-24 21:27:01', '2008-01-24 21:27:58');

-- --------------------------------------------------------

--
-- Table structure for table `ps_order_shipments`
--

CREATE TABLE IF NOT EXISTS `ps_order_shipments` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `order_id` int(10) unsigned zerofill NOT NULL,
  `shipping_rate_id` int(10) NOT NULL,
  `shipping_date` date NOT NULL,
  `reference_number` varchar(256) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `ps_order_shipments`
--

INSERT INTO `ps_order_shipments` (`id`, `order_id`, `shipping_rate_id`, `shipping_date`, `reference_number`) VALUES
(1, 0000000001, 2, '2008-01-15', '1234567890123456');

-- --------------------------------------------------------

--
-- Table structure for table `ps_order_shipments_order_items`
--

CREATE TABLE IF NOT EXISTS `ps_order_shipments_order_items` (
  `id` int(10) unsigned NOT NULL,
  `order_shipment_id` int(10) unsigned NOT NULL,
  `order_item_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ps_order_shipments_order_items`
--

INSERT INTO `ps_order_shipments_order_items` (`id`, `order_shipment_id`, `order_item_id`) VALUES
(0, 1, 16),
(1, 1, 1),
(2, 1, 15);

-- --------------------------------------------------------

--
-- Table structure for table `ps_order_statuses`
--

CREATE TABLE IF NOT EXISTS `ps_order_statuses` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(64) NOT NULL,
  `sort_order` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `ps_order_statuses`
--

INSERT INTO `ps_order_statuses` (`id`, `name`, `sort_order`) VALUES
(1, 'Pending', 1),
(2, 'Confirmed', 2),
(3, 'Cancelled', 3),
(4, 'Shipped', 4);

-- --------------------------------------------------------

--
-- Table structure for table `ps_products`
--

CREATE TABLE IF NOT EXISTS `ps_products` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `handle` varchar(255) NOT NULL,
  `description` text NOT NULL,
  `active` int(1) NOT NULL,
  `brand_id` int(10) unsigned NOT NULL,
  `product_type_id` int(10) unsigned default NULL,
  `tags` text NOT NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1000000008 ;

--
-- Dumping data for table `ps_products`
--

INSERT INTO `ps_products` (`id`, `name`, `handle`, `description`, `active`, `brand_id`, `product_type_id`, `tags`, `created`, `modified`) VALUES
(5, 'Nice Saw', 'nice_saw', 'You''ve been wanting to cut that tree down in the back yard for some time now.  Why not yell it out?  Timber! Hand crafted handle with maximum grip torque.  Titanium tipped shovel platter.  Half degree offset for less accidents Includes HowTo Video narrated by Bob Costas.', 1, 3, 1, 'saw', '0000-00-00 00:00:00', '2007-07-11 13:11:19'),
(1, 'Hand Shovel', 'hand-shovel', 'Hand crafted handle with maximum grip torque.  Titanium tipped shovel platter with falf degree offset for less accidents.  Includes HowTo Video narrated by Bob Costas.', 1, 3, 1, 'hand shovel', '1995-03-20 11:07:00', '2007-07-11 13:19:53'),
(2, 'Ladder', 'ladder', '<UL><LI>Hand crafted handle with maximum grip torque<LI>Titanium tipped shovel platter<LI>Half degree offset for less accidents<LI>Includes HowTo Video narrated by Bob Costas</UL><B>Specifications</B><BR>5" Diameter<BR>Tungsten handle tip with 5 point loft<BR>', 1, 3, 1, 'ladder', '1995-03-20 18:00:00', '2007-06-14 21:41:27'),
(3, 'Shovel', 'shovel', 'Hand crafted handle with maximum grip torque.  Titanium tipped shovel platter with half degree offset for less accidents.  Includes HowTo Video narrated by Bob Costas.  Uses 5" Diameter Tungsten handle tip with 5 point loft.', 1, 3, 1, 'shovel', '0000-00-00 00:00:00', '2007-07-11 13:41:44'),
(4, 'Smaller Shovel', 'smaller-shovel', '                        <UL><LI>Hand crafted handle with maximum grip torque<LI>Titanium tipped shovel platter<LI>Half degree offset for less accidents<LI>Includes HowTo Video narrated by Bob Costas</UL><B>Specifications</B><BR>5" Diameter<BR>Tungsten handle tip with 5 point loft<BR>                        ', 1, 3, 1, 'smaller shovel', '0000-00-00 00:00:00', '2007-06-14 21:42:02'),
(6, 'Hammer', 'hammer', '                <UL><LI>Hand crafted handle with maximum grip torque<LI>Titanium tipped shovel platter<LI>Half degree offset for less accidents<LI>Includes HowTo Video narrated by Bob Costas</UL><B>Specifications</B><BR>5" Diameter<BR>Tungsten handle tip with 5 point loft<BR>                ', 1, 3, 1, 'hammer', '0000-00-00 00:00:00', '2008-01-30 18:14:47'),
(7, 'Chain Saw', 'chain-saw', '                <ul><li>Tool-free tensioner for easy, convenient chain adjustment<li>3-Way Auto Stop; stops chain a fraction of a second<li>Automatic chain oiler regulates oil for proper chain lubrication<li>Small radius guide bar reduces kick-back</ul><br><b>Specifications</b><br>12.5 AMPS   <br> 16" Bar Length   <br> 3.5 HP   <br> 8.05 LBS. Weight   <br>                         ', 1, 3, 1, 'chain saw', '0000-00-00 00:00:00', '2007-06-14 21:42:42'),
(8, 'Circular Saw', 'Circular-Saw', '<ul><li>Patented Sightline; Window provides maximum visibility for straight cuts<li>Adjustable dust chute for cleaner work area<li>Bail handle for controlled cutting in 90? to 45? applications<li>1-1/2 to 2-1/2 lbs. lighter and 40% less noise than the average circular saw                     <li><B>Includes:</b>Carbide blade</ul><br><b>Specifications</b><br>10.0 AMPS   <br> 4,300 RPM   <br> Capacity: 2-1/16" at 90?, 1-3/4" at 45?<br> ', 1, 3, 1, 'circular saw', '0000-00-00 00:00:00', '2007-06-14 21:43:00'),
(9, 'Drill', 'drill', '                <ul>                        <li>High power motor and double gear reduction for increased durability and improved performance<li>Mid-handle design and two finger trigger for increased balance and comfort<li>Variable speed switch with lock-on button for continuous use<li><B>Includes:</B> Chuck key & holder</ul><br><b>Specifications</b><br>4.0 AMPS   <br> 0-1,350 RPM   <br> Capacity: 3/8" Steel, 1" Wood   <br>         ', 1, 3, 1, 'drill', '0000-00-00 00:00:00', '2007-06-14 21:43:14'),
(10, 'Power Sander', 'power-sander', '<ul><li>Lever activated paper clamps for simple sandpaper changes<li>Dust sealed rocker switch extends product life and keeps dust out of motor<li>Flush sands on three sides to get into corners<li>Front handle for extra control<li>Dust extraction port for cleaner work environment </ul><br><b>Specifications</b><br>1.2 AMPS    <br> 10,000 OPM    <br> ', 1, 3, 1, 'power sander', '0000-00-00 00:00:00', '2008-01-24 15:12:22');

-- --------------------------------------------------------

--
-- Table structure for table `ps_products_categories`
--

CREATE TABLE IF NOT EXISTS `ps_products_categories` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `product_id` int(10) unsigned NOT NULL,
  `category_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=461 ;

--
-- Dumping data for table `ps_products_categories`
--

INSERT INTO `ps_products_categories` (`id`, `product_id`, `category_id`) VALUES
(457, 6, 7),
(388, 1, 1),
(387, 5, 1),
(366, 2, 4),
(410, 4, 3),
(409, 3, 3),
(414, 10, 4),
(382, 9, 2),
(362, 8, 5),
(381, 8, 2),
(363, 9, 5),
(380, 7, 2),
(413, 10, 2),
(408, 1, 3),
(458, 5, 6),
(459, 1, 6),
(460, 2, 6),
(456, 6, 1),
(435, 4, 1000000009),
(434, 3, 1000000009),
(433, 2, 1000000009);

-- --------------------------------------------------------

--
-- Table structure for table `ps_product_images`
--

CREATE TABLE IF NOT EXISTS `ps_product_images` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `product_id` int(10) unsigned NOT NULL,
  `image` varchar(255) NOT NULL,
  `priority` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=14 ;

--
-- Dumping data for table `ps_product_images`
--

INSERT INTO `ps_product_images` (`id`, `product_id`, `image`, `priority`) VALUES
(1, 9, '1ff5f2527907ca86103288e1b7cc3446.jpg', 0),
(2, 5, 'e614ba08c3ee0c2adc62fd9e5b9440eb.jpg', 1),
(3, 1, '8d886c5855770cc01a3b8a2db57f6600.jpg', 0),
(4, 2, 'ffd5d5ace2840232c8c32de59553cd8d.jpg', 0),
(5, 3, 'a04395a8aefacd9c1659ebca4dbfd4ba.jpg', 0),
(6, 4, '520efefd6d7977f91b16fac1149c7438.jpg', 0),
(7, 6, '578563851019e01264a9b40dcf1c4ab6.jpg', 0),
(8, 7, '8716aefc3b0dce8870360604e6eb8744.jpg', 0),
(9, 8, 'b4a748303d0d996b29d5a1e1d1112537.jpg', 0),
(11, 10, '7a36a05526e93964a086f2ddf17fc609.jpg', 0),
(13, 5, '8716aefc3b0dce8870360604e6eb8744.jpg', 1);

-- --------------------------------------------------------

--
-- Table structure for table `ps_product_items`
--

CREATE TABLE IF NOT EXISTS `ps_product_items` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `product_id` int(10) unsigned NOT NULL,
  `sku` varchar(32) NOT NULL,
  `label` varchar(255) NOT NULL,
  `sell_price` decimal(10,2) NOT NULL,
  `regular_price` decimal(10,2) default NULL,
  `weight` decimal(10,4) default NULL,
  `quantity` int(10) unsigned default NULL,
  `track_stock` int(1) default NULL,
  `created` datetime default NULL,
  `modified` datetime default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `code_key` (`sku`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=22 ;

--
-- Dumping data for table `ps_product_items`
--

INSERT INTO `ps_product_items` (`id`, `product_id`, `sku`, `label`, `sell_price`, `regular_price`, `weight`, `quantity`, `track_stock`, `created`, `modified`) VALUES
(5, 5, 'H01', 'Nice Saw', 24.99, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2008-01-26 10:06:52'),
(1, 1, 'G01', 'Hand Shovel', 4.99, 0.00, 10.0000, 10, 0, '1995-03-20 11:07:00', '2007-06-14 21:49:09'),
(2, 2, 'G02', 'Ladder', 49.99, 0.00, 10.0000, 0, 0, '1995-03-20 18:00:00', '2007-06-14 21:49:15'),
(3, 3, 'G03', 'Shovel', 24.99, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2007-06-14 21:49:22'),
(4, 4, 'G04', 'Smaller Shovel', 19.99, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2007-06-14 21:49:28'),
(6, 6, 'H02', 'Hammer', 1.00, 0.00, 10.0000, 0, 1, '0000-00-00 00:00:00', '2008-01-26 15:02:00'),
(7, 7, 'P01', 'Chain Saw', 149.99, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2007-06-14 21:49:44'),
(8, 8, 'P02', 'Circular Saw', 220.90, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2007-06-14 21:49:50'),
(9, 9, 'P03', 'Drill', 48.12, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2007-06-14 21:49:57'),
(10, 10, 'P04', 'Power Sander', 74.99, 0.00, 10.0000, 0, 0, '0000-00-00 00:00:00', '2007-06-14 21:50:04'),
(12, 3, 'G03A', 'Nickel Handle', 35.00, 55.00, 10.0000, 10, 1, '2007-07-11 13:42:29', '2007-07-11 13:52:39');

-- --------------------------------------------------------

--
-- Table structure for table `ps_product_types`
--

CREATE TABLE IF NOT EXISTS `ps_product_types` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `ps_product_types`
--

INSERT INTO `ps_product_types` (`id`, `name`) VALUES
(1, 'Hardware');

-- --------------------------------------------------------

--
-- Table structure for table `ps_settings`
--

CREATE TABLE IF NOT EXISTS `ps_settings` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `key` varchar(255) NOT NULL,
  `value` text NOT NULL,
  `description` text,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Dumping data for table `ps_settings`
--

INSERT INTO `ps_settings` (`id`, `key`, `value`, `description`) VALUES
(1, 'Store.address', '101 Washupito Way\r\nGuaynabo City, Puerto Rico', 'Store address.'),
(2, 'Store.name', 'Washupito''s Tiendita', 'Store name.'),
(3, 'Shipping.taxable', '0', 'Do you want to tax the shipping charge?\r\n0 = No\r\n1 = Yes'),
(10, 'Store.currency', 'USD', 'Valid values are ''USD'', ''EUR'', ''GBP''.'),
(11, 'debug', '1', 'Changes debugging output.\r\n0 = Production mode. No output.\r\n1 = Show errors and warnings. (default)\r\n2 = Show errors, warnings, and SQL.\r\n3 = Show errors, warnings, SQL, and complete controller dump.'),
(12, 'Ups.products', '1DA,2DA,GND', 'Shipping products offered.  Comma separated list.\r\n1DM == Next Day Air Early AM\r\n1DA == Next Day Air\r\n1DP == Next Day Air Saver\r\n2DM == 2nd Day Air Early AM\r\n2DA == 2nd Day Air\r\n3DS == 3 Day Select\r\nGND == Ground\r\nSTD == Canada Standard\r\nXPR == Worldwide Express\r\nXDM == Worldwide Express Plus\r\nXPD == Worldwide Expedited'),
(13, 'Ups.container', 'CP', 'Standard container (i.e. box) for all shipments.  Can only be set globally.\r\n\r\nCP:  Customer Packaging\r\nULE: UPS Letter Envelope\r\nUT: 	UPS Tube\r\nUEB: UPS Express Box\r\nUW25: UPS Worldwide 25 kilo\r\nUW10: UPS Worldwide 10 kilo\r\n\r\n'),
(14, 'Session.save', 'cake', 'Tells CakePHP which session storage mechanism to use.\r\n\r\nphp = Use the default PHP session storage.\r\ncake = Store session data in /app/tmp (default)\r\ndatabase = store session data in a database table. '),
(15, 'Session.checkAgent', '0', 'When set to false, CakePHP sessions will not check to ensure the user agent does not change between requests.  If you are using Safari, you may need to turn this off so that you do not lose sessions between page loads. \r\n\r\n0 = Off (default)\r\n1 = On ');

-- --------------------------------------------------------

--
-- Table structure for table `ps_shipping_rates`
--

CREATE TABLE IF NOT EXISTS `ps_shipping_rates` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `country_id` int(10) NOT NULL,
  `zone_id` int(10) default NULL,
  `name` varchar(255) NOT NULL,
  `start` int(10) default NULL,
  `end` int(10) default NULL,
  `price` decimal(10,2) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- Dumping data for table `ps_shipping_rates`
--

INSERT INTO `ps_shipping_rates` (`id`, `country_id`, `zone_id`, `name`, `start`, `end`, `price`) VALUES
(1, 1, NULL, 'Standard Shipping', 0, 1, 5.00),
(2, 1, NULL, 'Standard Shipping', 1, 5, 10.00),
(3, 1, NULL, 'Standard Shipping', 5, 100, 50.00);

-- --------------------------------------------------------

--
-- Table structure for table `ps_users`
--

CREATE TABLE IF NOT EXISTS `ps_users` (
  `id` int(10) NOT NULL auto_increment,
  `username` varchar(250) NOT NULL default '',
  `password` varchar(32) NOT NULL default '',
  `role` varchar(50) NOT NULL default 'User',
  `name` varchar(255) default NULL,
  `email` varchar(250) NOT NULL default '',
  `created` datetime NOT NULL default '0000-00-00 00:00:00',
  `modified` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `ps_users`
--

-- --------------------------------------------------------

--
-- Table structure for table `ps_zones`
--

CREATE TABLE IF NOT EXISTS `ps_zones` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `country_id` int(10) NOT NULL,
  `name` varchar(64) default NULL,
  `code` char(2) default NULL,
  `tax_rate` decimal(10,4) default NULL,
  `active` int(1) NOT NULL default '1',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `code_unique` (`code`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=179 ;

--
-- Dumping data for table `ps_zones`
--

INSERT INTO `ps_zones` (`id`, `country_id`, `name`, `code`, `tax_rate`, `active`) VALUES
(120, 1, 'ALABAMA', 'AL', 0.0000, 1),
(121, 1, 'ALASKA', 'AK', 0.0000, 1),
(122, 1, 'AMERICAN SAMOA', 'AS', 0.0000, 1),
(123, 1, 'ARIZONA', 'AZ', 0.0000, 1),
(124, 1, 'ARKANSAS', 'AR', 0.0000, 1),
(125, 1, 'CALIFORNIA', 'CA', 0.0000, 1),
(126, 1, 'COLORADO', 'CO', 0.0000, 1),
(127, 1, 'CONNECTICUT', 'CT', 0.0000, 1),
(128, 1, 'DELAWARE', 'DE', 0.0000, 1),
(129, 1, 'DISTRICT OF COLUMBIA', 'DC', 0.0000, 1),
(130, 1, 'FEDERATED STATES OF MICRONESIA', 'FM', 0.0000, 1),
(131, 1, 'FLORIDA', 'FL', 0.0000, 1),
(132, 1, 'GEORGIA', 'GA', 0.0750, 1),
(133, 1, 'GUAM', 'GU', 0.0000, 1),
(134, 1, 'HAWAII', 'HI', 0.0000, 1),
(135, 1, 'IDAHO', 'ID', 0.0000, 1),
(136, 1, 'ILLINOIS', 'IL', 0.0000, 1),
(137, 1, 'INDIANA', 'IN', 0.0000, 1),
(138, 1, 'IOWA', 'IA', 0.0000, 1),
(139, 1, 'KANSAS', 'KS', 0.0000, 1),
(140, 1, 'KENTUCKY', 'KY', 0.0000, 1),
(141, 1, 'LOUISIANA', 'LA', 0.0000, 1),
(142, 1, 'MAINE', 'ME', 0.0000, 1),
(143, 1, 'MARSHALL ISLANDS', 'MH', 0.0000, 1),
(144, 1, 'MARYLAND', 'MD', 0.0000, 1),
(145, 1, 'MASSACHUSETTS', 'MA', 0.0000, 1),
(146, 1, 'MICHIGAN', 'MI', 0.0000, 1),
(147, 1, 'MINNESOTA', 'MN', 0.0000, 1),
(148, 1, 'MISSISSIPPI', 'MS', 0.0000, 1),
(149, 1, 'MISSOURI', 'MO', 0.0000, 1),
(150, 1, 'MONTANA', 'MT', 0.0000, 1),
(151, 1, 'NEBRASKA', 'NE', 0.0000, 1),
(152, 1, 'NEVADA', 'NV', 0.0000, 1),
(153, 1, 'NEW HAMPSHIRE', 'NH', 0.0000, 1),
(154, 1, 'NEW JERSEY', 'NJ', 0.0000, 1),
(155, 1, 'NEW MEXICO', 'NM', 0.0000, 1),
(156, 1, 'NEW YORK', 'NY', 0.0000, 1),
(157, 1, 'NORTH CAROLINA', 'NC', 0.0000, 1),
(158, 1, 'NORTH DAKOTA', 'ND', 0.0000, 1),
(159, 1, 'NORTHERN MARIANA ISLANDS', 'MP', 0.0000, 1),
(160, 1, 'OHIO', 'OH', 0.0000, 1),
(161, 1, 'OKLAHOMA', 'OK', 0.0000, 1),
(162, 1, 'OREGON', 'OR', 0.0000, 1),
(163, 1, 'PALAU', 'PW', 0.0000, 1),
(164, 1, 'PENNSYLVANIA', 'PA', 0.0000, 1),
(165, 1, 'PUERTO RICO', 'PR', 0.0000, 1),
(166, 1, 'RHODE ISLAND', 'RI', 0.0000, 1),
(167, 1, 'SOUTH CAROLINA', 'SC', 0.0000, 1),
(168, 1, 'SOUTH DAKOTA', 'SD', 0.0000, 1),
(169, 1, 'TENNESSEE', 'TN', 0.0000, 1),
(170, 1, 'TEXAS', 'TX', 0.0000, 1),
(171, 1, 'UTAH', 'UT', 0.0000, 1),
(172, 1, 'VERMONT', 'VT', 0.0000, 1),
(173, 1, 'VIRGIN ISLANDS', 'VI', 0.0000, 1),
(174, 1, 'VIRGINIA', 'VA', 0.0000, 1),
(175, 1, 'WASHINGTON', 'WA', 0.0000, 1),
(176, 1, 'WEST VIRGINIA', 'WV', 0.0000, 1),
(177, 1, 'WISCONSIN', 'WI', 0.0000, 1),
(178, 1, 'WYOMING', 'WY', 0.0000, 1);
