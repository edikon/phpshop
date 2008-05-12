<?php
/*
 * The ps_checkout class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_checkout.inc,v 1.1.1.1 2004/07/27 14:58:44 pablo Exp $
 *
 */

/****************************************************************************
*
* CLASS DESCRIPTION
*                   
* ps_checkout
*
* The class contains the shop checkout code.  It is used to checkout
* and order and collect payment information.
* 
* propeties:  
*       class_name: Holds the name of the class.  Necessary for PHPLIB.
*               id: Another PHPLIB required variable.
*            error: Holds most recent error message set in by a method.
*
* methods:
*    validate_form:  Called to validate the values in checkout_form.  
*     validate_add:  Validates the checkout values prior to adding
*  validate_update:  Validate the checkout values prior to updating
*           update:  Update the order in the database
*           delete:  Delete the order in the database
*             find:  Find the order in the database
* ship_to_addresses_radio:  Get all the user_info Ship To (ST) records 
*                    associated with the $user_id and print an HTML 
*                    radio check box form element using the retrieved data.
*  display_address:  Print an HTML table displaying the user_info record
*                    for the specified $user_info_id and $address_type.
*              add:  Store the order information in the database
* get_order_number:  Create an order number using the session id, session
*                    name, and the current unix timestamp.
* calc_order_subtotal:  Calculate the order subtotal for the current order.  
*                    Does not include tax or shipping charges.
*   calc_order_tax:  Calculate the tax charges for the current order.
* calc_order_shipping:  Calculate the shipping charges for the current order
* calc_order_shipping_tax:  Calculate the tax for the shipping of the 
*                    current order
* get_vendor_currency:  Get the currency type used by the $vendor_id
*    email_receipt:  Create a receipt for the current order and email it to 
*                    the customer and the vendor.
* payment_method_type_long_name_display:  Print the full name of the 
*                    payment method type based off of the $short_name
*     asterisk_pad:  Return $str with all but $display_length at the end as 
*                    asterisks.
* dropdown_display:  Print an HTML dropdown box named $name using $arr to
*                    load the drop down.  If $value is in $arr, then $value
*                    will be the selected option in the dropdown.
*      validate_cc:  Validates credit card number format.
*    to_char_array:  Helper method for validate_cc()
*************************************************************************/
class ps_checkout {
  var $classname = "ps_checkout";



  /**************************************************************************
  ** name: validate_form()
  ** created by: gday
  ** description: Called to validate the form values in checkout_form
  ** parameters: $d 
  ** returns: True  - validation passed
  **          False - validation failed
  ***************************************************************************/
   function validate_form(&$d) {
     global $cart, $auth;
     $db = new ps_DB;
     require_once("store/lib/ps_payment_method.inc");
     $ps_payment_method = new ps_payment_method;

   if (!$cart["idx"]) {
     $q  = "SELECT order_id FROM orders WHERE user_id='" . $auth["user_id"] . "' "; 
     $q .= "ORDER BY cdate DESC";
     $db->query($q);
     $db->next_record();
     $d["order_id"] = $db->f("order_id"); 
     $d["error"] = "";
     return False;
   }

   if (trim($d["ship_method_id"]) == "0") {
     $d["error"] = "Please select a shipping method.";
     return False;
   }

   if (!$d["payment_method_id"]) {
     $d["error"] = "Please select a payment method.";
     return False;
   }
   
   if (!$d["order_payment_number"]) {
     $d["error"] = "Please enter an account number.";
     return False;
   } 

   if (!$d["order_payment_name"]) {
     $d["error"] = "Please enter the name on the account.";
     return False;
   }

   if(!$ps_payment_method->validate_payment($d["payment_method_id"],$d["order_payment_number"])) {
     $d["error"] = "The account number entered is not valid.";
     return False;
   }

   if(!$d["order_payment_expire_month"]) {
     $d["error"] = "Please enter the account expiration month.";
     return False;
   }

   if(!$d["order_payment_expire_year"]) {
     $d["error"] = "Please enter the account expiration year.";
     return False;
   }
   $date = getdate(time());
   if ($d["order_payment_expire_year"] < $date["year"] or
      ($d["order_payment_expire_year"] == $date["year"] and
       $d["order_payment_expire_month"] < $date["mon"])) {
     $d["error"] = "The expiration date is invalid.";
     return False;
   }

   // calculate the unix timestamp for the specified expiration date
   // default the day to the 1st

   $expire_timestamp = mktime(0,0,0,$d["order_payment_expire_month"],
                              1,$d["order_payment_expire_year"]);
   $d["order_payment_expire"] = $expire_timestamp;
   
   return True;
  }


  /**************************************************************************
  ** name: validate_add()
  ** created by: gday
  ** description:  Validates the checkout form values prior to adding
  ** parameters: $d 
  ** returns:  True - validation passed
  **          False - validation failed
  ***************************************************************************/
  function validate_add(&$d) {

   require_once("store/lib/ps_payment_method.inc");
   $ps_payment_method = new ps_payment_method;

 
   if (!$d["ship_to_info_id"]) {
     $d["error"] = "Please select a ship to address.";
     return False;
   }

   if (!$d["payment_method_id"]) {
     $d["error"] = "Please select a payment method.";
     return False;
   }

   if (!$d["order_payment_number"]) {
     $d["error"] = "Please enter an account number.";
     return False;
   }

   if(!$ps_payment_method->validate_payment($d["payment_method_id"], 
                   $d["order_payment_number"])) {
     $d["error"] = "Invalid account number.";
     return False;
   }

   if(!$d["order_payment_expire"]) {
     $d["error"] = "Please enter the account expiration month.";
     return False;
   }
    
   return True;
  }

