<?php
// Copyright (C) 1996-2004 Copyright. All rights reserved.
//
// This source file is part of phpShop.
//
// This file may be distributed and/or modified under the terms of the
// "GNU General Public License" version 2 as published by the Free
// Software Foundation and appearing in the file LICENSE.GPL included in
// the packaging of this file.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING
// THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE.
//
// The "GNU General Public License" (GPL) is available at
// http://www.gnu.org/copyleft/gpl.html.
//
// Contact license@edikon.com if any conditions of this licencing isn't clear to
// you.

// $Id: db_mysql.inc,v 1.1.1.1 2004/07/27 14:57:41 pablo Exp $ 

/***********************************************************************

mySQL Database Access Class

Heavily based on the PHPLIB database access class available at 
http://phplib.netuse.de.

We use only a subset of the functions available in PHPLIB and their syntax is 
exactly the same.  This makes working with previous version of phpShop seamless
and keeps a consistent API for database access.  

Methods in the class are:

query($q) - Established connection to database and runs the query returning 
            a query ID if successfull.

next_record() - Returns the next row in the RecordSet for the last query run.  
                Returns False if RecordSet is empty or at the end.

num_rows()  -Returns the number of rows in the RecordSet from a query.

f($field_name) - Returns the value of the given field name for the current
                 record in the RecordSet.  

sf($field_name) - Returns the value of the field name from the $vars variable
                  if it is set, otherwise returns the value of the current
		  record in the RecordSet.  Useful for handling forms that have
		  been submitted with errors.  This way, fields retain the values 
		  sent in the $vars variable (user input) instead of the database
		  values.

p($field_name) - Prints the value of the given field name for the current
                 record in the RecordSet.

sp($field_name) - Prints the value of the field name from the $vars variable
                  if it is set, otherwise prints the value of the current
		  record in the RecordSet.  Useful for handling forms that have
		  been submitted with errors.  This way, fields retain the values 
		  sent in the $vars variable (user input) instead of the database
		  values.


************************************************************************/


class ps_DB {
  
  var $lid = 0;             	// Link ID for database connection
  var $qid = 0;			// Query ID for current query
  var $row;			// Current row in query result set
  var $record = array();	// Current row record data
  var $error = "";		// Error Message
  var $errno = "";		// Error Number



  // Connects to DB and returns DB lid 
  // PRIVATE
  function connect() { 

    if ($this->lid == 0) {
      $this->lid = mysql_pconnect(DB_HOST,DB_USER,DB_PWD); 
      if (!$this->lid) {
	$this->halt("connect(" . DB_HOST . "," . DB_USER . ",PASSWORD)  failed.");
      } 
      
      if (!@mysql_select_db(DB_NAME,$this->lid)) {
	$this->halt("Cannot connect to database ".DB_NAME);
	return 0;
      }
    }
    return $this->lid;
  }


  // Runs query and sets up the query id for the class.
  // PUBLIC
  function query($q) {
    
    if (empty($q))
      return 0;
    
    if (!$this->connect()) {
      return 0; 
    }
    
    if ($this->qid) {
      @mysql_free_result($this->qid);
      $this->qid = 0;
    }
    
    $this->qid = @mysql_query($q, $this->lid);
    $this->row   = 0;
    $this->errno = mysql_errno();
    $this->error = mysql_error();
    if (!$this->qid) {
      $this->halt("Invalid SQL: ".$q);
    }

    return $this->qid;
  }
  

  // Return next record in result set
  // PUBLIC
  function next_record() {

    if (!$this->qid) {
      $this->halt("next_record called with no query pending.");
      return 0;
    }
    
    $this->record = @mysql_fetch_array($this->qid);
    $this->row   += 1;
    $this->errno  = mysql_errno();
    $this->error  = mysql_error();
    
    $stat = is_array($this->record);
    return $stat;
  }
  

  // Field Value
  // PUBLIC
  function f($field_name) {
    return stripslashes($this->record[$field_name]);
  }

  // Selective field value
  // PUBLIC
  function sf($field_name) {
    global $vars, $default;

    if ($vars["error"] and $vars["$field_name"]) {
      return stripslashes($vars["$field_name"]);
    } elseif ($default["$field_name"]) {
      return stripslashes($default["$field_name"]);
    } else {
      return stripslashes($this->record[$field_name]);
    }
  }                             

  // Print field
  // PUBLIC
  function p($field_name) {
      print stripslashes($this->record[$field_name]);
  }                             

  // Selective print field
  // PUBLIC
  function sp($field_name) {
    global $vars, $default;

    if ($vars["error"] and $vars["$field_name"]) {
      print stripslashes($vars["$field_name"]);
    } elseif ($default["$field_name"]) {
      print stripslashes($default["$field_name"]);
    } else {
      print stripslashes($this->record[$field_name]);
    }
  }                          

  // Returns the number of rows in query
  function num_rows() { 
    
    if ($this->lid) { 
      return @mysql_numrows($this->qid); 
    } 
    else { 
      return 0; 
    } 
  }



  

  // Halt and display error message
  // PRIVATE
  function halt($msg) {
    $this->error = @mysql_error($this->lid);
    $this->errno = @mysql_errno($this->lid);

    printf("</td></tr></table><b>Database error:</b> %s<br />\n", $msg);
    printf("<b>MySQL Error</b>: %s (%s)<br />\n",
	   $this->errno,
	   $this->error);
    
    exit;

  }

}
?>
