<?php
/*
 * The ps_topic class
 *
 * Copyright (c) uli (ulisoft@gmail.com).  All rights reserved.
 *

****************************************************************************
*
* CLASS DESCRIPTION
*                   
* ps_topic
*
* The class handles topics from an adminstrative perspective.  topic
* processing is handled in the ps_process_topic.
* 
* properties:  
* 	
*       error - the error message returned by validation if any
* methods:
*	topic_val_delete()
*	topic_val_update()
*       topic_add()
*       topic_update()
*       topic_delete()
*	
*
*************************************************************************/
class ps_topic {
  var $classname = "ps_topic";
  var $error;


  /**************************************************************************
   * name: topic_validate
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
   function topic_validate(&$d) {
    global $lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $valid=True;

    if (!$d["topic_subject"]) {
      $d["error"]=$error_str_127;
      $valid=False;
    }

    if (!$d["topic_content"]) {
      $d["error"] .=$error_str_128;
      $valid=False;
    }
  
    return $valid;
  }


  /**************************************************************************
   * name: reply_validate
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
   function reply_validate(&$d) {
    global $lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $valid=True;

    if (!$d["reply_subject"]) {
      $d["error"]=$error_str_127;
      $valid=False;
    }

    if (!$d["reply_content"]) {
      $d["error"] .=$error_str_128;
      $valid=False;
    }
  
    return $valid;
  }

 /**************************************************************************
   * name: topic_status_set
   * created by: uli
   **************************************************************************/
  function topic_status_set(&$d) {
    global $ps_vendor_id, $topic_return, $topic_id, $topic_status, $lang;
    $db = new ps_DB;
    
    $timestamp = time();

    $q = "UPDATE topics SET";
    $q .= " topic_status='" . $d["topic_status"] . "'";
    $q .= ", mdate='$timestamp' ";
    $q .= "WHERE topic_id='" . $d["topic_id"] . "'";

    if ($d["all_lang"]!=="on") {
      $q .="AND language='$lang' ";
    }

    $db->query($q);
    $db->next_record();

    $topic_id=$d["topic_id"];
    $topic_status=$d["topic_status"];

    return True;
  }


 /***********************************************************************
  ** name: topic_delete()
  ** created by: uli
  ** description:  Delete the topic
  ** parameters: $d
  ** returns:  True - delete succeeded
  **          False - delete failed
  **********************************************************************/
  function topic_delete(&$d) {
    global $lang,$ps_vendor_id;
    $db = new ps_DB;

    $topic_id=$d["topic_id"];
    $topic_group_id=$d["topic_group_id"];
    $all_lang=$d["all_lang"];

    if (!$topic_id) {
      return False;
    }

    if ($all_lang=="on") {
      $q = "DELETE from topics where topic_id='$topic_id' AND vendor_id='$ps_vendor_id'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topic_reply where topic_id='$topic_id' AND vendor_id='$ps_vendor_id'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from latest_topic where topic_id='$topic_id' AND vendor_id='$ps_vendor_id'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topic_subscribe where topic_id='$topic_id' AND vendor_id='$ps_vendor_id'";
      $db->query($q);
      $db->next_record();
    }


    else {
      $q = "DELETE from topics where topic_id='$topic_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topic_reply where topic_id='$topic_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from latest_topic where topic_id='$topic_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
      $db->query($q);
      $db->next_record();

      $q = "DELETE from topic_subscribe where topic_id='$topic_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
      $db->query($q);
      $db->next_record();
    }

    $q="OPTIMIZE TABLE topics";
    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE topic_reply";
    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE latest_topic";
    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE topic_subscribe";
    $db->query($q);
    $db->next_record();

    return True;
  }


