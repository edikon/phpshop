<?php
/*
 * The ps_user_address class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_user_address.inc,v 1.1.1.1 2004/07/27 14:58:38 pablo Exp $
 *
 */


class ps_user_address {
  var $classname = "ps_user_address";

  /**************************************************************************
  ** name: validate_add()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function validate_add(&$d) {
    $valid = true;

    if (!$d["address_type_name"]) {
      $d["error"] .= "'Address Label' is a required field.<br />";
      $valid = false;
    }
    if (!$d["last_name"]) {
      $d["error"] .= "'Last Name' is a required field.<br />";
      $valid = false;
    }
    if (!$d["first_name"]) {
      $d["error"] .= "'First Name' is a required field.<br />";
      $valid = false;
    }
    if (!$d["address_1"]) {
      $d["error"] .= "'Address 1' is a required field.<br />";
      $valid = false;
    }
    if (!$d["city"]) {
      $d["error"] .= "'City' is a required field.<br />";
      $valid = false;
    }
    if (!$d["state"]) {
      $d["error"] .= "'State/Region' is a required field.<br />";
      $valid = false;
    }
    if (!$d["zip"]) {
      $d["error"] .= "'Zip' is a required field.<br />";
      $valid = false;
    }
    if (!$d["phone_1"]) {
      $d["error"] .= "'Phone Number' is a required field.<br />";
      $valid = false;
    }
    $db = new ps_DB;
    $q  = "SELECT * from user_info ";
    $q .= "WHERE address_type_name='" . $d["address_type_name"] . "' ";
    $q .= "AND address_type='" . $d["address_type"] . "' ";
    $q .= "AND user_id='" . $d["user_id"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] .= "The given address label already exists.<br />";
      $valid = false;
    }
    return $valid;    
  }
  
  /**************************************************************************
  ** name: validate_delete()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function validate_delete(&$d) {

    if (!$d["user_info_id"]) {
      $d["error"] .= "Please select a user address to delete.<br />";
      return false;
    }
    else {
      return true;
    }
  }

  /**************************************************************************
  ** name: validate_update()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function validate_update(&$d) {
    $valid = true;

    if (!$d["address_type_name"]) {
      $d["error"] .= "'Address Label' is a required field.<br />";
      $valid = false;
    }
    if (!$d["last_name"]) {
      $d["error"] .= "'Last Name' is a required field.<br />";
      $valid = false;
    }
    if (!$d["first_name"]) {
      $d["error"] .= "'First Name' is a required field.<br />";
      $valid = false;
    }
    return $valid;
  }
  
  /**************************************************************************
  ** name: add()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function add(&$d) {
    $hash_secret = "PHPShopIsCool";
    $db = new ps_DB;
    $timestamp = time();
    
    if (!$this->validate_add($d)) {
      return false;
    }
 
    $q = "INSERT INTO user_info (user_id,address_type,address_type_name,";
    $q .= "company,title,last_name,first_name,middle_name,";
    $q .= "phone_1,phone_2,fax,address_1,";
    $q .= "address_2,city,state,country,zip,";
    $q .= "cdate,mdate) VALUES ('";
    $q .= $d["user_id"] . "','";
    $q .= $d["address_type"] . "','";
    $q .= $d["address_type_name"] . "','";
    $q .= $d["company"] . "','";
    $q .= $d["title"] . "','";
    $q .= $d["last_name"] . "','";
    $q .= $d["first_name"] . "','";
    $q .= $d["middle_name"] . "','";
    $q .= $d["phone_1"] . "','";
    $q .= $d["phone_2"] . "','";
    $q .= $d["fax"] . "','";
    $q .= $d["address_1"] . "','";
    $q .= $d["address_2"] . "','";
    $q .= $d["city"] . "','";
    $q .= $d["state"] . "','";
    $q .= $d["country"] . "','";
    $q .= $d["zip"] . "','";
    $q .= $timestamp . "','";
    $q .= $timestamp . "') ";
    $db->query($q);

    return true;
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
      return false;
    }

    $q  = "UPDATE user_info set company='" . $d["company"] . "', ";
    $q .= "address_type='" . $d["address_type"] . "', ";
    $q .= "address_type_name='" . $d["address_type_name"] . "', ";
    $q .= "title='" . $d["title"] . "', ";
    $q .= "last_name='" . $d["last_name"] . "', ";
    $q .= "first_name='" . $d["first_name"] . "', ";
    $q .= "middle_name='" . $d["middle_name"] . "', ";
    $q .= "phone_1='" . $d["phone_1"] . "', ";
    $q .= "phone_2='" . $d["phone_2"] . "', ";
    $q .= "fax='" . $d["fax"] . "', ";
    $q .= "address_1='" . $d["address_1"] . "', ";
    $q .= "address_2='" . $d["address_2"] . "', ";
    $q .= "city='" . $d["city"] . "', ";
    $q .= "state='" . $d["state"] . "', ";
    $q .= "country='" . $d["country"] . "', ";
    $q .= "zip='" . $d["zip"] . "', ";
    $q .= "mdate='" . $timestamp . "' ";
    $q .= "WHERE user_info_id='" . $d["user_info_id"] . "'";
    $db->query($q);

    return true;
  }
  
  /**************************************************************************
  ** name: delete()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function delete(&$d) {
    $db = new ps_DB;
    
    if (!$this->validate_delete($d)) {
      return false;
    }

    $q  = "DELETE from user_info ";
    $q .= "WHERE user_info_id='" . $d["user_info_id"] . "'";
    $db->query($q);

    return true;
  }

}
?>
