<?php
/*
 * The ps_topic_group class
 *
 * Copyright (c) uli (ulisoft@gmail.com).  All rights reserved.
 *

****************************************************************************
*
* CLASS DESCRIPTION
*        
* ps_topic_group_class
*
* The class handles topic_groups from an adminstrative perspective.  topic
* processing is handled in the ps_process_topic.
* 
* properties:  
* 	
*       error - the error message returned by validation if any
* methods:
*	topic_group_val_delete()
*	topic_group_val_update()
*       topic_group_add()
*       topic_group_update()
*       topic_group_delete()
*	
*
*************************************************************************/
class ps_topic_group {
  var $classname = "ps_topic_group";
  var $error;
  


  /**************************************************************************
   * name: validate_add
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
  function validate_add(&$d) {
    global $lang,$ps_vendor_id;

    include(PS_BASE . "languages/lang_$lang.inc");

    $topic_group_id=$d["topic_group_id"];
    $topic_group_name=$d["topic_group_name"];

    if (!is_numeric($topic_group_id)) {
      $d["error"] = $error_str_135;
      return False;
    }

    $db = new ps_DB;
    $q = "SELECT * from topic_groups WHERE ";
    $q .= "topic_group_id = '$topic_group_id' ";

    if ($d["all_lang"]!="on") {
      $q .= "AND language='$lang' "; 
    }

    $q .= "AND vendor_id='$ps_vendor_id' "; 

    $db->query($q);

    if ($db->next_record()) {
      $d["error"] = $error_str_134;
      return False;
    }

    $q = "SELECT * from topic_groups WHERE ";
    $q .= "topic_group_name = '$topic_group_name' ";

    if ($d["all_lang"]!="on") {
      $q .= "AND language='$lang' "; 
    }

    $q .= "AND vendor_id='$ps_vendor_id' "; 

    $db->query($q);

    if ($db->next_record()) {
      $d["error"] = $error_str_136;
      return False;
    }


  }

  /**************************************************************************
   * name: validate_update
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
  function validate_update(&$d) {
    global $lang,$ps_vendor_id;

    include(PS_BASE . "languages/lang_$lang.inc");

    if (!is_numeric($d["topic_group_id"])) {
      $d["error"] = $error_str_135;
      return False;
    }

    $topic_group_id=$d["topic_group_id"];
    $topic_group_name=$d["topic_group_name"];
    $tgi=$d["tgi"];

    $db = new ps_DB;
    $q = "SELECT * from topic_groups WHERE ";
    $q .= "topic_group_id = '$topic_group_id' AND topic_group_id <> '$tgi'";

    if ($d["all_lang"]!="on") {
      $q .= "AND language='$lang' "; 
    }

    $q .= "AND vendor_id='$ps_vendor_id' "; 

    $db->query($q);

    if ($db->next_record()) {
      $d["error"] = $error_str_134;
      return False;
    }

    $q = "SELECT * from topic_groups WHERE ";
    $q .= "topic_group_name = '$topic_group_name' AND topic_group_id <> '$tgi'";

    if ($d["all_lang"]!="on") {
      $q .= "AND language='$lang' "; 
    }

    $q .= "AND vendor_id='$ps_vendor_id' "; 
    $db->query($q);

    if ($db->next_record()) {
      $d["error"] = $error_str_136;
      return False;
    }
  }

  /**************************************************************************
   * name: topic_group_delete
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
  function topic_group_delete(&$d) {
    global $lang,$ps_vendor_id;

    $db = new ps_DB;

    $topic_group_id=$d["topic_group_id"];

    if ($d["all_lang"]=="on") {
      $q = "DELETE from topic_groups WHERE ";
      $q .= "topic_group_id = '$topic_group_id'";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topics WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topic_reply WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from latest_topic WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();
    }

    else {
      $q = "DELETE from topic_groups WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $q .= "AND language='$lang' ";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topics WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $q .= "AND language='$lang' ";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topic_reply WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $q .= "AND language='$lang' ";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from latest_topic WHERE ";
      $q .= "topic_group_id = '$topic_group_id' ";
      $q .= "AND vendor_id='$ps_vendor_id' ";
      $q .= "AND language='$lang' ";
      $db->query($q);
      $db->next_record();
    }

    return True;
  }

  /**************************************************************************
   * name: topic_group_add
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
  function topic_group_add(&$d) {
    global $lang,$ps_vendor_id;

    if (!$this->validate_add($d)) {
      $d["topic_group_id"]="";
      $d["topic_group_name"]="";
      return False;
    }

    $db = new ps_DB;
    
    $topic_group_id= $d["topic_group_id"];
    $topic_group_name = $d["topic_group_name"];

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
          $q = "INSERT INTO topic_groups SET";
          $q .=" topic_group_id = '$topic_group_id', "; 
          $q .=" topic_group_name='$topic_group_name', ";
          $q .=" vendor_id='$ps_vendor_id', ";
          $q .=" language='$fl'";
          $db->query($q);
          $db->next_record();
        }
      }
    }

    else {
      $q = "INSERT INTO topic_groups SET";
      $q .=" topic_group_id = '$topic_group_id', "; 
      $q .=" topic_group_name='$topic_group_name', ";
      $q .=" vendor_id='$ps_vendor_id', ";
      $q .=" language='$lang'";
      $db->query($q);
      $db->next_record();
    }

    return True;
  }

  /**************************************************************************
   * name: topic_group_update
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
  function topic_group_update(&$d) {
    global $lang,$ps_vendor_id;

    if (!$this->validate_update($d)) {
      return False;
    }

    $db = new ps_DB;
    $tgi = $d["tgi"];

    $topic_group_id= $d["topic_group_id"];

    if ($d["all_lang"]=="on") {
      $q = "UPDATE topic_groups SET ";
      $q .="topic_group_id = '$topic_group_id', "; 
      $q .="topic_group_name='$topic_group_name' ";
      $q .="WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();

      $q = "UPDATE topics SET";
      $q .=" topic_group_id = '$topic_group_id' "; 
      $q .=" WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();

      $q = "UPDATE topic_reply SET";
      $q .=" topic_group_id = '$topic_group_id' "; 
      $q .=" WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();

      $q = "UPDATE latest_topic SET";
      $q .=" topic_group_id = '$topic_group_id' "; 
      $q .=" WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();
    }

    else {
      $q = "UPDATE topic_groups SET ";
      $q .="topic_group_id = '$topic_group_id', "; 
      $q .="topic_group_name='$topic_group_name' ";
      $q .="WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $q .="AND language='$lang' ";
      $db->query($q);
      $db->next_record();

      $q = "UPDATE topics SET";
      $q .=" topic_group_id = '$topic_group_id' "; 
      $q .=" WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $db->query($q);
      $db->next_record();
      $q .="AND language='$lang' ";

      $q = "UPDATE topic_reply SET";
      $q .=" topic_group_id = '$topic_group_id' "; 
      $q .=" WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $q .="AND language='$lang' ";
      $db->query($q);
      $db->next_record();

      $q = "UPDATE latest_topic SET";
      $q .=" topic_group_id = '$topic_group_id' "; 
      $q .=" WHERE topic_group_id='$tgi' ";
      $q .="AND vendor_id='$ps_vendor_id' ";
      $q .="AND language='$lang' ";
      $db->query($q);
      $db->next_record();
    }

    return True;
  }

  /**************************************************************************
   * name: list_topic_groups
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
  function list_topic_groups($topic_group_id) {
    global $lang,$ps_vendor_id;

    $db = new ps_DB;

    $q = "SELECT * from topic_groups WHERE language='$lang' AND vendor_id='$ps_vendor_id' ORDER BY topic_group_name ";
    $db->query($q);

    echo "<select name=topic_group_id>";
    while ($db->next_record()) {

      if ($db->f("topic_group_id") == $topic_group_id) {
        echo "<OPTION SELECTED VALUE=";
        echo $db->f("topic_group_id") . ">";
      }

      else {
        echo "<OPTION VALUE=";
        echo $db->f("topic_group_id");
        echo ">";
      }

      echo $db->f("topic_group_name") . "</OPTION>\n";
    }


    echo "</SELECT>";
    return True;
  }
}

?>

