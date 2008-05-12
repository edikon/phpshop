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

#
# Table structure for table `zone_country`
#

CREATE TABLE zone_country (
  country_id int(11) NOT NULL default '0',
  zone_id int(11) NOT NULL default '1',
  country_name varchar(64) default NULL,
  country_3_code char(3) default NULL,
  country_2_code char(2) default NULL,
  PRIMARY KEY  (country_id)
) TYPE=MyISAM;

#
# Dumping data for table `zone_country`
#

INSERT INTO zone_country VALUES (4, 4, 'AFGHANISTAN', 'AFG', 'AF');
INSERT INTO zone_country VALUES (8, 3, 'ALBANIA', 'ALB', 'AL');
INSERT INTO zone_country VALUES (12, 2, 'ALGERIA', 'DZA', 'DZ');
INSERT INTO zone_country VALUES (16, 1, 'AMERICAN SAMOA', 'ASM', 'AS');
INSERT INTO zone_country VALUES (20, 1, 'ANDORRA', 'AND', 'AD');
INSERT INTO zone_country VALUES (24, 1, 'ANGOLA', 'AGO', 'AO');
INSERT INTO zone_country VALUES (660, 1, 'ANGUILLA', 'AIA', 'AI');
INSERT INTO zone_country VALUES (10, 2, 'ANTARCTICA', 'ATA', 'AQ');
INSERT INTO zone_country VALUES (28, 1, 'ANTIGUA AND BARBUDA', 'ATG', 'AG');
INSERT INTO zone_country VALUES (32, 1, 'ARGENTINA', 'ARG', 'AR');
INSERT INTO zone_country VALUES (51, 1, 'ARMENIA', 'ARM', 'AM');
INSERT INTO zone_country VALUES (533, 1, 'ARUBA', 'ABW', 'AW');
INSERT INTO zone_country VALUES (36, 1, 'AUSTRALIA', 'AUS', 'AU');
INSERT INTO zone_country VALUES (40, 1, 'AUSTRIA', 'AUT', 'AT');
INSERT INTO zone_country VALUES (31, 1, 'AZERBAIJAN', 'AZE', 'AZ');
INSERT INTO zone_country VALUES (44, 1, 'BAHAMAS', 'BHS', 'BS');
INSERT INTO zone_country VALUES (48, 1, 'BAHRAIN', 'BHR', 'BH');
INSERT INTO zone_country VALUES (50, 1, 'BANGLADESH', 'BGD', 'BD');
INSERT INTO zone_country VALUES (52, 1, 'BARBADOS', 'BRB', 'BB');
INSERT INTO zone_country VALUES (112, 1, 'BELARUS', 'BLR', 'BY');
INSERT INTO zone_country VALUES (56, 1, 'BELGIUM', 'BEL', 'BE');
INSERT INTO zone_country VALUES (84, 1, 'BELIZE', 'BLZ', 'BZ');
INSERT INTO zone_country VALUES (204, 1, 'BENIN', 'BEN', 'BJ');
INSERT INTO zone_country VALUES (60, 1, 'BERMUDA', 'BMU', 'BM');
INSERT INTO zone_country VALUES (64, 1, 'BHUTAN', 'BTN', 'BT');
INSERT INTO zone_country VALUES (68, 1, 'BOLIVIA', 'BOL', 'BO');
INSERT INTO zone_country VALUES (70, 1, 'BOSNIA AND HERZEGOWINA', 'BIH', 'BA');
INSERT INTO zone_country VALUES (72, 1, 'BOTSWANA', 'BWA', 'BW');
INSERT INTO zone_country VALUES (74, 1, 'BOUVET ISLAND', 'BVT', 'BV');
INSERT INTO zone_country VALUES (76, 1, 'BRAZIL', 'BRA', 'BR');
INSERT INTO zone_country VALUES (86, 1, 'BRITISH INDIAN OCEAN TERRITORY', 'IOT', 'IO');
INSERT INTO zone_country VALUES (96, 1, 'BRUNEI DARUSSALAM', 'BRN', 'BN');
INSERT INTO zone_country VALUES (100, 1, 'BULGARIA', 'BGR', 'BG');
INSERT INTO zone_country VALUES (854, 1, 'BURKINA FASO', 'BFA', 'BF');
INSERT INTO zone_country VALUES (108, 1, 'BURUNDI', 'BDI', 'BI');
INSERT INTO zone_country VALUES (116, 1, 'CAMBODIA', 'KHM', 'KH');
INSERT INTO zone_country VALUES (120, 1, 'CAMEROON', 'CMR', 'CM');
INSERT INTO zone_country VALUES (124, 1, 'CANADA', 'CAN', 'CA');
INSERT INTO zone_country VALUES (132, 1, 'CAPE VERDE', 'CPV', 'CV');
INSERT INTO zone_country VALUES (136, 1, 'CAYMAN ISLANDS', 'CYM', 'KY');
INSERT INTO zone_country VALUES (140, 1, 'CENTRAL AFRICAN REPUBLIC', 'CAF', 'CF');
INSERT INTO zone_country VALUES (148, 1, 'CHAD', 'TCD', 'TD');
INSERT INTO zone_country VALUES (152, 1, 'CHILE', 'CHL', 'CL');
INSERT INTO zone_country VALUES (156, 1, 'CHINA', 'CHN', 'CN');
INSERT INTO zone_country VALUES (162, 1, 'CHRISTMAS ISLAND', 'CXR', 'CX');
INSERT INTO zone_country VALUES (166, 1, 'COCOS (KEELING) ISLANDS', 'CCK', 'CC');
INSERT INTO zone_country VALUES (170, 1, 'COLOMBIA', 'COL', 'CO');
INSERT INTO zone_country VALUES (174, 1, 'COMOROS', 'COM', 'KM');
INSERT INTO zone_country VALUES (178, 1, 'CONGO', 'COG', 'CG');
INSERT INTO zone_country VALUES (180, 1, 'CONGO, THE DEMOCRATIC REPUBLIC OF THE', 'COD', 'CD');
INSERT INTO zone_country VALUES (184, 1, 'COOK ISLANDS', 'COK', 'CK');
INSERT INTO zone_country VALUES (188, 1, 'COSTA RICA', 'CRI', 'CR');
INSERT INTO zone_country VALUES (384, 1, 'COTE D\'IVOIRE', 'CIV', 'CI');
INSERT INTO zone_country VALUES (191, 1, 'CROATIA (local name: Hrvatska)', 'HRV', 'HR');
INSERT INTO zone_country VALUES (192, 1, 'CUBA', 'CUB', 'CU');
INSERT INTO zone_country VALUES (196, 1, 'CYPRUS', 'CYP', 'CY');
INSERT INTO zone_country VALUES (203, 1, 'CZECH REPUBLIC', 'CZE', 'CZ');
INSERT INTO zone_country VALUES (208, 1, 'DENMARK', 'DNK', 'DK');
INSERT INTO zone_country VALUES (262, 1, 'DJIBOUTI', 'DJI', 'DJ');
INSERT INTO zone_country VALUES (212, 1, 'DOMINICA', 'DMA', 'DM');
INSERT INTO zone_country VALUES (214, 1, 'DOMINICAN REPUBLIC', 'DOM', 'DO');
INSERT INTO zone_country VALUES (626, 1, 'EAST TIMOR', 'TMP', 'TP');
INSERT INTO zone_country VALUES (218, 1, 'ECUADOR', 'ECU', 'EC');
INSERT INTO zone_country VALUES (818, 1, 'EGYPT', 'EGY', 'EG');
INSERT INTO zone_country VALUES (222, 1, 'EL SALVADOR', 'SLV', 'SV');
INSERT INTO zone_country VALUES (226, 1, 'EQUATORIAL GUINEA', 'GNQ', 'GQ');
INSERT INTO zone_country VALUES (232, 1, 'ERITREA', 'ERI', 'ER');
INSERT INTO zone_country VALUES (233, 1, 'ESTONIA', 'EST', 'EE');
INSERT INTO zone_country VALUES (231, 1, 'ETHIOPIA', 'ETH', 'ET');
INSERT INTO zone_country VALUES (238, 1, 'FALKLAND ISLANDS (MALVINAS)', 'FLK', 'FK');
INSERT INTO zone_country VALUES (234, 1, 'FAROE ISLANDS', 'FRO', 'FO');
INSERT INTO zone_country VALUES (242, 1, 'FIJI', 'FJI', 'FJ');
INSERT INTO zone_country VALUES (246, 1, 'FINLAND', 'FIN', 'FI');
INSERT INTO zone_country VALUES (250, 1, 'FRANCE', 'FRA', 'FR');
INSERT INTO zone_country VALUES (249, 1, 'FRANCE, METROPOLITAN', 'FXX', 'FX');
INSERT INTO zone_country VALUES (254, 1, 'FRENCH GUIANA', 'GUF', 'GF');
INSERT INTO zone_country VALUES (258, 1, 'FRENCH POLYNESIA', 'PYF', 'PF');
INSERT INTO zone_country VALUES (260, 1, 'FRENCH SOUTHERN TERRITORIES', 'ATF', 'TF');
INSERT INTO zone_country VALUES (266, 1, 'GABON', 'GAB', 'GA');
INSERT INTO zone_country VALUES (270, 1, 'GAMBIA', 'GMB', 'GM');
INSERT INTO zone_country VALUES (268, 1, 'GEORGIA', 'GEO', 'GE');
INSERT INTO zone_country VALUES (276, 1, 'GERMANY', 'DEU', 'DE');
INSERT INTO zone_country VALUES (288, 1, 'GHANA', 'GHA', 'GH');
INSERT INTO zone_country VALUES (292, 1, 'GIBRALTAR', 'GIB', 'GI');
INSERT INTO zone_country VALUES (300, 1, 'GREECE', 'GRC', 'GR');
INSERT INTO zone_country VALUES (304, 1, 'GREENLAND', 'GRL', 'GL');
INSERT INTO zone_country VALUES (308, 1, 'GRENADA', 'GRD', 'GD');
INSERT INTO zone_country VALUES (312, 1, 'GUADELOUPE', 'GLP', 'GP');
INSERT INTO zone_country VALUES (316, 1, 'GUAM', 'GUM', 'GU');
INSERT INTO zone_country VALUES (320, 1, 'GUATEMALA', 'GTM', 'GT');
INSERT INTO zone_country VALUES (324, 1, 'GUINEA', 'GIN', 'GN');
INSERT INTO zone_country VALUES (624, 1, 'GUINEA-BISSAU', 'GNB', 'GW');
INSERT INTO zone_country VALUES (328, 1, 'GUYANA', 'GUY', 'GY');
INSERT INTO zone_country VALUES (332, 1, 'HAITI', 'HTI', 'HT');
INSERT INTO zone_country VALUES (334, 1, 'HEARD AND MC DONALD ISLANDS', 'HMD', 'HM');
INSERT INTO zone_country VALUES (336, 1, 'HOLY SEE (VATICAN CITY STATE)', 'VAT', 'VA');
INSERT INTO zone_country VALUES (340, 1, 'HONDURAS', 'HND', 'HN');
INSERT INTO zone_country VALUES (344, 1, 'HONG KONG', 'HKG', 'HK');
INSERT INTO zone_country VALUES (348, 1, 'HUNGARY', 'HUN', 'HU');
INSERT INTO zone_country VALUES (352, 1, 'ICELAND', 'ISL', 'IS');
INSERT INTO zone_country VALUES (356, 1, 'INDIA', 'IND', 'IN');
INSERT INTO zone_country VALUES (360, 1, 'INDONESIA', 'IDN', 'ID');
INSERT INTO zone_country VALUES (364, 1, 'IRAN (ISLAMIC REPUBLIC OF)', 'IRN', 'IR');
INSERT INTO zone_country VALUES (368, 1, 'IRAQ', 'IRQ', 'IQ');
INSERT INTO zone_country VALUES (372, 1, 'IRELAND', 'IRL', 'IE');
INSERT INTO zone_country VALUES (376, 1, 'ISRAEL', 'ISR', 'IL');
INSERT INTO zone_country VALUES (380, 1, 'ITALY', 'ITA', 'IT');
INSERT INTO zone_country VALUES (388, 1, 'JAMAICA', 'JAM', 'JM');
INSERT INTO zone_country VALUES (392, 1, 'JAPAN', 'JPN', 'JP');
INSERT INTO zone_country VALUES (400, 1, 'JORDAN', 'JOR', 'JO');
INSERT INTO zone_country VALUES (398, 1, 'KAZAKHSTAN', 'KAZ', 'KZ');
INSERT INTO zone_country VALUES (404, 1, 'KENYA', 'KEN', 'KE');
INSERT INTO zone_country VALUES (296, 1, 'KIRIBATI', 'KIR', 'KI');
INSERT INTO zone_country VALUES (408, 1, 'KOREA, DEMOCRATIC PEOPLE\'S REPUBLIC OF', 'PRK', 'KP');
INSERT INTO zone_country VALUES (410, 1, 'KOREA, REPUBLIC OF', 'KOR', 'KR');
INSERT INTO zone_country VALUES (414, 1, 'KUWAIT', 'KWT', 'KW');
INSERT INTO zone_country VALUES (417, 1, 'KYRGYZSTAN', 'KGZ', 'KG');
INSERT INTO zone_country VALUES (418, 1, 'LAO PEOPLE\'S DEMOCRATIC REPUBLIC', 'LAO', 'LA');
INSERT INTO zone_country VALUES (428, 1, 'LATVIA', 'LVA', 'LV');
INSERT INTO zone_country VALUES (422, 1, 'LEBANON', 'LBN', 'LB');
INSERT INTO zone_country VALUES (426, 1, 'LESOTHO', 'LSO', 'LS');
INSERT INTO zone_country VALUES (430, 1, 'LIBERIA', 'LBR', 'LR');
INSERT INTO zone_country VALUES (434, 1, 'LIBYAN ARAB JAMAHIRIYA', 'LBY', 'LY');
INSERT INTO zone_country VALUES (438, 1, 'LIECHTENSTEIN', 'LIE', 'LI');
INSERT INTO zone_country VALUES (440, 1, 'LITHUANIA', 'LTU', 'LT');
INSERT INTO zone_country VALUES (442, 1, 'LUXEMBOURG', 'LUX', 'LU');
INSERT INTO zone_country VALUES (446, 1, 'MACAU', 'MAC', 'MO');
INSERT INTO zone_country VALUES (807, 1, 'MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF', 'MKD', 'MK');
INSERT INTO zone_country VALUES (450, 1, 'MADAGASCAR', 'MDG', 'MG');
INSERT INTO zone_country VALUES (454, 1, 'MALAWI', 'MWI', 'MW');
INSERT INTO zone_country VALUES (458, 1, 'MALAYSIA', 'MYS', 'MY');
INSERT INTO zone_country VALUES (462, 1, 'MALDIVES', 'MDV', 'MV');
INSERT INTO zone_country VALUES (466, 1, 'MALI', 'MLI', 'ML');
INSERT INTO zone_country VALUES (470, 1, 'MALTA', 'MLT', 'MT');
INSERT INTO zone_country VALUES (584, 1, 'MARSHALL ISLANDS', 'MHL', 'MH');
INSERT INTO zone_country VALUES (474, 1, 'MARTINIQUE', 'MTQ', 'MQ');
INSERT INTO zone_country VALUES (478, 1, 'MAURITANIA', 'MRT', 'MR');
INSERT INTO zone_country VALUES (480, 1, 'MAURITIUS', 'MUS', 'MU');
INSERT INTO zone_country VALUES (175, 1, 'MAYOTTE', 'MYT', 'YT');
INSERT INTO zone_country VALUES (484, 1, 'MEXICO', 'MEX', 'MX');
INSERT INTO zone_country VALUES (583, 1, 'MICRONESIA, FEDERATED STATES OF', 'FSM', 'FM');
INSERT INTO zone_country VALUES (498, 1, 'MOLDOVA, REPUBLIC OF', 'MDA', 'MD');
INSERT INTO zone_country VALUES (492, 1, 'MONACO', 'MCO', 'MC');
INSERT INTO zone_country VALUES (496, 2, 'MONGOLIA', 'MNG', 'MN');
INSERT INTO zone_country VALUES (500, 1, 'MONTSERRAT', 'MSR', 'MS');
INSERT INTO zone_country VALUES (504, 1, 'MOROCCO', 'MAR', 'MA');
INSERT INTO zone_country VALUES (508, 1, 'MOZAMBIQUE', 'MOZ', 'MZ');
INSERT INTO zone_country VALUES (104, 1, 'MYANMAR', 'MMR', 'MM');
INSERT INTO zone_country VALUES (516, 1, 'NAMIBIA', 'NAM', 'NA');
INSERT INTO zone_country VALUES (520, 1, 'NAURU', 'NRU', 'NR');
INSERT INTO zone_country VALUES (524, 1, 'NEPAL', 'NPL', 'NP');
INSERT INTO zone_country VALUES (528, 1, 'NETHERLANDS', 'NLD', 'NL');
INSERT INTO zone_country VALUES (530, 1, 'NETHERLANDS ANTILLES', 'ANT', 'AN');
INSERT INTO zone_country VALUES (540, 1, 'NEW CALEDONIA', 'NCL', 'NC');
INSERT INTO zone_country VALUES (554, 1, 'NEW ZEALAND', 'NZL', 'NZ');
INSERT INTO zone_country VALUES (558, 1, 'NICARAGUA', 'NIC', 'NI');
INSERT INTO zone_country VALUES (562, 1, 'NIGER', 'NER', 'NE');
INSERT INTO zone_country VALUES (566, 1, 'NIGERIA', 'NGA', 'NG');
INSERT INTO zone_country VALUES (570, 1, 'NIUE', 'NIU', 'NU');
INSERT INTO zone_country VALUES (574, 1, 'NORFOLK ISLAND', 'NFK', 'NF');
INSERT INTO zone_country VALUES (580, 1, 'NORTHERN MARIANA ISLANDS', 'MNP', 'MP');
INSERT INTO zone_country VALUES (578, 1, 'NORWAY', 'NOR', 'NO');
INSERT INTO zone_country VALUES (512, 1, 'OMAN', 'OMN', 'OM');
INSERT INTO zone_country VALUES (586, 1, 'PAKISTAN', 'PAK', 'PK');
INSERT INTO zone_country VALUES (585, 1, 'PALAU', 'PLW', 'PW');
INSERT INTO zone_country VALUES (275, 1, 'PALESTINIAN TERRITORY, OCCUPIED', '  P', '');
INSERT INTO zone_country VALUES (591, 1, 'PANAMA', 'PAN', 'PA');
INSERT INTO zone_country VALUES (598, 1, 'PAPUA NEW GUINEA', 'PNG', 'PG');
INSERT INTO zone_country VALUES (600, 1, 'PARAGUAY', 'PRY', 'PY');
INSERT INTO zone_country VALUES (604, 1, 'PERU', 'PER', 'PE');
INSERT INTO zone_country VALUES (608, 1, 'PHILIPPINES', 'PHL', 'PH');
INSERT INTO zone_country VALUES (612, 1, 'PITCAIRN', 'PCN', 'PN');
INSERT INTO zone_country VALUES (616, 1, 'POLAND', 'POL', 'PL');
INSERT INTO zone_country VALUES (620, 1, 'PORTUGAL', 'PRT', 'PT');
INSERT INTO zone_country VALUES (630, 1, 'PUERTO RICO', 'PRI', 'PR');
INSERT INTO zone_country VALUES (634, 1, 'QATAR', 'QAT', 'QA');
INSERT INTO zone_country VALUES (638, 1, 'REUNION', 'REU', 'RE');
INSERT INTO zone_country VALUES (642, 1, 'ROMANIA', 'ROM', 'RO');
INSERT INTO zone_country VALUES (643, 1, 'RUSSIAN FEDERATION', 'RUS', 'RU');
INSERT INTO zone_country VALUES (646, 1, 'RWANDA', 'RWA', 'RW');
INSERT INTO zone_country VALUES (659, 1, 'SAINT KITTS AND NEVIS', 'KNA', 'KN');
INSERT INTO zone_country VALUES (662, 1, 'SAINT LUCIA', 'LCA', 'LC');
INSERT INTO zone_country VALUES (670, 1, 'SAINT VINCENT AND THE GRENADINES', 'VCT', 'VC');
INSERT INTO zone_country VALUES (882, 1, 'SAMOA', 'WSM', 'WS');
INSERT INTO zone_country VALUES (674, 1, 'SAN MARINO', 'SMR', 'SM');
INSERT INTO zone_country VALUES (678, 1, 'SAO TOME AND PRINCIPE', 'STP', 'ST');
INSERT INTO zone_country VALUES (682, 1, 'SAUDI ARABIA', 'SAU', 'SA');
INSERT INTO zone_country VALUES (686, 1, 'SENEGAL', 'SEN', 'SN');
INSERT INTO zone_country VALUES (690, 1, 'SEYCHELLES', 'SYC', 'SC');
INSERT INTO zone_country VALUES (694, 1, 'SIERRA LEONE', 'SLE', 'SL');
INSERT INTO zone_country VALUES (702, 1, 'SINGAPORE', 'SGP', 'SG');
INSERT INTO zone_country VALUES (703, 1, 'SLOVAKIA (Slovak Republic)', 'SVK', 'SK');
INSERT INTO zone_country VALUES (705, 1, 'SLOVENIA', 'SVN', 'SI');
INSERT INTO zone_country VALUES (90, 1, 'SOLOMON ISLANDS', 'SLB', 'SB');
INSERT INTO zone_country VALUES (706, 1, 'SOMALIA', 'SOM', 'SO');
INSERT INTO zone_country VALUES (710, 1, 'SOUTH AFRICA', 'ZAF', 'ZA');
INSERT INTO zone_country VALUES (239, 1, 'SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS', 'SGS', 'GS');
INSERT INTO zone_country VALUES (724, 1, 'SPAIN', 'ESP', 'ES');
INSERT INTO zone_country VALUES (144, 1, 'SRI LANKA', 'LKA', 'LK');
INSERT INTO zone_country VALUES (654, 1, 'ST. HELENA', 'SHN', 'SH');
INSERT INTO zone_country VALUES (666, 1, 'ST. PIERRE AND MIQUELON', 'SPM', 'PM');
INSERT INTO zone_country VALUES (736, 1, 'SUDAN', 'SDN', 'SD');
INSERT INTO zone_country VALUES (740, 1, 'SURINAME', 'SUR', 'SR');
INSERT INTO zone_country VALUES (744, 1, 'SVALBARD AND JAN MAYEN ISLANDS', 'SJM', 'SJ');
INSERT INTO zone_country VALUES (748, 1, 'SWAZILAND', 'SWZ', 'SZ');
INSERT INTO zone_country VALUES (752, 1, 'SWEDEN', 'SWE', 'SE');
INSERT INTO zone_country VALUES (756, 1, 'SWITZERLAND', 'CHE', 'CH');
INSERT INTO zone_country VALUES (760, 1, 'SYRIAN ARAB REPUBLIC', 'SYR', 'SY');
INSERT INTO zone_country VALUES (158, 1, 'TAIWAN, PROVINCE OF CHINA', 'TWN', 'TW');
INSERT INTO zone_country VALUES (762, 1, 'TAJIKISTAN', 'TJK', 'TJ');
INSERT INTO zone_country VALUES (834, 1, 'TANZANIA, UNITED REPUBLIC OF', 'TZA', 'TZ');
INSERT INTO zone_country VALUES (764, 1, 'THAILAND', 'THA', 'TH');
INSERT INTO zone_country VALUES (768, 1, 'TOGO', 'TGO', 'TG');
INSERT INTO zone_country VALUES (772, 1, 'TOKELAU', 'TKL', 'TK');
INSERT INTO zone_country VALUES (776, 1, 'TONGA', 'TON', 'TO');
INSERT INTO zone_country VALUES (780, 1, 'TRINIDAD AND TOBAGO', 'TTO', 'TT');
INSERT INTO zone_country VALUES (788, 1, 'TUNISIA', 'TUN', 'TN');
INSERT INTO zone_country VALUES (792, 1, 'TURKEY', 'TUR', 'TR');
INSERT INTO zone_country VALUES (795, 1, 'TURKMENISTAN', 'TKM', 'TM');
INSERT INTO zone_country VALUES (796, 1, 'TURKS AND CAICOS ISLANDS', 'TCA', 'TC');
INSERT INTO zone_country VALUES (798, 1, 'TUVALU', 'TUV', 'TV');
INSERT INTO zone_country VALUES (800, 1, 'UGANDA', 'UGA', 'UG');
INSERT INTO zone_country VALUES (804, 1, 'UKRAINE', 'UKR', 'UA');
INSERT INTO zone_country VALUES (784, 1, 'UNITED ARAB EMIRATES', 'ARE', 'AE');
INSERT INTO zone_country VALUES (826, 1, 'UNITED KINGDOM', 'GBR', 'GB');
INSERT INTO zone_country VALUES (840, 1, 'UNITED STATES', 'USA', 'US');
INSERT INTO zone_country VALUES (581, 1, 'UNITED STATES MINOR OUTLYING ISLANDS', 'UMI', 'UM');
INSERT INTO zone_country VALUES (858, 1, 'URUGUAY', 'URY', 'UY');
INSERT INTO zone_country VALUES (860, 1, 'UZBEKISTAN', 'UZB', 'UZ');
INSERT INTO zone_country VALUES (548, 1, 'VANUATU', 'VUT', 'VU');
INSERT INTO zone_country VALUES (862, 1, 'VENEZUELA', 'VEN', 'VE');
INSERT INTO zone_country VALUES (704, 1, 'VIET NAM', 'VNM', 'VN');
INSERT INTO zone_country VALUES (92, 1, 'VIRGIN ISLANDS (BRITISH)', 'VGB', 'VG');
INSERT INTO zone_country VALUES (850, 1, 'VIRGIN ISLANDS (U.S.)', 'VIR', 'VI');
INSERT INTO zone_country VALUES (876, 1, 'WALLIS AND FUTUNA ISLANDS', 'WLF', 'WF');
INSERT INTO zone_country VALUES (732, 1, 'WESTERN SAHARA', 'ESH', 'EH');
INSERT INTO zone_country VALUES (887, 1, 'YEMEN', 'YEM', 'YE');
INSERT INTO zone_country VALUES (891, 1, 'YUGOSLAVIA', 'YUG', 'YU');
INSERT INTO zone_country VALUES (894, 1, 'ZAMBIA', 'ZMB', 'ZM');
INSERT INTO zone_country VALUES (716, 1, 'ZIMBABWE', 'ZWE', 'ZW');