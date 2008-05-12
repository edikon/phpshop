<?php
/*
 * The ps_vendor class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_vendor.inc,v 1.1.1.1 2004/07/27 14:59:53 pablo Exp $
 *
 */


class ps_vendor {
  var $classname = "ps_vendor";
  var $error;


  /**************************************************************************
  ** name: validate_add()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/ 
  function validate_add(&$d) {
    $db = new ps_DB;

    $q = "SELECT * from vendor";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] = "ERROR:  This version of phpShop only supports one vendor.";
      return false;
    } 
    if (!validate_image($d,"vendor_thumb_image","vendor")) {
      return false;
    }
    if (!validate_image($d,"vendor_full_image","vendor")) {
      return false;
    }
    if (!$d["vendor_name"]) {
      $d["error"] = "ERROR:  You must enter a name for the vendor.";
      return False;	
    }
    if (!$d["contact_email"]) {
      $d["error"]  = "ERROR:  You must enter an email address for the vendor ";
      $d["error"] .= "contact.";
      return False;
    }
    if (!validate_email($d["contact_email"])) {
      $d["error"]  = "ERROR:  Please provide a valide email address for the ";
      $d["error"] .= "vendor contact.";
      return False;
    } 
    else {
      return True;
    }
  }
  
  /**************************************************************************
  ** name: validate_delete()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/    
function validate_delete(&$d) {
    $db = new ps_DB;

    if (!$d["vendor_id"]) {
      $d["error"] = "Please select a vendor to delete.";
      return False;
    }
    $q = "SELECT * FROM product where vendor_id='" . $d["vendor_id"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"]  = "ERROR:  This vendor still has products.  ";
      $d["error"] .= "Delete all products first.";
      return False;
    }

    /* Get the image filenames from the database */
    $db = new ps_DB;
    $q  = "SELECT vendor_thumb_image,vendor_full_image ";
    $q .= "FROM vendor ";
    $q .= "WHERE vendor_id='" . $d["vendor_id"] . "'";
    $db->query($q);
    $db->next_record();
 
    /* Validate vendor_thumb_image */
    $d["vendor_thumb_image_curr"] = $db->f("vendor_thumb_image");
    $d["vendor_thumb_image_name"] = "none";
    if (!validate_image($d,"vendor_thumb_image","vendor")) {
      return false;
    }
 
    /* Validate vendor_full_image */
    $d["vendor_full_image_curr"] = $db->f("vendor_full_image");
    $d["vendor_full_image_name"] = "none";
    if (!validate_image($d,"vendor_full_image","vendor")) {
      return false;
    }

