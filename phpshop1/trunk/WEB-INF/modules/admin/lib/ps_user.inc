<?php
/*
 * The ps_user class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_user.inc,v 1.1.1.1 2004/07/27 14:58:38 pablo Exp $
 *
 */


class ps_user {
  var $classname = "ps_user";
  
  /**************************************************************************
  ** name: validate_add()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function validate_add(&$d) {
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
  
    if (!$d["password_1"]) {
      $d["error"] .= "'Password' is a required field.<br />";
      $valid = false;
    }
    if ($d["password_1"] != $d["password_2"]) {
      $d["error"] .= "The passwords entered do not match.<br />";
      $valid = false;
    }
//    if (!$d["perms"]) {
//      $d["error"] .= "You must assign the user to a group.<br />";
//      $valid = false;
//    }
    if (!$d["user_email"]) {
      $d["error"] .= "'Email' is a required field.<br />";
      $valid = false;
    } 
    elseif (!validate_email($d["user_email"])) {
      $d["error"] .= "Please provide a valid email address.<br />";
      $valid = false;
    }
    $db = new ps_DB;
    $q = "SELECT * from auth_user_md5 where username='" .  $d["username"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] .= "The given username already exists.  ";
      $d["error"] .= "Please try another username.<br />";
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
      $d["error"] .= "Please select a user to delete.";
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
   if ($d["password_1"] != $d["password_2"]) {
      $d["error"] .= "The passwords entered do not match.<br />";
      $valid = false;
    }
    if (!$d["user_email"]) {
      $d["error"] .= "'Email' is a required field.<br />";
      $valid = false;
    }
    if (!validate_email($d["user_email"])) {
      $d["error"] .= "Please provide a valid email address.<br />";
      $valid = false;
    }
    return $valid;
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
    
    if (!$this->validate_add($d)) {
      return False;
    }
    
    $user_id=md5(uniqid($hash_secret));
    
    $q = "INSERT INTO auth_user_md5 (user_id,username,password, perms) ";
    $q .= "VALUES ('";
    $q .= $user_id . "','";
    $q .= $d["username"] . "','";
    $q .= md5($d["password_1"]) . "','";
    $q .= $d["perms"] . "')";
    $db->query($q);
 
    if (USER_INFO_XF_4 and $d["extra_field_4"] == "") {
      $d["extra_field_4"] = "N";
    }
    if (USER_INFO_XF_5 and $d["extra_field_5"] == "") {
      $d["extra_field_5"] = "N";
    } 
    
    // Insert billto
    $q = "INSERT INTO user_info (user_id,address_type,address_type_name,";
    $q .= "company,title,last_name,first_name,middle_name,";
    $q .= "phone_1,phone_2,fax,address_1,";
    $q .= "address_2,city,state,country, zip,";
    $q .= "user_email,extra_field_1,extra_field_2,extra_field_3,";
    $q .= "extra_field_4,extra_field_5,cdate,mdate) VALUES ";
    $q .= "('$user_id','";
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
    $q .= $d["user_email"] . "','";
    $q .= $d["extra_field_1"] . "','";
    $q .= $d["extra_field_2"] . "','";
    $q .= $d["extra_field_3"] . "','";
    $q .= $d["extra_field_4"] . "','";
    $q .= $d["extra_field_5"] . "','";
    $q .= $timestamp . "','";
    $q .= $timestamp . "') ";
    $db->query($q);
    
    // Insert vendor relationship
    $q = "INSERT INTO auth_user_vendor (user_id,vendor_id)";
    $q .= " VALUES ";
    $q .= "('" . $user_id . "','";
    $q .= $ps_vendor_id . "') ";
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
    global $ps_vendor_id;
    $db = new ps_DB;
    $timestamp = time();
    
    if (!$this->validate_update($d)) {
      return False;
    }
    
    if ($d["password_1"]) {
      $d["password_1"] = md5($d["password_1"]);
      $q  = "UPDATE auth_user_md5 SET ";
      $q .= " password='" . $d["password_1"];
      $q .= "', perms='" . $d["perms"] . "', ";
      $q .= "username='" . $d["username"] . "' ";
      $q .= "WHERE user_id='" . $d["user_id"] . "'";      
      $db->query($q);
    }
    else {
      $q  = "UPDATE auth_user_md5 SET ";
      $q .= "perms='" . $d["perms"] . "', ";
      $q .= "username='" . $d["username"] . "' ";
      $q .= "WHERE user_id='" . $d["user_id"] . "'";      
      $db->query($q);
    }

    if (USER_INFO_XF_4 and $d["extra_field_4"] == "") {
      $d["extra_field_4"] = "N";
    }
    if (USER_INFO_XF_5 and $d["extra_field_5"] == "") {
      $d["extra_field_5"] = "N";
    }
    
    /* Update Bill To */
    $q  = "UPDATE user_info SET ";
    $q .= "company='" . $d["company"] . "', ";
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
    $q .= "user_email='" . $d["user_email"] . "', ";
    $q .= "extra_field_1='" . $d["extra_field_1"] . "', ";
    $q .= "extra_field_2='" . $d["extra_field_2"] . "', ";
    $q .= "extra_field_3='" . $d["extra_field_3"] . "', ";
    $q .= "extra_field_4='" . $d["extra_field_4"] . "', ";
    $q .= "extra_field_5='" . $d["extra_field_5"] . "', ";
    $q .= "mdate='" . $timestamp . "' "; 
    $q .= "WHERE user_id='" . $d["user_id"] . "' AND ";
    $q .= "address_type='BT'";
    $q .= $q_end;
    $db->query($q);

