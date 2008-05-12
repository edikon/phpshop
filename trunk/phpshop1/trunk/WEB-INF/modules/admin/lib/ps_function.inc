<?php
/*
 * ps_function Class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_function.inc,v 1.1.1.1 2004/07/27 14:58:32 pablo Exp $
 *
 */

/****************************************************************************
*
* CLASS DESCRIPTION
*                   
* ps_function_reg
*
* The class is is used to manage the function register.
* 
* propeties:  
* 	
*       error - the error message returned by validation if any
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
 class ps_function {
   var $classname = "ps_function";
   var $error;
   
   ////
   // !Validates adding a function to a module.
   // Validate routine for module-function add.  
   // A longer, more complete description would go here
   // We might include details of what the function parameters do and what the
   // result should be, etc
   function validate_add($d) {
     
     $db = new ps_DB;
     
     if (!$d["function_name"]) {
       $this->error = "ERROR:  You must enter a name for the function.";
       return False;	
     }
     if (!$d["module_id"]) {
       $this->error = "ERROR:  ERROR:  A module id must be specified.";
       return False;
     }
     if (!$d["function_class"]) {
       $this->error = "ERROR:  You must enter a name for the class.";
       return False;	
     }
     if (!$d["function_method"]) {
       $this->error = "ERROR:  You must enter a name for the method.";
       return False;	
     }
     if (!$d["function_perms"]) {
       $this->error = "ERROR:  You must enter a permissions for the method.";
       return False;	
     }
     if ($d["function_name"]) {
       $q = "SELECT count(*) as rowcnt from function where";
       $q .= " function_name='" .  $d["function_name"] . "'";
       $db->query($q);
       $db->next_record();
       if ($db->f("rowcnt") > 0) {
	 $this->error = "The given function name already exists.";
	 return False;
       }      
     }
     return True;    
   }
  
  /**************************************************************************
  ** name: validate_delete()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/   
  function validate_delete($d) {
    
    if (!$d["function_id"]) {
      $this->error = "ERROR:  Please select a function to delete.";
      return False;
    }
    else {
      return True;
    }
  }
  
  /**************************************************************************
  ** name: validate_update
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/   
  function validate_update($d) {
    
    if (!$d["function_name"]) {
      $this->error = "ERROR:  You must enter a name for the function.";
      return False;	
    }
    if (!$d["function_class"]) {
      $this->error = "ERROR:  You must enter a name for the class.";
      return False;	
    }
    if (!$d["function_method"]) {
      $this->error = "ERROR:  You must enter a name for the method.";
      return False;	
    }
    if (!$d["function_perms"]) {
      $this->error = "ERROR:  You must enter a permissions for the method.";
      return False;	
    }
    else {
      return True;
    }
  }
  
  
  /**************************************************************************
   * name: add()
   * created by: pablo
   * description: creates a new function record
   * parameters:
   * returns:
   **************************************************************************/
  function add(&$d) {
    $hash_secret="PHPShopIsCool";
    $db = new ps_DB;
    $timestamp = time();
    
    if (!$this->validate_add($d)) {
      $d["error"] = $this->error;
      return False;
    }
    $q = "INSERT INTO function (module_id, function_name, function_class, ";
    $q .= "function_method, function_perms, function_description)";
    $q .= " VALUES ('";
    $q .= $d["module_id"] . "','";
    $q .= $d["function_name"] . "','";
    $q .= $d["function_class"] . "','";
    $q .= $d["function_method"] . "','";
    $q .= $d["function_perms"] . "','";
    $q .= $d["function_description"] . "')";
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
    $timestamp = time();

    if (!$this->validate_update($d)) {
      $d["error"] = $this->error;
      return False;	
    }
    $q = "UPDATE function set ";
    $q .= "function_name='" . $d["function_name"];
    $q .= "',function_class='" . $d["function_class"];
    $q .= "',function_method='" . $d["function_method"];
    $q .= "',function_perms='" . $d["function_perms"];
    $q .= "', function_description='" . $d["function_description"];
    $q .= "' WHERE function_id='" . $d["function_id"] . "'";
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
    
    if (!$this->validate_delete($d)) {
      $d["error"]=$this->error;
      return False;
    }
    $q = "DELETE from function where function_id='" . $d["function_id"] . "'";
    $db->query($q);
    $db->next_record();
    return True;
  }

  function get_function($func) {
    $db = new ps_DB;
    $result = array(); 

    $q = "SELECT * from function where function_name='$func'";
    $db->query($q);
    if ($db->next_record()) {
      $result["perms"] = $db->f("function_perms");
      $result["class"] = $db->f("function_class");
      $result["method"] = $db->f("function_method");      
      return $result;
    }
    else {
      return False;
    }
  }
}

?>
