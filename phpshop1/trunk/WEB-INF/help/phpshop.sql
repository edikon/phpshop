# PHPshop DataBase Tables:

CREATE TABLE active_sessions (
  sid                    varchar(32)   DEFAULT ''       NOT NULL,
  name                   varchar(32)   DEFAULT ''       NOT NULL,
  val                    text,
  changed                varchar(14)   DEFAULT ''       NOT NULL,
  PRIMARY KEY (name,sid),
  KEY changed (changed)
);

CREATE TABLE auth_user_md5 (
  user_id                varchar(32)   DEFAULT ''       NOT NULL,
  username               varchar(32)   DEFAULT ''       NOT NULL,
  password               varchar(32)   DEFAULT ''       NOT NULL,
  perms                  varchar(255),
  PRIMARY KEY (user_id),
  UNIQUE k_username (username)
);

CREATE TABLE category (
  category_id            varchar(32)   DEFAULT ''       NOT NULL,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  category_name          varchar(128)  DEFAULT ''       NOT NULL,
  category_description   text,
  category_thumb_image   varchar(255),
  category_full_image    varchar(255),
  category_publish       char(1),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (category_id)
);

CREATE TABLE category_xref (
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  category_parent_id     varchar(32),
  category_child_id      varchar(32),
  category_list          int(11)
);

CREATE TABLE function (
  function_id            int(11)       DEFAULT '0'      NOT NULL auto_increment,
  function_name          varchar(32),
  function_class         varchar(32),
  function_method        varchar(32),
  function_description   text,
  function_perms         varchar(255),
  PRIMARY KEY (function_id)
);

CREATE TABLE groups (
  group_id               int(11)       DEFAULT '0'      NOT NULL auto_increment,
  group_name             varchar(32),
  group_description      text,
  PRIMARY KEY (group_id)
);

CREATE TABLE order_item (
  order_item_id          int(11)       DEFAULT '0'      NOT NULL auto_increment,
  order_id               int(11),
  user_info_id           int(11),
  vendor_id              int(11),
  product_id             int(11),
  product_quantity       int(11),
  product_item_price     decimal(10,2),
  order_item_currency    varchar(16),
  order_status           char(1),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (order_item_id)
);

CREATE TABLE order_payment (
  order_id               int(11)       DEFAULT '0'      NOT NULL,
  user_info_id           int(11)       DEFAULT '0'      NOT NULL,
  order_tax_1            decimal(10,2) DEFAULT '0.00',
  order_tax_2            decimal(10,2) DEFAULT '0.00',
  order_tax_3            decimal(10,2) DEFAULT '0.00',
  order_tax_4            decimal(10,2) DEFAULT '0.00',
  order_tax_5            decimal(10,2) DEFAULT '0.00',
  order_product_total    decimal(10,2),
  order_tax_total        decimal(10,2),
  order_ship_total       decimal(10,2),
  order_ship_tax_total   decimal(10,2),
  order_currency         char(16)
);

CREATE TABLE orders (
  order_id               int(11)       DEFAULT '0'      NOT NULL auto_increment,
  user_id                varchar(32)   DEFAULT ''       NOT NULL,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  order_number           varchar(32),
  user_info_id           int(11),
  order_subtotal         decimal(10,2),
  order_tax              decimal(10,2),
  order_shipping         decimal(10,2),
  order_shipping_tax     decimal(10,2),
  order_currency         varchar(16),
  order_status           char(1),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (order_id)
);

CREATE TABLE payment_method (
  order_id               int(11)       DEFAULT '0'      NOT NULL,
  payment_method_type    varchar(8),
  payment_method_number  varchar(128),
  payment_method_expire  int(11)
);

CREATE TABLE price_rate (
  price_scale_id         int(11)       DEFAULT '0'      NOT NULL,
  price_rate_start       decimal(10,4) DEFAULT '0.0000' NOT NULL,
  price_rate_end         decimal(10,4) DEFAULT '0.0000' NOT NULL,
  price_discount_rate    decimal(10,4) DEFAULT '0.0000' NOT NULL,
  price_rate_func        char(8)       DEFAULT ''       NOT NULL
);

CREATE TABLE price_scale (
  price_scale_id         int(11)       DEFAULT '0'      NOT NULL auto_increment,
  price_scale_name       varchar(16)   DEFAULT ''       NOT NULL,
  vendor_id              int(11),
  price_scale_desc       varchar(255),
  PRIMARY KEY (price_scale_id)
);

CREATE TABLE product (
  product_id             int(11)       DEFAULT '0'      NOT NULL auto_increment,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  product_parent_id      int(11),
  product_sku            varchar(64)   DEFAULT ''       NOT NULL,
  product_s_desc         varchar(255),
  product_desc           text,
  product_thumb_image    varchar(255),
  product_full_image     varchar(255),
  product_publish        char(1),
  product_weight         decimal(10,4),
  product_weight_uom     varchar(32),
  product_length         decimal(10,4),
  product_width          decimal(10,4),
  product_height         decimal(10,4),
  product_lwh_uom        varchar(32),
  product_url            varchar(255),
  product_in_stock       int(11),
  product_available_date int(11),
  product_special        char(1),
  product_discount_id    int(11),
  ship_code_id           int(11),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (product_id)
);

CREATE TABLE product_attribute (
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  product_id             int(11)       DEFAULT '0'      NOT NULL,
  attribute_name         char(255)     DEFAULT ''       NOT NULL,
  attribute_value        char(255)
);

CREATE TABLE product_attribute_sku (
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  product_id             int(11)       DEFAULT '0'      NOT NULL,
  attribute_name         char(255)     DEFAULT ''       NOT NULL,
  attribute_list         int(11)
);

