<?php
/*
 * The ps_shopper_group class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_shopper_group.inc,v 1.1.1.1 2004/07/27 14:59:42 pablo Exp $
 *
*************************************************************************/
class ps_shopper_group {
  var $classname = "ps_shopper_group";
  var $id = "";
  var $error;
  
  /**************************************************************************
  ** name: validate
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/    
function validate_add($d) {
    $db = new ps_DB;
    global $ps_vendor_id;
    
    if (!$d["shopper_group_name"]) {
      $this->error = "ERROR:  You must enter a shopper group name.";
      return False;	
    }
    elseif ($d["shopper_group_name"]) {
      $q = "SELECT count(*) as num_rows from shopper_group";
      $q .= " WHERE shopper_group_name='" . $d["shopper_group_name"] . "'";
      $q .= " AND vendor_id='" . $ps_vendor_id . "'";

      $db->query($q);
      $db->next_record();
      if ($db->f("num_rows") > 0) {
	$this->error = "ERROR:  Shopper group already exists for this vendor.";
	return False;
      }
      else {
	return True;
      }
    }
  }
  
  /**************************************************************************
  ** name: validate
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/    
function validate_delete(&$d) {

    $db = new ps_DB;

    if (!$d["shopper_group_id"]) {
      $d["error"] = "ERROR:  Please select a shopper group to delete.";
      return False;
    }
    if ($d["shopper_group_id"]) {
      $q = "SELECT * from shopper_group where shopper_group_id='";
      $q .= $d["shopper_group_id"] . "' AND shopper_group_name='-default-'";
      $db->query($q);
      if ($db->next_record()) {
        $d["error"] = "ERROR:  Cannot delete the default shopper group.";
        return False;
      }
    }
    return True;
  }

  /**************************************************************************
  ** name: validate
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/    
function validate_update($d) {
    
    if (!$d["shopper_group_name"]) {
      $this->error = "ERROR:  You must enter a shopper group name.";
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
    global $ps_vendor_id;
    $hash_secret = "PHPShopIsCool";
    $db = new ps_DB;
    $timestamp = time();
    
    if ($this->validate_add($d)) {
      $user_id=md5(uniqid($hash_secret));
      
      $q = "INSERT INTO shopper_group (shopper_group_name, shopper_group_desc, vendor_id) ";
      $q .= "VALUES ('";
      $q .= $d["shopper_group_name"] . "','";
      $q .= $d["shopper_group_desc"] . "','";
      $q .= $ps_vendor_id . "')";
      $db->query($q);
      $db->next_record();
      
      $q = "SELECT * from shopper_group where";
      $q .= " shopper_group_name='";
      $q .= $d["shopper_group_name"] . "' ";
      $q .= "AND shopper_group_desc='" . $d["shopper_group_desc"] ."'";
      $q .= "AND vendor_id='" . $ps_vendor_id ."'";
      $db->query($q);
      $db->next_record();
      return $db->f("shopper_group_id");
    }
      else {
	$d["error"]=$this->error;
	return False;
      }
  }

  /**************************************************************************
   * name: update()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function update($d) {
    global $ps_vendor_id;
    $db = new ps_DB;
    $timestamp = time();

    if ($this->validate_update($d)) {
      
      $q = "UPDATE shopper_group set shopper_group_name='" . $d["shopper_group_name"] . "', ";
      $q .= "shopper_group_desc='" . $d["shopper_group_desc"] . "', ";
      $q .= "vendor_id='" . $ps_vendor_id . "' ";
      $q .= "WHERE shopper_group_id='" . $d["shopper_group_id"] . "'";
      $db->query($q);
      $db->next_record();
      return True;
    }
    else {
      $d["error"] = $this->error;
      return False;
    }
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
    
    if ($this->validate_delete($d)) {
      $q = "DELETE FROM shopper_group WHERE shopper_group_id='" . $d["shopper_group_id"] . "'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE FROM shopper_vendor_xref WHERE shopper_group_id='" . $d["shopper_group_id"] . "'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE FROM product_price WHERE shopper_group_id='" . $d["shopper_group_id"] . "'";
      $db->query($q);
      $db->next_record();
      return True;
    }
    else {
      return False;
    }
  }
  
  /**************************************************************************
  ** name: list_shopper_groups
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function list_shopper_groups($name,$shopper_group_id=0,$product_id=0) {
    global $ps_vendor_id;
    $db = new ps_DB;
    
    echo "<select name=\"$name\">\n";

    $q  = "SELECT shopper_group_id,shopper_group_name from shopper_group ";
    $q .= "WHERE vendor_id = '$ps_vendor_id' ";
    $q .= "ORDER BY shopper_group_name";
    $db->query($q);
    while ($db->next_record()) {
      if ($db->f("shopper_group_id") == $shopper_group_id) {
        echo "<option value=\"" . $db->f("shopper_group_id")  . "\" selected=\"selected\">";
        echo $db->f("shopper_group_name") . "</option>\n";
      } elseif (!$product_id) {
        echo "<option value=\"" . $db->f("shopper_group_id")  . "\">";
        echo $db->f("shopper_group_name") . "</option>\n";
      } else {
        $db2 = new ps_DB;
        $q2  = "SELECT shopper_group_id FROM product_price ";
        $q2 .= "WHERE shopper_group_id = '" . $db->f("shopper_group_id") . "' ";
        $q2 .= "AND product_id = '$product_id' ";
        $db2->query($q2);
        if (!$db2->next_record()) {
          echo "<option value=\"" . $db->f("shopper_group_id")  . "\">";
          echo $db->f("shopper_group_name") . "</option>\n";
        }
      } 
    }
    echo "</select>\n";
  }        
  
  /**************************************************************************
  ** name: get_field
  ** created by: pablo
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function get_field($shopper_group_id, $field_name) {
    $db = new ps_DB;

    $q =  "SELECT $field_name FROM shopper_group ";
    $q .= "WHERE shopper_group_id='$shopper_group_id'";
    $db->query($q);
    if ($db->next_record()) {
       return $db->f($field_name);
    }
    else {
       return False;
    }
  }

  function get_id() {
    global $auth;
    $db = new ps_DB;

    $q =  "SELECT shopper_group.shopper_group_id FROM shopper_group,shopper_vendor_xref ";
    $q .= "WHERE shopper_vendor_xref.user_id='" . $auth["user_id"] . "' ";
    $q .= "AND shopper_group.shopper_group_id=shopper_vendor_xref.shopper_group_id";
    $db->query($q);
    $db->next_record();

    return $db->f("shopper_group_id");


  }

}
$ps_shopper_group = new ps_shopper_group;

?>
