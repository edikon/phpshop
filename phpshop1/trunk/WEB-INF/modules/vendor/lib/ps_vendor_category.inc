<?php
/*
 * The ps_vendor_category class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_vendor_category.inc,v 1.1.1.1 2004/07/27 14:59:53 pablo Exp $
 *
 */

class ps_vendor_category {

  var $classname = "ps_vendor_category";
  var $error;


  /**************************************************************************
  ** name: validate
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  function validate_add($d) {
    
    if (!$d["vendor_category_name"]) {
      $d["error"] = "You must enter a name for the vendor category.";
      return False;	
    }
    else {
      return True;
    }
  }
  
  /**************************************************************************
  ** name: validate
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  function validate_delete($d) {

    if (!$d["vendor_category_id"]) {
      $d["error"] = "Please select a vendor to delete.";
      return False;
    }
    else {
      return True;
    }
  }

  /**************************************************************************
  ** name: validate
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  function validate_update($d) {
    
    if (!$d["vendor_category_name"]) {
      $d["error"] = "You must enter a name for the vendor category.";
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

    if (!$this->validate_add($d)) {
      return False;
    }
    $q = "INSERT INTO vendor_category (";
    $q .= "vendor_category_name,";
    $q .= "vendor_category_desc) VALUES ('";
    $q .= $d["vendor_category_name"] . "','";
    $q .= $d["vendor_category_desc"] . "')";
    $db->query($q);
    $db->next_record();
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
    
    if (!$this->validate_update($d)) {
      return False;
    }
    $q = "UPDATE vendor_category ";
    $q .= "set vendor_category_name='" . $d["vendor_category_name"] . "',";
    $q .= "vendor_category_desc='" . $d["vendor_category_desc"];
    $q .= "' WHERE vendor_category_id='" . $d["vendor_category_id"] . "'";
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
    $q = "DELETE FROM vendor_category WHERE vendor_category_id='";
    $q .= $d["vendor_category_id"] . "'";
    $db->query($q);
    $db->next_record();
    return True;
  }


  /**************************************************************************
   * name: list_category()
   * created by: jep
   * description: Creates a list of Vendor Categories to be used in SELECT.
   * parameters:
   * returns: array of values
   **************************************************************************/
  function list_category($vendor_category_id=0) {
    
    // Create an array for a form drop down list using OOHFORMS
    $db = new ps_DB;
    // Creates a form drop down list and prints it
    $db = new ps_DB;
    
    $q = "SELECT count(*) as rowcnt FROM vendor_category ORDER BY vendor_category_name";
    $db->query($q);
    $db->next_record();
    $rowcnt = $db->f("rowcnt");


    $q = "SELECT * FROM vendor_category ORDER BY vendor_category_name";
    $db->query($q);                                                                                     
    $code = "<select name=\"vendor_category_id\">\n";
    if ( $rowcnt > 1) {
      $code .= "<option value=\"0\">Please Select</option>\n";      
    }   
    while ($db->next_record()) {
      $code .= "  <option value=\"" . $db->f("vendor_category_id") . "\"";
      if ($db->f("vendor_category_id") == $vendor_category_id) { 
        $code .= " selected=\"selected\""; 
      }
      $code .= ">" . $db->f("vendor_category_name") . "</option>\n";
    }
    $code .= "</select>\n";
    print $code;
  }
  
}
$ps_vendor_category = new ps_vendor_category;
?>
