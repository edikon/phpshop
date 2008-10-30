<?php
/*
 * The ps_shopper class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_shopper.inc,v 1.1.1.1 2004/07/27 14:59:41 pablo Exp $
 *
****************************************************************************
*
* CLASS DESCRIPTION
*                   
* ps_class
*
* The class is
* 
* propeties:  
* 	
* methods:
*       validate_add()
*	validate_delete()
*	validate_update()
*       add()
*       update()
*       delete()
*	
*
*************************************************************************/
class ps_shopper {
  var $classname = "ps_shopper";
  
  /**************************************************************************
  ** name: validate_add()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function validate_add(&$d) {
    global $lang;

    include(PS_BASE . "languages/lang_$lang.inc");
    
    $valid = true;
    
    if (!$d["last_name"]) {
      $d["error"] .= "'Last Name' is a required field.<br />";
      $valid = false;
    }
    if (!$d["first_name"]) {
      $d["error"] .= "'First Name' is a required field.<br />";
      $valid = false;
    }
    if (!$d["username"]) {
      $d["error"] .= "'Username' is a required field.<br />";
      $valid = false;
    }
    if (!eregi("^[_a-z0-9-]+(\.[_a-z0-9-]+)*$", $d["username"])) {
      $d["error"] .= "'Username' cannot contain spaces.<br />";
      $valid = false;
    }

    if (!$d["forum_name"]) {
      $d["error"] .= $shopper_err_17;
      $valid = false;
    }

    if (!$d["password_1"]) {
      $d["error"] .= "'Password' is a required field.<br />";
      $valid = false;
    }
    if ($d["password_1"] != $d["password_2"]) {
      $d["error"] .= "The passwords entered do not match.<br />";
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
    if (!$d["user_email"]) {
      $d["error"] .= "'Email' is a required field.<br />";
      $valid = false;
    }
    elseif (!validate_email($d["user_email"])) {
      $d["error"] .= "Please provide a valid email address.<br />";
      $valid = false;
    }

    $db = new ps_DB;
    $q  = "SELECT * from auth_user_md5 ";
    $q .= "WHERE username='" .  $d["username"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] .= "The given username already exists. ";
      $d["error"] .= "Please try another username.<br />";
      $valid = false;
    }

    $q = "SELECT * from auth_user_md5 where forum_name='" .  $d["forum_name"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] .= $shopper_err_18;
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

    if (!$d["user_id"]) {
      $d["error"] .= "ERROR:  Please select a user to delete.";
      return False;
    }
    else {
      return True;
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
    global $perm,$auth,$lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $valid = true;

   
    if (!eregi("^[_a-z0-9-]+(\.[_a-z0-9-]+)*$", $d["username"])) {
      $d["error"] .= "'Username' cannot contain spaces.<br />";
      $valid = false;
    }

    if (!$d["forum_name"]) {
      $d["error"] .= $shopper_err_17;
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

    if ($d["password_1"] != $d["password_2"]) {
      $d["error"] .= "The passwords entered do not match.<br />";
      $valid = false;
    }
    if (!$d["user_email"]) {
      $d["error"] .= "'Email' is a required field.<br />";
      $valid = false;
    }
    elseif (!validate_email($d["user_email"])) {
      $d["error"] .= "Please provide a valid email address.<br />";
      $valid = false;
    }

    $db=new ps_DB;

    if ($d["username"] != $d["old_username"]) {
      $q = "SELECT * from auth_user_md5 WHERE username='" .  $d["username"] . "' ";
      $db->query($q);

      if ($db->next_record()) {
        $d["error"] .= "The given username already exists.  ";
        $d["error"] .= "Please try another username.<br />";
        $valid = false;
      }
    }

    if ($d["forum_name"] != $d["old_forum_name"]) {
      $q = "SELECT * from auth_user_md5 where forum_name='" .  $d["forum_name"] . "' ";
      $db->query($q);

      if ($db->next_record()) {
        $d["error"] .= $shopper_err_18;
        $valid = false;
      }
    }

    return $valid;
  }
  
  /**************************************************************************
   * name: add()
   * created by: pablo
   * description: adds a shopper to a vendor
   * parameters:
   * returns:
   **************************************************************************/
  function add(&$d) {
    global $ps_vendor_id, $ps_user;

    $hash_secret = "PHPShopIsCool";

    $db = new ps_DB;
    $timestamp = time();
    
    if (!$this->validate_add($d)) {
      return False;
    }

    $user_id=md5(uniqid($hash_secret));
    
    $q = "INSERT INTO auth_user_md5 (user_id,username,password,forum_name,topic_group_id,perms) ";
    $q .= "VALUES ('";
    $q .= $user_id . "','";
    $q .= $d["username"] . "','";
    $q .= md5($d["password_1"]) . "','";
    $q .= $d["forum_name"] . "','";
    $q .= $d["topic_group_id"] . "','";
    $q .= "shopper')";
    $db->query($q);
    $db->next_record();

    if (USER_INFO_XF_4 and $d["extra_field_4"] == "") {
      $d["extra_field_4"] = "N";
    }
    if (USER_INFO_XF_5 and $d["extra_field_5"] == "") {
      $d["extra_field_5"] = "N";
    }
    
    // Insert billto
    $q = "INSERT INTO user_info (user_id,address_type, address_type_name,";
    $q .= "company, title, last_name, first_name,middle_name,";
    $q .= "phone_1, phone_2, fax, address_1,";
    $q .= "address_2, city, state, country, zip,";
    $q .= "user_email,extra_field_1,extra_field_2,extra_field_3,";
    $q .= "extra_field_4,extra_field_5,cdate, mdate) VALUES ";
    $q .= "('" . $user_id . "',";
    $q .= "'BT',";
    $q .= "'-default-','";
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
    $q .= $d["user_email"] . "','";
    $q .= $d["extra_field_1"] . "','";
    $q .= $d["extra_field_2"] . "','";
    $q .= $d["extra_field_3"] . "','";
    $q .= $d["extra_field_4"] . "','";
    $q .= $d["extra_field_5"] . "','";
    $q .= $timestamp . "','";
    $q .= $timestamp . "') ";
    $db->query($q);
   
    if (!$d["shopper_group_id"]) {
       $q =  "SELECT * from shopper_group WHERE ";
       $q .= "shopper_group_name='-default-'";
       $q .= "AND vendor_id='$ps_vendor_id'";
       $db->query($q);
       $db->next_record();
       $d["shopper_group_id"] = $db->f("shopper_group_id");
    }
 
    $q  = "INSERT INTO shopper_vendor_xref ";
    $q .= "(user_id,vendor_id,shopper_group_id,customer_number) ";
    $q .= "VALUES ('";
    $q .= $user_id . "','";
    $q .= $ps_vendor_id . "','";
    $q .= $d["shopper_group_id"] . "','";
    $q .= $d["customer_number"] . "')";
    $db->query($q);

    $d["password"] = $d["password_1"];
    if (!$d["nologin"]) {
      $ps_user->login($d);
    }
    return True;
    
  }
  
