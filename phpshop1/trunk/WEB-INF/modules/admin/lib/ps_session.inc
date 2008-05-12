<?php 
/*
 * The ps_session class for PHP4
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_session.inc,v 1.1.1.1 2004/07/27 14:58:34 pablo Exp $
 *
 */



class ps_session {
  var $classname = "ps_session";
  var $table_name = "sessions";
  var $serial_spacer = "|";
  var $firstcall;
  
  // Public
  function ps_session($newname = "ps_session", $forcenew=0) {
    if (defined("SESSION_PATH") && SESSION_PATH!="") {
	    session_save_path(SESSION_PATH);
    }
    if (defined("SESSION_EXPIRE") && !SESSION_EXPIRE!="") {
		  session_set_cookie_params(SESSION_EXPIRE * 60);
    }
    session_start();
    foreach($_SESSION as $key=>$val) {
		  global $$key;
			$$key = $val;
		}
  }
  
  
  // Public
  // Reference a global variable into the session
  function register($var_name) {
	  global $$var_name;
	  $_SESSION[$var_name] = $$var_name;
  }

  // Public
  // unreference a global variable from the session
  function unregister($var_name) {
    unset($_SESSION[$var_name]);
  }

  // Public
  // clear the session
  function destroy() {
    session_destroy();
  }
  
  // Public
  // save all registered variables.  Should be called at end of page
  function save() {
    foreach($_SESSION as $key=>$val) {
		  $this->register($key);
		}
    return True;
  }
  
  
  // Need these for backwards phplib compatibility
  function url($text) {
    global $QUERY_STRING;
    global $HTTP_COOKIE_VARS;
    global $HTTP_GET_VARS;
    global $HTTP_POST_VARS;

    if (empty($HTTP_COOKIE_VARS[$this->name])) {
      // Check for argument delimiter
      if (strpos($text, "?")) {
         $delim = "&amp;";
      } 
      else {
         $delim = "?";
      }
      return $text . $delim;
    }
    else 
      return $text;
  }

  function purl($text) {
    global $QUERY_STRING;   
    global $HTTP_GET_VARS;
    global $HTTP_POST_VARS;

    global $HTTP_COOKIE_VARS;

    if (empty($HTTP_COOKIE_VARS[$this->name])) {

    	// Check for argument delimiter
      if (strpos($text, "?")) {
       		$delim = "&amp;";
    	} 
    	else {
       		$delim = "?";
    	}
    	echo $text . $delim . SID;
    	return 1;
     }
     else {
    	echo $text;
    	return 1;
     }

  }
  
  function hidden_session() {
    echo "<input type=\"hidden\" name=\"" . session_name() . "\" value=\"" . session_id() . "\" />";
  }

  function cleanup() {
    return True;
  }
  
} // end of class session
?>