  /***********************************************************************
  ** name: reply_delete()
  ** created by: uli
  ** description:  Delete an reply
  ** parameters: $d
  ** returns:  True - delete succeeded
  **          False - delete failed
  **********************************************************************/
  function reply_delete(&$d) {
    global $lang,$ps_vendor_id;
    $db = new ps_DB;

    $reply_id=$d["reply_id"];
    $topic_group_id=$d["topic_group_id"];
    $all_lang=$d["all_lang"];

    if (!$reply_id) {
      return False;
    }

    else {
      if ($all_lang=="on") {
        $q = "DELETE from topic_reply where reply_id='$reply_id' AND vendor_id='$ps_vendor_id'";
        $db->query($q);
        $db->next_record();

        $q = "DELETE from latest_topic where topic_id='$reply_id' AND vendor_id='$ps_vendor_id'";
        $db->query($q);
        $db->next_record();

      }

      else {
        $q = "DELETE from topic_reply where reply_id='$reply_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
        $db->query($q);
        $db->next_record();

        $q = "DELETE from latest_topic where topic_id='$reply_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
        $db->query($q);
        $db->next_record();
      }
      return True;
    }
  }

/**************************************************************************
  * name: topic_add
  * created by: uli
  * description: submits a new topic
  * parameters:
  * returns:$topic_success

  **************************************************************************/
  function topic_add(&$d) {
    global $auth, $topic_success, $ps_vendor_id, $lang;
    $db = new ps_DB;
    $timestamp = time();

    if (!$this->topic_validate($d)) {
      return False;
    }

    $db = new ps_DB;
    $db_1 = new ps_DB;

    $user_id = $auth["user_id"];

    $q = "SELECT * FROM user_info WHERE user_id='$user_id' "; 
    $db->query($q);
    $db->next_record();

    $user_info_id=$db->f(user_info_id);
    $topic_id=md5(uniqid(HASH_SECRET));

    $topic_status="1";
    $topic_subject = nl2br($d["topic_subject"]);
    $topic_content = nl2br($d["topic_content"]);
    $topic_content = str_replace("<br />","<br>",$topic_content);

    $topic_group_id= $d["tg"];
  
    
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
          $q = "INSERT INTO topics SET";
          $q .=" topic_id = '$topic_id' ,"; 
          $q .=" user_id='$user_id' ,";
          $q .=" vendor_id='$ps_vendor_id' ,";
          $q .=" topic_status='$topic_status' ,";
          $q .=" cdate='$timestamp' ,";
          $q .=" mdate='$timestamp' ,";
          $q .=" topic_subject='$topic_subject' ,";
          $q .=" topic_content='$topic_content' ,";
          $q .=" topic_group_id='$topic_group_id' ,";
          $q .=" language='$fl'";

          $db->query($q);
          $db->next_record();

          $q_1 = "SELECT * FROM latest_topic WHERE topic_group_id='$topic_group_id' AND vendor_id='$ps_vendor_id' AND language='$fl'";
          $db_1->query($q_1);

          if ($db_1->next_record()) {
            $q = "UPDATE latest_topic SET";
            $q .=" topic_id='$topic_id', ";
            $q .=" topic_subject='$topic_subject' ";
            $q .="WHERE topic_group_id='$topic_group_id' AND vendor_id='$ps_vendor_id' AND language='$fl'";
            $db->query($q);
            $db->next_record();
          }

          else {
            $q = "INSERT INTO latest_topic SET";
            $q .=" type = 'topic' ,"; 
            $q .=" vendor_id='$ps_vendor_id' ,";
            $q .=" topic_group_id='$topic_group_id' ,";
            $q .=" topic_id='$topic_id' ,";
            $q .=" topic_subject='$topic_subject' ,";
            $q .=" language='$fl'";
            $db->query($q);
            $db->next_record();
          }
        }
      }
    }

    else {
      $q = "INSERT INTO topics SET";
      $q .=" topic_id = '$topic_id' ,"; 
      $q .=" user_id='$user_id' ,";
      $q .=" vendor_id='$ps_vendor_id' ,";
      $q .=" topic_status='$topic_status' ,";
      $q .=" cdate='$timestamp' ,";
      $q .=" mdate='$timestamp' ,";
      $q .=" topic_subject='$topic_subject' ,";
      $q .=" topic_content='$topic_content' ,";
      $q .=" topic_group_id='$topic_group_id' ,";
      $q .=" language='$lang'";
      $db->query($q);
      $db->next_record();

      $q_1 = "SELECT * FROM latest_topic WHERE topic_group_id='$topic_group_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
      $db_1->query($q_1);

      if ($db_1->next_record()) {
        $q = "UPDATE latest_topic SET";
        $q .=" topic_id='$topic_id', ";
        $q .=" topic_subject='$topic_subject', ";
        $q .=" mdate='$timespamp' ";
        $q .="WHERE topic_id='$topic_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
        $db->query($q);
        $db->next_record();
      }

      else {
        $q = "INSERT INTO latest_topic(type,vendor_id,topic_group_id,topic_id,topic_subject,language,mdate) VALUES (";
        $q .="'topic','$ps_vendor_id','$topic_group_id','$topic_id','$topic_subject','$lang','$timespamp'";
        $q .=")";
        $db->query($q);
        $db->next_record();
      }
    }

    $d["tid"]=$topic_id;
    $d["subject"]=$topic_subject;

    $cont=stripslashes($topic_content);
    $d["content"]=str_replace(" ","&nbsp;",$cont);

    $this->topic_receipt($d);
    return True;
  }


