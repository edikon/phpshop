<?php
/*
 * The ps_ticket_status class
 *
 * Copyright (c) uli (ulisoft@gmail.com).  All rights reserved.
 *
 */

class ps_ticket_status {
  var $classname = "ps_ticket_status";
  
  /**************************************************************************
  * name: ticket_status_val_add()
  * created by: uli
  * description: creates a new ticket record
  * parameters:
  * returns:
  **************************************************************************/

  function ticket_status_val_add(&$d) {
    global $lang,$ps_vendor_id;

    include(PS_BASE . "languages/lang_$lang.inc");   

    $db = new ps_DB;
   
    if (!$d["ticket_status_name"]) {
      $d["error"] = $error_str_28;
      return False;
    } 

    $ticket_status_name=$d["ticket_status_name"];
    $q="SELECT * FROM ticket_status WHERE ticket_status_name='$ticket_status_name' AND vendor_id='$ps_vendor_id' AND language='$lang'";
    $db->query($q);

    if ($db->next_record()){
      $d["error"] = $error_str_26;
      return False;
    } 

    return True;    
  }

  /**************************************************************************
  * name: ticket_val_delete()
  * created by: uli
  * description: validate
  * parameters:
  * returns:
  **************************************************************************/
  function ticket_status_val_delete(&$d) {
    global $lang;

    include(PS_BASE . "languages/lang_$lang.inc");    

    if (!$d["ticket_status_id"]) {
      $d["error"] = $error_str_27;
      return False;
    }

    if ($d["ticket_status_id"]==1 || $d["ticket_status_id"]==2) {
      $d["error"] = $error_str_236;
      return False;
    }

    return True;
  }
  
  /**************************************************************************
  * name: ticket_status_val_update()
  * created by: uli
  * description: validate
  * parameters:
  * returns:
  **************************************************************************/
  function ticket_status_val_update(&$d) {
    global $lang,$ps_vendor_id;

    include(PS_BASE . "languages/lang_$lang.inc");

    $db = new ps_DB;

    if (!$d["ticket_status_id"]) {
      $d["error"] = $error_str_27;
      return False;
    }

    if (!$d["ticket_status_name"]) {
      $d["error"] = $error_str_28;
      return False;
    }

    $ticket_status_name=$d["ticket_status_name"];
    $ticket_status_id=$d["ticket_status_id"];
    $q="SELECT * FROM ticket_status WHERE ticket_status_name='$ticket_status_name' ";
    $q .="AND vendor_id='$ps_vendor_id' AND language='$lang' AND ticket_status_id <> '$ticket_status_id'";
    $db->query($q);

    if ($db->next_record()){
      $d["error"] = $error_str_26;
      return False;
    } 

    return True;
  }
  
  
  /**************************************************************************
   * name: ticket_status_add()
   * created by: uli
   * description: creates a new ticket-status
   * parameters:
   * returns:
   **************************************************************************/
  function ticket_status_add(&$d) {
    global $ps_vendor_id,$lang;

    $db = new ps_DB; 
    $timestamp = time();
    
    if (!$this->ticket_status_val_add($d)) {
      return False;
    }

    $ticket_status_id=md5(uniqid(HASH_SECRET));

    if ($d["all_lang"]=="on") {
      $ldir=PS_BASE;
      $ldir .="languages/lang_*.inc";

      foreach (glob($ldir) as $filename) {
        list ($fn,$fl,$en) = split('[._]', basename($filename));

        $lfile=PS_BASE;
        $lfile .="languages/lang_";
        $lfile .=$fl;
        $lfile .=".inc";

        if (file_exists($lfile)) {
          $q = "INSERT INTO ticket_status (ticket_status_id,vendor_id,";
          $q .= "ticket_status_name,language) ";
          $q .= "VALUES (";
          $q .= "'$ticket_status_id',";
          $q .= "'$ps_vendor_id','";
          $q .= $d["ticket_status_name"] . "','";
          $q .= $fl . "')";
          $db->query($q);
          $db->next_record();
        }
      }
    }

    else {
      $q = "INSERT INTO ticket_status (ticket_status_id,vendor_id,";
      $q .= "ticket_status_name,language) ";
      $q .= "VALUES (";
      $q .= "'$ticket_status_id',";
      $q .= "'$ps_vendor_id','";
      $q .= $d["ticket_status_name"] . "','";
      $q .= $lang . "')";

      $db->query($q);
      $db->next_record();
    }

    return True;

  }
  
  /**************************************************************************
   * name: ticket_status_update()
   * created by: uli
   * description: updates ticket-function information
   * parameters:
   * returns:
   **************************************************************************/
  function ticket_status_update(&$d) {
    global $lang,$ps_vendor_id;

    $db = new ps_DB; 
    $timestamp = time();

    if (!$this->ticket_status_val_update($d)) {
      return False;	
    }

    $q = "UPDATE ticket_status SET ";
    $q .= "ticket_status_name='" . $d["ticket_status_name"];
    $q .= "' WHERE ticket_status_id='" . $d["ticket_status_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id'";

    if ($d["all_lang"] !== "on") {
      $q .= " AND language='$lang'";
    }

    $db->query($q);
    $db->next_record();

    return True;
  }

  /**************************************************************************
   * name: ticket_status_delete()
   * created by: uli
   * description: deletes a ticket
   * parameters: 
   * returns:
   **************************************************************************/
  function ticket_status_delete(&$d) {
    global $ps_vendor_id,$lang;

    $db = new ps_DB;
   
    if (!$this->ticket_status_val_delete($d)) {
      return False;
    }

    $q = "DELETE from ticket_status where ticket_status_id='" . $d["ticket_status_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id'";

    if ($d["all_lang"] !== "on") {
      $q .= " AND language='$lang'";
    }

    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE ticket_status";
    $db->query($q);
    $db->next_record();

    return True;
  }


  /**************************************************************************
   * name: ticket_status_list()
   * created by: uli
   * description: ticket-statuses
   * parameters: 
   * returns:
   **************************************************************************/

  function ticket_status_list($ticket_status_id) {
    global $lang;
    
    $db=new ps_DB;

    $q = "SELECT * from ticket_status WHERE language='$lang' ORDER BY ticket_status_name";
    $db->query($q);
    echo "<SELECT NAME=\"ticket_status\">\n";

    while ($db->next_record()) {
      echo "<OPTION VALUE=" . $db->f("ticket_status_id");

      if ($ticket_status_id == $db->f("ticket_status_id")) 
         echo " SELECTED>";
      else
         echo ">";
      echo $db->f("ticket_status_name") . "</OPTION>\n";
    }
    echo "</SELECT>\n";
  }

}
?>
