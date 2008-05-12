<?php 
#
# The phpShop Config File
#
# Copyright (c) Edikon Corporation.  All rights reserved.
# Distributed under the phpShop Public License (pSPL) Version 1.0.
#
# $Id: config-dist.php,v 1.1.1.1 2004/07/27 14:57:56 pablo Exp $
#
#
define("PHPSHOP_VERSION","0.8.1");
   
# LANGUAGE Directive
# Designates the default language for this site.  Each module has
# its own language file definitions specified by the given code.
# phpShop is currently distributed with English and Spanish by
# default.  Either eng or esl.		       
define("LANGUAGE","eng");

# URL & SECUREURL Settings
define("URL","http://localhost/demo/");
define("SECUREURL","http://localhost/demo/");

# Database Settings
define("DB_HOST","localhost");
define("DB_NAME","phpshop");
define("DB_USER","dbuser");
define("DB_PWD","dbpass");

# Sessions
# Used to specify settings for session management.
# - SESSION_PATH sets the directory where
#   session information will be saved. If left blank, the 
#   "session.save_path" directive from your php.ini will be used.
# - SESSION_EXPIRE sets the number of MINUTES that the session will last
#   when used in cookie mode. If left blank, the "session.cookie_lifetime"
#   directive from your php.ini will be used.
define("SESSION_PATH","");
define("SESSION_EXPIRE","");

# HOMEPAGE
# Sets the page to load by default
define("HOMEPAGE","shop/index");

# LOGINPAGE
define("LOGINPAGE","shop/login");

# FLYPAGE
# Sets the default flypage to use for all products (can also be specified in each category)
define("FLYPAGE","shop/flypage");

# ERRORPAGE
# Sets the page to load when an error occurs.
define("ERRORPAGE","msgs/error");

# DEBUG Directive
# Shows debug output.  Good while developing
define("DEBUG","0");
define("DEBUGPAGE","msgs/debug");

# Search Directives
# SEARCH_ROWS = number of rows per page
# SEARCH_PAGES = number of pages to show in nav links at bottom of list.  Should be even number. 
define("SEARCH_ROWS","20");
define("SEARCH_PAGES","6");    //should be an even number
define("SEARCH_COLOR_1","#f9f9f9");
define("SEARCH_COLOR_2","#f0f0f0");

# WYSIWYG Edit for Product Information
define("ENABLE_WYSIWYG","1");

# MAX_ROWS Directive
# Sets the number of rows to show in the order list select box.
define("MAX_ROWS","25");

# CHECK_STOCK Directive
# Sets whether to check the stock level when a user adds an item
# to the shopping cart.  If set, this will not allow user to add
# more items to the cart than are available in stock.
define("CHECK_STOCK","0");
					
# ENCODE_KEY Directive
# Used to encrypt data stored in database with this key.  This means that this file
# should be protected from viewing at all times.
define("STORE_CC", 1);
define("ENCODE_KEY","phpShopIsCool");


# Authorize.net Directives
# Used to set Authorize.net variables so that Authorize.net can be used with 
# phpShop. Please see Authorize.Nets documentation. 
#
# AN_ENABLE - If set to "1", Authorize.net will be used for the checkout 
#             procedures. Make sure you enable each "Payment Method". This
#             is done in the Adminitration area of phpshop, In "Store" 
#             choose "List Payment Methods" and make sure that the desired
#             Payment Methods have a "Y" for "Authorize".
# AN_LOGIN - Authorize.Net Login ID
# AN_TRAN_KEY - Merchant Provided by CyberCash
# AN_TYPE - Authorize.Net authentication type. 
# AN_TEST_REQUEST - set "True" while testing, "False" for live transactions.
define("AN_ENABLE","0");
define("AN_LOGIN","dgi00000");
define("AN_TRAN_KEY","xxxxxxxxxxxxxxxx");
define("AN_TYPE","AUTH_CAPTURE");
define("AN_TEST_REQUEST","True");

# CYBERCASH Directives
# Used to set Cybercash variables so that Cybercash can be used with phpShop.  
# CC_MERCHANT is the CyberCash Merchant ID
# CC_MERCHANT_KEY is the Merchant Provided by CyberCash
# CC_PAYMENT_URL is the URL provided by Cybercash for secure payment
# CC_AUTH_TYPE is the Cybercash authentication type provided by Cybercase
define("CC_ENABLE","0");
define("CC_MERCHANT","phpshop");
define("CC_MERCHANT_KEY","00000000000000000000000000");
define("CC_PAYMENT_URL","https://cr.cybercash.com/cgi-bin/");
define("CC_AUTH_TYPE","mauthonly");

# Zone Shipping 
# Set this to 1 to enable the zone shipping module
define("ZONE_ENABLE","1");

# If you want zero weight items excluded from taxes, set this to 0 
define("IS_TAX_VIRTUAL","1");

# SMTP Settings
define("SMTP_ENABLED",0);      // if enabled, uses SMTP, otherwise PHP's mail function
define("SMTP_HOST","yourmailserver.com");
define("SMTP_PORT","25");
define("SMTP_AUTH", "Y");    // Y or N - for SMTP authentication
define("SMTP_USER","username");
define("SMTP_PASS","password");
?>