  /**************************************************************************
  ** name: validate_shipto()
  ** created by: pablo
  ** description:  Validate the checkout shipto values prior to showing confirm
		   page.
  ** parameters: $d
  ** returns:  True - validation passed
  **          False - validation failed
  ***************************************************************************/
  function validate_shipto(&$d) {
    if (!$d["ship_to_info_id"]) {
       $d["error"] = "Please select a shipping address.";
       return False;
    } 
     
    return True;
  }
 
  /**************************************************************************
  ** name: update()
  ** created by: gday
  ** description:  Update the order in the database
  ** parameters: $d
  ** returns:  True - update succeeded
  **          False - update failed
  ***************************************************************************/
  function update(&$d) {
    $db = new ps_DB;
    $timestamp = time();
    
    
    if ($this->validate_update($d)) {
      return True;
    }
    else {
      $d["error"] = $this->error;
      return False;
    }
  }
  

 /**************************************************************************
  ** name: ship_to_address_radio()
  ** created by: gday
  ** description:  Get all the user_info Ship To (ST) records associated
  **               with the $user_id and print an HTML radio check box
  **               form element using the retrieved data.
  ** parameters: $user_id - user id of to display ship to addresses
  **             $name - name of the HTML radio element
  **             $value - If matched, then this radio item will be 
  **                      checked
  ** returns:  Prints html radio element to standard out
  ***************************************************************************/
   function ship_to_addresses_radio($user_id, $name, $value) {
      global $sess;

      $db = new ps_DB;
          
      /* Select all the ship to information for this user id and
       * order by modification date; most recently changed to oldest
       */

      $q  = "SELECT user_info_id FROM user_info ";
      $q .= "WHERE user_id = '" . $user_id . "' ";
      $q .= "AND address_type = 'BT' ";
      $db->query($q);
      $db->next_record();
      $bt_user_info_id = $db->f("user_info_id");
 
      $q  = "SELECT user_info_id, address_type_name, company, title, ";
      $q .= "last_name, first_name, middle_name, phone_1, phone_2, ";
      $q .= "fax, address_1, address_2, city, ";
      $q .= "state, country, zip ";
      $q .= "FROM user_info ";
      $q .= "WHERE user_id = '" . $user_id . "' ";
      $q .= "AND address_type = 'ST' ";
      $q .= "ORDER by address_type_name, mdate DESC";

      $db->query($q);

      echo "<table border=\"0\" width=\"100%\" cellpadding=\"2\" cellspacing=\"0\">\n";
      echo "<tr>\n";
      echo "<td>\n";
      if ($db->num_rows() and $bt_user_info_id != $value) {
        echo "<input type=\"radio\" name=\"$name\" value=\"$bt_user_info_id\" checked=\"checked\" />\n";
      } else {
        echo "<input type=\"radio\" name=\"$name\" value=\"$bt_user_info_id\" checked=\"checked\" />\n";
      }
      echo "</td>\n";
      echo "<td bgcolor=\"#f0f0f0\">\n";
      echo "<b>Same as Billing Address.</b>\n";
      echo "</td>\n";
      echo "</tr>\n";
      while($db->next_record()) {
         echo "<tr>\n";
         echo "<td>\n";
         if (!strcmp($value, $db->f("user_info_id"))) {
            echo "<input type=\"radio\" name=\"$name\" value=\"" . $db->f("user_info_id") . "\" checked=\"checked\" />\n";
         }
         else {
            echo "<input type=\"radio\" name=\"$name\" value=\"" . $db->f("user_info_id") . "\" />\n";
         }
         echo "</td>\n";
         echo "<td>\n";
         echo "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"#f0f0f0\">\n";
         echo "<tr>\n";
         echo "<td>\n";
         echo "<b>" . $db->f("address_type_name") . "</b> ";
         $url = SECUREURL . "?page=account/shipto&amp;user_info_id=" . $db->f('user_info_id');
         $url .= "&amp;next_page=checkout/index";
         echo "(<a href=\"";
         $sess->purl($url);
         echo "\">Update Address</a>)\n";
         echo "<br />\n";
         echo $db->f("title") . " ";
         echo $db->f("first_name") . " ";
         echo $db->f("middle_name") . " ";
         echo $db->f("last_name") . "\n";
         echo "<br />\n";
         if ($db->f("company")) {
           echo $db->f("company") . "\n";
           echo "<br />\n";
         }
         echo $db->f("address_1") . "\n";
         if ($db->f("address_2")) {
            echo "<br />";
            echo $db->f("address_2"). "\n";
         }
         echo "<br />\n";
         echo $db->f("city");
         echo ", ";
         echo $db->f("state") . " ";
         echo $db->f("zip") . "\n";
         echo "<br />\n";
         echo "Phone:";
         echo $db->f("phone_1") . "\n";
         echo "<br />\n";
         echo "Fax:";
         echo $db->f("fax") . "\n";
         echo "</td>\n";
         echo "</tr>\n";
         echo "</table>\n";
      }

      echo "</td>\n";
      echo "</tr>\n";
      echo "</table>\n";

      return(true);
   }