    $q = "UPDATE auth_user_vendor set ";
    $q .= "vendor_id='$ps_vendor_id' ";
    $q .= "WHERE user_id='" . $d["user_id"] . "'";
    $db->query($q);

    return True;
  }
  
  /**************************************************************************
   * name: update_admin_passwd()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function update_admin_passwd(&$d) {
    global $auth;
    $db = new ps_DB;

    $q  = "SELECT password from auth_user_md5 ";
    $q .= "WHERE user_id='" . $auth["user_id"] . "'";      
    $db->query($q);
    $db->next_record();
    if (md5($d["password_curr"]) != $db->f("password")) { 
      $d["error"] = "The current password entered does not match.";
      return false;
    }
    if ($d["password_1"] != $d["password_2"]) {
      $d["error"] = "The new passwords entered do not match.";
      return false;		
    }
    
    if ($d["password_1"] == $d["password_2"]) {
      $d["password_1"] = md5($d["password_1"]);
      $q  = "UPDATE auth_user_md5 ";
      $q .= "SET password='" . $d["password_1"] . "' ";
      $q .= "WHERE user_id='" . $auth["user_id"] . "'";      
      $db->query($q);
    }
    
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
    
    $q = "DELETE from auth_user_md5 where user_id='" . $d["user_id"] . "'";
    $db->query($q);
    $db->next_record();
    
    $q = "DELETE from user_info where user_id='" . $d["user_id"] . "'";
    $db->query($q);
    $db->next_record();

    // Delete auth_user_vendor entries
    $q = "DELETE from auth_user_vendor where user_id='" . $d["user_id"] . "'";
    $db->query($q);
    $db->next_record();

    return True;
  }
  
  
  /**************************************************************************
   * name: list_perms()
   * created by: pablo
   * description: lists the permission in a select box
   * parameters:
   * returns:
   **************************************************************************/
  function list_perms($name,$group_name) {
    global $perm;
    global $auth;
    $db = new ps_DB;
  
    // Get users current permission value 
    $dvalue = $perm->permissions[$auth["perms"]];
    echo "<select name=\"$name\">\n";
    echo "<option value=\"0\">Please Select</option>\n";
    while (list($key,$value) = each($perm->permissions)) {
      // Display only those permission that this user can set
      if ($value <= $dvalue)
      if ($key == $group_name) {
	echo "<option value=\"$key\" selected=\"selected\">$key</option>\n";
      }
      else {
	echo "<option value=\"$key\">$key</option>\n";
      }
    }
    echo "</select>\n";
  }        

  /**************************************************************************
   * name: logout()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function logout(&$d) {
    global $auth, $sess;
    
    $auth["uid"]="";
    $auth["user_id"]="";
    $auth["uname"]="";
    $auth["username"]="";
    $auth["perm"]="";
    $auth["perms"]="";
    $sess->destroy();
    return True;   
  }

  /**************************************************************************
   * name: logout()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function logged_in() {
    global $auth;
    
    if ($auth["perms"]) {
      return True;   
    }
    else return False;
  }

  /**************************************************************************
   * name: login()
   * created by:
   * description:
   * parameters:
   * returns:
   **************************************************************************/
  function login(&$d) {
    global $auth, $sess, $ps_vendor_id;
    $db = new ps_DB;

    $q = "SELECT * from auth_user_md5,user_info ";
    $q .= "WHERE auth_user_md5.username ='" . $d["username"] . "' ";
    $q .= "AND auth_user_md5.password ='" . md5($d["password"]) . "'";
    $q .= "AND auth_user_md5.password ='" . md5($d["password"]) . "'";
    $q .= "AND auth_user_md5.user_id = user_info.user_id ";
    $q .= "AND user_info.address_type = 'BT'";

    $db->query($q);

    if ($db->next_record()) {
      $auth["user_id"]   = $db->f("user_id");
      $auth["username"] = $d["username"];
      $auth["perms"]  = $db->f("perms");
      $auth["first_name"] = $db->f("first_name");
      $auth["last_name"] = $db->f("last_name");
    }
    else {
      $d["error"] = "The username and password you entered were not found.<br />";
      $d["error"] .= "Please try again.";
      $d["login"]="1";
      return False;
    }

    $q = "SELECT * from vendor";
    $db->query($q);
    if ($db->next_record()) {
       $ps_vendor_id=$db->f("vendor_id");
       $sess->register("ps_vendor_id");
    }
    $d["login"] = "0";
    return $auth["user_id"];

  }

