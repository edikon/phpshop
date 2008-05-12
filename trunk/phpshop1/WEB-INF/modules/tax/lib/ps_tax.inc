<?php
/*
 * The ps_tax class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_tax.inc,v 1.1.1.1 2004/07/27 14:59:48 pablo Exp $
 *
 */

class ps_tax {
  var $classname = "ps_tax";
  
  /*
  ** VALIDATION FUNCTIONS
  **
  */

  function validate_add(&$d) {
    
    $db = new ps_DB;
   
    $q = "SELECT * from tax_rate WHERE tax_state='" . $d["tax_state"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] = "ERROR:  You this state is already listed.";
      return False;
    } 
    if (!$d["tax_state"]) {
      $d["error"] = "ERROR:  You must enter a state or region for this tax rate.";
      return False;	
    }
    if (!$d["tax_country"]) {
      $d["error"] = "ERROR:  You must enter a country for this tax rate.";
      return False;
    }
    if (!$d["tax_rate"]) {
      $d["error"] = "ERROR:  You must enter a tax rate.";
      return False;
    }

    return True;    
  }
  
  function validate_delete($d) {
    
    if (!$d["tax_rate_id"]) {
      $d["error"] = "ERROR:  Please select a tax rate to delete.";
      return False;
    }
    else {
      return True;
    }
  }
  
  function validate_update(&$d) {
    $db = new ps_DB;

    if (!$d["tax_rate_id"]) {
      $d["error"] = "ERROR:  You must select a tax rate to update.";
      return False;
    }
    if (!$d["tax_state"]) {
      $d["error"] = "ERROR:  You must enter a state or region for this tax rate.";
      return False;
    }
    if (!$d["tax_country"]) {
      $d["error"] = "ERROR:  You must enter a country for this tax rate.";
      return False;
    }
    if (!$d["tax_rate"]) {
      $d["error"] = "ERROR:  You must enter a tax rate.";
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
    $q = "INSERT INTO tax_rate (vendor_id, tax_state, tax_country, ";
    $q .= "tax_rate, mdate) VALUES (";
    $q .= "'$ps_vendor_id','";
    $q .= $d["tax_state"] . "','";
    $q .= $d["tax_country"] . "','";
    $q .= $d["tax_rate"] . "','";
    $q .= $timestamp . "')";
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
    $q = "UPDATE tax_rate SET ";
    $q .= "tax_state='" . $d["tax_state"];
    $q .= "',tax_country='" . $d["tax_country"];
    $q .= "',tax_rate='" . $d["tax_rate"];
    $q .= "',mdate='" . $timestamp;
    $q .= "' WHERE tax_rate_id='" . $d["tax_rate_id"] . "'";
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
    $q = "DELETE from tax_rate where tax_rate_id='" . $d["tax_rate_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id'";
    $db->query($q);
    $db->next_record();
    return True;
  }

}
?>