  /**************************************************************************
  ** name: display_address()
  ** created by: gday
  ** description:  Print an HTML table displaying the user_info record
  **               for the specified $user_info_id and $address_type.
  ** parameters: $user_info_id - user info id to display
  **             $address_type - address type (BT or ST)
  ** returns: Prints HTML table displaying the address information
  ***************************************************************************/
   function display_address($user_info_id) {
      $db = new ps_DB;

      $q = "SELECT address_type_name, company, title, last_name, ";
      $q .= "first_name, middle_name, phone_1, phone_2, fax, ";
      $q .= "address_1, address_2, city, state, country, zip ";
      $q .= "FROM user_info ";
      $q .= "WHERE user_info_id = '$user_info_id'";

      $db->query($q);

      if($db->next_record()) {
         echo "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\">";
         echo "<tr>";
         echo "<td align=\"center\">";
         if ($db->f("address_type_name") != "-default-") {
           echo "<b>" . $db->f("address_type_name") . "</b><br />";
         }
         echo $db->f("title") . " ";
         echo $db->f("first_name") . " ";
         echo $db->f("middle_name") . " ";
         echo $db->f("last_name") . " ";
         echo "<br />";
         if ($db->f("company")) {
           echo $db->f("company");
           echo "<br />";
         }
         echo $db->f("address_1");
         if ($db->f("address_2")) {
            echo "<br />";
            echo $db->f("address_2");
         }
         echo "<br />";
         echo $db->f("city");
         echo ", ";
         echo $db->f("state") . " ";
         echo $db->f("zip");
         echo "<br />";
         echo "Phone:";
         echo $db->f("phone_1");
         echo "<br />";
         echo "Fax:";
         echo $db->f("fax");
         echo "</td>";
         echo "</tr>";
         echo "</table>";
      }

      return True;
   }