/**************************************************************************
  ** name: send_lost_password()
  ** created by: pablo <pablo@phpshop.org>
  ** converted to phpshop 0.6 by: Mr PHP www.mrphp.com.au
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function send_lost_password(&$d) {
    global $ps_vendor_id, $sess;

    $db = new ps_DB;

    if($d["username"]){
      $q  = "SELECT * FROM auth_user_md5, user_info ";
      $q .= "WHERE auth_user_md5.username='".$d["username"]."' ";
      $q .= "AND auth_user_md5.user_id=user_info.user_id ";
      $q .= "AND user_info.address_type='BT' ";
      $db->query($q);
      if(!$db->next_record()){
        $d["error"] .= "The username you entered was not found in our database.";
        return False;
      }
    }
    elseif($d["user_email"]){
      $q  = "SELECT * FROM auth_user_md5, user_info ";
      $q .= "WHERE user_info.user_email='".$d["user_email"]."' ";
      $q .= "AND auth_user_md5.user_id=user_info.user_id ";
      $q .= "AND user_info.address_type='BT' ";
      $db->query($q);
      if(!$db->next_record()){
        $d["error"] .= "The email address you entered was not found in our database.";
        return False;
      }
    }
    else{
      $d["error"] .= "Please enter a username or email address.";
      return False;
    }

    $user_id = $db->f("user_id");
    $user_email=$db->f("user_email");
    $password = $this->make_password();
    $reset_password = md5($password);
    $key = md5(md5(md5($password)));

    //get vendor info
    $dbv = new ps_DB;
    $qt = "SELECT * from vendor WHERE vendor_id = $ps_vendor_id";
    $dbv->query($qt);
    $dbv->next_record();
    $vendor_email = $dbv->f("contact_email");
    $vendor_name = $dbv->f("vendor_name");

    // Save the key and password in the db for later
    $q = "UPDATE auth_user_md5 SET reset_key='$key', reset_password='$reset_password' WHERE user_id='$user_id'";
    $db->query($q);

    $mail_text = "You are receiving this email because you (or someone pretending to be you) has requested a password change on the $vendor_name site. If you believe you have received this message in error simply delete it and your password will remain the same.\n\n";
    $mail_text .= "--> Your new password as generated is: $password\n\n";
    $mail_text .= "In order for this change to take effect you must visit this page:\n\n";
    $mail_text .= "   ".$sess->url(URL."?page=shop/lost_password_reset&func=resetLostPassword&key=$key")."\n\n";
    $mail_text .= "Once you have visited the page your password will be changed in our database, and you may login to the profile section and change it as desired.\n\n";
    $mail_text .= "Thank you for using our site.\n\n";
    $mail_text .= "Yours Truely,\n\n";
    $mail_text .= "The Site Admin\n\n";

	require_once('admin/lib/ps_mail.inc');
	$ps_mail = new ps_mail;
    $ps_mail->send($user_email,"Password Change Request",$mail_text,$vendor_email);
    $d["error"] .= "An email has been sent to you to you with the new password.";
    return True;
  }

  /**************************************************************************
  ** name: reset_lost_password()
  ** created by: pablo <pablo@phpshop.org>
  ** converted to phpshop 0.6 by: Mr PHP www.mrphp.com.au
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function reset_lost_password(&$d) {
    $db = new ps_DB;

    $q = "SELECT user_id FROM auth_user_md5 WHERE reset_key='".$d["key"]."'";
    $db->query($q);
    if (!$db->next_record()) {
      $d["error"] .= "The password reset key you are using is invalid.";
      return False;
    }
    // Key found so reset password
    $q = "UPDATE auth_user_md5 SET password=reset_password, reset_password='', reset_key='' WHERE reset_key='".$d["key"]."'";
    $db->query($q);
    $d["error"] .= "Password change successfull.";
    return True;
  }


  /**************************************************************************
  ** name: make_password()
  ** created by: pablo <pablo@phpshop.org>
  ** description: Creates an 8 letter random password.
  ***************************************************************************/
  function make_password() {
    $makepass="";
    $chars = array(
                   "a","A","b","B","c","C","d","D","e","E",
                   "f","F","g","G","h","H","i","I","j","J",
                   "k","K","l","L","m","M","n","N","o","O",
                   "p","P","q","Q","r","R","s","S","t","T",
                   "u","U","v","V","w","W","x","X","y","Y",
                   "z","Z","1","2","3","4","5","6","7","8",
                   "9","0"
                   );
    $max_elements = count($chars) - 1;
    srand((double)microtime()*1000000);
    $newpw = $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $newpw .= $chars[rand(0,$max_elements)];
    $makepass = $newpw;
    return($makepass);
  }
}

?>