/**************************************************************************
  * name: topic_edit
  * created by: uli
  * description: submits a new topic
  * parameters:
  * returns:$topic_success

  **************************************************************************/
  function topic_edit(&$d) {
    global $auth, $topic_success, $ps_vendor_id, $lang;

    if (!$this->topic_validate($d)) {
      return False;
    }

    $db = new ps_DB;
    $timestamp = time();

    $topic_id=$d["topic_id"];
    $user_id=$auth["user_id"];

    $q = "SELECT * FROM topics WHERE topic_id='$topic_id'";
    $db->query($q);
    $db->next_record();
    $topic_user_id=$db->f("user_id");
    $topic_group_id=$db->f("topic_group_id");

    if ($topic_user_id==$user_id || $auth["perms"]=="admin") {
      $topic_subject = nl2br($d["topic_subject"]);
      $topic_content = nl2br($d["topic_content"]);
      $topic_content = str_replace("<br />","<br>",$topic_content);

      $q = "UPDATE topics SET ";
      $q .="mdate='$timestamp' ,";
      $q .="topic_subject='$topic_subject', ";
      $q .="topic_content='$topic_content' ";
      $q .="WHERE topic_id='$topic_id' ";
      $q .="AND vendor_id='$ps_vendor_id' ";

      if ($d["all_lang"]!=="on") {
        $q .="AND language='$lang' ";
      }

      $db->query($q);
      $db->next_record();

      $q = "UPDATE latest_topic SET";
      $q .=" topic_subject='$topic_subject', ";
      $q .=" mdate='$timestamp' ";
      $q .="WHERE topic_group_id='$topic_group_id' ";
      $q .="AND vendor_id='$ps_vendor_id' ";

      if ($d["all_lang"]!=="on") {
        $q .="AND language='$lang' ";
      }

      $db->query($q);
      $db->next_record();

      $d["tid"]=$topic_id;
      $d["subject"]="Update ";
      $d["subject"] .=$topic_subject;

      $cont=stripslashes($topic_content);
      $d["content"]=str_replace(" ","&nbsp;",$cont);

      $this->topic_receipt($d);
      return True;
    }

    else {
      return False;
    }
  }

/**************************************************************************
  * name: topic_reply
  * created by: uli
  * description: submits an reply
  * parameters:

  **************************************************************************/
  function topic_reply(&$d) {
    global $ps_vendor_id, $auth, $lang;

    if (!$this->reply_validate($d)) {
      return False;
    }

    $db = new ps_DB;
    $db_1 = new ps_DB;
    $timestamp = time();

    $reply_subject=$d["reply_subject"];
    $reply_content = nl2br($d["reply_content"]);
    $reply_content = str_replace("<br />","<br>",$reply_content);

    $topic_id=$d["topic_id"];
    $topic_group_id = $d["tg"];
    $d["topic_id"]=$topic_id;

    $user_id= $auth["user_id"];

    $q = "SELECT * FROM user_info WHERE user_id='$user_id' "; 
    $db->query($q);
    $db->next_record();

    $user_info_id=$db->f(user_info_id);
    $reply_id=md5(uniqid(HASH_SECRET));

    $reply_status="1";

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
          $q = "INSERT INTO topic_reply SET";
          $q .=" reply_id = '$reply_id',"; 
          $q .=" topic_id = '$topic_id',"; 
          $q .=" topic_group_id = '$topic_group_id',"; 
          $q .=" user_id='$user_id',";
          $q .=" vendor_id='$ps_vendor_id',";
          $q .=" reply_status='$reply_status',";
          $q .=" cdate='$timestamp',";
          $q .=" mdate='$timestamp',";
          $q .=" reply_subject='$reply_subject',";
          $q .=" reply_content='$reply_content',";
          $q .=" language='$fl'";

          $db->query($q);
          $db->next_record();

          $q_1 = "SELECT * FROM latest_topic WHERE topic_group_id='$topic_group_id' AND vendor_id='$ps_vendor_id' AND language='$fl'";
          $db_1->query($q_1);

          if ($db_1->next_record()) {
            $q = "UPDATE latest_topic SET";
            $q .=" topic_id='$reply_id', ";
            $q .=" topic_subject='$reply_subject', ";
            $q .=" mdate='$timestamp' ";
            $q .="WHERE topic_id='$reply_id' AND vendor_id='$ps_vendor_id' AND language='$fl'";
            $db->query($q);
            $db->next_record();
          }

          else {
            $q = "INSERT INTO latest_topic SET";
            $q .=" type = 'reply' ,"; 
            $q .=" vendor_id='$ps_vendor_id' ,";
            $q .=" topic_group_id='$topic_group_id' ,";
            $q .=" topic_id='$reply_id' ,";
            $q .=" topic_subject='$reply_subject' ,";
            $q .=" mdate='$timestamp', ";
            $q .=" language='$fl'";
            $db->query($q);
            $db->next_record();
          }
        }
      }
    }

    else {
      $q = "INSERT INTO topic_reply SET";
      $q .=" reply_id = '$reply_id',"; 
      $q .=" topic_id = '$topic_id',"; 
      $q .=" topic_group_id = '$topic_group_id',"; 
      $q .=" user_id='$user_id',";
      $q .=" vendor_id='$ps_vendor_id',";
      $q .=" reply_status='$reply_status',";
      $q .=" cdate='$timestamp',";
      $q .=" mdate='$timestamp',";
      $q .=" reply_subject='$reply_subject',";
      $q .=" reply_content='$reply_content',";
      $q .=" language='$lang'";

      $db->query($q);
      $db->next_record();

      $q_1 = "SELECT * FROM latest_topic WHERE topic_group_id='$topic_group_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
      $db_1->query($q_1);

      if ($db_1->next_record()) {
        $q = "UPDATE latest_topic SET";
        $q .=" topic_id='$reply_id', ";
        $q .=" topic_subject='$reply_subject', ";
        $q .=" mdate='$timestamp' ";
        $q .="WHERE topic_id='$reply_id' AND vendor_id='$ps_vendor_id' AND language='$lang'";
        $db->query($q);
        $db->next_record();
      }

      else {
        $q = "INSERT INTO latest_topic SET";
        $q .=" type = 'reply' ,"; 
        $q .=" vendor_id='$ps_vendor_id' ,";
        $q .=" topic_group_id='$topic_group_id' ,";
        $q .=" topic_id='$reply_id' ,";
        $q .=" topic_subject='$reply_subject' ,";
        $q .=" mdate='$timestamp', ";
        $q .=" language='$lang'";
        $db->query($q);
        $db->next_record();
      }
    }

    $d["tid"]=$topic_id;
    $d["subject"]=$reply_subject;

    $cont=stripslashes($reply_content);
    $d["content"]=str_replace(" ","&nbsp;",$cont);

    $this->topic_receipt($d);

    return True;
  }