  /**************************************************************************
  ** name: add()
  ** created by: gday
  ** description:  Store the order information in the database
  ** parameters: $d
  ** returns:  True - order information stored
  **          False - Failure in storing the order information
  ***************************************************************************/
   function add(&$d) {
     global $auth,
       $HTTP_POST_VARS,
       $cart,
       $ps_vendor_id;

       require_once("store/lib/ps_payment_method.inc");
       $ps_payment_method = new ps_payment_method;
       require_once("product/lib/ps_product.inc");
       $ps_product= new ps_product;
       require_once("shop/lib/ps_cart.inc");
       $ps_cart = new ps_cart;


     $db = new ps_DB;
     
     
     if (!$this->validate_form($d)) {
       return False;
     }
     
     if (!$this->validate_add($d)) {
       return False;
     }

     $order_number = $this->get_order_number();
     $order_subtotal = $this->calc_order_subtotal($d);
     $order_taxable = $this->calc_order_taxable($d);
     $order_tax = $this->calc_order_tax($order_taxable, $d);
     $order_shipping = $this->calc_order_shipping($d);
     $order_shipping_tax = $this->calc_order_shipping_tax($d);
     
     $timestamp = time();
     
     $order_total = $order_subtotal + $order_tax + $order_shipping + $order_shipping_tax;
     $order_total = sprintf("%.2f", $order_total);

     // Check to see if Cybercash Processing is wanted for this payment method
     if (($ps_payment_method->get_field($d["payment_method_id"], "enable_processor") == "Y") && CC_ENABLE) {
       if (!$this->cybercash_process($order_number, $order_total, $d)) {
	       return False;
       }
     }
     elseif (($ps_payment_method->get_field($d["payment_method_id"], "enable_processor") == "Y") && AN_ENABLE) {
       if (!$this->authnet_process($order_number, $order_total, $d)) {
	       return False;
       }
     }
     else {
       $d["order_payment_log"] = "Payment information captured for later processing.<br />";
       $d["order_status"] = 'P';
     }
     
     /* Insert the main order information */
     $q = "INSERT INTO orders ";
     $q .= "(user_id, vendor_id, order_number, user_info_id, ";
     $q .= "ship_method_id, order_subtotal, order_tax, order_shipping, ";
     $q .= "order_shipping_tax, order_currency, order_status, cdate, ";
     $q .= "mdate) ";
     $q .= "VALUES (";
     $q .= "'" . $auth["user_id"] . "', ";
     $q .= $ps_vendor_id . ", ";  
     $q .= "'" . $order_number . "', ";
     $q .= $d["ship_to_info_id"] . ", '";
     $q .= $d["ship_method_id"] . "', ";
     $q .= $order_subtotal . ", ";
     $q .= $order_tax . ", "; 
     $q .= $order_shipping . ", ";
     $q .= $order_shipping_tax . ", ";
     $q .= "'', "; /* Currency is at the product level - line item */
     $q .= "'" . $d["order_status"] . "', ";
     $q .= $timestamp . ", ";
     $q .= $timestamp;
     $q .= ")";
     
     $db->query($q);
     $db->next_record();
     
     /* Get the order id just stored */
     
     $q = "SELECT order_id FROM orders WHERE order_number = ";
     $q .= "'" . $order_number . "'";
     
     $db->query($q);
     $db->next_record();
     
     $order_id = $db->f("order_id");
     
     /* Insert the Order payment info */
     
     $payment_number = ereg_replace(" |-", "", $d["order_payment_number"]);
     
     // Payment number is encrypted using mySQL ENCODE function.

     $q = "INSERT INTO order_payment ";
     $q .= "(order_id, payment_method_id, order_payment_number, ";
     $q .= "order_payment_expire, order_payment_log, order_payment_name) ";
     $q .= "VALUES (";
     $q .= $order_id . ", ";
     $q .= "'" . $d["payment_method_id"] . "', ";
     $q .= "ENCODE(\"$payment_number\",\"" . ENCODE_KEY . "\"), ";
     $q .= "'" . $d["order_payment_expire"] . "',";
     $q .= "'" . $d["order_payment_log"] . "',";
     $q .= "'" . $d["order_payment_name"] . "'";
     $q .= ")";
     $db->query($q);
     $db->next_record();
     
     /* Insert the order line items; one row per product in the cart */

     for($i = 0; $i < $cart["idx"]; $i++) {
       
       $product_price_arr = $ps_product->get_price($cart[$i]["product_id"]);
       
       $product_price = $product_price_arr["product_price"];
       
       $vendor_id = $ps_vendor_id;
       
       $product_currency = $product_price_arr["product_currency"];
       
       $q = "INSERT INTO order_item ";
       $q .= "(order_id, user_info_id, vendor_id, ";
       $q .= "product_id, product_quantity, product_item_price, ";
       $q .= "order_item_currency, order_status, cdate, mdate) ";
       $q .= "VALUES ('";
       $q .= $order_id . "', '";
       $q .= $d["ship_to_info_id"] . "', '";
       $q .= $vendor_id . "', '";
       $q .= $cart[$i]["product_id"] . "', '";
       $q .= $cart[$i]["quantity"] . "', '";
       $q .= $product_price . "', '";
       $q .= $product_currency . "', ";
       $q .= "'P','";
       $q .= $timestamp . "','";
       $q .= $timestamp . "'";
       $q .= ")";
       
       $db->query($q);
       $db->next_record();
     } 
     for($i = 0; $i < $cart["idx"]; $i++) {
      $r = "SELECT product_in_stock ";
      $r .= "FROM product where product_id=";
      $r .= $cart[$i]["product_id"];
      $db->query($r);
      $db->next_record();

      if ($db->f("product_in_stock")) {
       $newquantity=($db->f("product_in_stock")-$cart[$i]["quantity"]);
       if ($newquantity <0) $newquantity=0;
       $q = "UPDATE product ";
       $q .= "SET product_in_stock=$newquantity ";
       $q .= "where product_id=";
       $q .= $cart[$i]["product_id"];
       $db->query($q);
       $db->next_record();
      }
     } 
     
     // Export the order_id so the checkout complete page can get it
     $d["order_id"] = $order_id;
     
     // Unset the payment_method variables 
     
     $d["payment_method_id"] = "";
     $d["order_payment_number"] = "";
     $d["order_payment_expire"] = "";
     $d["order_payment_name"] = "";
     
     $HTTP_POST_VARS["payment_method_id"] = "";
     $HTTP_POST_VARS["order_payment_number"] = "";         
     $HTTP_POST_VARS["order_payment_expire"] = "";
     $HTTP_POST_VARS["order_payment_name"] = "";
     
     // Send the e-mail confirmation messages
     $this->email_receipt($order_id);

     // Reset the cart 
     $ps_cart->reset();     

     return True;
   }

  /**************************************************************************
  ** name: get_order_number()
  ** created by: gday
  ** description:  Create an order number using the session id, session
  **               name, and the current unix timestamp.
  ** parameters: 
  ** returns: unique order_number
  ***************************************************************************/
   function get_order_number() {
      global $sess;

      /* Generated a unique order number */

      $str = (string)$sess->id;
      $str .= (string)$sess->name;
      $str .= (string)time();

      $order_number = md5($str);

   return($order_number);
   }


  /***************************************************************************
  ** name: calc_order_taxable()
  ** created by: Chris Coleman
  ** description:  Calculates the taxable order subtotal for the order.  
  ** If an item has no weight, it is non taxable.              
  ** parameters: $d IS_TAX_VIRTUAL
  ** returns: taxable dollar value for this order.
  ***************************************************************************/
   function calc_order_taxable($d) {
      global $auth, $cart;
      $subtotal = 0.0;

       require_once("product/lib/ps_product.inc");
       $ps_product= new ps_product;

       require_once("zone/lib/ps_zone.inc");
       $ps_zone= new ps_zone;
     
      $db = new ps_DB;
 
      for($i = 0; $i < $cart["idx"]; $i++) {
            $product_price_arr = $ps_product->get_price($cart[$i]["product_id"]);
	    $item_weight = $ps_zone->get_weight($cart[$i]["product_id"]);
	    if ($item_weight !=0 or IS_TAX_VIRTUAL) {
            $subtotal += $product_price_arr["product_price"] * $cart[$i]["quantity"];
            }
      }         
      return($subtotal); 
   }

