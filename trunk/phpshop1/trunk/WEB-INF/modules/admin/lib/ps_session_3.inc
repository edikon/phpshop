<?php
/*
 * The ps_session class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_session_3.inc,v 1.1.1.1 2004/07/27 14:58:36 pablo Exp $
 *
 */
 

class ps_session {
  var $classname = "ps_session";
  var $table_name = "sessions";
  var $serial_spacer = "|";
  var $firstcall;
  var $session_hash = "phpShopIsCool";
  
  
  // Private
  function sendCookie ($value="@#&") {
    if ($value == "@#&")
      $value = $this->cookie;
    if ($this->mode != "get")
      setcookie($this->name, $value, 0, $this->cookiepath,$this->cookie_name); 
  }
  
  // Public
  function ps_session($newname = "ps_session", $forcenew=0) {
    
    $this->sessid = "";
    $this->sdata  = array();
    $this->sfile = "";
    $this->cookie = "";
    $this->cookiepath = "/";
    $this->firstcall = 0;
    $this->forcenew = $forcenew;
    $this->client = $GLOBALS["REMOTE_ADDR"];
    $this->name = $newname;
    $this->sessid = md5(uniqid("test"));
    $this->cookie = $this->sessid;
    $this->cookiepath="/";
    $this->cookie_name = SESSION_DOMAIN ? SESSION_DOMAIN : getenv("SERVER_NAME");
    $this->timeout=SESSION_EXPIRE;
    $this->cleanup_rate = "5";          # percentage of visit that trigger cleanup
    $this->history = SESSION_HISTORY;
    $this->mode = SESSION_MODE;
    $this->start();
    $this->cleanup();
  }
  
  
  // Public
  function start () {
    global $HTTP_COOKIE_VARS, $HTTP_POST_VARS, $HTTP_GET_VARS;
    $db = new ps_DB;
    
    $php_sessid = $HTTP_COOKIE_VARS[$this->name];
    
    if (empty($php_sessid))
       $php_sessid = $HTTP_GET_VARS[$this->name];

    if (empty($php_sessid))
       $php_sessid = $HTTP_POST_VARS[$this->name];

    if ($php_sessid == "") {
      $this->sendCookie(); 
      $this->firstcall = true;
      return;
    }
    else {
      $q = "SELECT * from sessions WHERE sess_id='$php_sessid'";
      $db->query($q);
      if ($db->next_record()) {
	$mdate = $db->f("mdate");
	$delay = time() - $mdate;
	if (($delay > $this->timeout) && ($this->timeout != 0)) {
	  $q = "DELETE from $this->table_name where sess_id='$php_sessid'";
	  $db->query($q);
	  $this->firstcall = true;
          $this->sendCookie(); 
	  return;
	}
      }

      if ($this->forcenew) {
	$q = "DELETE from $this->table_name where sess_id='$php_sessid'";
	$db->query($q);
	$this->sendCookie(); 
	$this->firstcall = true;
	return;
      }
      else {
	$this->firstcall = false;
	$this->cookie = $php_sessid;
	$this->sessid = $php_sessid;
      }
    }

    $q = "SELECT * from $this->table_name WHERE sess_id='$php_sessid'";
    $db->query($q);
    if (!$db->next_record()) {
      $this->firstcall = true;
      $this->sendCookie(); 
      return;
    }

    $session_data = $db->f("session_data");
    $line_tok = strtok($session_data, $this->serial_spacer);

    if ($line_tok != $php_sessid) {
      $this->sendCookie($php_sessid); 
      return;
    }
    else
      {
	$this->cookie = $php_sessid;
      }

    while ($line_tok = strtok($this->serial_spacer))  
    {
      list($name, $svar) = explode("=", $line_tok);
      $GLOBALS[$name] = unserialize($svar);
      $this->sdata[$name] = $name;
    }
  }


  // Public
  // Reference a global variable into the session
  function register($var) {
    if (!isset($this->sdata[$var]))
      $this->sdata[$var] = $var;
  }

  // Public
  // unreference a global variable from the session
  function unregister($var) {
    unset ($this->sdata[$var]);
  }

  // Public
  // clear the session
  function destroy() {
    $db = new ps_DB;

    $q = "DELETE from $this->table_name where sess_id='$this->sessid'";
    $db->query($q);
    unset($this->sdata);
  }
  
  // Public
  // save all registered variables.  Should be called at end of page
  function save() {
    $db = new ps_DB;

    if (!is_array($this->sdata))
      return;

    $session_data = trim($this->cookie) . "|";

    $i = 0;
    while ($i++ < count($this->sdata)) {
      $var = key($this->sdata);   
      $data = $GLOBALS[$var];
      $svar = serialize($data);
      $session_data .= $var . "=" . $svar . $this->serial_spacer;
      next($this->sdata);
    }

    // Get rid of single quotes in data by escaping them with a slash    
    $session_data = ereg_replace("'","\'",$session_data); 

    if ($this->firstcall) {
      $q = "INSERT INTO $this->table_name ";
      $q .= "(sess_id, mdate, session_data) ";
      $q .= "VALUES ('$this->sessid', '" . time() . "', '$session_data')";
      $db->query($q);
    }
    else {
      $q = "UPDATE $this->table_name SET ";
      $q .= "mdate='" . time() . "',";
      $q .= "session_data='$session_data' ";
      $q .= "WHERE sess_id='$this->sessid'";
      $db->query($q);
    }
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
      return $text . $delim . $this->name . "=" . $this->sessid;
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
    	echo $text . $delim . $this->name . "=" . $this->sessid;
    	return 1;
     }
     else {
    	echo $text;
    	return 1;
     }

  }
  
  function hidden_session() {
    echo "<input type=\"hidden\" name=\"" . $this->name . "\" value=\"" . $this->sessid . "\" />";
  }

  function cleanup() {
    $db = new ps_DB;

    srand(time());
    if ((rand()%100) < $this->cleanup_rate) {
      $timeout = time() -($this->history*60);
      $q  = "DELETE FROM $this->table_name WHERE ";
      $q .= "mdate < '$timeout' AND sess_id <> '$this->sessid'";
      $db->query($q);
    }    
  }
  
} // end of class session

?>
