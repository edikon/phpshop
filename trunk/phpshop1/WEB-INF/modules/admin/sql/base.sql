#
# Table structure for table 'auth_user_md5'
#
CREATE TABLE auth_user_md5 (
  user_id varchar(32) DEFAULT '' NOT NULL,
  username varchar(32) DEFAULT '' NOT NULL,
  password varchar(32) DEFAULT '' NOT NULL,
  perms varchar(255),
  PRIMARY KEY (user_id),
  UNIQUE k_username (username)
);

#
# Dumping data for table 'auth_user_md5'
#

INSERT INTO auth_user_md5 VALUES ('7322f75cc7ba16db1799fd8d25dbcde4','admin','098f6bcd4621d373cade4e832627b4f6','admin');




CREATE TABLE user_info (
  user_info_id int(11) DEFAULT '0' NOT NULL auto_increment,
  user_id varchar(32) DEFAULT '' NOT NULL,
  address_type char(2),
  address_type_name varchar(32),
  company varchar(64),
  title varchar(32),
  last_name varchar(32),
  first_name varchar(32),
  middle_name varchar(32),
  phone_1 varchar(32),
  phone_2 varchar(32),
  fax varchar(32),
  address_1 varchar(64) DEFAULT '' NOT NULL,
  address_2 varchar(64),
  city varchar(32) DEFAULT '' NOT NULL,
  state varchar(32) DEFAULT '' NOT NULL,
  country varchar(32) DEFAULT 'US' NOT NULL,
  zip varchar(32) DEFAULT '' NOT NULL,
  user_email varchar(255),
  extra_field_1 varchar(255),
  extra_field_2 varchar(255),
  extra_field_3 varchar(255),
  extra_field_4 char(1),
  extra_field_5 char(1),
  cdate int(11),
  mdate int(11),
  PRIMARY KEY (user_info_id)
);


#
# Dumping data for table 'user_info'
#

INSERT INTO user_info VALUES (14,'7322f75cc7ba16db1799fd8d25dbcde4','BT',NULL,'','','Administrator','Site','','555-555-1212','','','1 Apache Street','','Apache','Open Source','','00000','admin@phpshop.org','','','','N','N',NULL,957942082);



CREATE TABLE sessions (
  sess_id varchar(255) DEFAULT '' NOT NULL,
  mdate int(11) DEFAULT '0' NOT NULL,
  session_data text,
  PRIMARY KEY (sess_id),
  KEY mdate (mdate)
);


CREATE TABLE module (
  module_id int(11) DEFAULT '0' NOT NULL auto_increment,
  module_name varchar(255),
  module_description text,
  module_header varchar(255),
  module_footer varchar(255),
  module_perms varchar(255),
  PRIMARY KEY (module_id)
);
INSERT INTO module VALUES 
            (1,'base','Base phpShop Installation.','header.ihtml','footer.ihtml','admin');



CREATE TABLE function (
  function_id int(11) DEFAULT '0' NOT NULL auto_increment,
  module_id int(11),
  function_name varchar(32),
  function_class varchar(32),
  function_method varchar(32),
  function_description text,
  function_perms varchar(255),
  PRIMARY KEY (function_id)
);
INSERT INTO function VALUES (1,1, 'userAdd','ps_user','add','','admin,storeadmin');
INSERT INTO function VALUES (2,1, 'userDelete','ps_user','delete','','admin,storeadmin');
INSERT INTO function VALUES (3,1, 'userUpdate','ps_user','update','','admin,storeadmin');
INSERT INTO function VALUES (4,1, 'adminPasswdUpdate','ps_user','update_admin_passwd','Updates Site Adminnistrator Password','admin');
INSERT INTO function VALUES (5,1 ,'productAdd','ps_product','add','','admin,storeadmin');
INSERT INTO function VALUES (6,1 ,'functionAdd','ps_function_reg','add','','admin');
INSERT INTO function VALUES (7,1 ,'functionUpdate','ps_function_reg','update','','admin');
INSERT INTO function VALUES (8,1 ,'functionDelete','ps_function_reg','delete','','admin');
INSERT INTO function VALUES (9,1 ,'userLogout','ps_user','logout','','none');
INSERT INTO function VALUES (10,1,'userAddressAdd','ps_user_address','add','','admin,storeadmin,shopper');
INSERT INTO function VALUES (11,1,'userAddressUpdate','ps_user_address','update','','admin,storeadmin,shopper');
INSERT INTO function VALUES (12,1,'userAddressDelete','ps_user_address','delete','','admin,storeadmin,shopper');
INSERT INTO function VALUES (13,1,'moduleAdd','ps_module_reg','add','','admin');
INSERT INTO function VALUES (14,1,'moduleUpdate','ps_module_reg','update','','admin');
INSERT INTO function VALUES (15,1,'moduleDelete','ps_module_reg','delete','','admin');
INSERT INTO function VALUES (16,1,'userLogin','ps_user','login','','none');