  /**************************************************************************
  ** name: update()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function update(&$d) {
    global $auth,
           $perm;

    $db = new ps_DB;
    $timestamp = time();
 
    if (!$this->validate_update($d)) {
      return False;
    }

    if ($d["user_id"] != $auth["user_id"] && $auth["perms"] != "admin") {
      $d["error"] = "Tricky tricky, but we know about this one.";
      return False;
    }
    if ($d["password_1"]) {
      $d["password_1"] = md5($d["password_1"]);
      $q  = "UPDATE auth_user_md5 SET ";
      $q .= "password='" . $d["password_1"] . "', ";

      if($d["username"]) {
        $q .= ",username='" . $d["username"] . "', ";
      }

      $q .= "forum_name='" . $d["forum_name"] . "', ";
      $q .= "topic_group_id='" . $d["topic_group_id"] . "' ";

      $q .= "WHERE user_id='" . $d["user_id"] . "'";      
      $db->query($q); 
    }
    elseif($d["username"]) {
      $q  = "UPDATE auth_user_md5 SET ";
      $q .= "username='" . $d["username"] . "', ";
      $q .= "forum_name='" . $d["forum_name"] . "', ";
      $q .= "topic_group_id='" . $d["topic_group_id"] . "' ";

      $q .= "WHERE user_id='" . $d["user_id"] . "'";      
      $db->query($q);
    }

    if (USER_INFO_XF_4 and $d["extra_field_4"] == "") {
      $d["extra_field_4"] = "N";
    }
    if (USER_INFO_XF_5 and $d["extra_field_5"] == "") {
      $d["extra_field_5"] = "N";
    }
    
    if ($perm->check("storeadmin,admin") && $d["user_id"])
       $user_id = $d["user_id"];
    else
       $user_id = $auth["user_id"];

    /* Update Bill To */
    $q  = "UPDATE user_info SET ";
    $q .= "company='" . $d["company"] . "', ";
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
    $q .= "user_email='" . $d["user_email"] . "', ";
    $q .= "extra_field_1='" . $d["extra_field_1"] . "', ";
    $q .= "extra_field_2='" . $d["extra_field_2"] . "', ";
    $q .= "extra_field_3='" . $d["extra_field_3"] . "', ";
    $q .= "extra_field_4='" . $d["extra_field_4"] . "', ";
    $q .= "extra_field_5='" . $d["extra_field_5"] . "', ";
    $q .= "mdate='" . $timestamp . "' ";
    $q .= "WHERE user_id='" . $user_id . "' ";
    $q .= "AND address_type='BT'";

    $db->query($q);

    // Update shopper group relationship

    $q = "UPDATE shopper_vendor_xref SET ";
    $q .= "shopper_group_id='" . $d["shopper_group_id"] . "', ";
    $q .= "customer_number='" . $d["customer_number"] . "' ";
    $q .= "WHERE user_id='" . $user_id . "'";
    $db->query($q);

    return True;
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
      return False;
    }

    // Delete auth_user_md5 entries    
    $q = "DELETE from auth_user_md5 where user_id='" . $d["user_id"] . "'";
    $db->query($q);

    // Delete user_info entries
    $q = "DELETE from user_info where user_id='" . $d["user_id"] . "'";
    $db->query($q);

    // Delete shopper_vendor_xref entries
    $q = "DELETE from shopper_vendor_xref where user_id='" . $d["user_id"] . "'"; 
    $db->query($q);
    
    return True;
  }
}
$ps_shopper = new ps_shopper;
?>