  /**************************************************************************
  ** name: calc_order_subtotal()
  ** created by: gday
  ** description:  Calculate the order subtotal for the current order.  
  **               Does not include tax or shipping charges.
  ** parameters: $d
  ** returns: sub total for this order
  ***************************************************************************/
   function calc_order_subtotal($d) {
      global $auth, $cart;
      $subtotal = 0.0;

       require_once("product/lib/ps_product.inc");
       $ps_product= new ps_product;

     
      $db = new ps_DB;
 
      for($i = 0; $i < $cart["idx"]; $i++) {
            $product_price_arr = $ps_product->get_price($cart[$i]["product_id"]);
            $subtotal += $product_price_arr["product_price"] * $cart[$i]["quantity"];
      }         

      return($subtotal); 
   }

  /**************************************************************************
  ** name: calc_order_tax()
  ** created by: pablo
  ** description:Calculate the tax charges for the current order.  This is 
  **             calculating tax based on the ship-to address.
  ** parameters: $d
  **             $order_subtotal - sub total for the order
  ** returns: Tax for the current order
  ***************************************************************************/
   function calc_order_tax($order_subtotal, $d) {
      global $ps_vendor_id;
      $db = new ps_DB;
       
       require_once("tax/lib/ps_tax.inc");
       $ps_tax= new ps_tax;
     
      $q = "SELECT state, country FROM user_info WHERE user_info_id='";
      $q .= $d["ship_to_info_id"] . "'";
      $db->query($q);
      $db->next_record(); 
      $state = $db->f("state");
      $country = $db->f("country");
    
      $q = "SELECT * FROM tax_rate WHERE tax_country='$country' ";
      $q .= "AND tax_state='$state'"; 
      $db->query($q);
      if ($db->next_record()) {
         $rate = $order_subtotal * $db->f("tax_rate");
         return $rate;
      }
      else
         return(0);
   }

   /**************************************************************************  
   ** name: calc_order_shipping() 
   ** created by: Mike Wattier <geek@devcompany.com>   
   ** description:  Calculate the shipping charges for the current order   
   **                       using zones assigned in the zone module and the  
   **                       total quantity of items in the cart   
   ** parameters: $d,   
   ** returns: Shipping costs for this order based on country  
   ***************************************************************************/
   function calc_order_shipping($d) {
   	
   	global $ps_vendor_id;
   	
   	$db = new ps_DB;   	
   	$db2 = new ps_DB;  	
   	$db3 = new ps_DB; 	
   	  	
   	$q = "SELECT country FROM user_info WHERE user_info_id='"; 	
   	$q .= $d["ship_to_info_id"] . "'";	
   	$db->query($q);
   	$db->next_record();
   	$country = $db->f("country");   	
   	
   	$q2 = "SELECT zone_id FROM zone_country WHERE country_3_code='$country' ";  	
   	$db2->query($q2);	
   	$db2->next_record();
   	$the_zone = $db2->f("zone_id");	
   	
   	$q3 = "SELECT * FROM zone_shipping WHERE zone_id ='$the_zone' ";
   	$db3->query($q3);
   	$db3->next_record(); 	
   	
   	$cost_low = $db3->f("zone_cost") * $d["zone_qty"];
  	
   	if($cost_low < $db3->f("zone_limit")) {  		
   		return $cost_low; 		
   	}  	
   	else { 	
   		return $db3->f("zone_limit");
   	} 	
   }
   
  /**************************************************************************/
      
  /**************************************************************************
  ** name: calc_order_shipping_tax()
  ** created by: gday
  ** description:  Calculate the tax for the shipping of the current order
  ** parameters: $d
  ** returns: Tax for the shipping of this order
  ***************************************************************************/
   function calc_order_shipping_tax($d) { 

      /* 01/25/2000 - Dummy function for now */

      return(0);
   }
    
  /**************************************************************************
  ** name: get_vendor_currency()
  ** created by: gday
  ** description:  Get the currency type used by the $vendor_id
  ** parameters: $vendor_id - vendor id to return currency type
  ** returns: Currency type for this vendor
  ***************************************************************************/
   function get_vendor_currency($vendor_id) {
      $db = new ps_DB;

      $q = "SELECT vendor_currency FROM vendor WHERE vendor_id=$vendor_id";

      $db->query($q);
      $db->next_record();

      $currency = $db->f("vendor_currency");

      return($currency);
   }

