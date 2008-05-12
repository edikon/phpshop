# phpMyAdmin SQL Dump
# version 2.5.4
# http://www.phpmyadmin.net
#
# Host: localhost
# Generation Time: Jul 27, 2004 at 11:12 AM
# Server version: 3.23.58
# PHP Version: 4.3.4
# 
# Database : `phpshop`
# 

# --------------------------------------------------------

#
# Table structure for table `auth_user_md5`
#

CREATE TABLE `auth_user_md5` (
  `user_id` varchar(32) NOT NULL default '',
  `username` varchar(32) NOT NULL default '',
  `password` varchar(32) NOT NULL default '',
  `perms` varchar(255) default NULL,
  `reset_key` varchar(32) default NULL,
  `reset_password` varchar(32) default NULL,
  PRIMARY KEY  (`user_id`),
  UNIQUE KEY `k_username` (`username`)
) TYPE=MyISAM;

#
# Dumping data for table `auth_user_md5`
#

INSERT INTO `auth_user_md5` VALUES ('7322f75cc7ba16db1799fd8d25dbcde4', 'admin', '098f6bcd4621d373cade4e832627b4f6', 'admin', NULL, NULL);
INSERT INTO `auth_user_md5` VALUES ('02acf876459c748dbb71b3b40714c0d7', 'test', '098f6bcd4621d373cade4e832627b4f6', 'shopper', NULL, NULL);
INSERT INTO `auth_user_md5` VALUES ('c88ce1c0ad365513d6fe085a8aacaebc', 'demo', 'fe01ce2a7fbac8fafaed7c982a04e229', 'demo', '0d446c28015d2ffbb32c720f75d6e55b', '87569dd1ecdff4ffb958d121a9240f4a');
INSERT INTO `auth_user_md5` VALUES ('1438a90d1888a2814b2bdedc43c03e99', 'storeadmin', '098f6bcd4621d373cade4e832627b4f6', 'storeadmin', NULL, NULL);
INSERT INTO `auth_user_md5` VALUES ('6845b3a8d95fc4799e9e962d1f9976bd', 'gold', '098f6bcd4621d373cade4e832627b4f6', 'shopper', NULL, NULL);

# --------------------------------------------------------

#
# Table structure for table `auth_user_vendor`
#

