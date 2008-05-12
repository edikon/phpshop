<?php
/*
 * The ps_order_status class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_order_status.inc,v 1.1.1.1 2004/07/27 14:58:48 pablo Exp $
 *
 */

class ps_order_status {
  var $classname = "ps_order_status";
  
  /*
  ** VALIDATION FUNCTIONS
  **
  */

  function validate_add(&$d) {
    
    $db = new ps_DB;
   
    if (!$d["order_status_code"]) {
      $d["error"] = "ERROR:  You this order status type is already defined.";
      return False;
    } 

    return True;    
  }
  
  function validate_delete($d) {
    
    if (!$d["order_status_id"]) {
      $d["error"] = "ERROR:  Please select an order status type to delete.";
      return False;
    }
    else {
      return True;
    }
  }
  
  function validate_update(&$d) {
    $db = new ps_DB;

    if (!$d["order_status_id"]) {
      $d["error"] = "ERROR:  You must select an order status to update.";
      return False;
    }
    if (!$d["order_status_code"]) {
      $d["error"] = "ERROR:  You must enter a order status code.";
      return False;
    }
    return True;
  }
  
  
  /**************************************************************************
   * name: add()
   * created by: pablo
   * description: creates a new tax rate record
   * parameters:
   * returns:
   **************************************************************************/
  function add(&$d) {
    $db = new ps_DB; 
    global $ps_vendor_id;
    $timestamp = time();
    
    if (!$this->validate_add($d)) {
      return False;
    }
    $q = "INSERT INTO order_status (vendor_id, order_status_code,";
    $q .= "order_status_name, list_order) ";
    $q .= "VALUES (";
    $q .= "'$ps_vendor_id','";
    $q .= $d["order_status_code"] . "','";
    $q .= $d["order_status_name"] . "','";
    $q .= $d["list_order"] . "')";
    $db->query($q);
    $db->next_record();
    return True;

  }
  
  /**************************************************************************
   * name: update()
   * created by: pablo
   * description: updates function information
   * parameters:
   * returns:
   **************************************************************************/
  function update(&$d) {
    $db = new ps_DB; 
    global $ps_vendor_id;
    $timestamp = time();

    if (!$this->validate_update($d)) {
      return False;	
    }
    $q = "UPDATE order_status SET ";
    $q .= "order_status_code='" . $d["order_status_code"];
    $q .= "',order_status_name='" . $d["order_status_name"];
    $q .= "',list_order='" . $d["list_order"];
    $q .= "' WHERE order_status_id='" . $d["order_status_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id'";
    $db->query($q);
    $db->next_record();
    return True;
  }

  /**************************************************************************
   * name: delete()
   * created by: pablo
   * description: Should delete a category and and categories under it.
   * parameters: 
   * returns:
   **************************************************************************/
  function delete(&$d) {
    $db = new ps_DB;
    global $ps_vendor_id;
    
    if (!$this->validate_delete($d)) {
      return False;
    }
    $q = "DELETE from order_status where order_status_id='" . $d["order_status_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id'";
    $db->query($q);
    $db->next_record();
    return True;
  }


  function list_order_status($order_status_code) {
    $db = new ps_DB;

    $q = "SELECT * from order_status ORDER BY list_order";
    $db->query($q);
    echo "<select name=\"order_status\">\n";
    while ($db->next_record()) {
      echo "<option value=\"" . $db->f("order_status_code") . "\"";
      if ($order_status_code == $db->f("order_status_code")) 
         echo " selected=\"selected\">";
      else
         echo ">";
      echo $db->f("order_status_name") . "</option>\n";
    }
    echo "</select>\n";

  }

}
?>