  /**************************************************************************
  ** name: email_receipt()
  ** created by: gday
  ** description:  Create a receipt for the current order and email it to 
  **               the customer and the vendor.
  ** parameters: $order_id - Order ID for which to create the email receipts
  ** returns:  True - receipt created and emailed
  **          False - error occured 
  ***************************************************************************/
   function email_receipt($order_id) {
       global $sess,
              $ps_product,
              $ps_vendor_id;

       require_once("product/lib/ps_product.inc");
       $ps_product = new ps_product;


       // Connect to database and gather appropriate order information
       $db = new ps_DB;
       $q  = "SELECT * FROM orders ";
       $q .= "WHERE order_id='$order_id'";
       $db->query($q);
       $db->next_record();
       $user_id = $db->f("user_id");

       $dbbt = new ps_DB;
       $qt = "SELECT * from user_info ";
       $qt .= "WHERE user_info.user_id='$user_id' ";
       $qt .= "AND user_info.address_type='BT'";
       $dbbt->query($qt);
       $dbbt->next_record();

       $dbst = new ps_DB;
       $qt = "SELECT * FROM user_info ";
       $qt .= "WHERE user_info_id='";
       $qt .= $db->f("user_info_id") . "'";
       $dbst->query($qt);
       $dbst->next_record(); 

       $dbv = new ps_DB;
       $qt = "SELECT * from vendor ";
       /* Need to decide on vendor_id <=> order relationship */
       $qt .= "WHERE vendor_id = $ps_vendor_id";
       $dbv->query($qt);
       $dbv->next_record();


       // Email Addresses for shopper and vendor
       // **************************************
       $shopper_email = $dbbt->f("user_email");
       $from_email = $dbv->f("contact_email");


       // Headers and Footers
       // ******************************
       // Shopper Header
       $shopper_header = "Thank you for shopping with us.  Your order ";
       $shopper_header .= "information follows.\n\n";

       //Shopper Footer
       $shopper_footer = "\n\nThank you for your patronage.\n";
       $shopper_footer .= "\n\nQuestions? Problems?\n";
       $shopper_footer .= "Email: " . $dbv->f("contact_email");
       
       $shopper_subject = $dbv->f("vendor_name") . " Order -" . $db->f("order_id");

       // Vendor Header
       $vendor_header = "The following order was received.\n";
       $vendor_subject = "Order Notice-" . $db->f("order_id");

       // Vendor Footer
       $url = $sess->url(SECUREURL . "?page=order/order_print&amp;order_id=$order_id");
       $vendor_footer = "\n\nView the order by following the link below.\n";
       $vendor_footer .= $sess->url($url);
       $vendor_email = $dbv->f("contact_email");
 

       // Main Email Message Purchase Order
       // *********************************
       $shopper_message  = "\nPURCHASE ORDER\n";
       $shopper_message .= "------------------------------------------------------------------------\n";
       $shopper_message .= "ORDER NUMBER: " . $db->f("order_id") . "\n";
       $shopper_message .= "ORDER DATE:   ";
       $shopper_message .= date("d-M-Y:H:i", $db->f("cdate")) . "\n";
       $shopper_message .= "ORDER STATUS: ";
       switch($db->f("order_status")) {
         case ("P"):
           $shopper_message .= "Pending\n\n";
           break;
         case ("X"):
           $shopper_message .= "Canceled\n\n";
           break;
         case ("C"):
           $shopper_message .= "Confirmed\n\n";
           break;
       }
       $shopper_message .= "CUSTOMER INFORMATION\n";
       $shopper_message .= "--------------------\n\n";
       $shopper_message .= "Bill To\n";
       $shopper_message .= "-------\n\n";
       $shopper_message .= "     Company:    ";
       $shopper_message .= $dbbt->f("company") . "\n";
       $shopper_message .= "     Name:       ";
       if ($dbbt->f("title")) {
         $shopper_message .= $dbbt->f("title") . " ";
       }
       $shopper_message .= $dbbt->f("first_name") . " ";
       if ($dbbt->f("middle_name")) {
         $shopper_message .= $dbbt->f("middle_name") . " ";
       }
       $shopper_message .= $dbbt->f("last_name") . "\n";
       $shopper_message .= "     Address1:   ";
       $shopper_message .= $dbbt->f("address_1") . "\n";
       $shopper_message .= "     Address2:   ";
       $shopper_message .= $dbbt->f("address_2") . "\n";
       $shopper_message .= "     City:       ";
       $shopper_message .= $dbbt->f("city") . "\n";
       $shopper_message .= "     State/Region:      ";
       $shopper_message .= $dbbt->f("state") . "\n";
       $shopper_message .= "     Zip:        ";
       $shopper_message .= $dbbt->f("zip") . "\n";
       $shopper_message .= "     Country:    ";
       $shopper_message .= $dbbt->f("country") . "\n";
       $shopper_message .= "     Phone:      ";
       $shopper_message .= $dbbt->f("phone_1") . "\n";
       $shopper_message .= "     Fax:        ";
       $shopper_message .= $dbbt->f("fax") . "\n\n";
       
       $shopper_message .= "Ship To\n";
       $shopper_message .= "-------\n\n";
       $shopper_message .= "     Company:    ";
       $shopper_message .= $dbst->f("company") . "\n";
       $shopper_message .= "     Name:       ";
       $shopper_message .= $dbbt->f("title") . " ";
       $shopper_message .= $dbst->f("first_name") . " ";
       $shopper_message .= $dbst->f("middle_name") . " ";
       $shopper_message .= $dbst->f("last_name") . "\n";
       $shopper_message .= "     Address1:   ";
       $shopper_message .= $dbst->f("address_1") . "\n";
       $shopper_message .= "     Address2:   ";
       $shopper_message .= $dbst->f("address_2") . "\n";
       $shopper_message .= "     City:       ";
       $shopper_message .= $dbst->f("city") . "\n";
       $shopper_message .= "     State/Region:      ";
       $shopper_message .= $dbst->f("state") . "\n";
       $shopper_message .= "     Zip:        ";
       $shopper_message .= $dbst->f("zip") . "\n";
       $shopper_message .= "     Country:    ";
       $shopper_message .= $dbst->f("country") . "\n";
       $shopper_message .= "     Phone:      ";
       $shopper_message .= $dbst->f("phone_1") . "\n";
       $shopper_message .= "     Fax:        ";
       $shopper_message .= $dbst->f("fax") . "\n\n";

       $shopper_message .= "ORDER ITEMS\n";
       $shopper_message .= "-----------";

       $dboi = new ps_DB;
       $q = "SELECT * ";
       $q .= "FROM product, order_item, orders ";
       $q .= "WHERE product.product_id=order_item.product_id ";
       $q .= "AND order_item.order_id='";
       $q .= $order_id . "' ";
       $q .= "AND orders.order_id=order_item.order_id";
       $dboi->query($q);

       while($dboi->next_record()) {
          $shopper_message .= "\n\n";
          $shopper_message .= "PRODUCT  = ";
          if ($dboi->f("product_parent_id")) {
            $shopper_message .= $ps_product->get_field($dboi->f("product_parent_id"), "product_name") . "\n";
            $shopper_message .= "SERVICE  = ";
          }
          $shopper_message .= $dboi->f("product_name") . "\n";
          $shopper_message .= "QUANTITY = ";
          $shopper_message .= $dboi->f("product_quantity") . "\n";
          $shopper_message .= "SKU      = ";
          $shopper_message .= $ps_product->get_field($dboi->f("product_id"), "product_sku") . "\n";
          $price = $ps_product->get_price($dboi->f("product_id"));
          $shopper_message .= "PRICE    = ";
          $shopper_message .= sprintf("%1.2f %s", $price["product_price"], $price["product_currency"]);
       }

       $shopper_message .= "\n\n";
       $sub_total = $db->f("order_subtotal");
       $shopper_message .= "SUBTOTAL = ";
       $shopper_message .= sprintf("%1.2f %s\n", $sub_total, $price["product_currency"]);
       $order_tax = $db->f("order_tax");
       $shopper_message .= "TAX      = ";
       $shopper_message .= sprintf("%1.2f\n", $order_tax);

       $order_shipping = $db->f("order_shipping");
       $shopper_message .= "SHIPPING = ";
       $shopper_message .= sprintf("%1.2f\n", $order_shipping);

       $order_shipping_tax = $db->f("order_shipping_tax");
       $shopper_message .= "SHIPPING TAX   = ";
       $shopper_message .= sprintf("%1.2f\n", $order_shipping_tax);

       $order_total= $sub_total + 
                     $order_tax + 
                     $order_shipping + 
                     $order_shipping_tax;
       $shopper_message .= "\n\n";
       $shopper_message .= "TOTAL    = ";
       $shopper_message .= sprintf("%1.2f %s\n", $order_total, $price["product_currency"]);
       $shopper_message .= "------------------------------------------------------------------------\n";
       // End of Purchase Order
       // *********************
       
		require_once("admin/lib/ps_mail.inc");
		$ps_mail = new ps_mail;
		
       // Mail receipt to the shopper
       $ps_mail->send($shopper_email, 
            $shopper_subject, 
            $shopper_header . $shopper_message . $shopper_footer,
            $from_email);

       // Mail receipt to the vendor
       $ps_mail->send($vendor_email,
            $vendor_subject,
            $vendor_header . $shopper_message . $vendor_footer,
            $from_email);

      return(True); 
   }