/**************************************************************************
  * name: reply_edit
  * created by: uli
  * description: submits a new reply
  * parameters:
  * returns:$reply_success

  **************************************************************************/
  function reply_edit(&$d) {
    global $auth, $reply_success, $ps_vendor_id, $lang;

    if (!$this->reply_validate($d)) {
      return False;
    }

    $timestamp = time();
    $db = new ps_DB;

    $reply_id=$d["reply_id"];
    $all_lang=$d["all_lang"];

    $user_id=$auth["user_id"];

    $q = "SELECT * FROM topic_reply WHERE reply_id='$reply_id'";
    $db->query($q);
    $db->next_record();
    $reply_user_id=$db->f("user_id");
    $topic_id=$db->f("topic_id");

    if ($reply_user_id==$user_id || $auth["perms"]=="admin") {
      $reply_subject = nl2br($d["reply_subject"]);
      $reply_content = nl2br($d["reply_content"]);
      $reply_content = str_replace("<br />","<br>",$reply_content);

      $topic_group_id=$db->f("topic_group_id");

      $q = "UPDATE topic_reply SET ";
      $q .="mdate='$timestamp' ,";
      $q .="reply_subject='$reply_subject', ";
      $q .="reply_content='$reply_content' ";
      $q .="WHERE reply_id='$reply_id'";
      $q .="AND vendor_id='$ps_vendor_id' ";

      if ($d["all_lang"]!=="on") {
        $q .="AND language='$lang' ";
      }

      $db->query($q);
      $db->next_record();

      $q = "UPDATE latest_topic SET";
      $q .=" topic_subject='$reply_subject', ";
      $q .=" mdate='$timestamp' ";
      $q .="WHERE topic_group_id='$topic_group_id' ";
      $q .="AND vendor_id='$ps_vendor_id' ";

      if ($d["all_lang"]!=="on") {
        $q .="AND language='$lang' ";
      }

      $db->query($q);
      $db->next_record();

      $d["tid"]=$topic_id;
      $d["subject"]="Update ";
      $d["subject"] .=$reply_subject;

      $cont=stripslashes($reply_content);
      $d["content"]=str_replace(" ","&nbsp;",$cont);

      $this->topic_receipt($d);

      return True;
    }

    else {
      return False;
    }

  }

 /**************************************************************************
   * name: reply_status_set
   * created by: uli
   * description: changes the status of an topic.  Can be 3 statuses:
   *              default: O - offen
   *                       E - erledigt
   *                       G - gelesen
   * parameters:
   * returns: $reply_return

   **************************************************************************/
  function reply_status_set(&$d) {
    global $ps_vendor_id, $reply_return, $reply_id, $topic_status,$lang;
    $db = new ps_DB;
    
    $timestamp = time();

    $q = "UPDATE topic_reply SET";
    $q .= " reply_status='" . $d["topic_status"] . "'";
    $q .= ", mdate='$timestamp' ";
    $q .= "WHERE reply_id='" . $d["reply_id"] . "' ";
    $q .= "AND vendor_id='$ps_vendor_id' ";

    if ($d["all_lang"]!=="on") {
      $q .="AND language='$lang' ";
    }

    $reply_id=$d["reply_id"];
    $reply_status=$d["reply_status"];

    return True;
  }


  /**************************************************************************
   * name: topic_subscribe
   * created by: uli
   * description: find an reply by its reply_id
   * parameters:
   * returns:
   **************************************************************************/
  function topic_subscribe(&$d) {
    global $lang,$ps_vendor_id,$auth;
    $db = new ps_DB;

    $topic_subscribe=$d["topic_subscribe"];
    $topic_id=$d["topic_id"];
    $user_id=$auth["user_id"];

    if ($topic_subscribe=="on") {
      $q="INSERT INTO topic_subscribe SET ";
      $q .="user_id='$user_id',";
      $q .="vendor_id='$ps_vendor_id',";
      $q .="topic_id='$topic_id',";
      $q .="language='$lang'";
      $db->query($q);
      $db->next_record();
    }

    else {
      $q="DELETE FROM topic_subscribe WHERE user_id='$user_id' AND vendor_id='$ps_vendor_id' AND topic_id='$topic_id' AND language='$lang'";
      $db->query($q);
      $db->next_record();
    }
  
    return true;
  }


  /************************************************************************
  ** name: topic_receipt()
  ** created by: uli
  ** parameters:
  ** returns:
  ************************************************************************/ 
  function topic_receipt(&$d) {
    global $topic_id,$lang,$data,$ps_vendor_id;

    include(PS_BASE . "languages/lang_$lang.inc");

    $tid=$d["tid"];

    $subject = $d["subject"];
    $content = $d["content"];

    $db = new ps_DB;
    $dbu = new ps_DB;
    $dbl=new ps_DB;

    $q="SELECT * FROM vendor WHERE vendor_id='$ps_vendor_id'";
    $db->query($q);
    $db->next_record();

    $vendor_name = $db->f("vendor_name");
    $vendor_email = $db->f("contact_email");


//    $vendor_name = $data["vendor_store_name"];
//    $vendor_email = $data["vendor_email"];

    $message = "<html><head><title>$subject $vendor_name</title></head><body><table border=1 width=100%><tr><td>\n";
    $message .= $subject_lbl . ": " . $subject . ", ";
    $message .= "$lang </td></tr>";
    $message .= "<tr><td>$content </td></tr>";

//    $ql="SELECT * FROM languages WHERE vendor_id='$ps_vendor_id' AND shop_name='$lang'";
//    $dbl->query($ql);
//    $dbl->next_record();

//    $language_name=$dbl->f("language_name");
//    $language_code=$dbl->f("shop_name");
//    $lg_code=$dbl->f("code");
//    $direction=$dbl->f("direction");
//    $charset=$dbl->f("charset");

    $direction="LTR";
    $charset="UTF-8";

    $headers  = "MIME-Version: 1.0\r\n";
    $headers .= "From: $vendor_name <$vendor_email>\r\n";
    $headers .= "Content-type: text/html; charset=$charset\r\n";

    require_once("admin/lib/ps_mail.inc");
    $ps_mail=new ps_mail;

    $q = "SELECT * FROM topic_subscribe WHERE vendor_id='$ps_vendor_id'AND language='$lang' AND topic_id='$tid'";
    $db->query($q);

    while($db->next_record()) {
      $user_id=$db->f("user_id");
      
      $q = "SELECT * FROM user_info ";
      $q .= "WHERE user_id='$user_id'AND address_type='BT'";
      $dbu->query($q);
      $dbu->next_record();
      $to=$dbu->f("user_email");

      $ps_mail->send($to,
        $info_lbl, 
        $message, 
        $headers);
    }

    $to=$vendor_email;
    $ps_mail->send($to,
      $info_lbl, 
      $message, 
      $headers);

    return True; 
  }
}

?>