CREATE TABLE product_category_xref (
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  category_id            int(11),
  product_id             int(11)       DEFAULT '0'      NOT NULL,
  product_list           int(11)
);

CREATE TABLE product_discount (
  product_discount_id    int(11)       DEFAULT '0'      NOT NULL auto_increment,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  price_scale_id         int(11)       DEFAULT '0'      NOT NULL,
  discount_type          char(8),
  product_discount_vdate int(11),
  product_discount_edate int(11),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (product_discount_id)
);

CREATE TABLE product_price (
  product_price_id       int(11)       DEFAULT '0'      NOT NULL auto_increment,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  product_id             int(11)       DEFAULT '0'      NOT NULL,
  group_id               int(11),
  product_price          decimal(10,4),
  product_currency       char(16),
  product_price_vdate    int(11),
  product_price_edate    int(11),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (product_price_id)
);

CREATE TABLE ship_code (
  ship_code_id           int(11)       DEFAULT '0'      NOT NULL auto_increment,
  product_ship_code      varchar(8)    DEFAULT ''       NOT NULL,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  ship_calc_method       varchar(8),
  ship_code_desc         varchar(255),
  PRIMARY KEY (ship_code_id)
);

CREATE TABLE ship_method (
  ship_method_id         int(11)       DEFAULT '0'      NOT NULL auto_increment,
  ship_carrier           varchar(32),
  ship_mode              varchar(32),
  ship_desc              varchar(255),
  PRIMARY KEY (ship_method_id)
);

CREATE TABLE shipping (
  shipping_id            int(11)       DEFAULT '0'      NOT NULL auto_increment,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  vship_method_id        int(11),
  ship_code_id           int(11),
  shipping_area          char(32),
  shipping_country       char(32),
  shipping_charge        decimal(10,2),
  shipping_vdate         int(11),
  shipping_edate         int(11),
  PRIMARY KEY (shipping_id)
);

CREATE TABLE tax_category (
  tax_category_id        int(11)       DEFAULT '0'      NOT NULL auto_increment,
  tax_category_name      char(128),
  PRIMARY KEY (tax_category_id)
);

CREATE TABLE user_info (
  user_info_id           int(11)       DEFAULT '0'      NOT NULL auto_increment,
  user_id                varchar(32)   DEFAULT ''       NOT NULL,
  address_type           char(2),
  address_type_name      varchar(32),
  company                varchar(64),
  title                  varchar(32),
  last_name              varchar(32),
  first_name             varchar(32),
  middle_name            varchar(32),
  phone_1                varchar(32),
  phone_2                varchar(32),
  fax                    varchar(32),
  address_1              varchar(64)   DEFAULT ''       NOT NULL,
  address_2              varchar(64),
  city                   varchar(32)   DEFAULT ''       NOT NULL,
  state                  varchar(32)   DEFAULT ''       NOT NULL,
  country                varchar(32)   DEFAULT 'US'     NOT NULL,
  zip                    varchar(32)   DEFAULT ''       NOT NULL,
  cdate                  int(11),
  mdate                  int(11),
  user_email             varchar(255),
  PRIMARY KEY (user_info_id)
);

CREATE TABLE vendor (
  vendor_id              int(11)       DEFAULT '0'      NOT NULL auto_increment,
  vendor_name            varchar(64),
  contact_last_name      varchar(32)   DEFAULT ''       NOT NULL,
  contact_first_name     varchar(32)   DEFAULT ''       NOT NULL,
  contact_middle_name    varchar(32),
  contact_title          varchar(32),
  contact_phone_1        varchar(32)   DEFAULT ''       NOT NULL,
  contact_phone_2        varchar(32),
  contact_fax            varchar(32),
  contact_email          varchar(255),
  vendor_phone           varchar(32),
  vendor_address_1       varchar(64)   DEFAULT ''       NOT NULL,
  vendor_address_2       varchar(64),
  vendor_city            varchar(32)   DEFAULT ''       NOT NULL,
  vendor_state           varchar(32)   DEFAULT ''       NOT NULL,
  vendor_country         varchar(32)   DEFAULT 'US'     NOT NULL,
  vendor_zip             varchar(32)   DEFAULT ''       NOT NULL,
  vendor_store_name      varchar(128)  DEFAULT ''       NOT NULL,
  vendor_store_desc      text,
  vendor_category_id     int(11),
  vendor_thumb_image     varchar(255),
  vendor_full_image      varchar(255),
  vendor_currency        varchar(16),
  cdate                  int(11),
  mdate                  int(11),
  PRIMARY KEY (vendor_id)
);

CREATE TABLE vendor_category (
  vendor_category_id     int(11)       DEFAULT '0'      NOT NULL auto_increment,
  vendor_category_name   varchar(64),
  vendor_category_desc   text,
  PRIMARY KEY (vendor_category_id)
);

CREATE TABLE vendor_tax (
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  tax_rate_1             decimal(4,2),
  tax_name_1             varchar(32),
  tax_rate_2             decimal(4,2),
  tax_name_2             varchar(32),
  tax_rate_3             decimal(4,2),
  tax_name_3             varchar(32),
  tax_rate_4             decimal(4,2),
  tax_name_4             varchar(32),
  tax_rate_5             decimal(4,2),
  tax_name_5             varchar(32)
);

CREATE TABLE vship_method (
  vship_method_id        int(11)       DEFAULT '0'      NOT NULL auto_increment,
  ship_method_id         int(11)       DEFAULT '0'      NOT NULL,
  vendor_id              int(11)       DEFAULT '0'      NOT NULL,
  vship_method_vdate     int(11),
  vship_method_edate     int(11),
  PRIMARY KEY (vship_method_id)
);