  /**************************************************************************
  ** name: asterisk_pad()
  ** created by: gday
  ** description:  Return $str with all but $display_length at the end as 
  **               asterisks.
  ** parameters: $str - string to asterisk pad
  **             $display_length - length at the end of $str that will not
  **                               be obscured by asterisks
  ** returns: $str with all but $display_length at the end obscured
  **          by asterisks
  ***************************************************************************/
   function asterisk_pad($str, $display_length) {

      $total_length = strlen($str);

      if($total_length > $display_length) {
         for($i = 0; $i < $total_length - $display_length; $i++) {
           $str[$i] = "*";
         }
      }

      return($str);
   } 

  /**************************************************************************
  ** name: cybercash_process()
  ** created by: pablo
  ** description:  Based on the cyberlib class found in the PHP extensions library.
  ** parameters: 
  ** returns: 
  ***************************************************************************/
   function cybercash_process($order_number, $order_total, &$d) {
     global $auth,
       $ps_vendor_id;

     require "checkout/lib/ps_cyberlib.inc";
     
     // Get user billing information
     $dbbt = new ps_DB;
     $qt = "SELECT * from user_info ";
     $qt .= "WHERE user_info.user_id='".$auth["user_id"]."' ";
     $qt .= "AND user_info.address_type='BT'";
     $dbbt->query($qt);
     $dbbt->next_record();     

     $merchant=CC_MERCHANT;
     $merchant_key=CC_MERCHANT_KEY;
     $payment_url=CC_PAYMENT_URL;
     $auth_type=CC_AUTH_TYPE;
     
     $expire_date = date("m/y",(int)$d["order_payment_expire"]);

     $response=SendCC2_1Server($merchant,$merchant_key,$payment_url,
			       $auth_type,
			       array(
				     "Order-ID" => $order_number,
				     "Amount" => $this->get_vendor_currency($ps_vendor_id) . " " . $order_total,
				     "Card-Number" => $d["order_payment_number"],
				     "Card-Address" => $dbbt->f("address_1"),
				     "Card-City" => $dbbt->f("city"),
				     "Card-State" => $dbbt->f("state"),
				     "Card-Zip" => $dbbt->f("zip"),
				     "Card-Country" => $dbbt->f("country"),
				     "Card-Exp" => $expire_date,
				     "Card-Name" => $dbbt->f("first_name")." ".$dbbt->f("last_name")
				     )
			       );
    
     $d["order_payment_log"] = "";
     while(list($key,$val)=each($response)) {
       $d["order_payment_log"] .= $key."=".$val."<br />";
     }   
     
     if ($response["MStatus"] == "success")
       return True;
     else {
       $d["error"] = $response["MErrMsg"];
       return False;
     }
   }

