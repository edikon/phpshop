<?php
/*
 * ps_module Class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_module.inc,v 1.1.1.1 2004/07/27 14:58:34 pablo Exp $
 *
 */




class ps_module {
  var $classname = "ps_module";
  var $error;
  
  /*
  ** VALIDATION FUNCTIONS
  **
  */

  function validate_add(&$d) {
    
    $db = new ps_DB;
    
    if (!$d["module_name"]) {
      $this->error = "ERROR:  You must enter a name for the module.";
      return False;	
    }
    if ($d["module_name"]) {
      $q = "SELECT count(*) as rowcnt from module where module_name='" .  $d["module_name"] . "'";
      $db->query($q);
      $db->next_record();
      if ($db->f("rowcnt") > 0) {
	$this->error = "The given module name already exists.";
	return False;
      }      
    }
    $filepath = PS_BASE . "modules/". $d["module_name"]."/lib/ps_include.inc";
    if (!is_readable($filepath)) {
      $this->error = "ERROR:  The module you specified is not installed.";
      return False;
    }
    if (!$d["module_perms"]) {
      $this->error = "ERROR:  You must enter permissions for the module.";
      return False;	
    }
    if (!$d["list_order"]) {
      $d["list_order"] = "99";
    }
    return True;    
  }
  
  function validate_delete($d) {
    
    if (!$d["module_id"]) {
      $this->error = "ERROR:  Please select a module to delete.";
      return False;
    }
    else {
      return True;
    }
  }
  
  function validate_update(&$d) {
    
    if (!$d["module_name"]) {
      $this->error = "ERROR:  You must enter a name for the module.";
      return False;	
    }
    if (!$d["module_perms"]) {
      $this->error = "ERROR:  You must enter permissions for the module.";
      return False;	
    }
    if (!$d["list_order"]) {
      $d["list_order"] = "99";
    }
    return True;
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
    $q = "INSERT INTO module (module_name, module_description, ";
    $q .= "module_perms, module_header, ";
    $q .= "module_publish, list_order, module_footer, ";
    $q .= "language_code_1, ";
    $q .= "language_code_2, ";
    $q .= "language_code_3, ";
    $q .= "language_code_4, ";
    $q .= "language_code_5, ";
    $q .= "module_label_1, ";
    $q .= "module_label_2, ";
    $q .= "module_label_3, ";
    $q .= "module_label_4, ";
    $q .= "module_label_5, ";
    $q .= "language_file_1, ";
    $q .= "language_file_2, ";
    $q .= "language_file_3, ";
    $q .= "language_file_4, ";
    $q .= "language_file_5) ";
    $q .= " VALUES ('";
    $q .= $d["module_name"] . "','";
    $q .= $d["module_description"] . "','";
    $q .= $d["module_perms"] . "','";
    $q .= $d["module_header"] . "','";
    $q .= $d["module_publish"] . "','";
    $q .= $d["list_order"] . "','";
    $q .= $d["module_footer"] . "','";
    $q .= $d["language_code_1"] . "','";
    $q .= $d["language_code_2"] . "','";
    $q .= $d["language_code_3"] . "','";
    $q .= $d["language_code_4"] . "','";
    $q .= $d["language_code_5"] . "','";
    $q .= $d["module_label_1"] . "','";
    $q .= $d["module_label_2"] . "','";
    $q .= $d["module_label_3"] . "','";
    $q .= $d["module_label_4"] . "','";
    $q .= $d["module_label_5"] . "','";
    $q .= $d["language_file_1"] . "','";
    $q .= $d["language_file_2"] . "','";
    $q .= $d["language_file_3"] . "','";
    $q .= $d["language_file_4"] . "','";
    $q .= $d["language_file_5"] . "')";
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
    $q = "UPDATE module SET ";
    $q .= "module_name='" . $d["module_name"];
    $q .= "',module_perms='" . $d["module_perms"];
    $q .= "',module_description='" . $d["module_description"];
    $q .= "',module_header='" . $d["module_header"];
    $q .= "',module_footer='" . $d["module_footer"];
    $q .= "',module_publish='" . $d["module_publish"];
    $q .= "',list_order='" . $d["list_order"];
    $q .= "',language_code_1='" . $d["language_code_1"];
    $q .= "',language_code_2='" . $d["language_code_2"];
    $q .= "',language_code_3='" . $d["language_code_3"];
    $q .= "',language_code_4='" . $d["language_code_4"];
    $q .= "',language_code_5='" . $d["language_code_5"];
    $q .= "',module_label_1='" . $d["module_label_1"];
    $q .= "',module_label_2='" . $d["module_label_2"];
    $q .= "',module_label_3='" . $d["module_label_3"];
    $q .= "',module_label_4='" . $d["module_label_4"];
    $q .= "',module_label_5='" . $d["module_label_5"];
    $q .= "',language_file_1='" . $d["language_file_1"];
    $q .= "',language_file_2='" . $d["language_file_2"];
    $q .= "',language_file_3='" . $d["language_file_3"];
    $q .= "',language_file_4='" . $d["language_file_4"];
    $q .= "',language_file_5='" . $d["language_file_5"];
    $q .= "' WHERE module_id='" . $d["module_id"] . "'";
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
    $q = "DELETE from function WHERE module_id='" . $d["module_id"] . "'";
    $db->query($q);
    $db->next_record();

    $q = "DELETE from module where module_id='" . $d["module_id"] . "'";
    $db->query($q);
    $db->next_record();
    return True;
  }


  function get_dir($basename) {
    $db = new ps_DB;
    $results = array();
    
    $q = "SELECT * from module where module_name='$basename'";
    $db->query($q);
    if ($db->next_record()) {
      $results["perms"] = $db->f("module_perms");
      return $results;
    }
    else {
      return False;
    }
  }

  function set_language(&$d) {
    global $lang;
 
    if (!$d["lang"]) {
       $d["error"] = "ERROR:  You must specify a valid language code.";
       return False;
    }
    $lang = $d["lang"];
    return TRUE;
  }
}

?>