    return True;
  }

  /**************************************************************************
  ** name: validate_update()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/    
function validate_update(&$d) {
    
    if (!$d["vendor_name"]) {
      $d["error"] = "ERROR:  You must enter a name for the vendor.";
      return False;	
    }
    if (!validate_image($d,"vendor_thumb_image","vendor")) {
      return false;
    }
    if (!validate_image($d,"vendor_full_image","vendor")) {
      return false;
    }
    if (!$d["contact_email"]) {
      $d["error"]  = "ERROR:  You must enter an email address for the vendor ";
      $d["error"] .= "contact.";
      return False;
    }
    if (!validate_email($d["contact_email"])) {
      $d["error"]  = "ERROR:  Please provide a valide email address for the ";
      $d["error"] .= "vendor contact.";
      return False;
    } 
    else {
      return True;
    }
  }
  
  /**************************************************************************
   * name: add()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function add(&$d) {
    $db = new ps_DB;
    $timestamp = time();

    if (!$this->validate_add($d)) {
      return False;
    }

    if (!process_images($d)) {
      return false;
    }

    $q = "INSERT INTO vendor (";
    $q .= "vendor_name,";
    $q .= "contact_last_name,";
    $q .= "contact_first_name,";
    $q .= "contact_middle_name,";
    $q .= "contact_title,";
    $q .= "contact_phone_1,";
    $q .= "contact_phone_2,";
    $q .= "contact_fax,";
    $q .= "contact_email,";
    $q .= "vendor_phone,";
    $q .= "vendor_address_1,";
    $q .= "vendor_address_2,";
    $q .= "vendor_city,";
    $q .= "vendor_state,";
    $q .= "vendor_country,";
    $q .= "vendor_zip,";
    $q .= "vendor_store_name,";
    $q .= "vendor_store_desc,";
    $q .= "vendor_category_id,";
    $q .= "vendor_image_path,";
    $q .= "vendor_thumb_image,";
    $q .= "vendor_full_image,";
    $q .= "vendor_currency,";
    $q .= "cdate,mdate) VALUES ('";
    $q .= $d["vendor_name"] . "','";
    $q .= $d["contact_last_name"] . "','";
    $q .= $d["contact_first_name"] . "','";
    $q .= $d["contact_middle_name"] . "','";
    $q .= $d["contact_title"] . "','";
    $q .= $d["contact_phone_1"] . "','";
    $q .= $d["contact_phone_2"] . "','";
    $q .= $d["contact_fax"] . "','";
    $q .= $d["contact_email"] . "','";
    $q .= $d["vendor_phone"] . "','";
    $q .= $d["vendor_address_1"] . "','";
    $q .= $d["vendor_address_2"] . "','";
    $q .= $d["vendor_city"] . "','";
    $q .= $d["vendor_state"] . "','";
    $q .= $d["vendor_country"] . "','";
    $q .= $d["vendor_zip"] . "','";
    $q .= $d["vendor_store_name"] . "','";
    $q .= $d["vendor_store_desc"] . "','";
    $q .= $d["vendor_category_id"] . "','";
    $q .= $d["vendor_image_path"] . "','";
    $q .= $d["vendor_thumb_image"] . "','";
    $q .= $d["vendor_full_image"] . "','";
    $q .= $d["vendor_currency"] . "','";
    $q .= "$timestamp','$timestamp')";
    $db->query($q);
    $db->next_record();

    // Get the assigned vendor_id //
    $q  = "SELECT vendor_id FROM vendor ";
    $q .= "WHERE vendor_name = '" . $d["vendor_name"] . "' ";
    $q .= "AND cdate = $timestamp";
    $db->query($q);
    $db->next_record();
    $d["vendor_id"] = $db->f("vendor_id");

    /* Insert -default- shopper group */
    $q = "INSERT INTO shopper_group (";
    $q .= "vendor_id,";
    $q .= "shopper_group_name,";
    $q .= "shopper_group_desc) VALUES ('";
    $q .= $d["vendor_id"] . "',";
    $q .= "'-default-',";
    $q .= "'Default shopper group.')";
    $db->query($q);

    return True;
  }

  /**************************************************************************
   * name: update()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function update(&$d) {
    $db = new ps_DB;
    $timestamp = time();

    if (!$this->validate_update($d)) {
      return False;
    }

    if (!process_images($d)) {
      return false;
    }

    $q = "UPDATE vendor set vendor_name='" . $d["vendor_name"] . "',";
    $q .= "contact_last_name='" . $d["contact_last_name"] . "',";
    $q .= "contact_first_name='" . $d["contact_first_name"] . "',";
    $q .= "contact_middle_name='" . $d["contact_middle_name"] . "',";
    $q .= "contact_title='" . $d["contact_title"] . "',";
    $q .= "contact_phone_1='" . $d["contact_phone_1"] . "',";
    $q .= "contact_phone_2='" . $d["contact_phone_2"] . "',";
    $q .= "contact_fax='" . $d["contact_fax"] . "',";
    $q .= "contact_email='" . $d["contact_email"] . "',";
    $q .= "vendor_phone='" . $d["vendor_phone"] . "',";
    $q .= "vendor_address_1='" . $d["vendor_address_1"] . "',";
    $q .= "vendor_address_2='" . $d["vendor_address_2"] . "',";
    $q .= "vendor_city='" . $d["vendor_city"] . "',";
    $q .= "vendor_state='" . $d["vendor_state"] . "',";
    $q .= "vendor_country='" . $d["vendor_country"] . "',";
    $q .= "vendor_zip='" . $d["vendor_zip"] . "',";
    $q .= "vendor_store_name='" . $d["vendor_store_name"] . "',";
    $q .= "vendor_store_desc='" . $d["vendor_store_desc"] . "',";
    $q .= "vendor_category_id='" . $d["vendor_category_id"] . "',";
    if ($d["vendor_image_path"])
    $q .= "vendor_image_path='" . $d["vendor_image_path"] . "',";
    $q .= "vendor_thumb_image='" . $d["vendor_thumb_image"] . "',";
    $q .= "vendor_full_image='" . $d["vendor_full_image"] . "',";
    $q .= "vendor_currency='" . $d["vendor_currency"] . "',";
    $q .= "mdate='$timestamp' ";
    $q .= "WHERE vendor_id='" . $d["vendor_id"] . "'";    
    $db->query($q);
    $db->next_record();
    return True;
  }

  /**************************************************************************
   * name: delete()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function delete(&$d) {
    $db = new ps_DB;
    
    if (!$this->validate_delete($d)) {
      return False;
    }

    /* Delete Image files */
    if (!process_images($d)) {
      return false;
    }

    $q = "DELETE from vendor where vendor_id='" . $d["vendor_id"] . "'";
    $db->query($q);
    $db->next_record();

    return True;
  }

  /**************************************************************************
  ** name: get_user_vendor_id
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function get_user_vendor_id() {
    global $auth;

    $db = new ps_DB;

    $q  = "SELECT vendor_id FROM auth_user_vendor ";
    $q .= "WHERE user_id='" . $auth["user_id"] . "'";
    $db->query($q);
    $db->next_record();
    return $db->f("vendor_id");
  }

  /**************************************************************************
   * name: find()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function find($d, $start=0) {
    $db = new ps_DB;
    
    if ($d["vendor_thumb_image"] == "none") {
      $d["vendor_thumb_image"] = "";
    }
    if ($d["vendor_full_image"] == "none") {
      $d["vendor_full_image"] = "";
    }
    
    if ($d["vendor_category_id"] == "0") {
      $d["vendor_category_id"] = "";
    } 
    $q = "SELECT * from vendor where vendor_name LIKE '%" . $d["vendor_name"] . "%'";
    $q .= " AND contact_last_name LIKE '%" . $d["contact_last_name"] . "%'";
    $q .= " AND contact_first_name LIKE '%" . $d["contact_first_name"] . "%'";
    $q .= " AND contact_middle_name LIKE '%" . $d["contact_middle_name"] . "%'";
    $q .= " AND contact_title LIKE '%" . $d["contact_title"] . "%'";
    $q .= " AND contact_phone_1 LIKE '%" . $d["contact_phone_1"] . "%'";
    $q .= " AND contact_phone_2 LIKE '%" . $d["contact_phone_2"] . "%'";
    $q .= " AND contact_fax LIKE '%" . $d["contact_fax"] . "%'";
    $q .= " AND contact_email LIKE '%" . $d["contact_email"] . "%'";
    $q .= " AND vendor_phone LIKE '%" . $d["vendor_phone"] . "%'";
    $q .= " AND vendor_address_1 LIKE '%" . $d["vendor_address_1"] . "%'";
    $q .= " AND vendor_address_2 LIKE '%" . $d["vendor_address_2"] . "%'";
    $q .= " AND vendor_city LIKE '%" . $d["vendor_city"] . "%'";
    $q .= " AND vendor_state LIKE '%" . $d["vendor_state"] . "%'";
    $q .= " AND vendor_country LIKE '%" . $d["vendor_country"] . "%'";
    $q .= " AND vendor_zip LIKE '%" . $d["vendor_zip"] . "%'";
    $q .= " AND vendor_store_name LIKE '%" . $d["vendor_store_name"] . "%'";
    $q .= " AND vendor_store_desc LIKE '%" . $d["vendor_store_desc"] . "%'";
    $q .= " AND vendor_category_id LIKE '%" . $d["vendor_category_id"] . "%'";
    $q .= " AND vendor_thumb_image LIKE '%" . $d["vendor_thumb_image"] . "%'";
    $q .= " AND vendor_full_image LIKE '%" . $d["vendor_full_image"] . "%'";
    $q .= " AND vendor_currency LIKE '%" . $d["vendor_currency"] . "%'";

    $db->query($q);
    $db->next_record();
    if ($db->num_rows() == 1) {
      return "?vid=" . $db->f("vendor_id");
    }
    $t = new phpshop_Table;
    $t->query = $q;
    $t->table = "vendor";
    $t->start = $start;
    // Select fields to display
    $t->fields = array(
		       "vendor_id",
		       "vendor_name",
		       "vendor_store_desc"
		       );
    
    // Set column header names
    $t->map_cols = array(
			 "vendor_id" => "Vendor ID",
			 "vendor_name" => "Vendor Name",
			 "vendor_store_desc" => "Vendor Description"
			 );
    $t->show_table();    
    return True;
  }


  /**************************************************************************
   * name: listVendor()
   * created by:
   * description: Creates a list of SELECT recods using vendor name and vendor id.
   * parameters:
   * returns: array of values
   **************************************************************************/
  function get_name($vendor_id,$product_id="") {

    // Returns the vendor name corresponding to a vendor_id;
    $db = new ps_DB;

    if ($vendor_id) {
      $q = "SELECT vendor_name FROM vendor WHERE vendor_id = '$vendor_id'";
    } elseif ($product_id) {
      $q  = "SELECT vendor_name FROM product,vendor ";
      $q .= "WHERE product_id = '$product_id' ";
      $q .= "AND product.vendor_id = vendor.vendor_id ";
    } else {
      /* ERROR: No arguments were specified. */
      return 0;
    }
    
    $db->query($q);
    $db->next_record();
    return $db->f("vendor_name");
  }


  /**************************************************************************
   * name: set_vendor()
   * created by:
   * description: Creates a list of SELECT recods using vendor name and vendor id.
   * parameters:
   * returns: array of values
   **************************************************************************/
  function set_vendor($d) {
    global $ps_vendor_id, $sess;
 
    $ps_vendor_id = $d["vendor_id"];
    return True;

  }

  /**************************************************************************
  ** name: listVendor()
  ** created by:
  ** description: Creates a list of SELECT recods using vendor name and 
  **              vendor id.
  ** parameters:
  ** returns: array of values
  ***************************************************************************/
  function list_vendor($vendor_id=0) {
    global $ps_vendor_id, $sess;

    // Creates a form drop down list and prints it
    $db = new ps_DB;
    
    $q = "SELECT count(*) as rowcnt FROM vendor ORDER BY vendor_name";
    $db->query($q);
    $db->next_record();
    $rowcnt = $db->f("rowcnt");
 
    // If only one vendor do not show list 
    if ($rowcnt == 1) 
       return True;

    $q = "SELECT * FROM vendor ORDER BY vendor_name";
    $db->query($q);
   
    $code = "<form action=\"" . SECUREURL . "\" METHOD=\"post\">\n";
    $code .= "<input type=\"hidden\" name=\"page\" value=\"admin/index\" />\n";
    $code .= "<input type=\"hidden\" name=\"func\" value=\"setVendor\" />\n";
    $code .= $sess->hidden_session() . "\n";
    $code .= "<select name=\"vendor_id\">\n";
    while ($db->next_record()) {     
      $code .= "  <option value=\"" . $db->f("vendor_id") . "\"";
      if ($db->f("vendor_id") == $vendor_id) { 
	$code .= " selected=\"selected\""; 
      }
      $code .= ">" . $db->f("vendor_name") . "</option>\n";
    }
    $code .= "</select><br />\n";
    $code .= "<input type=\"submit\" name=\"go\" value=\"go\" />\n";
    $code .= "</FONT>";
    print $code;
  }

  /****************************************************************************
   *    function: validate_email
   *  created by: Gregory Day
   * description: Validates an e-mail address.  Only checks that the format
   *              is valid.  It does not validate that the address will
   *              work.
   *  parameters: $email: Email address to validate
   *     returns: true: Email address is valid
   *             false: Email address is not valid 
   ****************************************************************************/

  function validate_email ( $email ) {

   if(ereg('^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*$', $email)) {      return(true);
   }
   else {
      return(false);
   }
  } // validate_email() 

  /**************************************************************************
  ** name: get_field
  ** created by: pablo
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function get_field($vendor_id, $field_name) {
    $db = new ps_DB;

    $q = "SELECT $field_name FROM vendor WHERE vendor_id='$vendor_id'";
    $db->query($q);
    if ($db->next_record()) {
       return $db->f($field_name);
    }
    else {
       return False;
    }
  }


  /**************************************************************************
  ** name: show_image()
  ** created by: pablo
  ** description:  Shows the image send in the $image field.
  **               $args are appended to the IMG tag.
  ** parameters:
  ** returns:
  ***************************************************************************/
  function show_image($image, $args="") {
    
    global $ps_vendor_id;
   
    if ($SERVER_PORT == "443")
        $url = SECUREURL;
    else
        $url = URL;
 
    $url = $this->get_field($ps_vendor_id,"vendor_image_path");
    $url .= "vendor/";
    if (!isset($image) || ($image == "")) {
    	$url .= "noimage.gif";
    } else {
    	$url .= $image;
    }
    echo "<img src=\"$url\" $args />\n";
    
    return True;
  }
}
?>