  /**************************************************************************
  ** name: authnet_process()
  ** created by: jep
  ** description: process transaction using ps_authnet.inc class
  ** parameters: 
  ** returns: 
  ***************************************************************************/
   function authnet_process($order_number, $order_total, &$d) {
     global $auth,
       $ps_vendor_id;

     // Get user billing information
     $dbbt = new ps_DB;
     $qt = "SELECT * from user_info ";
     $qt .= "WHERE user_info.user_id='".$auth["user_id"]."' ";
     $qt .= "AND user_info.address_type='BT'";
     $dbbt->query($qt);
     $dbbt->next_record();     

     //Object to convert country code to two character code
     include("admin/lib/ps_country.inc");
     $country = new ps_country;

     //Authnet - connect settings
     $host = "secure.authorize.net";
     $port = 443;
     $path = "/gateway/transact.dll";

     //Authnet vars to send
     //More can be added if needed.
     $formdata = array (
       'x_version' => '3.1',
       'x_delim_data' => 'True',
       'x_delim_char' => '|',
       'x_relay_response' => 'False',
       'x_login' => AN_LOGIN,
       'x_tran_key' => AN_TRAN_KEY,
       'x_test_request' => AN_TEST_REQUEST,
       'x_type' => AN_TYPE,

       'x_first_name' => $dbbt->f("first_name"),
       'x_last_name' => $dbbt->f("last_name"),
       'x_address' => $dbbt->f("address_1"),
       'x_city' => $dbbt->f("city"),
       'x_state' => $dbbt->f("state"),
       'x_zip' => $dbbt->f("zip"),
       'x_country' => $country->getTwoLetterCode($dbbt->f("country")),
       'x_card_num' => $d["order_payment_number"],
       'x_card_code' => '',
       'x_amount' => $this->get_vendor_currency($ps_vendor_id) . " " . $order_total,

       'x_exp_date' => date("mY",(int)$d["order_payment_expire"]),
       'x_email' => '',
       'x_email_customer' => 'False',
       'x_cust_id' => '',
       'x_customer_ip' => $_SERVER["REMOTE_ADDR"],
       'x_phone' => '',
       'x_fax' => '',
       'x_invoice_num' => $order_number,
       'x_description' => ''
     );

     //build the post string
       $poststring = '';
       foreach($formdata AS $key => $val){
         $poststring .= urlencode($key) . "=" . urlencode($val) . "&amp;";
       }
     // strip off trailing ampersand escape entity ('&amp;')
     $poststring = substr($poststring, 0, -5);
 
     $fp = fsockopen("ssl://".$host, $port, $errno, $errstr, $timeout = 60);

     if(!$fp){
      //error tell us
      echo "$errstr ($errno)\n";

     }else{

       //send the server request
       fputs($fp, "POST $path HTTP/1.1\r\n");
       fputs($fp, "Host: $host\r\n");
       fputs($fp, "Content-type: application/x-www-form-urlencoded\r\n");
       fputs($fp, "Content-length: ".strlen($poststring)."\r\n");
       fputs($fp, "Connection: close\r\n\r\n");
       fputs($fp, $poststring . "\r\n\r\n");

       //Get the response header from the server
       $str = '';
       while(!feof($fp) && !stristr($str, 'content-length')) {
         $str = fgets($fp, 4096);
       }
       // If didnt get content-lenght, something is wrong, return false.
       if (!stristr($str, 'content-length')) {
         return false;
       }
       // Get length of data to be received.
       $length = trim(substr($str,strpos($str,'content-length') + 15));
       // Get buffer (blank data before real data)
       fgets($fp, 4096);
       // Get real data
       $data = fgets($fp, $length);
       fclose($fp);
       $response = explode("|", $data);
     }

     $d["order_payment_log"] = $response[3];
     
     if ($response[0] == '1') {
       $d["order_status"] = 'C';
       return True;
     } else {
       $d["error"] = $response[3];
       return False;
     }
   }
   
   
} 
?>
