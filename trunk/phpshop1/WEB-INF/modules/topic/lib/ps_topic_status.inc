<?php
/*
 * The ps_topic_status class
 *
 * Copyright (c) uli (ulisoft@gmail.com).  All rights reserved.
 *
 */

class ps_topic_status {
  var $classname = "ps_topic_status";
  
  /*
  ** VALIDATION FUNCTIONS
  **
  */


  /**************************************************************************
   * name: topic_status_val_add()
   * created by: uli
   * description: creates a new topic record
   * parameters:
   * returns:
   **************************************************************************/

  function topic_status_val_add(&$d) {
    global $lang,$ps_vendor_id;

    include(PS_BASE . "languages/lang_$lang.inc");   

    $db = new ps_DB;
   
    if (!$d["topic_status_name"]) {
      $d["error"] = $error_str_28;
      return False;
    } 

    $topic_status_name=$d["topic_status_name"];
    $q="SELECT * FROM topic_status WHERE topic_status_name='$topic_status_name' AND vendor_id='$ps_vendor_id' AND language='$lang'";
    $db->query($q);

    if ($db->next_record()){
      $d["error"] = $error_str_26;
      return False;
    } 
    return True;    
  }


  /**************************************************************************
   * name: topic_status_val_delete()
   * created by: uli
   * description: validate
   * parameters:
   * returns:
   **************************************************************************/
  
  function topic_status_val_delete(&$d) {
    global $lang;
  
    if (!$d["topic_status_id"]) {
      include(PS_BASE . "languages/lang_$lang.inc");
      $d["error"] = $error_str_27;
      return False;
    }

    if ($d["topic_status_id"]==1 || $d["topic_status_id"]==2) {
      $d["error"] = $error_str_236;
      return False;
    }

    return True;
  }
  
  /**************************************************************************
   * name: topic_status_val_update()
   * created by: uli
   * description: validate
   * parameters:
   * returns:
   **************************************************************************/

  function topic_status_val_update(&$d) {
    global $lang,$ps_vendor_id;

    $db = new ps_DB;

    include(PS_BASE . "languages/lang_$lang.inc");

    if (!$d["topic_status_id"]) {
      $d["error"] = $error_str_27;
      return False;
    }

    if (!$d["topic_status_name"]) {
      $d["error"] = $error_str_28;
      return False;
    }

    $topic_status_name=$d["topic_status_name"];
    $topic_status_id=$d["topic_status_id"];
    $q="SELECT * FROM topic_status WHERE topic_status_name='$topic_status_name' ";
    $q .="AND vendor_id='$ps_vendor_id' AND language='$lang' AND topic_status_id <> '$topic_status_id'";
    $db->query($q);

    if ($db->next_record()){
      $d["error"] = $error_str_26;
      return False;
    } 

    return True;
  }
  
  
  /**************************************************************************
   * name: topic_status_add()
   * created by: uli
   * description: creates a new topic-status
   * parameters:
   * returns:
   **************************************************************************/
  function topic_status_add(&$d) {
    global $ps_vendor_id, $lang;

    $db = new ps_DB; 
    $timestamp = time();
    
    if (!$this->topic_status_val_add($d)) {
      return False;
    }

    $topic_status_id=md5(uniqid(HASH_SECRET));

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
          $q = "INSERT INTO topic_status (topic_status_id,vendor_id,";
          $q .= "topic_status_name,language) ";
          $q .= "VALUES (";
          $q .= "'$topic_status_id',";
          $q .= "'$ps_vendor_id','";
          $q .= $d["topic_status_name"] . "','";
          $q .= $fl . "')";

          $db->query($q);
          $db->next_record();
        }
      }
    }

    else {
      $q = "INSERT INTO topic_status (topic_status_id,vendor_id,";
      $q .= "topic_status_name,language) ";
      $q .= "VALUES (";
      $q .= "'$topic_status_id',";
      $q .= "'$ps_vendor_id','";
      $q .= $d["topic_status_name"] . "','";
      $q .= $lang . "')";

      $db->query($q);
      $db->next_record();

    }

    return True;

  }
  
  /**************************************************************************
   * name: topic_status_update()
   * created by: uli
   * description: updates topic-function information
   * parameters:
   * returns:
   **************************************************************************/
  function topic_status_update(&$d) {
    global $ps_vendor_id,$lang;

    $db = new ps_DB; 
    $timestamp = time();

    if (!$this->topic_status_val_update($d)) {
      return False;	
    }

    $q = "UPDATE topic_status SET ";
    $q .= "',topic_status_name='" . $d["topic_status_name"];
    $q .= "' WHERE topic_status_id='" . $d["topic_status_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id' ";

    if ($d["all_lang"] !== "on") {
      $q .= " AND language='$lang'";
    }

    $db->query($q);
    $db->next_record();

    return True;
  }

  /**************************************************************************
   * name: topic_status_delete()
   * created by: uli
   * description: deletes a topic
   * parameters: 
   * returns:
   **************************************************************************/
  function topic_status_delete(&$d) {
    $db = new ps_DB;
    global $ps_vendor_id,$lang;

    if (!$this->topic_status_val_delete($d)) {
      return False;
    }

    $q = "DELETE from topic_status where topic_status_id='" . $d["topic_status_id"] . "'";
    $q .= " AND vendor_id='$ps_vendor_id'";

    if ($d["all_lang"] !== "on") {
      $q .= " AND language='$lang'";
    }

    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE topic_status";
    $db->query($q);
    $db->next_record();

    return True;
  }


  /**************************************************************************
   * name: topic_status_list()
   * created by: uli
   * description: topic-statuses
   * parameters: 
   * returns:
   **************************************************************************/

  function topic_status_list($topic_status_id) {
    global $lang;

    $db=new ps_DB;

    $q = "SELECT * from topic_status WHERE language='$lang' ORDER BY topic_status_name";
    $db->query($q);
    echo "<SELECT NAME=\"topic_status\">\n";

    while ($db->next_record()) {
      echo "<OPTION VALUE=" . $db->f("topic_status_id");

      if ($topic_status_id == $db->f("topic_status_id")) 
         echo " SELECTED>";
      else
         echo ">";
      echo $db->f("topic_status_name") . "</OPTION>\n";
    }
    echo "</SELECT>\n";
    return True;
  }

}
?>
