# Server version: 3.23.37
# PHP Version: 4.0.6
# Database : 
# --------------------------------------------------------

#
# Table structure for table `zone_shipping`
#

CREATE TABLE zone_shipping (
  zone_id int(11) NOT NULL auto_increment,
  zone_name varchar(255) default NULL,
  zone_cost decimal(10,2) default NULL,
  zone_limit decimal(10,2) default NULL,
  zone_description text NOT NULL,
  PRIMARY KEY  (zone_id),
  KEY zone_id (zone_id)
) TYPE=MyISAM;

#
# Dumping data for table `zone_shipping`
#

INSERT INTO zone_shipping VALUES (1, 'Default', '6.00', '35.00', 'This is the default Shipping Zone. This is the zone information that all countries will use until you assign each individual country to a Zone.');
INSERT INTO zone_shipping VALUES (2, 'Zone 1', '1000.00', '10000.00', 'This is a zone example');
INSERT INTO zone_shipping VALUES (3, 'Zone 2', '2.00', '22.00', 'This is the second zone. You can use this for notes about this zone');
INSERT INTO zone_shipping VALUES (4, 'Zone 3', '11.00', '64.00', 'Another usefull thing might be details about this zone or special instructions.');