CREATE TABLE `auth_user_vendor` (
  `user_id` varchar(32) default NULL,
  `vendor_id` int(11) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `auth_user_vendor`
#

INSERT INTO `auth_user_vendor` VALUES ('7322f75cc7ba16db1799fd8d25dbcde4', 1);
INSERT INTO `auth_user_vendor` VALUES ('c88ce1c0ad365513d6fe085a8aacaebc', 1);
INSERT INTO `auth_user_vendor` VALUES ('1438a90d1888a2814b2bdedc43c03e99', 1);

# --------------------------------------------------------

#
# Table structure for table `category`
#

CREATE TABLE `category` (
  `category_id` varchar(32) NOT NULL default '',
  `vendor_id` int(11) NOT NULL default '0',
  `category_name` varchar(128) NOT NULL default '',
  `category_description` text,
  `category_thumb_image` varchar(255) default NULL,
  `category_full_image` varchar(255) default NULL,
  `category_publish` char(1) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  `category_flypage` varchar(255) default NULL,
  `category_url` varchar(255) default NULL,
  PRIMARY KEY  (`category_id`)
) TYPE=MyISAM;

#
# Dumping data for table `category`
#

INSERT INTO `category` VALUES ('541a03b2b0e1b6dbd972e9f5af5ca992', 1, 'Hand Tools', 'Hand Tools', NULL, NULL, 'Y', 950319905, 1090673019, '', 'handtools');
INSERT INTO `category` VALUES ('1c914424d2569bea3439fbcca9123a27', 1, 'Power Tools', 'Power Tools', NULL, NULL, 'Y', 950319916, 1090673022, '', 'powertools');
INSERT INTO `category` VALUES ('6834dda8e3e6e5aa18bafc63a57fd04a', 1, 'Garden Tools', 'Garden Tools', NULL, NULL, 'Y', 950321122, 1090680680, '', 'gardentools');
INSERT INTO `category` VALUES ('f85e462baf927f8e53989dd969c0e430', 1, 'Outdoor Tools', 'Outdoor Tools', NULL, NULL, 'Y', 955626629, 1090673024, '', 'powertools_outdoortools');
INSERT INTO `category` VALUES ('2f34f8bf003a5f27bed2e8dfe0b6f33a', 1, 'Indoor Tools', 'Indoor Tools', NULL, NULL, 'Y', 958892894, 1090673027, '', 'powertools_indoortools');

# --------------------------------------------------------

#
# Table structure for table `category_xref`
#

CREATE TABLE `category_xref` (
  `category_parent_id` varchar(32) default NULL,
  `category_child_id` varchar(32) default NULL,
  `category_list` int(11) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `category_xref`
#

INSERT INTO `category_xref` VALUES ('0', '541a03b2b0e1b6dbd972e9f5af5ca992', NULL);
INSERT INTO `category_xref` VALUES ('0', '1c914424d2569bea3439fbcca9123a27', NULL);
INSERT INTO `category_xref` VALUES ('0', '6834dda8e3e6e5aa18bafc63a57fd04a', NULL);
INSERT INTO `category_xref` VALUES ('1c914424d2569bea3439fbcca9123a27', 'f85e462baf927f8e53989dd969c0e430', NULL);
INSERT INTO `category_xref` VALUES ('1c914424d2569bea3439fbcca9123a27', '2f34f8bf003a5f27bed2e8dfe0b6f33a', NULL);

# --------------------------------------------------------

#
# Table structure for table `country`
#

CREATE TABLE `country` (
  `country_id` int(11) NOT NULL default '0',
  `country_name` varchar(64) default NULL,
  `country_3_code` char(3) default NULL,
  `country_2_code` char(2) default NULL,
  PRIMARY KEY  (`country_id`)
) TYPE=MyISAM;

#
# Dumping data for table `country`
#

INSERT INTO `country` VALUES (4, 'AFGHANISTAN', 'AFG', 'AF');
INSERT INTO `country` VALUES (8, 'ALBANIA', 'ALB', 'AL');
INSERT INTO `country` VALUES (12, 'ALGERIA', 'DZA', 'DZ');
INSERT INTO `country` VALUES (16, 'AMERICAN SAMOA', 'ASM', 'AS');
INSERT INTO `country` VALUES (20, 'ANDORRA', 'AND', 'AD');
INSERT INTO `country` VALUES (24, 'ANGOLA', 'AGO', 'AO');
INSERT INTO `country` VALUES (660, 'ANGUILLA', 'AIA', 'AI');
INSERT INTO `country` VALUES (10, 'ANTARCTICA', 'ATA', 'AQ');
INSERT INTO `country` VALUES (28, 'ANTIGUA AND BARBUDA', 'ATG', 'AG');
INSERT INTO `country` VALUES (32, 'ARGENTINA', 'ARG', 'AR');
INSERT INTO `country` VALUES (51, 'ARMENIA', 'ARM', 'AM');
INSERT INTO `country` VALUES (533, 'ARUBA', 'ABW', 'AW');
INSERT INTO `country` VALUES (36, 'AUSTRALIA', 'AUS', 'AU');
INSERT INTO `country` VALUES (40, 'AUSTRIA', 'AUT', 'AT');
INSERT INTO `country` VALUES (31, 'AZERBAIJAN', 'AZE', 'AZ');
INSERT INTO `country` VALUES (44, 'BAHAMAS', 'BHS', 'BS');
INSERT INTO `country` VALUES (48, 'BAHRAIN', 'BHR', 'BH');
INSERT INTO `country` VALUES (50, 'BANGLADESH', 'BGD', 'BD');
INSERT INTO `country` VALUES (52, 'BARBADOS', 'BRB', 'BB');
INSERT INTO `country` VALUES (112, 'BELARUS', 'BLR', 'BY');
INSERT INTO `country` VALUES (56, 'BELGIUM', 'BEL', 'BE');
INSERT INTO `country` VALUES (84, 'BELIZE', 'BLZ', 'BZ');
INSERT INTO `country` VALUES (204, 'BENIN', 'BEN', 'BJ');
INSERT INTO `country` VALUES (60, 'BERMUDA', 'BMU', 'BM');
INSERT INTO `country` VALUES (64, 'BHUTAN', 'BTN', 'BT');
INSERT INTO `country` VALUES (68, 'BOLIVIA', 'BOL', 'BO');
INSERT INTO `country` VALUES (70, 'BOSNIA AND HERZEGOWINA', 'BIH', 'BA');
INSERT INTO `country` VALUES (72, 'BOTSWANA', 'BWA', 'BW');
INSERT INTO `country` VALUES (74, 'BOUVET ISLAND', 'BVT', 'BV');
INSERT INTO `country` VALUES (76, 'BRAZIL', 'BRA', 'BR');
INSERT INTO `country` VALUES (86, 'BRITISH INDIAN OCEAN TERRITORY', 'IOT', 'IO');
INSERT INTO `country` VALUES (96, 'BRUNEI DARUSSALAM', 'BRN', 'BN');
INSERT INTO `country` VALUES (100, 'BULGARIA', 'BGR', 'BG');
INSERT INTO `country` VALUES (854, 'BURKINA FASO', 'BFA', 'BF');
INSERT INTO `country` VALUES (108, 'BURUNDI', 'BDI', 'BI');
INSERT INTO `country` VALUES (116, 'CAMBODIA', 'KHM', 'KH');
INSERT INTO `country` VALUES (120, 'CAMEROON', 'CMR', 'CM');
INSERT INTO `country` VALUES (124, 'CANADA', 'CAN', 'CA');
INSERT INTO `country` VALUES (132, 'CAPE VERDE', 'CPV', 'CV');
INSERT INTO `country` VALUES (136, 'CAYMAN ISLANDS', 'CYM', 'KY');
INSERT INTO `country` VALUES (140, 'CENTRAL AFRICAN REPUBLIC', 'CAF', 'CF');
INSERT INTO `country` VALUES (148, 'CHAD', 'TCD', 'TD');
INSERT INTO `country` VALUES (152, 'CHILE', 'CHL', 'CL');
INSERT INTO `country` VALUES (156, 'CHINA', 'CHN', 'CN');
INSERT INTO `country` VALUES (162, 'CHRISTMAS ISLAND', 'CXR', 'CX');
INSERT INTO `country` VALUES (166, 'COCOS (KEELING) ISLANDS', 'CCK', 'CC');
INSERT INTO `country` VALUES (170, 'COLOMBIA', 'COL', 'CO');
INSERT INTO `country` VALUES (174, 'COMOROS', 'COM', 'KM');
INSERT INTO `country` VALUES (178, 'CONGO', 'COG', 'CG');
INSERT INTO `country` VALUES (180, 'CONGO, THE DEMOCRATIC REPUBLIC OF THE', 'COD', 'CD');
INSERT INTO `country` VALUES (184, 'COOK ISLANDS', 'COK', 'CK');
INSERT INTO `country` VALUES (188, 'COSTA RICA', 'CRI', 'CR');
INSERT INTO `country` VALUES (384, 'COTE D\'IVOIRE', 'CIV', 'CI');
INSERT INTO `country` VALUES (191, 'CROATIA (local name: Hrvatska)', 'HRV', 'HR');
INSERT INTO `country` VALUES (192, 'CUBA', 'CUB', 'CU');
INSERT INTO `country` VALUES (196, 'CYPRUS', 'CYP', 'CY');
INSERT INTO `country` VALUES (203, 'CZECH REPUBLIC', 'CZE', 'CZ');
INSERT INTO `country` VALUES (208, 'DENMARK', 'DNK', 'DK');
INSERT INTO `country` VALUES (262, 'DJIBOUTI', 'DJI', 'DJ');
INSERT INTO `country` VALUES (212, 'DOMINICA', 'DMA', 'DM');
INSERT INTO `country` VALUES (214, 'DOMINICAN REPUBLIC', 'DOM', 'DO');
INSERT INTO `country` VALUES (626, 'EAST TIMOR', 'TMP', 'TP');
INSERT INTO `country` VALUES (218, 'ECUADOR', 'ECU', 'EC');
INSERT INTO `country` VALUES (818, 'EGYPT', 'EGY', 'EG');
INSERT INTO `country` VALUES (222, 'EL SALVADOR', 'SLV', 'SV');
INSERT INTO `country` VALUES (226, 'EQUATORIAL GUINEA', 'GNQ', 'GQ');
INSERT INTO `country` VALUES (232, 'ERITREA', 'ERI', 'ER');
INSERT INTO `country` VALUES (233, 'ESTONIA', 'EST', 'EE');
INSERT INTO `country` VALUES (231, 'ETHIOPIA', 'ETH', 'ET');
INSERT INTO `country` VALUES (238, 'FALKLAND ISLANDS (MALVINAS)', 'FLK', 'FK');
INSERT INTO `country` VALUES (234, 'FAROE ISLANDS', 'FRO', 'FO');
INSERT INTO `country` VALUES (242, 'FIJI', 'FJI', 'FJ');
INSERT INTO `country` VALUES (246, 'FINLAND', 'FIN', 'FI');
INSERT INTO `country` VALUES (250, 'FRANCE', 'FRA', 'FR');
INSERT INTO `country` VALUES (249, 'FRANCE, METROPOLITAN', 'FXX', 'FX');
INSERT INTO `country` VALUES (254, 'FRENCH GUIANA', 'GUF', 'GF');
INSERT INTO `country` VALUES (258, 'FRENCH POLYNESIA', 'PYF', 'PF');
INSERT INTO `country` VALUES (260, 'FRENCH SOUTHERN TERRITORIES', 'ATF', 'TF');
INSERT INTO `country` VALUES (266, 'GABON', 'GAB', 'GA');
INSERT INTO `country` VALUES (270, 'GAMBIA', 'GMB', 'GM');
INSERT INTO `country` VALUES (268, 'GEORGIA', 'GEO', 'GE');
INSERT INTO `country` VALUES (276, 'GERMANY', 'DEU', 'DE');
INSERT INTO `country` VALUES (288, 'GHANA', 'GHA', 'GH');
INSERT INTO `country` VALUES (292, 'GIBRALTAR', 'GIB', 'GI');
INSERT INTO `country` VALUES (300, 'GREECE', 'GRC', 'GR');
INSERT INTO `country` VALUES (304, 'GREENLAND', 'GRL', 'GL');
INSERT INTO `country` VALUES (308, 'GRENADA', 'GRD', 'GD');
INSERT INTO `country` VALUES (312, 'GUADELOUPE', 'GLP', 'GP');
INSERT INTO `country` VALUES (316, 'GUAM', 'GUM', 'GU');
INSERT INTO `country` VALUES (320, 'GUATEMALA', 'GTM', 'GT');
INSERT INTO `country` VALUES (324, 'GUINEA', 'GIN', 'GN');
INSERT INTO `country` VALUES (624, 'GUINEA-BISSAU', 'GNB', 'GW');
INSERT INTO `country` VALUES (328, 'GUYANA', 'GUY', 'GY');
INSERT INTO `country` VALUES (332, 'HAITI', 'HTI', 'HT');
INSERT INTO `country` VALUES (334, 'HEARD AND MC DONALD ISLANDS', 'HMD', 'HM');
INSERT INTO `country` VALUES (336, 'HOLY SEE (VATICAN CITY STATE)', 'VAT', 'VA');
INSERT INTO `country` VALUES (340, 'HONDURAS', 'HND', 'HN');
INSERT INTO `country` VALUES (344, 'HONG KONG', 'HKG', 'HK');
INSERT INTO `country` VALUES (348, 'HUNGARY', 'HUN', 'HU');
INSERT INTO `country` VALUES (352, 'ICELAND', 'ISL', 'IS');
INSERT INTO `country` VALUES (356, 'INDIA', 'IND', 'IN');
INSERT INTO `country` VALUES (360, 'INDONESIA', 'IDN', 'ID');
INSERT INTO `country` VALUES (364, 'IRAN (ISLAMIC REPUBLIC OF)', 'IRN', 'IR');
INSERT INTO `country` VALUES (368, 'IRAQ', 'IRQ', 'IQ');
INSERT INTO `country` VALUES (372, 'IRELAND', 'IRL', 'IE');
INSERT INTO `country` VALUES (376, 'ISRAEL', 'ISR', 'IL');
INSERT INTO `country` VALUES (380, 'ITALY', 'ITA', 'IT');
INSERT INTO `country` VALUES (388, 'JAMAICA', 'JAM', 'JM');
INSERT INTO `country` VALUES (392, 'JAPAN', 'JPN', 'JP');
INSERT INTO `country` VALUES (400, 'JORDAN', 'JOR', 'JO');
INSERT INTO `country` VALUES (398, 'KAZAKHSTAN', 'KAZ', 'KZ');
INSERT INTO `country` VALUES (404, 'KENYA', 'KEN', 'KE');
INSERT INTO `country` VALUES (296, 'KIRIBATI', 'KIR', 'KI');
INSERT INTO `country` VALUES (408, 'KOREA, DEMOCRATIC PEOPLE\'S REPUBLIC OF', 'PRK', 'KP');
INSERT INTO `country` VALUES (410, 'KOREA, REPUBLIC OF', 'KOR', 'KR');
INSERT INTO `country` VALUES (414, 'KUWAIT', 'KWT', 'KW');
INSERT INTO `country` VALUES (417, 'KYRGYZSTAN', 'KGZ', 'KG');
INSERT INTO `country` VALUES (418, 'LAO PEOPLE\'S DEMOCRATIC REPUBLIC', 'LAO', 'LA');
INSERT INTO `country` VALUES (428, 'LATVIA', 'LVA', 'LV');
INSERT INTO `country` VALUES (422, 'LEBANON', 'LBN', 'LB');
INSERT INTO `country` VALUES (426, 'LESOTHO', 'LSO', 'LS');
INSERT INTO `country` VALUES (430, 'LIBERIA', 'LBR', 'LR');
INSERT INTO `country` VALUES (434, 'LIBYAN ARAB JAMAHIRIYA', 'LBY', 'LY');
INSERT INTO `country` VALUES (438, 'LIECHTENSTEIN', 'LIE', 'LI');
INSERT INTO `country` VALUES (440, 'LITHUANIA', 'LTU', 'LT');
INSERT INTO `country` VALUES (442, 'LUXEMBOURG', 'LUX', 'LU');
INSERT INTO `country` VALUES (446, 'MACAU', 'MAC', 'MO');
INSERT INTO `country` VALUES (807, 'MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF', 'MKD', 'MK');
INSERT INTO `country` VALUES (450, 'MADAGASCAR', 'MDG', 'MG');
INSERT INTO `country` VALUES (454, 'MALAWI', 'MWI', 'MW');
INSERT INTO `country` VALUES (458, 'MALAYSIA', 'MYS', 'MY');
INSERT INTO `country` VALUES (462, 'MALDIVES', 'MDV', 'MV');
INSERT INTO `country` VALUES (466, 'MALI', 'MLI', 'ML');
INSERT INTO `country` VALUES (470, 'MALTA', 'MLT', 'MT');
INSERT INTO `country` VALUES (584, 'MARSHALL ISLANDS', 'MHL', 'MH');
INSERT INTO `country` VALUES (474, 'MARTINIQUE', 'MTQ', 'MQ');
INSERT INTO `country` VALUES (478, 'MAURITANIA', 'MRT', 'MR');
INSERT INTO `country` VALUES (480, 'MAURITIUS', 'MUS', 'MU');
INSERT INTO `country` VALUES (175, 'MAYOTTE', 'MYT', 'YT');
INSERT INTO `country` VALUES (484, 'MEXICO', 'MEX', 'MX');
INSERT INTO `country` VALUES (583, 'MICRONESIA, FEDERATED STATES OF', 'FSM', 'FM');
INSERT INTO `country` VALUES (498, 'MOLDOVA, REPUBLIC OF', 'MDA', 'MD');
INSERT INTO `country` VALUES (492, 'MONACO', 'MCO', 'MC');
INSERT INTO `country` VALUES (496, 'MONGOLIA', 'MNG', 'MN');
INSERT INTO `country` VALUES (500, 'MONTSERRAT', 'MSR', 'MS');
INSERT INTO `country` VALUES (504, 'MOROCCO', 'MAR', 'MA');
INSERT INTO `country` VALUES (508, 'MOZAMBIQUE', 'MOZ', 'MZ');
INSERT INTO `country` VALUES (104, 'MYANMAR', 'MMR', 'MM');
INSERT INTO `country` VALUES (516, 'NAMIBIA', 'NAM', 'NA');
INSERT INTO `country` VALUES (520, 'NAURU', 'NRU', 'NR');
INSERT INTO `country` VALUES (524, 'NEPAL', 'NPL', 'NP');
INSERT INTO `country` VALUES (528, 'NETHERLANDS', 'NLD', 'NL');
INSERT INTO `country` VALUES (530, 'NETHERLANDS ANTILLES', 'ANT', 'AN');
INSERT INTO `country` VALUES (540, 'NEW CALEDONIA', 'NCL', 'NC');
INSERT INTO `country` VALUES (554, 'NEW ZEALAND', 'NZL', 'NZ');
INSERT INTO `country` VALUES (558, 'NICARAGUA', 'NIC', 'NI');
INSERT INTO `country` VALUES (562, 'NIGER', 'NER', 'NE');
INSERT INTO `country` VALUES (566, 'NIGERIA', 'NGA', 'NG');
INSERT INTO `country` VALUES (570, 'NIUE', 'NIU', 'NU');
INSERT INTO `country` VALUES (574, 'NORFOLK ISLAND', 'NFK', 'NF');
INSERT INTO `country` VALUES (580, 'NORTHERN MARIANA ISLANDS', 'MNP', 'MP');
INSERT INTO `country` VALUES (578, 'NORWAY', 'NOR', 'NO');
INSERT INTO `country` VALUES (512, 'OMAN', 'OMN', 'OM');
INSERT INTO `country` VALUES (586, 'PAKISTAN', 'PAK', 'PK');
INSERT INTO `country` VALUES (585, 'PALAU', 'PLW', 'PW');
INSERT INTO `country` VALUES (275, 'PALESTINIAN TERRITORY, OCCUPIED', '  P', '');
INSERT INTO `country` VALUES (591, 'PANAMA', 'PAN', 'PA');
INSERT INTO `country` VALUES (598, 'PAPUA NEW GUINEA', 'PNG', 'PG');
INSERT INTO `country` VALUES (600, 'PARAGUAY', 'PRY', 'PY');
INSERT INTO `country` VALUES (604, 'PERU', 'PER', 'PE');
INSERT INTO `country` VALUES (608, 'PHILIPPINES', 'PHL', 'PH');
INSERT INTO `country` VALUES (612, 'PITCAIRN', 'PCN', 'PN');
INSERT INTO `country` VALUES (616, 'POLAND', 'POL', 'PL');
INSERT INTO `country` VALUES (620, 'PORTUGAL', 'PRT', 'PT');
INSERT INTO `country` VALUES (630, 'PUERTO RICO', 'PRI', 'PR');
INSERT INTO `country` VALUES (634, 'QATAR', 'QAT', 'QA');
INSERT INTO `country` VALUES (638, 'REUNION', 'REU', 'RE');
INSERT INTO `country` VALUES (642, 'ROMANIA', 'ROM', 'RO');
INSERT INTO `country` VALUES (643, 'RUSSIAN FEDERATION', 'RUS', 'RU');
INSERT INTO `country` VALUES (646, 'RWANDA', 'RWA', 'RW');
INSERT INTO `country` VALUES (659, 'SAINT KITTS AND NEVIS', 'KNA', 'KN');
INSERT INTO `country` VALUES (662, 'SAINT LUCIA', 'LCA', 'LC');
INSERT INTO `country` VALUES (670, 'SAINT VINCENT AND THE GRENADINES', 'VCT', 'VC');
INSERT INTO `country` VALUES (882, 'SAMOA', 'WSM', 'WS');
INSERT INTO `country` VALUES (674, 'SAN MARINO', 'SMR', 'SM');
INSERT INTO `country` VALUES (678, 'SAO TOME AND PRINCIPE', 'STP', 'ST');
INSERT INTO `country` VALUES (682, 'SAUDI ARABIA', 'SAU', 'SA');
INSERT INTO `country` VALUES (686, 'SENEGAL', 'SEN', 'SN');
INSERT INTO `country` VALUES (690, 'SEYCHELLES', 'SYC', 'SC');
INSERT INTO `country` VALUES (694, 'SIERRA LEONE', 'SLE', 'SL');
INSERT INTO `country` VALUES (702, 'SINGAPORE', 'SGP', 'SG');
INSERT INTO `country` VALUES (703, 'SLOVAKIA (Slovak Republic)', 'SVK', 'SK');
INSERT INTO `country` VALUES (705, 'SLOVENIA', 'SVN', 'SI');
INSERT INTO `country` VALUES (90, 'SOLOMON ISLANDS', 'SLB', 'SB');
INSERT INTO `country` VALUES (706, 'SOMALIA', 'SOM', 'SO');
INSERT INTO `country` VALUES (710, 'SOUTH AFRICA', 'ZAF', 'ZA');
INSERT INTO `country` VALUES (239, 'SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS', 'SGS', 'GS');
INSERT INTO `country` VALUES (724, 'SPAIN', 'ESP', 'ES');
INSERT INTO `country` VALUES (144, 'SRI LANKA', 'LKA', 'LK');
INSERT INTO `country` VALUES (654, 'ST. HELENA', 'SHN', 'SH');
INSERT INTO `country` VALUES (666, 'ST. PIERRE AND MIQUELON', 'SPM', 'PM');
INSERT INTO `country` VALUES (736, 'SUDAN', 'SDN', 'SD');
INSERT INTO `country` VALUES (740, 'SURINAME', 'SUR', 'SR');
INSERT INTO `country` VALUES (744, 'SVALBARD AND JAN MAYEN ISLANDS', 'SJM', 'SJ');
INSERT INTO `country` VALUES (748, 'SWAZILAND', 'SWZ', 'SZ');
INSERT INTO `country` VALUES (752, 'SWEDEN', 'SWE', 'SE');
INSERT INTO `country` VALUES (756, 'SWITZERLAND', 'CHE', 'CH');
INSERT INTO `country` VALUES (760, 'SYRIAN ARAB REPUBLIC', 'SYR', 'SY');
INSERT INTO `country` VALUES (158, 'TAIWAN, PROVINCE OF CHINA', 'TWN', 'TW');
INSERT INTO `country` VALUES (762, 'TAJIKISTAN', 'TJK', 'TJ');
INSERT INTO `country` VALUES (834, 'TANZANIA, UNITED REPUBLIC OF', 'TZA', 'TZ');
INSERT INTO `country` VALUES (764, 'THAILAND', 'THA', 'TH');
INSERT INTO `country` VALUES (768, 'TOGO', 'TGO', 'TG');
INSERT INTO `country` VALUES (772, 'TOKELAU', 'TKL', 'TK');
INSERT INTO `country` VALUES (776, 'TONGA', 'TON', 'TO');
INSERT INTO `country` VALUES (780, 'TRINIDAD AND TOBAGO', 'TTO', 'TT');
INSERT INTO `country` VALUES (788, 'TUNISIA', 'TUN', 'TN');
INSERT INTO `country` VALUES (792, 'TURKEY', 'TUR', 'TR');
INSERT INTO `country` VALUES (795, 'TURKMENISTAN', 'TKM', 'TM');
INSERT INTO `country` VALUES (796, 'TURKS AND CAICOS ISLANDS', 'TCA', 'TC');
INSERT INTO `country` VALUES (798, 'TUVALU', 'TUV', 'TV');
INSERT INTO `country` VALUES (800, 'UGANDA', 'UGA', 'UG');
INSERT INTO `country` VALUES (804, 'UKRAINE', 'UKR', 'UA');
INSERT INTO `country` VALUES (784, 'UNITED ARAB EMIRATES', 'ARE', 'AE');
INSERT INTO `country` VALUES (826, 'UNITED KINGDOM', 'GBR', 'GB');
INSERT INTO `country` VALUES (840, 'UNITED STATES', 'USA', 'US');
INSERT INTO `country` VALUES (581, 'UNITED STATES MINOR OUTLYING ISLANDS', 'UMI', 'UM');
INSERT INTO `country` VALUES (858, 'URUGUAY', 'URY', 'UY');
INSERT INTO `country` VALUES (860, 'UZBEKISTAN', 'UZB', 'UZ');
INSERT INTO `country` VALUES (548, 'VANUATU', 'VUT', 'VU');
INSERT INTO `country` VALUES (862, 'VENEZUELA', 'VEN', 'VE');
INSERT INTO `country` VALUES (704, 'VIET NAM', 'VNM', 'VN');
INSERT INTO `country` VALUES (92, 'VIRGIN ISLANDS (BRITISH)', 'VGB', 'VG');
INSERT INTO `country` VALUES (850, 'VIRGIN ISLANDS (U.S.)', 'VIR', 'VI');
INSERT INTO `country` VALUES (876, 'WALLIS AND FUTUNA ISLANDS', 'WLF', 'WF');
INSERT INTO `country` VALUES (732, 'WESTERN SAHARA', 'ESH', 'EH');
INSERT INTO `country` VALUES (887, 'YEMEN', 'YEM', 'YE');
INSERT INTO `country` VALUES (891, 'YUGOSLAVIA', 'YUG', 'YU');
INSERT INTO `country` VALUES (894, 'ZAMBIA', 'ZMB', 'ZM');
INSERT INTO `country` VALUES (716, 'ZIMBABWE', 'ZWE', 'ZW');

# --------------------------------------------------------

#
# Table structure for table `csv`
#

CREATE TABLE `csv` (
  `csv_product_sku` int(2) default NULL,
  `csv_product_s_desc` int(2) default NULL,
  `csv_product_desc` int(2) default NULL,
  `csv_product_thumb_image` int(2) default NULL,
  `csv_product_full_image` int(2) default NULL,
  `csv_product_weight` int(2) default NULL,
  `csv_product_weight_uom` int(2) default NULL,
  `csv_product_length` int(2) default NULL,
  `csv_product_width` int(2) default NULL,
  `csv_product_height` int(2) default NULL,
  `csv_product_lwh_uom` int(2) default NULL,
  `csv_product_in_stock` int(2) default NULL,
  `csv_product_available_date` int(2) default NULL,
  `csv_product_special` int(2) default NULL,
  `csv_product_discount_id` int(2) default NULL,
  `csv_product_name` int(2) default NULL,
  `csv_product_price` int(2) default NULL,
  `csv_category_path` int(2) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `csv`
#

INSERT INTO `csv` VALUES (4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 24, 25, 26);

# --------------------------------------------------------

#
# Table structure for table `currency`
#

CREATE TABLE `currency` (
  `currency_id` int(11) NOT NULL auto_increment,
  `currency_name` varchar(64) default NULL,
  `currency_code` char(3) default NULL,
  PRIMARY KEY  (`currency_id`)
) TYPE=MyISAM AUTO_INCREMENT=157 ;

#
# Dumping data for table `currency`
#

INSERT INTO `currency` VALUES (1, 'Andorran Peseta', 'ADP');
INSERT INTO `currency` VALUES (2, 'United Arab Emirates Dirham', 'AED');
INSERT INTO `currency` VALUES (3, 'Afghanistan Afghani', 'AFA');
INSERT INTO `currency` VALUES (4, 'Albanian Lek', 'ALL');
INSERT INTO `currency` VALUES (5, 'Netherlands Antillian Guilder', 'ANG');
INSERT INTO `currency` VALUES (6, 'Angolan Kwanza', 'AOK');
INSERT INTO `currency` VALUES (7, 'Argentinian Austral', 'ARA');
INSERT INTO `currency` VALUES (8, 'Austrian Schilling', 'ATS');
INSERT INTO `currency` VALUES (9, 'Australian Dollar', 'AUD');
INSERT INTO `currency` VALUES (10, 'Aruban Florin', 'AWG');
INSERT INTO `currency` VALUES (11, 'Barbados Dollar', 'BBD');
INSERT INTO `currency` VALUES (12, 'Bangladeshi Taka', 'BDT');
INSERT INTO `currency` VALUES (13, 'Belgian Franc', 'BEF');
INSERT INTO `currency` VALUES (14, 'Bulgarian Lev', 'BGL');
INSERT INTO `currency` VALUES (15, 'Bahraini Dinar', 'BHD');
INSERT INTO `currency` VALUES (16, 'Burundi Franc', 'BIF');
INSERT INTO `currency` VALUES (17, 'Bermudian Dollar', 'BMD');
INSERT INTO `currency` VALUES (18, 'Brunei Dollar', 'BND');
INSERT INTO `currency` VALUES (19, 'Bolivian Boliviano', 'BOB');
INSERT INTO `currency` VALUES (20, 'Brazilian Cruzeiro', 'BRC');
INSERT INTO `currency` VALUES (21, 'Bahamian Dollar', 'BSD');
INSERT INTO `currency` VALUES (22, 'Bhutan Ngultrum', 'BTN');
INSERT INTO `currency` VALUES (23, 'Burma Kyat', 'BUK');
INSERT INTO `currency` VALUES (24, 'Botswanian Pula', 'BWP');
INSERT INTO `currency` VALUES (25, 'Belize Dollar', 'BZD');
INSERT INTO `currency` VALUES (26, 'Canadian Dollar', 'CAD');
INSERT INTO `currency` VALUES (27, 'Swiss Franc', 'CHF');
INSERT INTO `currency` VALUES (28, 'Chilean Unidades de Fomento', 'CLF');
INSERT INTO `currency` VALUES (29, 'Chilean Peso', 'CLP');
INSERT INTO `currency` VALUES (30, 'Yuan (Chinese) Renminbi', 'CNY');
INSERT INTO `currency` VALUES (31, 'Colombian Peso', 'COP');
INSERT INTO `currency` VALUES (32, 'Costa Rican Colon', 'CRC');
INSERT INTO `currency` VALUES (33, 'Czech Koruna', 'CSK');
INSERT INTO `currency` VALUES (34, 'Cuban Peso', 'CUP');
INSERT INTO `currency` VALUES (35, 'Cape Verde Escudo', 'CVE');
INSERT INTO `currency` VALUES (36, 'Cyprus Pound', 'CYP');
INSERT INTO `currency` VALUES (37, 'East German Mark (DDR)', 'DDM');
INSERT INTO `currency` VALUES (38, 'Deutsche Mark', 'DEM');
INSERT INTO `currency` VALUES (39, 'Djibouti Franc', 'DJF');
INSERT INTO `currency` VALUES (40, 'Danish Krone', 'DKK');
INSERT INTO `currency` VALUES (41, 'Dominican Peso', 'DOP');
INSERT INTO `currency` VALUES (42, 'Algerian Dinar', 'DZD');
INSERT INTO `currency` VALUES (43, 'Ecuador Sucre', 'ECS');
INSERT INTO `currency` VALUES (44, 'Egyptian Pound', 'EGP');
INSERT INTO `currency` VALUES (45, 'Spanish Peseta', 'ESP');
INSERT INTO `currency` VALUES (46, 'Ethiopian Birr', 'ETB');
INSERT INTO `currency` VALUES (47, 'Euro', 'EUR');
INSERT INTO `currency` VALUES (48, 'Finnish Markka', 'FIM');
INSERT INTO `currency` VALUES (49, 'Fiji Dollar', 'FJD');
INSERT INTO `currency` VALUES (50, 'Falkland Islands Pound', 'FKP');
INSERT INTO `currency` VALUES (51, 'French Franc', 'FRF');
INSERT INTO `currency` VALUES (52, 'British Pound', 'GBP');
INSERT INTO `currency` VALUES (53, 'Ghanaian Cedi', 'GHC');
INSERT INTO `currency` VALUES (54, 'Gibraltar Pound', 'GIP');
INSERT INTO `currency` VALUES (55, 'Gambian Dalasi', 'GMD');
INSERT INTO `currency` VALUES (56, 'Guinea Franc', 'GNF');
INSERT INTO `currency` VALUES (57, 'Greek Drachma', 'GRD');
INSERT INTO `currency` VALUES (58, 'Guatemalan Quetzal', 'GTQ');
INSERT INTO `currency` VALUES (59, 'Guinea-Bissau Peso', 'GWP');
INSERT INTO `currency` VALUES (60, 'Guyanan Dollar', 'GYD');
INSERT INTO `currency` VALUES (61, 'Hong Kong Dollar', 'HKD');
INSERT INTO `currency` VALUES (62, 'Honduran Lempira', 'HNL');
INSERT INTO `currency` VALUES (63, 'Haitian Gourde', 'HTG');
INSERT INTO `currency` VALUES (64, 'Hungarian Forint', 'HUF');
INSERT INTO `currency` VALUES (65, 'Indonesian Rupiah', 'IDR');
INSERT INTO `currency` VALUES (66, 'Irish Punt', 'IEP');
INSERT INTO `currency` VALUES (67, 'Israeli Shekel', 'ILS');
INSERT INTO `currency` VALUES (68, 'Indian Rupee', 'INR');
INSERT INTO `currency` VALUES (69, 'Iraqi Dinar', 'IQD');
INSERT INTO `currency` VALUES (70, 'Iranian Rial', 'IRR');
INSERT INTO `currency` VALUES (71, 'Iceland Krona', 'ISK');
INSERT INTO `currency` VALUES (72, 'Italian Lira', 'ITL');
INSERT INTO `currency` VALUES (73, 'Jamaican Dollar', 'JMD');
INSERT INTO `currency` VALUES (74, 'Jordanian Dinar', 'JOD');
INSERT INTO `currency` VALUES (75, 'Japanese Yen', 'JPY');
INSERT INTO `currency` VALUES (76, 'Kenyan Schilling', 'KES');
INSERT INTO `currency` VALUES (77, 'Kampuchean (Cambodian) Riel', 'KHR');
INSERT INTO `currency` VALUES (78, 'Comoros Franc', 'KMF');
INSERT INTO `currency` VALUES (79, 'North Korean Won', 'KPW');
INSERT INTO `currency` VALUES (80, '(South) Korean Won', 'KRW');
INSERT INTO `currency` VALUES (81, 'Kuwaiti Dinar', 'KWD');
INSERT INTO `currency` VALUES (82, 'Cayman Islands Dollar', 'KYD');
INSERT INTO `currency` VALUES (83, 'Lao Kip', 'LAK');
INSERT INTO `currency` VALUES (84, 'Lebanese Pound', 'LBP');
INSERT INTO `currency` VALUES (85, 'Sri Lanka Rupee', 'LKR');
INSERT INTO `currency` VALUES (86, 'Liberian Dollar', 'LRD');
INSERT INTO `currency` VALUES (87, 'Lesotho Loti', 'LSL');
INSERT INTO `currency` VALUES (88, 'Luxembourg Franc', 'LUF');
INSERT INTO `currency` VALUES (89, 'Libyan Dinar', 'LYD');
INSERT INTO `currency` VALUES (90, 'Moroccan Dirham', 'MAD');
INSERT INTO `currency` VALUES (91, 'Malagasy Franc', 'MGF');
INSERT INTO `currency` VALUES (92, 'Mongolian Tugrik', 'MNT');
INSERT INTO `currency` VALUES (93, 'Macau Pataca', 'MOP');
INSERT INTO `currency` VALUES (94, 'Mauritanian Ouguiya', 'MRO');
INSERT INTO `currency` VALUES (95, 'Maltese Lira', 'MTL');
INSERT INTO `currency` VALUES (96, 'Mauritius Rupee', 'MUR');
INSERT INTO `currency` VALUES (97, 'Maldive Rufiyaa', 'MVR');
INSERT INTO `currency` VALUES (98, 'Malawi Kwacha', 'MWK');
INSERT INTO `currency` VALUES (99, 'Mexican Peso', 'MXP');
INSERT INTO `currency` VALUES (100, 'Malaysian Ringgit', 'MYR');
INSERT INTO `currency` VALUES (101, 'Mozambique Metical', 'MZM');
INSERT INTO `currency` VALUES (102, 'Nigerian Naira', 'NGN');
INSERT INTO `currency` VALUES (103, 'Nicaraguan Cordoba', 'NIC');
INSERT INTO `currency` VALUES (104, 'Dutch Guilder', 'NLG');
INSERT INTO `currency` VALUES (105, 'Norwegian Kroner', 'NOK');
INSERT INTO `currency` VALUES (106, 'Nepalese Rupee', 'NPR');
INSERT INTO `currency` VALUES (107, 'New Zealand Dollar', 'NZD');
INSERT INTO `currency` VALUES (108, 'Omani Rial', 'OMR');
INSERT INTO `currency` VALUES (109, 'Panamanian Balboa', 'PAB');
INSERT INTO `currency` VALUES (110, 'Peruvian Inti', 'PEI');
INSERT INTO `currency` VALUES (111, 'Papua New Guinea Kina', 'PGK');
INSERT INTO `currency` VALUES (112, 'Philippine Peso', 'PHP');
INSERT INTO `currency` VALUES (113, 'Pakistan Rupee', 'PKR');
INSERT INTO `currency` VALUES (114, 'Polish Zloty', 'PLZ');
INSERT INTO `currency` VALUES (115, 'Portuguese Escudo', 'PTE');
INSERT INTO `currency` VALUES (116, 'Paraguay Guarani', 'PYG');
INSERT INTO `currency` VALUES (117, 'Qatari Rial', 'QAR');
INSERT INTO `currency` VALUES (118, 'Romanian Leu', 'ROL');
INSERT INTO `currency` VALUES (119, 'Rwanda Franc', 'RWF');
INSERT INTO `currency` VALUES (120, 'Saudi Arabian Riyal', 'SAR');
INSERT INTO `currency` VALUES (121, 'Solomon Islands Dollar', 'SBD');
INSERT INTO `currency` VALUES (122, 'Seychelles Rupee', 'SCR');
INSERT INTO `currency` VALUES (123, 'Sudanese Pound', 'SDP');
INSERT INTO `currency` VALUES (124, 'Swedish Krona', 'SEK');
INSERT INTO `currency` VALUES (125, 'Singapore Dollar', 'SGD');
INSERT INTO `currency` VALUES (126, 'St. Helena Pound', 'SHP');
INSERT INTO `currency` VALUES (127, 'Sierra Leone Leone', 'SLL');
INSERT INTO `currency` VALUES (128, 'Somali Schilling', 'SOS');
INSERT INTO `currency` VALUES (129, 'Suriname Guilder', 'SRG');
INSERT INTO `currency` VALUES (130, 'Sao Tome and Principe Dobra', 'STD');
INSERT INTO `currency` VALUES (131, 'USSR Rouble', 'SUR');
INSERT INTO `currency` VALUES (132, 'El Salvador Colon', 'SVC');
INSERT INTO `currency` VALUES (133, 'Syrian Potmd', 'SYP');
INSERT INTO `currency` VALUES (134, 'Swaziland Lilangeni', 'SZL');
INSERT INTO `currency` VALUES (135, 'Thai Bhat', 'THB');
INSERT INTO `currency` VALUES (136, 'Tunisian Dinar', 'TND');
INSERT INTO `currency` VALUES (137, 'Tongan Pa\'anga', 'TOP');
INSERT INTO `currency` VALUES (138, 'East Timor Escudo', 'TPE');
INSERT INTO `currency` VALUES (139, 'Turkish Lira', 'TRL');
INSERT INTO `currency` VALUES (140, 'Trinidad and Tobago Dollar', 'TTD');
INSERT INTO `currency` VALUES (141, 'Taiwan Dollar', 'TWD');
INSERT INTO `currency` VALUES (142, 'Tanzanian Schilling', 'TZS');
INSERT INTO `currency` VALUES (143, 'Uganda Shilling', 'UGS');
INSERT INTO `currency` VALUES (144, 'US Dollar', 'USD');
INSERT INTO `currency` VALUES (145, 'Uruguayan Peso', 'UYP');
INSERT INTO `currency` VALUES (146, 'Venezualan Bolivar', 'VEB');
INSERT INTO `currency` VALUES (147, 'Vietnamese Dong', 'VND');
INSERT INTO `currency` VALUES (148, 'Vanuatu Vatu', 'VUV');
INSERT INTO `currency` VALUES (149, 'Samoan Tala', 'WST');
INSERT INTO `currency` VALUES (150, 'Democratic Yemeni Dinar', 'YDD');
INSERT INTO `currency` VALUES (151, 'Yemeni Rial', 'YER');
INSERT INTO `currency` VALUES (152, 'New Yugoslavia Dinar', 'YUD');
INSERT INTO `currency` VALUES (153, 'South African Rand', 'ZAR');
INSERT INTO `currency` VALUES (154, 'Zambian Kwacha', 'ZMK');
INSERT INTO `currency` VALUES (155, 'Zaire Zaire', 'ZRZ');
INSERT INTO `currency` VALUES (156, 'Zimbabwe Dollar', 'ZWD');

# --------------------------------------------------------

#
# Table structure for table `function`
#

CREATE TABLE `function` (
  `function_id` int(11) NOT NULL auto_increment,
  `module_id` int(11) default NULL,
  `function_name` varchar(32) default NULL,
  `function_class` varchar(32) default NULL,
  `function_method` varchar(32) default NULL,
  `function_description` text,
  `function_perms` varchar(255) default NULL,
  PRIMARY KEY  (`function_id`)
) TYPE=MyISAM AUTO_INCREMENT=69 ;

#
# Dumping data for table `function`
#

INSERT INTO `function` VALUES (1, 1, 'userAdd', 'ps_user', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (2, 1, 'userDelete', 'ps_user', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (3, 1, 'userUpdate', 'ps_user', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (4, 1, 'adminPasswdUpdate', 'ps_user', 'update_admin_passwd', 'Updates Site Adminnistrator Password', 'admin');
INSERT INTO `function` VALUES (31, 2, 'productAdd', 'ps_product', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (6, 1, 'functionAdd', 'ps_function', 'add', '', 'admin');
INSERT INTO `function` VALUES (7, 1, 'functionUpdate', 'ps_function', 'update', '', 'admin');
INSERT INTO `function` VALUES (8, 1, 'functionDelete', 'ps_function', 'delete', '', 'admin');
INSERT INTO `function` VALUES (9, 1, 'userLogout', 'ps_user', 'logout', '', 'none');
INSERT INTO `function` VALUES (10, 1, 'userAddressAdd', 'ps_user_address', 'add', '', 'admin,storeadmin,shopper');
INSERT INTO `function` VALUES (11, 1, 'userAddressUpdate', 'ps_user_address', 'update', '', 'admin,storeadmin,shopper');
INSERT INTO `function` VALUES (12, 1, 'userAddressDelete', 'ps_user_address', 'delete', '', 'admin,storeadmin,shopper');
INSERT INTO `function` VALUES (13, 1, 'moduleAdd', 'ps_module', 'add', '', 'admin');
INSERT INTO `function` VALUES (14, 1, 'moduleUpdate', 'ps_module', 'update', '', 'admin');
INSERT INTO `function` VALUES (15, 1, 'moduleDelete', 'ps_module', 'delete', '', 'admin');
INSERT INTO `function` VALUES (16, 1, 'userLogin', 'ps_user', 'login', '', 'none');
INSERT INTO `function` VALUES (17, 3, 'vendorAdd', 'ps_vendor', 'add', '', 'admin');
INSERT INTO `function` VALUES (18, 3, 'vendorUpdate', 'ps_vendor', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (19, 3, 'vendorDelete', 'ps_vendor', 'delete', '', 'admin');
INSERT INTO `function` VALUES (20, 3, 'vendorCategoryAdd', 'ps_vendor_category', 'add', '', 'admin');
INSERT INTO `function` VALUES (21, 3, 'vendorCategoryUpdate', 'ps_vendor_category', 'update', '', 'admin');
INSERT INTO `function` VALUES (22, 3, 'vendorCategoryDelete', 'ps_vendor_category', 'delete', '', 'admin');
INSERT INTO `function` VALUES (23, 4, 'shopperAdd', 'ps_shopper', 'add', '', 'none');
INSERT INTO `function` VALUES (24, 4, 'shopperDelete', 'ps_shopper', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (25, 4, 'shopperUpdate', 'ps_shopper', 'update', '', 'admin,storeadmin,shopper');
INSERT INTO `function` VALUES (26, 4, 'shopperGroupAdd', 'ps_shopper_group', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (27, 4, 'shopperGroupUpdate', 'ps_shopper_group', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (28, 4, 'shopperGroupDelete', 'ps_shopper_group', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (29, 5, 'orderSearch', 'ps_order', 'find', '', 'admin,storeadmin,demo');
INSERT INTO `function` VALUES (30, 5, 'orderStatusSet', 'ps_order', 'order_status_update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (32, 2, 'productDelete', 'ps_product', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (33, 2, 'productUpdate', 'ps_product', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (34, 2, 'productCategoryAdd', 'ps_product_category', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (35, 2, 'productCategoryUpdate', 'ps_product_category', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (36, 2, 'productCategoryDelete', 'ps_product_category', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (37, 2, 'productPriceAdd', 'ps_product_price', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (38, 2, 'productPriceUpdate', 'ps_product_price', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (39, 2, 'productPriceDelete', 'ps_product_price', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (40, 2, 'productAttributeAdd', 'ps_product_attribute', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (41, 2, 'productAttributeUpdate', 'ps_product_attribute', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (42, 2, 'productAttributeDelete', 'ps_product_attribute', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (43, 7, 'cartAdd', 'ps_cart', 'add', '', 'none');
INSERT INTO `function` VALUES (44, 7, 'cartUpdate', 'ps_cart', 'update', '', 'none');
INSERT INTO `function` VALUES (45, 7, 'cartDelete', 'ps_cart', 'delete', '', 'none');
INSERT INTO `function` VALUES (46, 10, 'checkoutComplete', 'ps_checkout', 'add', '', 'shopper,storeadmin,admin,demo');
INSERT INTO `function` VALUES (47, 1, 'setLanguage', 'ps_module', 'set_language', '', 'none');
INSERT INTO `function` VALUES (48, 8, 'paymentMethodUpdate', 'ps_payment_method', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (49, 8, 'paymentMethodAdd', 'ps_payment_method', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (50, 8, 'paymentMethodDelete', 'ps_payment_method', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (51, 5, 'orderDelete', 'ps_order', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (52, 11, 'addTaxRate', 'ps_tax', 'add', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (53, 11, 'updateTaxRate', 'ps_tax', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (54, 11, 'deleteTaxRate', 'ps_tax', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (57, 12837, 'shipQuote', 'ps_intershipper', 'fetch_quote', '', 'admin,storeadmin,demo,shopper');
INSERT INTO `function` VALUES (55, 10, 'checkoutValidateST', 'ps_checkout', 'validate_shipto', '', 'none');
INSERT INTO `function` VALUES (56, 12837, 'shipUpdate', 'ps_intershipper', 'update', 'Updates shipping methods with shipping form changes.', 'admin,storeadmin');
INSERT INTO `function` VALUES (58, 12837, 'shipRefresh', 'ps_intershipper', 'refresh', 'Deletes database of shipping methods and restores it with the latest available shipping methods from InterShipper.', 'admin');
INSERT INTO `function` VALUES (59, 5, 'orderStatusUpdate', 'ps_order_status', 'update', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (60, 5, 'orderStatusAdd', 'ps_order_status', 'add', '', 'storeadmin,admin');
INSERT INTO `function` VALUES (61, 5, 'orderStatusDelete', 'ps_order_status', 'delete', '', 'admin,storeadmin');
INSERT INTO `function` VALUES (62, 12838, 'addzone', 'ps_zone', 'add', 'This will add a zone.', 'admin,storeadmin');
INSERT INTO `function` VALUES (63, 12838, 'updatezone', 'ps_zone', 'update', 'This updates a zone.', 'admin,storeadmin');
INSERT INTO `function` VALUES (64, 12838, 'deletezone', 'ps_zone', 'delete', 'Deletes a zone.', 'admin,storeadmin');
INSERT INTO `function` VALUES (65, 12838, 'zoneassign', 'ps_zone', 'assign', 'This will assign a country to a zone.', 'admin,storeadmin');
INSERT INTO `function` VALUES (66, 1, 'sendLostPassword', 'ps_user', 'send_lost_password', 'Generates a new password and sends an email to the user for confirmation of the changes.', 'none');
INSERT INTO `function` VALUES (67, 1, 'resetLostPassword', 'ps_user', 'reset_lost_password', 'Resets a new password once a user responds to the confirmation.', 'none');
INSERT INTO `function` VALUES (68, 2, 'product_csv', 'ps_csv', 'upload_csv', 'Imports a CSV formatted file of product data.', 'admin,storeadmin');

# --------------------------------------------------------

# --------------------------------------------------------

#
# Table structure for table `language`
#

CREATE TABLE `language` (
  `language_id` int(11) NOT NULL auto_increment,
  `language_name` varchar(64) default NULL,
  `language_code` char(3) default NULL,
  PRIMARY KEY  (`language_id`)
) TYPE=MyISAM AUTO_INCREMENT=411 ;

#
# Dumping data for table `language`
#

INSERT INTO `language` VALUES (1, 'Afar', 'aar');
INSERT INTO `language` VALUES (2, 'Abkhazian', 'abk');
INSERT INTO `language` VALUES (3, 'Achinese', 'ace');
INSERT INTO `language` VALUES (4, 'Acoli', 'ach');
INSERT INTO `language` VALUES (5, 'Adangme', 'ada');
INSERT INTO `language` VALUES (6, 'Afro-Asiatic (Other)', 'afa');
INSERT INTO `language` VALUES (7, 'Afrihili', 'afh');
INSERT INTO `language` VALUES (8, 'Africaans', 'afr');
INSERT INTO `language` VALUES (9, 'Aljamia', 'ajm');
INSERT INTO `language` VALUES (10, 'Akan', 'aka');
INSERT INTO `language` VALUES (11, 'Akkadian', 'akk');
INSERT INTO `language` VALUES (12, 'Albanian', 'alb');
INSERT INTO `language` VALUES (13, 'Albanian2', 'sqi');
INSERT INTO `language` VALUES (14, 'Aleut', 'ale');
INSERT INTO `language` VALUES (15, 'Algonquian languages', 'alg');
INSERT INTO `language` VALUES (16, 'Amharic', 'amh');
INSERT INTO `language` VALUES (17, 'English, Old (ca. 450-1100)', 'ang');
INSERT INTO `language` VALUES (18, 'Apache languages', 'apa');
INSERT INTO `language` VALUES (19, 'Arabic', 'ara');
INSERT INTO `language` VALUES (20, 'Aramaic', 'arc');
INSERT INTO `language` VALUES (21, 'Armenian', 'arm');
INSERT INTO `language` VALUES (22, 'Armenian2', 'hye');
INSERT INTO `language` VALUES (23, 'Araucanian', 'arn');
INSERT INTO `language` VALUES (24, 'Arapaho', 'arp');
INSERT INTO `language` VALUES (25, 'Artificial (Other)', 'art');
INSERT INTO `language` VALUES (26, 'Arawak', 'arw');
INSERT INTO `language` VALUES (27, 'Assamese', 'asm');
INSERT INTO `language` VALUES (28, 'Athapascan languages', 'ath');
INSERT INTO `language` VALUES (29, 'Avaric', 'ava');
INSERT INTO `language` VALUES (30, 'Avestan', 'ave');
INSERT INTO `language` VALUES (31, 'Awandhi', 'awa');
INSERT INTO `language` VALUES (32, 'Aymara', 'aym');
INSERT INTO `language` VALUES (33, 'Azerbaijani', 'aze');
INSERT INTO `language` VALUES (34, 'Banda', 'bad');
INSERT INTO `language` VALUES (35, 'Bamileke languages', 'bai');
INSERT INTO `language` VALUES (36, 'Bashkir', 'bak');
INSERT INTO `language` VALUES (37, 'Baluchi', 'bal');
INSERT INTO `language` VALUES (38, 'Bambara', 'bam');
INSERT INTO `language` VALUES (39, 'Balinese', 'ban');
INSERT INTO `language` VALUES (40, 'Basque', 'baq');
INSERT INTO `language` VALUES (41, 'Basque2', 'eus');
INSERT INTO `language` VALUES (42, 'Basa', 'bas');
INSERT INTO `language` VALUES (43, 'Baltic (Other)', 'bat');
INSERT INTO `language` VALUES (44, 'Beja', 'bej');
INSERT INTO `language` VALUES (45, 'Byelorussian', 'bel');
INSERT INTO `language` VALUES (46, 'Bemba', 'bem');
INSERT INTO `language` VALUES (47, 'Bengali', 'ben');
INSERT INTO `language` VALUES (48, 'Berber languages', 'ber');
INSERT INTO `language` VALUES (49, 'Bhojpuri', 'bho');
INSERT INTO `language` VALUES (50, 'Bihari', 'bih');
INSERT INTO `language` VALUES (51, 'Bikol', 'bik');
INSERT INTO `language` VALUES (52, 'Bini', 'bin');
INSERT INTO `language` VALUES (53, 'Bislama', 'bis');
INSERT INTO `language` VALUES (54, 'Siksika', 'bla');
INSERT INTO `language` VALUES (55, 'Tibetan', 'bod');
INSERT INTO `language` VALUES (56, 'Tibetan2', 'tib');
INSERT INTO `language` VALUES (57, 'Braj', 'bra');
INSERT INTO `language` VALUES (58, 'Breton', 'bre');
INSERT INTO `language` VALUES (59, 'Buginese', 'bug');
INSERT INTO `language` VALUES (60, 'Bulgarian', 'bul');
INSERT INTO `language` VALUES (61, 'Burmese', 'bur');
INSERT INTO `language` VALUES (62, 'Burmese', 'mya');
INSERT INTO `language` VALUES (63, 'Caddo', 'cad');
INSERT INTO `language` VALUES (64, 'Central American Indian (Other)', 'cai');
INSERT INTO `language` VALUES (65, 'Carib', 'car');
INSERT INTO `language` VALUES (66, 'Catalan', 'cat');
INSERT INTO `language` VALUES (67, 'Caucasian (Other)', 'cau');
INSERT INTO `language` VALUES (68, 'Cebuano', 'ceb');
INSERT INTO `language` VALUES (69, 'Celtic (Other)', 'cel');
INSERT INTO `language` VALUES (70, 'Czeck', 'ces');
INSERT INTO `language` VALUES (71, 'Czeck2', 'cze');
INSERT INTO `language` VALUES (72, 'Chamorro', 'cha');
INSERT INTO `language` VALUES (73, 'Chibcha', 'chb');
INSERT INTO `language` VALUES (74, 'Chechen', 'che');
INSERT INTO `language` VALUES (75, 'Chagatai', 'chg');
INSERT INTO `language` VALUES (76, 'Chinese', 'chi');
INSERT INTO `language` VALUES (77, 'Chinese2', 'zho');
INSERT INTO `language` VALUES (78, 'Chinook jargon', 'chn');
INSERT INTO `language` VALUES (79, 'Choctaw', 'cho');
INSERT INTO `language` VALUES (80, 'Cherokee', 'chr');
INSERT INTO `language` VALUES (81, 'Church Slavic', 'chu');
INSERT INTO `language` VALUES (82, 'Chuvash', 'chv');
INSERT INTO `language` VALUES (83, 'Cheyenne', 'chy');
INSERT INTO `language` VALUES (84, 'Coptic', 'cop');
INSERT INTO `language` VALUES (85, 'Cornish', 'cor');
INSERT INTO `language` VALUES (86, 'Corsican', 'cos');
INSERT INTO `language` VALUES (87, 'Creoles and pidgins, English-based (Other)', 'cpe');
INSERT INTO `language` VALUES (88, 'Creoles and pidgins, French-based (Other)', 'cpf');
INSERT INTO `language` VALUES (89, 'Creoles and pidgins, Portuguese-based (Other)', 'cpp');
INSERT INTO `language` VALUES (90, 'Cree', 'cre');
INSERT INTO `language` VALUES (91, 'Creoles and pidgins (Other)', 'crp');
INSERT INTO `language` VALUES (92, 'Cushitic (Other)', 'cus');
INSERT INTO `language` VALUES (93, 'Welsh', 'cym');
INSERT INTO `language` VALUES (94, 'Welsh2', 'wel');
INSERT INTO `language` VALUES (95, 'Dakota', 'dak');
INSERT INTO `language` VALUES (96, 'Danish', 'dan');
INSERT INTO `language` VALUES (97, 'Delaware', 'del');
INSERT INTO `language` VALUES (98, 'German', 'deu');
INSERT INTO `language` VALUES (99, 'German', 'ger');
INSERT INTO `language` VALUES (100, 'Dinka', 'din');
INSERT INTO `language` VALUES (101, 'Dogri', 'doi');
INSERT INTO `language` VALUES (102, 'Dravidian (Other)', 'dra');
INSERT INTO `language` VALUES (103, 'Duala', 'dua');
INSERT INTO `language` VALUES (104, 'Dutch, Middle (ca. 1050-1350)', 'dum');
INSERT INTO `language` VALUES (105, 'Dutch', 'dut');
INSERT INTO `language` VALUES (106, 'Dutch2', 'nld');
INSERT INTO `language` VALUES (107, 'Dyula', 'dyu');
INSERT INTO `language` VALUES (108, 'Dzongkha', 'dzo');
INSERT INTO `language` VALUES (109, 'Efik', 'efi');
INSERT INTO `language` VALUES (110, 'Egyptian (Ancient)', 'egy');
INSERT INTO `language` VALUES (111, 'Ekajuk', 'eka');
INSERT INTO `language` VALUES (112, 'Greek, Modern (1453- )', 'ell');
INSERT INTO `language` VALUES (113, 'Greek, Modern (1453- )2', 'gre');
INSERT INTO `language` VALUES (114, 'Elamite', 'elx');
INSERT INTO `language` VALUES (115, 'English', 'eng');
INSERT INTO `language` VALUES (116, 'English, Middle (1100-1500)', 'enm');
INSERT INTO `language` VALUES (117, 'Esperanto', 'epo');
INSERT INTO `language` VALUES (118, 'Eskimo (Other)', 'esk');
INSERT INTO `language` VALUES (119, 'Spanish', 'esl');
INSERT INTO `language` VALUES (120, 'Spanish2', 'spa');
INSERT INTO `language` VALUES (121, 'Estonian', 'est');
INSERT INTO `language` VALUES (122, 'Ethiopic', 'eth');
INSERT INTO `language` VALUES (123, 'Ewe', 'ewe');
INSERT INTO `language` VALUES (124, 'Ewondo', 'ewo');
INSERT INTO `language` VALUES (125, 'Fang', 'fan');
INSERT INTO `language` VALUES (126, 'Faroese', 'fao');
INSERT INTO `language` VALUES (127, 'Persian', 'fas');
INSERT INTO `language` VALUES (128, 'Persian', 'per');
INSERT INTO `language` VALUES (129, 'Fanti', 'fat');
INSERT INTO `language` VALUES (130, 'Fijian', 'fij');
INSERT INTO `language` VALUES (131, 'Finnish', 'fin');
INSERT INTO `language` VALUES (132, 'Finno-Ugrian (Other)', 'fiu');
INSERT INTO `language` VALUES (133, 'Fon', 'fon');
INSERT INTO `language` VALUES (134, 'French', 'fra');
INSERT INTO `language` VALUES (135, 'French2', 'fre');
INSERT INTO `language` VALUES (136, 'French, Middel (ca. 1400-1600)', 'frm');
INSERT INTO `language` VALUES (137, 'French, Old (ca. 842-1400)', 'fro');
INSERT INTO `language` VALUES (138, 'Friesian', 'fry');
INSERT INTO `language` VALUES (139, 'Fulah', 'ful');
INSERT INTO `language` VALUES (140, 'Ga', 'gaa');
INSERT INTO `language` VALUES (141, 'Gaelic (Scots)', 'gae');
INSERT INTO `language` VALUES (142, 'Gaelic (Scots)2', 'gdh');
INSERT INTO `language` VALUES (143, 'Irish', 'gai');
INSERT INTO `language` VALUES (144, 'Irish2', 'iri');
INSERT INTO `language` VALUES (145, 'Gayo', 'gay');
INSERT INTO `language` VALUES (146, 'Germanic (Other)', 'gem');
INSERT INTO `language` VALUES (147, 'Georgian', 'geo');
INSERT INTO `language` VALUES (148, 'Georgian2', 'kat');
INSERT INTO `language` VALUES (149, 'Gilbertese', 'gil');
INSERT INTO `language` VALUES (150, 'Gallegan', 'glg');
INSERT INTO `language` VALUES (151, 'German, Middle High (ca. 1050-1500)', 'gmh');
INSERT INTO `language` VALUES (152, 'German, Old High (ca. 750-1050)', 'goh');
INSERT INTO `language` VALUES (153, 'Gondi', 'gon');
INSERT INTO `language` VALUES (154, 'Gothic', 'got');
INSERT INTO `language` VALUES (155, 'Grebo', 'grb');
INSERT INTO `language` VALUES (156, 'Greek, Ancient (to 1453)', 'grc');
INSERT INTO `language` VALUES (157, 'Guarani', 'grn');
INSERT INTO `language` VALUES (158, 'Gujarati', 'guj');
INSERT INTO `language` VALUES (159, 'Haida', 'hai');
INSERT INTO `language` VALUES (160, 'Hausa', 'hau');
INSERT INTO `language` VALUES (161, 'Hawaiian', 'haw');
INSERT INTO `language` VALUES (162, 'Hebrew', 'heb');
INSERT INTO `language` VALUES (163, 'Herero', 'her');
INSERT INTO `language` VALUES (164, 'Hiligaynon', 'hil');
INSERT INTO `language` VALUES (165, 'Himachali', 'him');
INSERT INTO `language` VALUES (166, 'Hindi', 'hin');
INSERT INTO `language` VALUES (167, 'Hiri Motu', 'hmo');
INSERT INTO `language` VALUES (168, 'Hungarian', 'hun');
INSERT INTO `language` VALUES (169, 'Hupa', 'hup');
INSERT INTO `language` VALUES (170, 'Iban', 'iba');
INSERT INTO `language` VALUES (171, 'Igbo', 'ibo');
INSERT INTO `language` VALUES (172, 'Icelandic', 'ice');
INSERT INTO `language` VALUES (173, 'Icelandic2', 'isl');
INSERT INTO `language` VALUES (174, 'Ijo', 'ijo');
INSERT INTO `language` VALUES (175, 'Inuktitut', 'iku');
INSERT INTO `language` VALUES (176, 'Interlingue', 'ile');
INSERT INTO `language` VALUES (177, 'Iloko', 'ilo');
INSERT INTO `language` VALUES (178, 'Interlingua (International Auxilary Language Association)', 'ina');
INSERT INTO `language` VALUES (179, 'Indic (Other)', 'inc');
INSERT INTO `language` VALUES (180, 'Indonesian', 'ind');
INSERT INTO `language` VALUES (181, 'Indo-European (Other)', 'ine');
INSERT INTO `language` VALUES (182, 'Inupiak', 'ipk');
INSERT INTO `language` VALUES (183, 'Iranian (Other)', 'ira');
INSERT INTO `language` VALUES (184, 'Iroquoian languages', 'iro');
INSERT INTO `language` VALUES (185, 'Italian', 'ita');
INSERT INTO `language` VALUES (186, 'Javanese', 'jav');
INSERT INTO `language` VALUES (187, 'Javanese2', 'jaw');
INSERT INTO `language` VALUES (188, 'Japanese', 'jpn');
INSERT INTO `language` VALUES (189, 'Judeo-Persian', 'jpr');
INSERT INTO `language` VALUES (190, 'Judeo-Arabic', 'jrb');
INSERT INTO `language` VALUES (191, 'Kara-Kalpak', 'kaa');
INSERT INTO `language` VALUES (192, 'Kabyle', 'kab');
INSERT INTO `language` VALUES (193, 'Kachin', 'kac');
INSERT INTO `language` VALUES (194, 'Greenlandic', 'kal');
INSERT INTO `language` VALUES (195, 'Kamba', 'kam');
INSERT INTO `language` VALUES (196, 'Kannada', 'kan');
INSERT INTO `language` VALUES (197, 'Karen', 'kar');
INSERT INTO `language` VALUES (198, 'Kashmiri', 'kas');
INSERT INTO `language` VALUES (199, 'Kanuri', 'kau');
INSERT INTO `language` VALUES (200, 'Kawi', 'kaw');
INSERT INTO `language` VALUES (201, 'Kazakh', 'kaz');
INSERT INTO `language` VALUES (202, 'Khasi', 'kha');
INSERT INTO `language` VALUES (203, 'Khoisan (Other)', 'khi');
INSERT INTO `language` VALUES (204, 'Khmer', 'khm');
INSERT INTO `language` VALUES (205, 'Khotanese', 'kho');
INSERT INTO `language` VALUES (206, 'Kikuyu', 'kik');
INSERT INTO `language` VALUES (207, 'Kinyarwanda', 'kin');
INSERT INTO `language` VALUES (208, 'Kirghiz', 'kir');
INSERT INTO `language` VALUES (209, 'Konkani', 'kok');
INSERT INTO `language` VALUES (210, 'Kongo', 'kon');
INSERT INTO `language` VALUES (211, 'Korean', 'kor');
INSERT INTO `language` VALUES (212, 'Kpelle', 'kpe');
INSERT INTO `language` VALUES (213, 'Kru', 'kro');
INSERT INTO `language` VALUES (214, 'Kurukh', 'kru');
INSERT INTO `language` VALUES (215, 'Kuanyama', 'kua');
INSERT INTO `language` VALUES (216, 'Kurdish', 'kur');
INSERT INTO `language` VALUES (217, 'Kusaie', 'kus');
INSERT INTO `language` VALUES (218, 'Kutenai', 'kut');
INSERT INTO `language` VALUES (219, 'Ladino', 'lad');
INSERT INTO `language` VALUES (220, 'Lahnda', 'lah');
INSERT INTO `language` VALUES (221, 'Lamba', 'lam');
INSERT INTO `language` VALUES (222, 'Lao', 'lao');
INSERT INTO `language` VALUES (223, 'Lapp languages', 'lap');
INSERT INTO `language` VALUES (224, 'Latin', 'lat');
INSERT INTO `language` VALUES (225, 'Latvian', 'lav');
INSERT INTO `language` VALUES (226, 'Lingala', 'lin');
INSERT INTO `language` VALUES (227, 'Lithuanian', 'lit');
INSERT INTO `language` VALUES (228, 'Mongo', 'lol');
INSERT INTO `language` VALUES (229, 'Lozi', 'loz');
INSERT INTO `language` VALUES (230, 'Luba-Katanga', 'lub');
INSERT INTO `language` VALUES (231, 'Ganda', 'lug');
INSERT INTO `language` VALUES (232, 'Luiseno', 'lui');
INSERT INTO `language` VALUES (233, 'Lunda', 'lun');
INSERT INTO `language` VALUES (234, 'Luo (Kenya and Tanzania)', 'luo');
INSERT INTO `language` VALUES (235, 'Macedonian', 'mac');
INSERT INTO `language` VALUES (236, 'Macedonian', 'mke');
INSERT INTO `language` VALUES (237, 'Madurese', 'mad');
INSERT INTO `language` VALUES (238, 'Magahi', 'mag');
INSERT INTO `language` VALUES (239, 'Marshall', 'mah');
INSERT INTO `language` VALUES (240, 'Maithili', 'mai');
INSERT INTO `language` VALUES (241, 'Makasar', 'mak');
INSERT INTO `language` VALUES (242, 'Malayalam', 'mal');
INSERT INTO `language` VALUES (243, 'Mandingo', 'man');
INSERT INTO `language` VALUES (244, 'Maori', 'mao');
INSERT INTO `language` VALUES (245, 'Maori', 'mri');
INSERT INTO `language` VALUES (246, 'Austronesian (Other)', 'map');
INSERT INTO `language` VALUES (247, 'Marathi', 'mar');
INSERT INTO `language` VALUES (248, 'Masai', 'mas');
INSERT INTO `language` VALUES (249, 'Manx', 'max');
INSERT INTO `language` VALUES (250, 'Malay', 'may');
INSERT INTO `language` VALUES (251, 'Malay', 'msa');
INSERT INTO `language` VALUES (252, 'Mende', 'men');
INSERT INTO `language` VALUES (253, 'Micmac', 'mic');
INSERT INTO `language` VALUES (254, 'Minangkabau', 'min');
INSERT INTO `language` VALUES (255, 'Miscellaneous (Other)', 'mis');
INSERT INTO `language` VALUES (256, 'Mon-Khmer (Other)', 'mkh');
INSERT INTO `language` VALUES (257, 'Malagasy', 'mlg');
INSERT INTO `language` VALUES (258, 'Maltese', 'mlt');
INSERT INTO `language` VALUES (259, 'Manipuri', 'mni');
INSERT INTO `language` VALUES (260, 'Manobo languages', 'mno');
INSERT INTO `language` VALUES (261, 'Mohawk', 'moh');
INSERT INTO `language` VALUES (262, 'Moldavian', 'mol');
INSERT INTO `language` VALUES (263, 'Mongolian', 'mon');
INSERT INTO `language` VALUES (264, 'Mossi', 'mos');
INSERT INTO `language` VALUES (265, 'Multiple languages', 'mul');
INSERT INTO `language` VALUES (266, 'Munda (Other)', 'mun');
INSERT INTO `language` VALUES (267, 'Creek', 'mus');
INSERT INTO `language` VALUES (268, 'Marwari', 'mwr');
INSERT INTO `language` VALUES (269, 'Mayan languages', 'myn');
INSERT INTO `language` VALUES (270, 'Aztec', 'nah');
INSERT INTO `language` VALUES (271, 'North American Indian (Other)', 'nai');
INSERT INTO `language` VALUES (272, 'Nauru', 'nau');
INSERT INTO `language` VALUES (273, 'Navajo', 'nav');
INSERT INTO `language` VALUES (274, 'Ndebele (Zimbabwe)', 'nde');
INSERT INTO `language` VALUES (275, 'Ndonga', 'ndo');
INSERT INTO `language` VALUES (276, 'Nepali', 'nep');
INSERT INTO `language` VALUES (277, 'Newari', 'new');
INSERT INTO `language` VALUES (278, 'Niger-Kordofanian (Other)', 'nic');
INSERT INTO `language` VALUES (279, 'Niuean', 'niu');
INSERT INTO `language` VALUES (280, 'Old Norse', 'non');
INSERT INTO `language` VALUES (281, 'Norwegian', 'nor');
INSERT INTO `language` VALUES (282, 'Northern Sohto', 'nso');
INSERT INTO `language` VALUES (283, 'Nubian languages', 'nub');
INSERT INTO `language` VALUES (284, 'Nyanja', 'nya');
INSERT INTO `language` VALUES (285, 'Nyamwezi', 'nym');
INSERT INTO `language` VALUES (286, 'Nyankole', 'nyn');
INSERT INTO `language` VALUES (287, 'Nyoro', 'nyo');
INSERT INTO `language` VALUES (288, 'Nzima', 'nzi');
INSERT INTO `language` VALUES (289, 'Langue d\'oc (post 1500)', 'oci');
INSERT INTO `language` VALUES (290, 'Ojibwa', 'oji');
INSERT INTO `language` VALUES (291, 'Oriya', 'ori');
INSERT INTO `language` VALUES (292, 'Oromo', 'orm');
INSERT INTO `language` VALUES (293, 'Osage', 'osa');
INSERT INTO `language` VALUES (294, 'Ossetic', 'oss');
INSERT INTO `language` VALUES (295, 'Turkish, Ottoman', 'ota');
INSERT INTO `language` VALUES (296, 'Otomian languages', 'oto');
INSERT INTO `language` VALUES (297, 'Papuan-Australian (Other)', 'paa');
INSERT INTO `language` VALUES (298, 'Pangasinan', 'pag');
INSERT INTO `language` VALUES (299, 'Pahlavi', 'pal');
INSERT INTO `language` VALUES (300, 'Pampanga', 'pam');
INSERT INTO `language` VALUES (301, 'Panjabi', 'pan');
INSERT INTO `language` VALUES (302, 'Papiamento', 'pap');
INSERT INTO `language` VALUES (303, 'Palauan', 'pau');
INSERT INTO `language` VALUES (304, 'Old Persian (ca. 600-400 B.C.)', 'peo');
INSERT INTO `language` VALUES (305, 'Pali', 'pli');
INSERT INTO `language` VALUES (306, 'Polish', 'pol');
INSERT INTO `language` VALUES (307, 'Ponape', 'pon');
INSERT INTO `language` VALUES (308, 'Portuguese', 'por');
INSERT INTO `language` VALUES (309, 'Prakrit languages', 'pra');
INSERT INTO `language` VALUES (310, 'Provencal, Old (to 1500)', 'pro');
INSERT INTO `language` VALUES (311, 'Pushto', 'pus');
INSERT INTO `language` VALUES (312, 'Quechua', 'que');
INSERT INTO `language` VALUES (313, 'Rajasthani', 'raj');
INSERT INTO `language` VALUES (314, 'Rarotongan', 'rar');
INSERT INTO `language` VALUES (315, 'Romance (Other)', 'roa');
INSERT INTO `language` VALUES (316, 'Raeto-Romance', 'roh');
INSERT INTO `language` VALUES (317, 'Romany', 'rom');
INSERT INTO `language` VALUES (318, 'Romanian', 'ron');
INSERT INTO `language` VALUES (319, 'Romanian2', 'rum');
INSERT INTO `language` VALUES (320, 'Rundi', 'run');
INSERT INTO `language` VALUES (321, 'Russian', 'rus');
INSERT INTO `language` VALUES (322, 'Sandawe', 'sad');
INSERT INTO `language` VALUES (323, 'Sango', 'sag');
INSERT INTO `language` VALUES (324, 'South American Indian (Other)', 'sai');
INSERT INTO `language` VALUES (325, 'Salishan languages', 'sal');
INSERT INTO `language` VALUES (326, 'Samaritan Aramaic', 'sam');
INSERT INTO `language` VALUES (327, 'Sanskrit', 'san');
INSERT INTO `language` VALUES (328, 'Scots', 'sco');
INSERT INTO `language` VALUES (329, 'Serbo-Croatian', 'scr');
INSERT INTO `language` VALUES (330, 'Selkup', 'sel');
INSERT INTO `language` VALUES (331, 'Semitic (Other)', 'sem');
INSERT INTO `language` VALUES (332, 'Shan', 'shn');
INSERT INTO `language` VALUES (333, 'Sidamo', 'sid');
INSERT INTO `language` VALUES (334, 'Sinhalese', 'sin');
INSERT INTO `language` VALUES (335, 'Siouan languages', 'sio');
INSERT INTO `language` VALUES (336, 'Sino-Tibetan (Other)', 'sit');
INSERT INTO `language` VALUES (337, 'Slavic (Other)', 'sla');
INSERT INTO `language` VALUES (338, 'Slovak', 'slk');
INSERT INTO `language` VALUES (339, 'Slovak2', 'slo');
INSERT INTO `language` VALUES (340, 'Slovenian', 'slv');
INSERT INTO `language` VALUES (341, 'Samoan', 'smo');
INSERT INTO `language` VALUES (342, 'Shona', 'sna');
INSERT INTO `language` VALUES (343, 'Sindhi', 'snd');
INSERT INTO `language` VALUES (344, 'Sogdian', 'sog');
INSERT INTO `language` VALUES (345, 'Somali', 'som');
INSERT INTO `language` VALUES (346, 'Songhai', 'son');
INSERT INTO `language` VALUES (347, 'Sotho', 'sot');
INSERT INTO `language` VALUES (348, 'Serer', 'srr');
INSERT INTO `language` VALUES (349, 'Nilo-Saharan (Other)', 'ssa');
INSERT INTO `language` VALUES (350, 'Swazi', 'ssw');
INSERT INTO `language` VALUES (351, 'Sukuma', 'suk');
INSERT INTO `language` VALUES (352, 'Sundanese', 'sun');
INSERT INTO `language` VALUES (353, 'Susu', 'sus');
INSERT INTO `language` VALUES (354, 'Sumerian', 'sux');
INSERT INTO `language` VALUES (355, 'Swedish', 'sve');
INSERT INTO `language` VALUES (356, 'Swahili', 'swa');
INSERT INTO `language` VALUES (357, 'Swedish2', 'swe');
INSERT INTO `language` VALUES (358, 'Syriac', 'syr');
INSERT INTO `language` VALUES (359, 'Tahitian', 'tah');
INSERT INTO `language` VALUES (360, 'Tamil', 'tam');
INSERT INTO `language` VALUES (361, 'Tatar', 'tat');
INSERT INTO `language` VALUES (362, 'Telugu', 'tel');
INSERT INTO `language` VALUES (363, 'Timne', 'tem');
INSERT INTO `language` VALUES (364, 'Tereno', 'ter');
INSERT INTO `language` VALUES (365, 'Tajik', 'tgk');
INSERT INTO `language` VALUES (366, 'Tagalog', 'tgl');
INSERT INTO `language` VALUES (367, 'Thai', 'tha');
INSERT INTO `language` VALUES (368, 'Tigre', 'tig');
INSERT INTO `language` VALUES (369, 'Tigrinya', 'tir');
INSERT INTO `language` VALUES (370, 'Tivi', 'tiv');
INSERT INTO `language` VALUES (371, 'Tlingit', 'tli');
INSERT INTO `language` VALUES (372, 'Tonga (Nyasa)', 'tog');
INSERT INTO `language` VALUES (373, 'Tonga (Tonga Islands)', 'ton');
INSERT INTO `language` VALUES (374, 'Truk', 'tru');
INSERT INTO `language` VALUES (375, 'Tsimshian', 'tsi');
INSERT INTO `language` VALUES (376, 'Tswana', 'tsn');
INSERT INTO `language` VALUES (377, 'Tsonga', 'tso');
INSERT INTO `language` VALUES (378, 'Turkmen', 'tuk');
INSERT INTO `language` VALUES (379, 'Tumbuka', 'tum');
INSERT INTO `language` VALUES (380, 'Turkish', 'tur');
INSERT INTO `language` VALUES (381, 'Altaic (Other)', 'tut');
INSERT INTO `language` VALUES (382, 'Twi', 'twi');
INSERT INTO `language` VALUES (383, 'Ugaritic', 'uga');
INSERT INTO `language` VALUES (384, 'Uighur', 'uig');
INSERT INTO `language` VALUES (385, 'Ukrainian', 'ukr');
INSERT INTO `language` VALUES (386, 'Umbundu', 'umb');
INSERT INTO `language` VALUES (387, 'Undetermined', 'und');
INSERT INTO `language` VALUES (388, 'Urdu', 'urd');
INSERT INTO `language` VALUES (389, 'Uzbek', 'uzb');
INSERT INTO `language` VALUES (390, 'Vai', 'vai');
INSERT INTO `language` VALUES (391, 'Venda', 'ven');
INSERT INTO `language` VALUES (392, 'Vietnamese', 'vie');
INSERT INTO `language` VALUES (393, 'Volapuk', 'vol');
INSERT INTO `language` VALUES (394, 'Votic', 'vot');
INSERT INTO `language` VALUES (395, 'Wakashan languages', 'wak');
INSERT INTO `language` VALUES (396, 'Walamo', 'wal');
INSERT INTO `language` VALUES (397, 'Waray', 'war');
INSERT INTO `language` VALUES (398, 'Washo', 'was');
INSERT INTO `language` VALUES (399, 'Sorbian languages', 'wen');
INSERT INTO `language` VALUES (400, 'Wolof', 'wol');
INSERT INTO `language` VALUES (401, 'Xhosa', 'xho');
INSERT INTO `language` VALUES (402, 'Yao', 'yao');
INSERT INTO `language` VALUES (403, 'Yap', 'yap');
INSERT INTO `language` VALUES (404, 'Yiddish', 'yid');
INSERT INTO `language` VALUES (405, 'Yoruba', 'yor');
INSERT INTO `language` VALUES (406, 'Zapotec', 'zap');
INSERT INTO `language` VALUES (407, 'Zenaga', 'zen');
INSERT INTO `language` VALUES (408, 'Zhuang', 'zha');
INSERT INTO `language` VALUES (409, 'Zulu', 'zul');
INSERT INTO `language` VALUES (410, 'Zuni', 'zun');

# --------------------------------------------------------

#
# Table structure for table `module`
#

CREATE TABLE `module` (
  `module_id` int(11) NOT NULL auto_increment,
  `module_name` varchar(255) default NULL,
  `module_description` text,
  `module_perms` varchar(255) default NULL,
  `module_header` varchar(255) default NULL,
  `module_footer` varchar(255) default NULL,
  `module_publish` char(1) default NULL,
  `list_order` int(11) default NULL,
  `language_code_1` varchar(4) default NULL,
  `language_code_2` varchar(4) default NULL,
  `language_code_3` varchar(4) default NULL,
  `language_code_4` varchar(4) default NULL,
  `language_code_5` varchar(4) default NULL,
  `language_file_1` varchar(255) default NULL,
  `language_file_2` varchar(255) default NULL,
  `language_file_3` varchar(255) default NULL,
  `language_file_4` varchar(255) default NULL,
  `language_file_5` varchar(255) default NULL,
  `module_label_1` varchar(255) default NULL,
  `module_label_2` varchar(255) default NULL,
  `module_label_3` varchar(255) default NULL,
  `module_label_4` varchar(255) default NULL,
  `module_label_5` varchar(255) default NULL,
  PRIMARY KEY  (`module_id`)
) TYPE=MyISAM AUTO_INCREMENT=12841 ;

#
# Dumping data for table `module`
#

INSERT INTO `module` VALUES (1, 'admin', '<h4>ADMINISTRATIVE USERS ONLY</h4>\r\n\r\n<p>Only used for the following:</p>\r\n<ol>\r\n\r\n<li>User Maintenance</li>\r\n<li>Module Maintenance</li>\r\n<li>Function Maintenance</li>\r\n</ol>\r\n', 'admin', 'header.ihtml', 'footer.ihtml', 'Y', 1, 'eng', 'esl', '', '', '', 'lang_eng.inc', 'lang_esl.inc', '', '', '', 'Admin', 'Admin', '', '', '');
INSERT INTO `module` VALUES (2, 'product', '<p>Here you can adminster your online catalog of products.  The Product Administrator allows you to create product categories, create new products, edit product attributes, and add product items for each attribute value.</p>', 'storeadmin,admin,demo', 'header.ihtml', 'footer.ihtml', 'Y', 6, 'eng', 'esl', '', '', '', 'lang_en.inc', 'lang_es.inc', '', '', '', 'Products', 'Mis<br />Productos', '', '', '');
INSERT INTO `module` VALUES (3, 'vendor', '<h4>ADMINISTRATIVE USERS ONLY</h4>\r\n<p>Here you can manage the vendors on the phpShop system.</p>', 'admin', 'header.ihtml', 'footer.ihtml', 'Y', 2, 'eng', 'esl', '', '', '', 'lang_en.inc', 'lang_es.inc', '', '', '', 'Vendors', 'Los<br />Distribuidores', '', '', '');
INSERT INTO `module` VALUES (4, 'shopper', '<p>Manage shoppers in your store.  Allows you to create shopper groups.  Shopper groups can be used when setting the price for a product.  This allows you to create different prices for different types of users.  An example of this would be to have a \'wholesale\' group and a \'retail\' group. </p>', 'admin,storeadmin,demo', 'header.ihtml', 'footer.ihtml', 'Y', 9, 'eng', 'esl', '', '', '', 'lang_en.inc', 'lang_es.inc', '', '', '', 'Shoppers', 'Mis<br />Clientes', '', '', '');
INSERT INTO `module` VALUES (5, 'order', '<p>View Order and Update Order Status.</p>', 'admin,storeadmin,demo', 'header.ihtml', 'footer.ihtml', 'Y', 7, 'eng', 'esl', '', '', '', 'lang_en.inc', 'lang_es.inc', '', '', '', 'Orders', 'Mis<br />Ordenes', '', '', '');
INSERT INTO `module` VALUES (6, 'msgs', 'This module is unprotected an used for displaying system messages to users.  We need to have an area that does not require authorization when things go wrong.', 'none', 'header.ihtml', 'footer.ihtml', 'N', 99, 'eng', 'esl', '', '', '', 'lang_en.inc', '', '', '', '', 'Admin', '', '', '', '');
INSERT INTO `module` VALUES (7, 'shop', 'This is the Washupito store module.  This is the demo store included with the phpShop distribution.', 'none', 's_header.ihtml', 's_footer.ihtml', 'N', 99, 'eng', 'esl', '', '', '', '', '', '', '', '', 'Shop', 'Visita<br />la Tienda', '', '', '');
INSERT INTO `module` VALUES (8, 'store', '', 'storeadmin,admin,demo', 'header.ihtml', 'footer.ihtml', 'Y', 3, 'eng', 'esl', '', '', '', '', '', '', '', '', 'Store', 'Mi<br />Tienda', '', '', '');
INSERT INTO `module` VALUES (9, 'account', 'This module allows shoppers to update their account information and view previously placed orders.', 'shopper,storeadmin,admin,demo', 's_header.ihtml', 's_footer.ihtml', 'N', 99, 'eng', 'esl', '', '', '', '', '', '', '', '', 'Account', 'Account', '', '', '');
INSERT INTO `module` VALUES (10, 'checkout', '', 'shopper,storeadmin,admin,demo', 'c_header.ihtml', 'c_footer.ihtml', 'N', 99, 'eng', 'esl', '', '', '', '', '', '', '', '', 'Checkout', 'Checkout', '', '', '');
INSERT INTO `module` VALUES (11, 'tax', 'The tax module allows you to set tax rates for states or regions within a country.  The rate is set as a decimal figure.  For example, 2 percent tax would be 0.02.', 'admin,storeadmin,demo', 'header.ihtml', 'footer.ihtml', 'Y', 4, 'eng', 'esl', '', '', '', '', '', '', '', '', 'Taxes', 'Impuestos', '', '', '');
INSERT INTO `module` VALUES (12837, 'intershipper', '<p>Configure Your shipping methods here.</p>', 'admin,storeadmin,demo', 'header.ihtml', 'footer.ihtml', 'N', 10, 'eng', 'esl', '', '', '', '', '', '', '', '', 'Shipping', '', '', '', '');
INSERT INTO `module` VALUES (12838, 'zone', 'This is the zone-shipping module. Here you can manage your shipping costs according to Zones.', 'admin,storeadmin,demo', 'header.ihtml', 'footer.ihtml', 'Y', 10, 'eng', '', '', '', '', '', '', '', '', '', 'Zone Shipping', '', '', '', '');
INSERT INTO `module` VALUES (12839, 'reportbasic', '', 'admin,storeadmin', 's_header.ihtml', 's_footer.ihtml', 'N', 11, 'eng', '', '', '', '', '', '', '', '', '', 'Report Basic', '', '', '', '');

# --------------------------------------------------------

#
# Table structure for table `order_item`
#

CREATE TABLE `order_item` (
  `order_item_id` int(11) NOT NULL auto_increment,
  `order_id` int(11) default NULL,
  `user_info_id` int(11) default NULL,
  `vendor_id` int(11) default NULL,
  `product_id` int(11) default NULL,
  `product_quantity` int(11) default NULL,
  `product_item_price` decimal(10,2) default NULL,
  `order_item_currency` varchar(16) default NULL,
  `order_status` char(1) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  PRIMARY KEY  (`order_item_id`)
) TYPE=MyISAM AUTO_INCREMENT=17 ;

#
# Dumping data for table `order_item`
#

INSERT INTO `order_item` VALUES (1, 1, 14, 1, 11, 1, '4.99', 'USD', 'P', 1088460404, 1088460404);

# --------------------------------------------------------

#
# Table structure for table `order_payment`
#

CREATE TABLE `order_payment` (
  `order_id` int(11) NOT NULL default '0',
  `payment_method_id` int(11) default NULL,
  `order_payment_number` blob,
  `order_payment_expire` int(11) default NULL,
  `order_payment_name` varchar(255) default NULL,
  `order_payment_log` text
) TYPE=MyISAM;

#
# Dumping data for table `order_payment`
#

INSERT INTO `order_payment` VALUES (1, 1, 0xa647cfe3b119fc92ff7f2afbfca0eee8, 1143864000, 'John Smith', 'Payment information captured for later processing.<br />');

# --------------------------------------------------------

#
# Table structure for table `order_status`
#

CREATE TABLE `order_status` (
  `order_status_id` int(11) NOT NULL auto_increment,
  `order_status_code` char(1) NOT NULL default '',
  `order_status_name` varchar(64) default NULL,
  `list_order` int(11) default NULL,
  `vendor_id` int(11) default NULL,
  PRIMARY KEY  (`order_status_id`)
) TYPE=MyISAM AUTO_INCREMENT=5 ;

#
# Dumping data for table `order_status`
#

INSERT INTO `order_status` VALUES (1, 'P', 'Pending', 1, 1);
INSERT INTO `order_status` VALUES (2, 'C', 'Confirmed', 1, 1);
INSERT INTO `order_status` VALUES (3, 'X', 'Cancelled', 3, 1);
INSERT INTO `order_status` VALUES (4, 'S', 'Shipped', 4, 1);

# --------------------------------------------------------

#
# Table structure for table `orders`
#

CREATE TABLE `orders` (
  `order_id` int(11) NOT NULL auto_increment,
  `user_id` varchar(32) NOT NULL default '',
  `vendor_id` int(11) NOT NULL default '0',
  `order_number` varchar(32) default NULL,
  `user_info_id` int(11) default NULL,
  `order_subtotal` decimal(10,2) default NULL,
  `order_tax` decimal(10,2) default NULL,
  `order_shipping` decimal(10,2) default NULL,
  `order_shipping_tax` decimal(10,2) default NULL,
  `order_currency` varchar(16) default NULL,
  `order_status` char(1) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  `ship_method_id` int(11) default NULL,
  PRIMARY KEY  (`order_id`)
) TYPE=MyISAM AUTO_INCREMENT=15 ;

#
# Dumping data for table `orders`
#

INSERT INTO `orders` VALUES (1, '7322f75cc7ba16db1799fd8d25dbcde4', 1, '2163dcbbc0659f9889f8eb1e96eae5a8', 14, '4.99', '0.32', '0.00', '0.00', '', 'P', 1088460404, 1088543110, 0);

# --------------------------------------------------------

#
# Table structure for table `payment_method`
#

CREATE TABLE `payment_method` (
  `payment_method_id` int(11) NOT NULL auto_increment,
  `vendor_id` int(11) default NULL,
  `payment_method_name` varchar(255) default NULL,
  `shopper_group_id` int(11) default NULL,
  `payment_method_discount` decimal(10,2) default NULL,
  `list_order` int(11) default NULL,
  `payment_method_code` varchar(8) default NULL,
  `enable_processor` char(1) default NULL,
  PRIMARY KEY  (`payment_method_id`)
) TYPE=MyISAM AUTO_INCREMENT=5 ;

#
# Dumping data for table `payment_method`
#

INSERT INTO `payment_method` VALUES (1, 1, 'Visa', 5, '0.00', 1, 'VISA', '');
INSERT INTO `payment_method` VALUES (2, 1, 'Master Card', 5, '0.00', 2, 'MC', '');
INSERT INTO `payment_method` VALUES (3, 1, 'American Express', 5, '0.00', 3, 'AMEX', NULL);
INSERT INTO `payment_method` VALUES (4, 1, 'Purchase Order', 6, '0.00', 4, 'PO', NULL);

# --------------------------------------------------------

#
# Table structure for table `product`
#

CREATE TABLE `product` (
  `product_id` int(11) NOT NULL auto_increment,
  `vendor_id` int(11) NOT NULL default '0',
  `product_parent_id` int(11) default NULL,
  `product_sku` varchar(64) NOT NULL default '',
  `product_s_desc` varchar(255) default NULL,
  `product_desc` text,
  `product_thumb_image` varchar(255) default NULL,
  `product_full_image` varchar(255) default NULL,
  `product_publish` char(1) default NULL,
  `product_weight` decimal(10,4) default NULL,
  `product_weight_uom` varchar(32) default 'pounds.',
  `product_length` decimal(10,4) default NULL,
  `product_width` decimal(10,4) default NULL,
  `product_height` decimal(10,4) default NULL,
  `product_lwh_uom` varchar(32) default 'inches',
  `product_url` varchar(255) default NULL,
  `product_in_stock` int(11) default NULL,
  `product_available_date` int(11) default NULL,
  `product_special` char(1) default NULL,
  `product_discount_id` int(11) default NULL,
  `ship_code_id` int(11) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  `product_name` varchar(64) default NULL,
  PRIMARY KEY  (`product_id`)
) TYPE=MyISAM AUTO_INCREMENT=18 ;

#
# Dumping data for table `product`
#

INSERT INTO `product` VALUES (1, 1, 0, 'G01', '                <p>Nice hand shovel to dig with in the yard.</p>\r\n', '                <ul>\r\n<li>Hand crafted handle with maximum grip torque\r\n</li><li>Titanium tipped shovel platter\r\n</li><li>Half degree offset for less accidents\r\n</li><li>Includes HowTo Video narrated by Bob Costas\r\n</li></ul>\r\n\r\n<b>Specifications</b><br />\r\n5" Diameter<br />\r\nTungsten handle tip with 5 point loft<br />\r\n                ', '8d886c5855770cc01a3b8a2db57f6600.jpg', 'cca3cd5db813ee6badf6a3598832f2fc.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 10, 0, 'Y', 10, NULL, 950320117, 1090667852, 'Hand Shovel');
INSERT INTO `product` VALUES (2, 1, 0, 'G02', 'A really long ladder to reach high places.', '<ul>\r\n<li>Hand crafted handle with maximum grip torque\r\n</li><li>Titanium tipped shovel platter\r\n</li><li>Half degree offset for less accidents\r\n</li><li>Includes HowTo Video narrated by Bob Costas\r\n</li></ul>\r\n\r\n<b>Specifications</b><br />\r\n5" Diameter<br />\r\nTungsten handle tip with 5 point loft<br />\r\n', 'ffd5d5ace2840232c8c32de59553cd8d.jpg', '8cb8d644ef299639b7eab25829d13dbc.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 950320180, 960375748, 'Ladder');
INSERT INTO `product` VALUES (3, 1, 0, 'G03', 'Nice shovel.  You can dig your way to China with this one.', '<ul>\r\n<li>Hand crafted handle with maximum grip torque\r\n</li><li>Titanium tipped shovel platter\r\n</li><li>Half degree offset for less accidents\r\n</li><li>Includes HowTo Video narrated by Bob Costas\r\n</li></ul>\r\n\r\n<b>Specifications</b><br />\r\n5" Diameter<br />\r\nTungsten handle tip with 5 point loft<br />\r\n', '8147a3a9666aec0296525dbd81f9705e.jpg', '520efefd6d7977f91b16fac1149c7438.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 950320243, 965123675, 'Shovel');
INSERT INTO `product` VALUES (4, 1, 0, 'G04', '                        This shovel is smaller but you\'ll be able to dig real quick.', '                        <ul>\r\n<li>Hand crafted handle with maximum grip torque\r\n</li><li>Titanium tipped shovel platter\r\n</li><li>Half degree offset for less accidents\r\n</li><li>Includes HowTo Video narrated by Bob Costas\r\n</li></ul>\r\n\r\n<b>Specifications</b><br />\r\n5" Diameter<br />\r\nTungsten handle tip with 5 point loft<br />\r\n                        ', 'a04395a8aefacd9c1659ebca4dbfd4ba.jpg', '1b0c96d67abdbea648cd0ea96fd6abcb.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, 'N', 0, NULL, 950320378, 1090672023, 'Smaller Shovel');
INSERT INTO `product` VALUES (5, 1, 0, 'H01', 'This saw is great for getting cutting through downed limbs.', '<ul>\r\n<li>Hand crafted handle with maximum grip torque\r\n</li><li>Titanium tipped shovel platter\r\n</li><li>Half degree offset for less accidents\r\n</li><li>Includes HowTo Video narrated by Bob Costas\r\n</li></ul>\r\n\r\n<b>Specifications</b><br />\r\n5" Diameter<br />\r\nTungsten handle tip with 5 point loft<br />\r\n', '1aa8846d3cfe3504b2ccaf7c23bb748f.jpg', 'e614ba08c3ee0c2adc62fd9e5b9440eb.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 950321256, 960375831, 'Nice Saw');
INSERT INTO `product` VALUES (6, 1, 0, 'H02', '                A great hammer to hammer away with.', '                <ul>\r\n<li>Hand crafted handle with maximum grip torque\r\n</li><li>Titanium tipped shovel platter\r\n</li><li>Half degree offset for less accidents\r\n</li><li>Includes HowTo Video narrated by Bob Costas\r\n</li></ul>\r\n\r\n<b>Specifications</b><br />\r\n5" Diameter<br />\r\nTungsten handle tip with 5 point loft<br />\r\n                ', 'dccb8223891a17d752bfc1477d320da9.jpg', '578563851019e01264a9b40dcf1c4ab6.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, 'Y', 20, NULL, 950321631, 1090667450, 'Hammer');
INSERT INTO `product` VALUES (7, 1, 0, 'P01', '                Don\'t do it with an axe.  Get a chain saw.', '                <ul>\r\n<li>Tool-free tensioner for easy, convenient chain adjustment\r\n</li><li>3-Way Auto Stop; stops chain a fraction of a second\r\n</li><li>Automatic chain oiler regulates oil for proper chain lubrication\r\n</li><li>Small radius guide bar reduces kick-back\r\n</li></ul>\r\n<br />\r\n<b>Specifications</b><br />\r\n12.5 AMPS   <br /> \r\n16" Bar Length   <br /> \r\n3.5 HP   <br /> \r\n8.05 LBS. Weight   <br /> \r\n                        ', '8716aefc3b0dce8870360604e6eb8744.jpg', 'c3a5bf074da14f30c849d13a2dd87d2c.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, 'Y', 5, NULL, 950321725, 1090667842, 'Chain Saw');
INSERT INTO `product` VALUES (8, 1, 0, 'P02', 'Cut rings around wood.  This saw can handle the most delicate projects.', '<ul>\r\n<li>Patented Sightline; Window provides maximum visibility for straight cuts\r\n</li><li>Adjustable dust chute for cleaner work area\r\n</li><li>Bail handle for controlled cutting in 90° to 45° applications\r\n</li><li>1-1/2 to 2-1/2 lbs. lighter and 40% less noise than the average circular saw                     </li><li><b>Includes:</b>Carbide blade\r\n</li></ul>\r\n<br />\r\n<b>Specifications</b><br />\r\n10.0 AMPS   <br /> \r\n4,300 RPM   <br /> \r\nCapacity: 2-1/16" at 90°, 1-3/4" at 45°<br /> \r\n', 'b4a748303d0d996b29d5a1e1d1112537.jpg', '9a4448bb13e2f7699613b2cfd7cd51ad.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 950321795, 1088459284, 'Circular Saw');
INSERT INTO `product` VALUES (9, 1, 0, 'P03', '        Drill through anything.  This drill has the power you need for those demanding hole boring duties.', '                <ul>\r\n<li>High power motor and double gear reduction for increased durability and improved performance\r\n</li><li>Mid-handle design and two finger trigger for increased balance and comfort\r\n</li><li>Variable speed switch with lock-on button for continuous use\r\n</li><li><b>Includes:</b> Chuck key & holder\r\n</li></ul>\r\n<br />\r\n<b>Specifications</b><br />\r\n4.0 AMPS   <br /> \r\n0-1,350 RPM   <br /> \r\nCapacity: 3/8" Steel, 1" Wood   <br /> \r\n        ', 'c70a3f47baf9a4020aeeee919eb3fda4.jpg', '1ff5f2527907ca86103288e1b7cc3446.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 950321879, 1090602602, 'Drill');
INSERT INTO `product` VALUES (10, 1, 0, 'P04', 'Blast away that paint job from the past.  Use this power sander to really show them you mean business.', '<ul>\r\n<li>Lever activated paper clamps for simple sandpaper changes\r\n</li><li>Dust sealed rocker switch extends product life and keeps dust out of motor\r\n</li><li>Flush sands on three sides to get into corners\r\n</li><li>Front handle for extra control\r\n</li><li>Dust extraction port for cleaner work environment \r\n</li></ul>\r\n<br />\r\n<b>Specifications</b><br />\r\n1.2 AMPS    <br /> \r\n10,000 OPM    <br /> \r\n\r\n', '7a36a05526e93964a086f2ddf17fc609.jpg', '480655b410d98a5cc3bef3927e786866.jpg', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 950321963, 960314245, 'Power Sander');
INSERT INTO `product` VALUES (11, 1, 1, 'G01-01', '', '', '', '', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 955696949, 960372163, 'Hand Shovel');
INSERT INTO `product` VALUES (12, 1, 1, 'G01-02', '', '', '', '', 'Y', '10.0000', '', '0.0000', '0.0000', '0.0000', '', '', 0, 0, '', 0, NULL, 955697006, 960372187, 'Hand Shovel');
INSERT INTO `product` VALUES (13, 1, 1, 'G01-03', '', '', '', '', 'Y', '10.0000', '', '0.0000', '0.0000', '0.0000', '', '', 0, 0, '', 0, NULL, 955697044, 960372206, 'Hand Shovel');
INSERT INTO `product` VALUES (14, 1, 2, 'L01', '', '', '', '', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 962351149, 962351149, 'Metal Ladder');
INSERT INTO `product` VALUES (15, 1, 2, 'L02', '', '', '', '', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 962351165, 962351165, 'Wooden Ladder');
INSERT INTO `product` VALUES (16, 1, 2, 'L03', '', '', '', '', 'Y', '10.0000', 'pounds', '0.0000', '0.0000', '0.0000', 'inches', '', 0, 0, '', 0, NULL, 962351180, 962351180, 'Plastic Ladder');

# --------------------------------------------------------

#
# Table structure for table `product_attribute`
#

CREATE TABLE `product_attribute` (
  `product_id` int(11) NOT NULL default '0',
  `attribute_name` char(255) NOT NULL default '',
  `attribute_value` char(255) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `product_attribute`
#

INSERT INTO `product_attribute` VALUES (11, 'Color', 'Red');
INSERT INTO `product_attribute` VALUES (12, 'Color', 'Green');
INSERT INTO `product_attribute` VALUES (13, 'Color', 'Blue');
INSERT INTO `product_attribute` VALUES (11, 'Size', 'Small');
INSERT INTO `product_attribute` VALUES (12, 'Size', 'Medium');
INSERT INTO `product_attribute` VALUES (13, 'Size', 'Large');
INSERT INTO `product_attribute` VALUES (14, 'Material', 'Metal');
INSERT INTO `product_attribute` VALUES (15, 'Material', 'Wood');
INSERT INTO `product_attribute` VALUES (16, 'Material', 'Plastic');

# --------------------------------------------------------

#
# Table structure for table `product_attribute_sku`
#

CREATE TABLE `product_attribute_sku` (
  `product_id` int(11) NOT NULL default '0',
  `attribute_name` char(255) NOT NULL default '',
  `attribute_list` int(11) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `product_attribute_sku`
#

INSERT INTO `product_attribute_sku` VALUES (1, 'Color', 1);
INSERT INTO `product_attribute_sku` VALUES (1, 'Size', 2);
INSERT INTO `product_attribute_sku` VALUES (2, 'Material', 1);

# --------------------------------------------------------

#
# Table structure for table `product_category_xref`
#

CREATE TABLE `product_category_xref` (
  `category_id` varchar(32) default NULL,
  `product_id` int(11) NOT NULL default '0',
  `product_list` int(11) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `product_category_xref`
#

INSERT INTO `product_category_xref` VALUES ('541a03b2b0e1b6dbd972e9f5af5ca992', 1, NULL);
INSERT INTO `product_category_xref` VALUES ('6834dda8e3e6e5aa18bafc63a57fd04a', 2, NULL);
INSERT INTO `product_category_xref` VALUES ('6834dda8e3e6e5aa18bafc63a57fd04a', 3, NULL);
INSERT INTO `product_category_xref` VALUES ('6834dda8e3e6e5aa18bafc63a57fd04a', 4, NULL);
INSERT INTO `product_category_xref` VALUES ('541a03b2b0e1b6dbd972e9f5af5ca992', 5, NULL);
INSERT INTO `product_category_xref` VALUES ('541a03b2b0e1b6dbd972e9f5af5ca992', 6, NULL);
INSERT INTO `product_category_xref` VALUES ('f85e462baf927f8e53989dd969c0e430', 7, NULL);
INSERT INTO `product_category_xref` VALUES ('1c914424d2569bea3439fbcca9123a27', 8, NULL);
INSERT INTO `product_category_xref` VALUES ('2f34f8bf003a5f27bed2e8dfe0b6f33a', 9, NULL);
INSERT INTO `product_category_xref` VALUES ('1c914424d2569bea3439fbcca9123a27', 10, NULL);

# --------------------------------------------------------

#
# Table structure for table `product_price`
#

CREATE TABLE `product_price` (
  `product_price_id` int(11) NOT NULL auto_increment,
  `product_id` int(11) NOT NULL default '0',
  `product_price` decimal(10,2) default NULL,
  `product_currency` char(16) default NULL,
  `product_price_vdate` int(11) default NULL,
  `product_price_edate` int(11) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  `shopper_group_id` int(11) default NULL,
  PRIMARY KEY  (`product_price_id`)
) TYPE=MyISAM AUTO_INCREMENT=17 ;

#
# Dumping data for table `product_price`
#

INSERT INTO `product_price` VALUES (1, 5, '24.99', 'USD', 0, 0, 950321309, 950321309, 5);
INSERT INTO `product_price` VALUES (2, 1, '4.99', 'USD', 0, 0, 950321324, 950321324, 5);
INSERT INTO `product_price` VALUES (3, 2, '49.99', 'USD', 0, 0, 950321340, 950321340, 5);
INSERT INTO `product_price` VALUES (4, 3, '24.99', 'USD', 0, 0, 950321368, 950321368, 5);
INSERT INTO `product_price` VALUES (5, 4, '19.99', 'USD', 0, 0, 950321385, 950321385, 5);
INSERT INTO `product_price` VALUES (6, 6, '1.00', 'USD', 0, 0, 950321686, 963808699, 5);
INSERT INTO `product_price` VALUES (7, 7, '149.99', 'USD', 0, 0, 950321754, 966506270, 5);
INSERT INTO `product_price` VALUES (8, 8, '220.90', 'USD', 0, 0, 950321833, 955614388, 5);
INSERT INTO `product_price` VALUES (9, 9, '48.12', 'USD', 0, 0, 950321933, 950321933, 5);
INSERT INTO `product_price` VALUES (10, 10, '74.99', 'USD', 0, 0, 950322005, 950322005, 5);
INSERT INTO `product_price` VALUES (11, 1, '2.99', 'USD', 0, 0, 955626841, 955626841, 6);
INSERT INTO `product_price` VALUES (12, 13, '14.99', 'USD', 0, 0, 955697213, 955697213, 5);
INSERT INTO `product_price` VALUES (13, 14, '79.99', 'USD', 0, 0, 962351197, 962351271, 5);
INSERT INTO `product_price` VALUES (14, 15, '49.99', 'USD', 0, 0, 962351233, 962351233, 5);
INSERT INTO `product_price` VALUES (15, 16, '59.99', 'USD', 0, 0, 962351259, 962351259, 5);
INSERT INTO `product_price` VALUES (16, 7, '2.99', 'USD', 0, 0, 966589140, 966589140, 6);

# --------------------------------------------------------

#
# Table structure for table `shopper_group`
#

CREATE TABLE `shopper_group` (
  `shopper_group_id` int(11) NOT NULL auto_increment,
  `vendor_id` int(11) default NULL,
  `shopper_group_name` varchar(32) default NULL,
  `shopper_group_desc` text,
  PRIMARY KEY  (`shopper_group_id`)
) TYPE=MyISAM AUTO_INCREMENT=8 ;

#
# Dumping data for table `shopper_group`
#

INSERT INTO `shopper_group` VALUES (5, 1, '-default-', 'Default shopper group.');
INSERT INTO `shopper_group` VALUES (6, 1, 'Gold Level', 'Gold Level phpShoppers.');
INSERT INTO `shopper_group` VALUES (7, 1, 'Wholesale', 'Shoppers that can buy at wholesale.');

# --------------------------------------------------------

#
# Table structure for table `shopper_vendor_xref`
#

CREATE TABLE `shopper_vendor_xref` (
  `user_id` varchar(32) default NULL,
  `vendor_id` int(11) default NULL,
  `shopper_group_id` int(11) default NULL,
  `customer_number` varchar(32) default NULL
) TYPE=MyISAM;

#
# Dumping data for table `shopper_vendor_xref`
#

INSERT INTO `shopper_vendor_xref` VALUES ('02acf876459c748dbb71b3b40714c0d7', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('55a3c25dd71e4cde5ac0db8e3d9af59a', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('dc8b89d41d1e0e2cf456510ca144a9f7', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('9a1fe0ca8ce7c527e29a6cca87151f78', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('b846daf4553dafbd445408d246bcfb6b', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('f79d82296f18bea3abb82200b06e21cb', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('f899168db2bff0e03539afbc5207fca0', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('2090153eee4cd48550c63229d67f53c4', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('899819677aa23ae5a8d0c0f149ab985c', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('1bd199850c2ac0e0b7b922f27127ff07', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('8b1c36c89a2bd119f3eb160bb129573c', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('e9f2a4c42c7d3c30a4335e5180ee7763', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('84f1af3d1ee577250f88a7ea06f6a2ed', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('afaf1ab70a518e048f82fd4937647ab4', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('4a9df5871f3836a101482aeba9a60ab2', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('239f55280fa2e71346068cf4e80acfb6', 1, 5, '');
INSERT INTO `shopper_vendor_xref` VALUES ('6845b3a8d95fc4799e9e962d1f9976bd', 1, 6, '');
INSERT INTO `shopper_vendor_xref` VALUES ('aa916b7b56a679596b38617d80303767', 1, 5, '');

# --------------------------------------------------------

#
# Table structure for table `tax_rate`
#

CREATE TABLE `tax_rate` (
  `tax_rate_id` int(11) NOT NULL auto_increment,
  `vendor_id` int(11) default NULL,
  `tax_state` varchar(64) default NULL,
  `tax_country` varchar(64) default NULL,
  `mdate` int(11) default NULL,
  `tax_rate` decimal(10,4) default NULL,
  PRIMARY KEY  (`tax_rate_id`)
) TYPE=MyISAM AUTO_INCREMENT=3 ;

#
# Dumping data for table `tax_rate`
#

INSERT INTO `tax_rate` VALUES (2, 1, 'GA', 'USA', 964565926, '0.0650');

# --------------------------------------------------------

#
# Table structure for table `user_info`
#

CREATE TABLE `user_info` (
  `user_info_id` int(11) NOT NULL auto_increment,
  `user_id` varchar(32) NOT NULL default '',
  `address_type` char(2) default NULL,
  `address_type_name` varchar(32) default NULL,
  `company` varchar(64) default NULL,
  `title` varchar(32) default NULL,
  `last_name` varchar(32) default NULL,
  `first_name` varchar(32) default NULL,
  `middle_name` varchar(32) default NULL,
  `phone_1` varchar(32) default NULL,
  `phone_2` varchar(32) default NULL,
  `fax` varchar(32) default NULL,
  `address_1` varchar(64) NOT NULL default '',
  `address_2` varchar(64) default NULL,
  `city` varchar(32) NOT NULL default '',
  `state` varchar(32) NOT NULL default '',
  `country` varchar(32) NOT NULL default 'US',
  `zip` varchar(32) NOT NULL default '',
  `user_email` varchar(255) default NULL,
  `extra_field_1` varchar(255) default NULL,
  `extra_field_2` varchar(255) default NULL,
  `extra_field_3` varchar(255) default NULL,
  `extra_field_4` char(1) default NULL,
  `extra_field_5` char(1) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  PRIMARY KEY  (`user_info_id`)
) TYPE=MyISAM AUTO_INCREMENT=20 ;

#
# Dumping data for table `user_info`
#

INSERT INTO `user_info` VALUES (16, 'c88ce1c0ad365513d6fe085a8aacaebc', 'ST', 'New York Warehouse', 'Demo Company', 'Mr.', 'User', 'Demo', '', '555-555-1212', '', '', 'Demo St.', '', 'New York', 'NY', 'USA', '10019', NULL, NULL, NULL, NULL, NULL, NULL, 957936118, 968309878);
INSERT INTO `user_info` VALUES (14, '7322f75cc7ba16db1799fd8d25dbcde4', 'BT', '-default-', '', '', 'Administrator', 'Site', '', '555-555-1212', '', '', '1 Apache Street', '', 'Apache', 'GA', 'USA', '30307', 'noreply@phpshop.org', '', '', '', 'N', 'N', NULL, 1090758681);
INSERT INTO `user_info` VALUES (10, '02acf876459c748dbb71b3b40714c0d7', 'BT', '-default-', '', 'Mr.', 'Shopper', 'Testing', 'T.', '555-555-1212', '', '555-555-1212', '3455 Peachtree Road', '', 'Atlanta', 'GA', 'USA', '30341', 'noreply@phpshop.org', '', '', '', 'N', 'N', 955626947, 1090758676);
INSERT INTO `user_info` VALUES (11, 'c88ce1c0ad365513d6fe085a8aacaebc', 'BT', '-default-', 'Demo Inc.', 'Mr.', 'User', 'Demonstration', '', '555-555-1212', '', '', 'Demo St.', '', 'Atlanta', 'GA', 'USA', '30326', 'noreply@phpshop.org', '', '', '', 'N', 'N', 955698389, 1090758661);
INSERT INTO `user_info` VALUES (17, '1438a90d1888a2814b2bdedc43c03e99', 'BT', '-default-', 'Washupito\'s Tiendita', 'Mr.', 'Administrator', 'Store', '', '555-555-1212', '', '555-555-1212', 'Washupito Place', '', 'Washupitito', 'WA', 'USA', '00000', 'noreply@phpshop.org', '', '', '', 'N', 'N', 958708505, 1090758672);
INSERT INTO `user_info` VALUES (19, '7322f75cc7ba16db1799fd8d25dbcde4', 'ST', 'warehouse', 'test', '', 'test', 'test', '', '555-555-1212', '', '', '3897 Admiral', '', 'Atlanta', 'GA', 'USA', '30341', NULL, NULL, NULL, NULL, NULL, NULL, 966588093, 968039052);
INSERT INTO `user_info` VALUES (18, '6845b3a8d95fc4799e9e962d1f9976bd', 'BT', '-default-', 'Gold', 'Mr.', 'Shopper', 'Gold', 'T.', '555-555-1212', '', '555-555-1212', '222 Gold Ave.', '', 'Atlanta', 'GA', 'USA', '30327', 'noreply@phpshop.org', '', '', '', 'N', 'N', 963464058, 1090758667);

# --------------------------------------------------------

#
# Table structure for table `vendor`
#

CREATE TABLE `vendor` (
  `vendor_id` int(11) NOT NULL auto_increment,
  `vendor_name` varchar(64) default NULL,
  `contact_last_name` varchar(32) NOT NULL default '',
  `contact_first_name` varchar(32) NOT NULL default '',
  `contact_middle_name` varchar(32) default NULL,
  `contact_title` varchar(32) default NULL,
  `contact_phone_1` varchar(32) NOT NULL default '',
  `contact_phone_2` varchar(32) default NULL,
  `contact_fax` varchar(32) default NULL,
  `contact_email` varchar(255) default NULL,
  `vendor_phone` varchar(32) default NULL,
  `vendor_address_1` varchar(64) NOT NULL default '',
  `vendor_address_2` varchar(64) default NULL,
  `vendor_city` varchar(32) NOT NULL default '',
  `vendor_state` varchar(32) NOT NULL default '',
  `vendor_country` varchar(32) NOT NULL default 'US',
  `vendor_zip` varchar(32) NOT NULL default '',
  `vendor_store_name` varchar(128) NOT NULL default '',
  `vendor_store_desc` text,
  `vendor_category_id` int(11) default NULL,
  `vendor_thumb_image` varchar(255) default NULL,
  `vendor_full_image` varchar(255) default NULL,
  `vendor_currency` varchar(16) default NULL,
  `cdate` int(11) default NULL,
  `mdate` int(11) default NULL,
  `vendor_image_path` varchar(255) default NULL,
  PRIMARY KEY  (`vendor_id`)
) TYPE=MyISAM AUTO_INCREMENT=2 ;

#
# Dumping data for table `vendor`
#

INSERT INTO `vendor` VALUES (1, 'Washupito\'s Tiendita', 'Owner', 'Demo', 'Store', 'Mr.', '555-555-1212', '555-555-1212', '555-555-1212', 'noreply@phpshop.org', '555-555-1212', '100 Washupito Avenue, N.W.', '', 'Lake Forest', 'CA', 'USA', '92630', 'Washupito\'s Tiendita', '<table bgcolor="#DDDDDD" width="80%" align="center"><tr align="center"><td>\r\n<p>For this demonstration, please login as<br />Username: demo, Password: demo.</p>\r\n<p>This demonstration does not allow new shopper registration or any administrative changes to the system.</p>\r\n</td></tr></table>\r\n<p>We have the best tools for do-it-yourselfers.  Check us out! </p>\r\n<p>We were established in 1969 in a time when getting good tools was expensive, but the quality was good.  Now that only a select few of those authentic tools survive, we have dedicated this store to bringing the experience alive for collectors and master mechanics everywhere.  </p>\r\n\r\n<p>You can easily find products selecting the category you would like to browse above.</p>', 0, '', 'c19970d6f2970cb0d1b13bea3af3144a.gif', 'USD', 950302468, 1090507214, 'images/shop/');

# --------------------------------------------------------

#
# Table structure for table `vendor_category`
#

CREATE TABLE `vendor_category` (
  `vendor_category_id` int(11) NOT NULL auto_increment,
  `vendor_category_name` varchar(64) default NULL,
  `vendor_category_desc` text,
  PRIMARY KEY  (`vendor_category_id`)
) TYPE=MyISAM AUTO_INCREMENT=7 ;

#
# Dumping data for table `vendor_category`
#

INSERT INTO `vendor_category` VALUES (6, '-default-', 'Default');

# --------------------------------------------------------

#
# Table structure for table `zone_country`
#

CREATE TABLE `zone_country` (
  `country_id` int(11) NOT NULL default '0',
  `zone_id` int(11) NOT NULL default '1',
  `country_name` varchar(64) default NULL,
  `country_3_code` char(3) default NULL,
  `country_2_code` char(2) default NULL,
  PRIMARY KEY  (`country_id`)
) TYPE=MyISAM;

#
# Dumping data for table `zone_country`
#

INSERT INTO `zone_country` VALUES (4, 4, 'AFGHANISTAN', 'AFG', 'AF');
INSERT INTO `zone_country` VALUES (8, 3, 'ALBANIA', 'ALB', 'AL');
INSERT INTO `zone_country` VALUES (12, 2, 'ALGERIA', 'DZA', 'DZ');
INSERT INTO `zone_country` VALUES (16, 1, 'AMERICAN SAMOA', 'ASM', 'AS');
INSERT INTO `zone_country` VALUES (20, 1, 'ANDORRA', 'AND', 'AD');
INSERT INTO `zone_country` VALUES (24, 1, 'ANGOLA', 'AGO', 'AO');
INSERT INTO `zone_country` VALUES (660, 1, 'ANGUILLA', 'AIA', 'AI');
INSERT INTO `zone_country` VALUES (10, 2, 'ANTARCTICA', 'ATA', 'AQ');
INSERT INTO `zone_country` VALUES (28, 1, 'ANTIGUA AND BARBUDA', 'ATG', 'AG');
INSERT INTO `zone_country` VALUES (32, 1, 'ARGENTINA', 'ARG', 'AR');
INSERT INTO `zone_country` VALUES (51, 1, 'ARMENIA', 'ARM', 'AM');
INSERT INTO `zone_country` VALUES (533, 1, 'ARUBA', 'ABW', 'AW');
INSERT INTO `zone_country` VALUES (36, 1, 'AUSTRALIA', 'AUS', 'AU');
INSERT INTO `zone_country` VALUES (40, 1, 'AUSTRIA', 'AUT', 'AT');
INSERT INTO `zone_country` VALUES (31, 1, 'AZERBAIJAN', 'AZE', 'AZ');
INSERT INTO `zone_country` VALUES (44, 1, 'BAHAMAS', 'BHS', 'BS');
INSERT INTO `zone_country` VALUES (48, 1, 'BAHRAIN', 'BHR', 'BH');
INSERT INTO `zone_country` VALUES (50, 1, 'BANGLADESH', 'BGD', 'BD');
INSERT INTO `zone_country` VALUES (52, 1, 'BARBADOS', 'BRB', 'BB');
INSERT INTO `zone_country` VALUES (112, 1, 'BELARUS', 'BLR', 'BY');
INSERT INTO `zone_country` VALUES (56, 1, 'BELGIUM', 'BEL', 'BE');
INSERT INTO `zone_country` VALUES (84, 1, 'BELIZE', 'BLZ', 'BZ');
INSERT INTO `zone_country` VALUES (204, 1, 'BENIN', 'BEN', 'BJ');
INSERT INTO `zone_country` VALUES (60, 1, 'BERMUDA', 'BMU', 'BM');
INSERT INTO `zone_country` VALUES (64, 1, 'BHUTAN', 'BTN', 'BT');
INSERT INTO `zone_country` VALUES (68, 1, 'BOLIVIA', 'BOL', 'BO');
INSERT INTO `zone_country` VALUES (70, 1, 'BOSNIA AND HERZEGOWINA', 'BIH', 'BA');
INSERT INTO `zone_country` VALUES (72, 1, 'BOTSWANA', 'BWA', 'BW');
INSERT INTO `zone_country` VALUES (74, 1, 'BOUVET ISLAND', 'BVT', 'BV');
INSERT INTO `zone_country` VALUES (76, 1, 'BRAZIL', 'BRA', 'BR');
INSERT INTO `zone_country` VALUES (86, 1, 'BRITISH INDIAN OCEAN TERRITORY', 'IOT', 'IO');
INSERT INTO `zone_country` VALUES (96, 1, 'BRUNEI DARUSSALAM', 'BRN', 'BN');
INSERT INTO `zone_country` VALUES (100, 1, 'BULGARIA', 'BGR', 'BG');
INSERT INTO `zone_country` VALUES (854, 1, 'BURKINA FASO', 'BFA', 'BF');
INSERT INTO `zone_country` VALUES (108, 1, 'BURUNDI', 'BDI', 'BI');
INSERT INTO `zone_country` VALUES (116, 1, 'CAMBODIA', 'KHM', 'KH');
INSERT INTO `zone_country` VALUES (120, 1, 'CAMEROON', 'CMR', 'CM');
INSERT INTO `zone_country` VALUES (124, 1, 'CANADA', 'CAN', 'CA');
INSERT INTO `zone_country` VALUES (132, 1, 'CAPE VERDE', 'CPV', 'CV');
INSERT INTO `zone_country` VALUES (136, 1, 'CAYMAN ISLANDS', 'CYM', 'KY');
INSERT INTO `zone_country` VALUES (140, 1, 'CENTRAL AFRICAN REPUBLIC', 'CAF', 'CF');
INSERT INTO `zone_country` VALUES (148, 1, 'CHAD', 'TCD', 'TD');
INSERT INTO `zone_country` VALUES (152, 1, 'CHILE', 'CHL', 'CL');
INSERT INTO `zone_country` VALUES (156, 1, 'CHINA', 'CHN', 'CN');
INSERT INTO `zone_country` VALUES (162, 1, 'CHRISTMAS ISLAND', 'CXR', 'CX');
INSERT INTO `zone_country` VALUES (166, 1, 'COCOS (KEELING) ISLANDS', 'CCK', 'CC');
INSERT INTO `zone_country` VALUES (170, 1, 'COLOMBIA', 'COL', 'CO');
INSERT INTO `zone_country` VALUES (174, 1, 'COMOROS', 'COM', 'KM');
INSERT INTO `zone_country` VALUES (178, 1, 'CONGO', 'COG', 'CG');
INSERT INTO `zone_country` VALUES (180, 1, 'CONGO, THE DEMOCRATIC REPUBLIC OF THE', 'COD', 'CD');
INSERT INTO `zone_country` VALUES (184, 1, 'COOK ISLANDS', 'COK', 'CK');
INSERT INTO `zone_country` VALUES (188, 1, 'COSTA RICA', 'CRI', 'CR');
INSERT INTO `zone_country` VALUES (384, 1, 'COTE D\'IVOIRE', 'CIV', 'CI');
INSERT INTO `zone_country` VALUES (191, 1, 'CROATIA (local name: Hrvatska)', 'HRV', 'HR');
INSERT INTO `zone_country` VALUES (192, 1, 'CUBA', 'CUB', 'CU');
INSERT INTO `zone_country` VALUES (196, 1, 'CYPRUS', 'CYP', 'CY');
INSERT INTO `zone_country` VALUES (203, 1, 'CZECH REPUBLIC', 'CZE', 'CZ');
INSERT INTO `zone_country` VALUES (208, 1, 'DENMARK', 'DNK', 'DK');
INSERT INTO `zone_country` VALUES (262, 1, 'DJIBOUTI', 'DJI', 'DJ');
INSERT INTO `zone_country` VALUES (212, 1, 'DOMINICA', 'DMA', 'DM');
INSERT INTO `zone_country` VALUES (214, 1, 'DOMINICAN REPUBLIC', 'DOM', 'DO');
INSERT INTO `zone_country` VALUES (626, 1, 'EAST TIMOR', 'TMP', 'TP');
INSERT INTO `zone_country` VALUES (218, 1, 'ECUADOR', 'ECU', 'EC');
INSERT INTO `zone_country` VALUES (818, 1, 'EGYPT', 'EGY', 'EG');
INSERT INTO `zone_country` VALUES (222, 1, 'EL SALVADOR', 'SLV', 'SV');
INSERT INTO `zone_country` VALUES (226, 1, 'EQUATORIAL GUINEA', 'GNQ', 'GQ');
INSERT INTO `zone_country` VALUES (232, 1, 'ERITREA', 'ERI', 'ER');
INSERT INTO `zone_country` VALUES (233, 1, 'ESTONIA', 'EST', 'EE');
INSERT INTO `zone_country` VALUES (231, 1, 'ETHIOPIA', 'ETH', 'ET');
INSERT INTO `zone_country` VALUES (238, 1, 'FALKLAND ISLANDS (MALVINAS)', 'FLK', 'FK');
INSERT INTO `zone_country` VALUES (234, 1, 'FAROE ISLANDS', 'FRO', 'FO');
INSERT INTO `zone_country` VALUES (242, 1, 'FIJI', 'FJI', 'FJ');
INSERT INTO `zone_country` VALUES (246, 1, 'FINLAND', 'FIN', 'FI');
INSERT INTO `zone_country` VALUES (250, 1, 'FRANCE', 'FRA', 'FR');
INSERT INTO `zone_country` VALUES (249, 1, 'FRANCE, METROPOLITAN', 'FXX', 'FX');
INSERT INTO `zone_country` VALUES (254, 1, 'FRENCH GUIANA', 'GUF', 'GF');
INSERT INTO `zone_country` VALUES (258, 1, 'FRENCH POLYNESIA', 'PYF', 'PF');
INSERT INTO `zone_country` VALUES (260, 1, 'FRENCH SOUTHERN TERRITORIES', 'ATF', 'TF');
INSERT INTO `zone_country` VALUES (266, 1, 'GABON', 'GAB', 'GA');
INSERT INTO `zone_country` VALUES (270, 1, 'GAMBIA', 'GMB', 'GM');
INSERT INTO `zone_country` VALUES (268, 1, 'GEORGIA', 'GEO', 'GE');
INSERT INTO `zone_country` VALUES (276, 1, 'GERMANY', 'DEU', 'DE');
INSERT INTO `zone_country` VALUES (288, 1, 'GHANA', 'GHA', 'GH');
INSERT INTO `zone_country` VALUES (292, 1, 'GIBRALTAR', 'GIB', 'GI');
INSERT INTO `zone_country` VALUES (300, 1, 'GREECE', 'GRC', 'GR');
INSERT INTO `zone_country` VALUES (304, 1, 'GREENLAND', 'GRL', 'GL');
INSERT INTO `zone_country` VALUES (308, 1, 'GRENADA', 'GRD', 'GD');
INSERT INTO `zone_country` VALUES (312, 1, 'GUADELOUPE', 'GLP', 'GP');
INSERT INTO `zone_country` VALUES (316, 1, 'GUAM', 'GUM', 'GU');
INSERT INTO `zone_country` VALUES (320, 1, 'GUATEMALA', 'GTM', 'GT');
INSERT INTO `zone_country` VALUES (324, 1, 'GUINEA', 'GIN', 'GN');
INSERT INTO `zone_country` VALUES (624, 1, 'GUINEA-BISSAU', 'GNB', 'GW');
INSERT INTO `zone_country` VALUES (328, 1, 'GUYANA', 'GUY', 'GY');
INSERT INTO `zone_country` VALUES (332, 1, 'HAITI', 'HTI', 'HT');
INSERT INTO `zone_country` VALUES (334, 1, 'HEARD AND MC DONALD ISLANDS', 'HMD', 'HM');
INSERT INTO `zone_country` VALUES (336, 1, 'HOLY SEE (VATICAN CITY STATE)', 'VAT', 'VA');
INSERT INTO `zone_country` VALUES (340, 1, 'HONDURAS', 'HND', 'HN');
INSERT INTO `zone_country` VALUES (344, 1, 'HONG KONG', 'HKG', 'HK');
INSERT INTO `zone_country` VALUES (348, 1, 'HUNGARY', 'HUN', 'HU');
INSERT INTO `zone_country` VALUES (352, 1, 'ICELAND', 'ISL', 'IS');
INSERT INTO `zone_country` VALUES (356, 1, 'INDIA', 'IND', 'IN');
INSERT INTO `zone_country` VALUES (360, 1, 'INDONESIA', 'IDN', 'ID');
INSERT INTO `zone_country` VALUES (364, 1, 'IRAN (ISLAMIC REPUBLIC OF)', 'IRN', 'IR');
INSERT INTO `zone_country` VALUES (368, 1, 'IRAQ', 'IRQ', 'IQ');
INSERT INTO `zone_country` VALUES (372, 1, 'IRELAND', 'IRL', 'IE');
INSERT INTO `zone_country` VALUES (376, 1, 'ISRAEL', 'ISR', 'IL');
INSERT INTO `zone_country` VALUES (380, 1, 'ITALY', 'ITA', 'IT');
INSERT INTO `zone_country` VALUES (388, 1, 'JAMAICA', 'JAM', 'JM');
INSERT INTO `zone_country` VALUES (392, 1, 'JAPAN', 'JPN', 'JP');
INSERT INTO `zone_country` VALUES (400, 1, 'JORDAN', 'JOR', 'JO');
INSERT INTO `zone_country` VALUES (398, 1, 'KAZAKHSTAN', 'KAZ', 'KZ');
INSERT INTO `zone_country` VALUES (404, 1, 'KENYA', 'KEN', 'KE');
INSERT INTO `zone_country` VALUES (296, 1, 'KIRIBATI', 'KIR', 'KI');
INSERT INTO `zone_country` VALUES (408, 1, 'KOREA, DEMOCRATIC PEOPLE\'S REPUBLIC OF', 'PRK', 'KP');
INSERT INTO `zone_country` VALUES (410, 1, 'KOREA, REPUBLIC OF', 'KOR', 'KR');
INSERT INTO `zone_country` VALUES (414, 1, 'KUWAIT', 'KWT', 'KW');
INSERT INTO `zone_country` VALUES (417, 1, 'KYRGYZSTAN', 'KGZ', 'KG');
INSERT INTO `zone_country` VALUES (418, 1, 'LAO PEOPLE\'S DEMOCRATIC REPUBLIC', 'LAO', 'LA');
INSERT INTO `zone_country` VALUES (428, 1, 'LATVIA', 'LVA', 'LV');
INSERT INTO `zone_country` VALUES (422, 1, 'LEBANON', 'LBN', 'LB');
INSERT INTO `zone_country` VALUES (426, 1, 'LESOTHO', 'LSO', 'LS');
INSERT INTO `zone_country` VALUES (430, 1, 'LIBERIA', 'LBR', 'LR');
INSERT INTO `zone_country` VALUES (434, 1, 'LIBYAN ARAB JAMAHIRIYA', 'LBY', 'LY');
INSERT INTO `zone_country` VALUES (438, 1, 'LIECHTENSTEIN', 'LIE', 'LI');
INSERT INTO `zone_country` VALUES (440, 1, 'LITHUANIA', 'LTU', 'LT');
INSERT INTO `zone_country` VALUES (442, 1, 'LUXEMBOURG', 'LUX', 'LU');
INSERT INTO `zone_country` VALUES (446, 1, 'MACAU', 'MAC', 'MO');
INSERT INTO `zone_country` VALUES (807, 1, 'MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF', 'MKD', 'MK');
INSERT INTO `zone_country` VALUES (450, 1, 'MADAGASCAR', 'MDG', 'MG');
INSERT INTO `zone_country` VALUES (454, 1, 'MALAWI', 'MWI', 'MW');
INSERT INTO `zone_country` VALUES (458, 1, 'MALAYSIA', 'MYS', 'MY');
INSERT INTO `zone_country` VALUES (462, 1, 'MALDIVES', 'MDV', 'MV');
INSERT INTO `zone_country` VALUES (466, 1, 'MALI', 'MLI', 'ML');
INSERT INTO `zone_country` VALUES (470, 1, 'MALTA', 'MLT', 'MT');
INSERT INTO `zone_country` VALUES (584, 1, 'MARSHALL ISLANDS', 'MHL', 'MH');
INSERT INTO `zone_country` VALUES (474, 1, 'MARTINIQUE', 'MTQ', 'MQ');
INSERT INTO `zone_country` VALUES (478, 1, 'MAURITANIA', 'MRT', 'MR');
INSERT INTO `zone_country` VALUES (480, 1, 'MAURITIUS', 'MUS', 'MU');
INSERT INTO `zone_country` VALUES (175, 1, 'MAYOTTE', 'MYT', 'YT');
INSERT INTO `zone_country` VALUES (484, 1, 'MEXICO', 'MEX', 'MX');
INSERT INTO `zone_country` VALUES (583, 1, 'MICRONESIA, FEDERATED STATES OF', 'FSM', 'FM');
INSERT INTO `zone_country` VALUES (498, 1, 'MOLDOVA, REPUBLIC OF', 'MDA', 'MD');
INSERT INTO `zone_country` VALUES (492, 1, 'MONACO', 'MCO', 'MC');
INSERT INTO `zone_country` VALUES (496, 2, 'MONGOLIA', 'MNG', 'MN');
INSERT INTO `zone_country` VALUES (500, 1, 'MONTSERRAT', 'MSR', 'MS');
INSERT INTO `zone_country` VALUES (504, 1, 'MOROCCO', 'MAR', 'MA');
INSERT INTO `zone_country` VALUES (508, 1, 'MOZAMBIQUE', 'MOZ', 'MZ');
INSERT INTO `zone_country` VALUES (104, 1, 'MYANMAR', 'MMR', 'MM');
INSERT INTO `zone_country` VALUES (516, 1, 'NAMIBIA', 'NAM', 'NA');
INSERT INTO `zone_country` VALUES (520, 1, 'NAURU', 'NRU', 'NR');
INSERT INTO `zone_country` VALUES (524, 1, 'NEPAL', 'NPL', 'NP');
INSERT INTO `zone_country` VALUES (528, 1, 'NETHERLANDS', 'NLD', 'NL');
INSERT INTO `zone_country` VALUES (530, 1, 'NETHERLANDS ANTILLES', 'ANT', 'AN');
INSERT INTO `zone_country` VALUES (540, 1, 'NEW CALEDONIA', 'NCL', 'NC');
INSERT INTO `zone_country` VALUES (554, 1, 'NEW ZEALAND', 'NZL', 'NZ');
INSERT INTO `zone_country` VALUES (558, 1, 'NICARAGUA', 'NIC', 'NI');
INSERT INTO `zone_country` VALUES (562, 1, 'NIGER', 'NER', 'NE');
INSERT INTO `zone_country` VALUES (566, 1, 'NIGERIA', 'NGA', 'NG');
INSERT INTO `zone_country` VALUES (570, 1, 'NIUE', 'NIU', 'NU');
INSERT INTO `zone_country` VALUES (574, 1, 'NORFOLK ISLAND', 'NFK', 'NF');
INSERT INTO `zone_country` VALUES (580, 1, 'NORTHERN MARIANA ISLANDS', 'MNP', 'MP');
INSERT INTO `zone_country` VALUES (578, 1, 'NORWAY', 'NOR', 'NO');
INSERT INTO `zone_country` VALUES (512, 1, 'OMAN', 'OMN', 'OM');
INSERT INTO `zone_country` VALUES (586, 1, 'PAKISTAN', 'PAK', 'PK');
INSERT INTO `zone_country` VALUES (585, 1, 'PALAU', 'PLW', 'PW');
INSERT INTO `zone_country` VALUES (275, 1, 'PALESTINIAN TERRITORY, OCCUPIED', '  P', '');
INSERT INTO `zone_country` VALUES (591, 1, 'PANAMA', 'PAN', 'PA');
INSERT INTO `zone_country` VALUES (598, 1, 'PAPUA NEW GUINEA', 'PNG', 'PG');
INSERT INTO `zone_country` VALUES (600, 1, 'PARAGUAY', 'PRY', 'PY');
INSERT INTO `zone_country` VALUES (604, 1, 'PERU', 'PER', 'PE');
INSERT INTO `zone_country` VALUES (608, 1, 'PHILIPPINES', 'PHL', 'PH');
INSERT INTO `zone_country` VALUES (612, 1, 'PITCAIRN', 'PCN', 'PN');
INSERT INTO `zone_country` VALUES (616, 1, 'POLAND', 'POL', 'PL');
INSERT INTO `zone_country` VALUES (620, 1, 'PORTUGAL', 'PRT', 'PT');
INSERT INTO `zone_country` VALUES (630, 1, 'PUERTO RICO', 'PRI', 'PR');
INSERT INTO `zone_country` VALUES (634, 1, 'QATAR', 'QAT', 'QA');
INSERT INTO `zone_country` VALUES (638, 1, 'REUNION', 'REU', 'RE');
INSERT INTO `zone_country` VALUES (642, 1, 'ROMANIA', 'ROM', 'RO');
INSERT INTO `zone_country` VALUES (643, 1, 'RUSSIAN FEDERATION', 'RUS', 'RU');
INSERT INTO `zone_country` VALUES (646, 1, 'RWANDA', 'RWA', 'RW');
INSERT INTO `zone_country` VALUES (659, 1, 'SAINT KITTS AND NEVIS', 'KNA', 'KN');
INSERT INTO `zone_country` VALUES (662, 1, 'SAINT LUCIA', 'LCA', 'LC');
INSERT INTO `zone_country` VALUES (670, 1, 'SAINT VINCENT AND THE GRENADINES', 'VCT', 'VC');
INSERT INTO `zone_country` VALUES (882, 1, 'SAMOA', 'WSM', 'WS');
INSERT INTO `zone_country` VALUES (674, 1, 'SAN MARINO', 'SMR', 'SM');
INSERT INTO `zone_country` VALUES (678, 1, 'SAO TOME AND PRINCIPE', 'STP', 'ST');
INSERT INTO `zone_country` VALUES (682, 1, 'SAUDI ARABIA', 'SAU', 'SA');
INSERT INTO `zone_country` VALUES (686, 1, 'SENEGAL', 'SEN', 'SN');
INSERT INTO `zone_country` VALUES (690, 1, 'SEYCHELLES', 'SYC', 'SC');
INSERT INTO `zone_country` VALUES (694, 1, 'SIERRA LEONE', 'SLE', 'SL');
INSERT INTO `zone_country` VALUES (702, 1, 'SINGAPORE', 'SGP', 'SG');
INSERT INTO `zone_country` VALUES (703, 1, 'SLOVAKIA (Slovak Republic)', 'SVK', 'SK');
INSERT INTO `zone_country` VALUES (705, 1, 'SLOVENIA', 'SVN', 'SI');
INSERT INTO `zone_country` VALUES (90, 1, 'SOLOMON ISLANDS', 'SLB', 'SB');
INSERT INTO `zone_country` VALUES (706, 1, 'SOMALIA', 'SOM', 'SO');
INSERT INTO `zone_country` VALUES (710, 1, 'SOUTH AFRICA', 'ZAF', 'ZA');
INSERT INTO `zone_country` VALUES (239, 1, 'SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS', 'SGS', 'GS');
INSERT INTO `zone_country` VALUES (724, 1, 'SPAIN', 'ESP', 'ES');
INSERT INTO `zone_country` VALUES (144, 1, 'SRI LANKA', 'LKA', 'LK');
INSERT INTO `zone_country` VALUES (654, 1, 'ST. HELENA', 'SHN', 'SH');
INSERT INTO `zone_country` VALUES (666, 1, 'ST. PIERRE AND MIQUELON', 'SPM', 'PM');
INSERT INTO `zone_country` VALUES (736, 1, 'SUDAN', 'SDN', 'SD');
INSERT INTO `zone_country` VALUES (740, 1, 'SURINAME', 'SUR', 'SR');
INSERT INTO `zone_country` VALUES (744, 1, 'SVALBARD AND JAN MAYEN ISLANDS', 'SJM', 'SJ');
INSERT INTO `zone_country` VALUES (748, 1, 'SWAZILAND', 'SWZ', 'SZ');
INSERT INTO `zone_country` VALUES (752, 1, 'SWEDEN', 'SWE', 'SE');
INSERT INTO `zone_country` VALUES (756, 1, 'SWITZERLAND', 'CHE', 'CH');
INSERT INTO `zone_country` VALUES (760, 1, 'SYRIAN ARAB REPUBLIC', 'SYR', 'SY');
INSERT INTO `zone_country` VALUES (158, 1, 'TAIWAN, PROVINCE OF CHINA', 'TWN', 'TW');
INSERT INTO `zone_country` VALUES (762, 1, 'TAJIKISTAN', 'TJK', 'TJ');
INSERT INTO `zone_country` VALUES (834, 1, 'TANZANIA, UNITED REPUBLIC OF', 'TZA', 'TZ');
INSERT INTO `zone_country` VALUES (764, 1, 'THAILAND', 'THA', 'TH');
INSERT INTO `zone_country` VALUES (768, 1, 'TOGO', 'TGO', 'TG');
INSERT INTO `zone_country` VALUES (772, 1, 'TOKELAU', 'TKL', 'TK');
INSERT INTO `zone_country` VALUES (776, 1, 'TONGA', 'TON', 'TO');
INSERT INTO `zone_country` VALUES (780, 1, 'TRINIDAD AND TOBAGO', 'TTO', 'TT');
INSERT INTO `zone_country` VALUES (788, 1, 'TUNISIA', 'TUN', 'TN');
INSERT INTO `zone_country` VALUES (792, 1, 'TURKEY', 'TUR', 'TR');
INSERT INTO `zone_country` VALUES (795, 1, 'TURKMENISTAN', 'TKM', 'TM');
INSERT INTO `zone_country` VALUES (796, 1, 'TURKS AND CAICOS ISLANDS', 'TCA', 'TC');
INSERT INTO `zone_country` VALUES (798, 1, 'TUVALU', 'TUV', 'TV');
INSERT INTO `zone_country` VALUES (800, 1, 'UGANDA', 'UGA', 'UG');
INSERT INTO `zone_country` VALUES (804, 1, 'UKRAINE', 'UKR', 'UA');
INSERT INTO `zone_country` VALUES (784, 1, 'UNITED ARAB EMIRATES', 'ARE', 'AE');
INSERT INTO `zone_country` VALUES (826, 1, 'UNITED KINGDOM', 'GBR', 'GB');
INSERT INTO `zone_country` VALUES (840, 1, 'UNITED STATES', 'USA', 'US');
INSERT INTO `zone_country` VALUES (581, 1, 'UNITED STATES MINOR OUTLYING ISLANDS', 'UMI', 'UM');
INSERT INTO `zone_country` VALUES (858, 1, 'URUGUAY', 'URY', 'UY');
INSERT INTO `zone_country` VALUES (860, 1, 'UZBEKISTAN', 'UZB', 'UZ');
INSERT INTO `zone_country` VALUES (548, 1, 'VANUATU', 'VUT', 'VU');
INSERT INTO `zone_country` VALUES (862, 1, 'VENEZUELA', 'VEN', 'VE');
INSERT INTO `zone_country` VALUES (704, 1, 'VIET NAM', 'VNM', 'VN');
INSERT INTO `zone_country` VALUES (92, 1, 'VIRGIN ISLANDS (BRITISH)', 'VGB', 'VG');
INSERT INTO `zone_country` VALUES (850, 1, 'VIRGIN ISLANDS (U.S.)', 'VIR', 'VI');
INSERT INTO `zone_country` VALUES (876, 1, 'WALLIS AND FUTUNA ISLANDS', 'WLF', 'WF');
INSERT INTO `zone_country` VALUES (732, 1, 'WESTERN SAHARA', 'ESH', 'EH');
INSERT INTO `zone_country` VALUES (887, 1, 'YEMEN', 'YEM', 'YE');
INSERT INTO `zone_country` VALUES (891, 1, 'YUGOSLAVIA', 'YUG', 'YU');
INSERT INTO `zone_country` VALUES (894, 1, 'ZAMBIA', 'ZMB', 'ZM');
INSERT INTO `zone_country` VALUES (716, 1, 'ZIMBABWE', 'ZWE', 'ZW');

# --------------------------------------------------------

#
# Table structure for table `zone_shipping`
#

CREATE TABLE `zone_shipping` (
  `zone_id` int(11) NOT NULL auto_increment,
  `zone_name` varchar(255) default NULL,
  `zone_cost` decimal(10,2) default NULL,
  `zone_limit` decimal(10,2) default NULL,
  `zone_description` text NOT NULL,
  PRIMARY KEY  (`zone_id`),
  KEY `zone_id` (`zone_id`)
) TYPE=MyISAM AUTO_INCREMENT=5 ;

#
# Dumping data for table `zone_shipping`
#

INSERT INTO `zone_shipping` VALUES (1, 'Default', '6.00', '35.00', 'This is the default Shipping Zone. This is the zone information that all countries will use until you assign each individual country to a Zone.');
INSERT INTO `zone_shipping` VALUES (2, 'Zone 1', '1000.00', '10000.00', 'This is a zone example');
INSERT INTO `zone_shipping` VALUES (3, 'Zone 2', '2.00', '22.00', 'This is the second zone. You can use this for notes about this zone');
INSERT INTO `zone_shipping` VALUES (4, 'Zone 3', '11.00', '64.00', 'Another usefull thing might be details about this zone or special instructions.');
