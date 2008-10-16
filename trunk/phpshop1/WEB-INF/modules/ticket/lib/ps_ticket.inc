<?php
/*
 * The ps_ticket class
 *
 * Copyright (c) uli (ulisoft@gmail.com) All rights reserved.
 *

****************************************************************************
*
* CLASS DESCRIPTION
*                   
* ps_ticket
*
* The class handles tickets from an adminstrative perspective.  ticket
* processing is handled in the ps_process_ticket.
* 
* properties:  
* 	
*       error - the error message returned by validation if any
* methods:
*	ticket_val_delete()
*	ticket_val_update()
*       new_ticket()
*       ticket_update()
*       ticket_delete()
*	
*
*************************************************************************/
class ps_ticket {
  var $classname = "ps_ticket";
  var $error;


  /**************************************************************************
   * name: ticket_validate
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
   function ticket_validate(&$d) {
    global $lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $valid=True;

    if (!$d["ticket_subject"]) {
      $d["error"]=$error_str_127;
      $valid=False;
    }

    if (!$d["ticket_content"]) {
      $d["error"] .=$error_str_128;
      $valid=False;
    }
  
    return $valid;
  }


  /**************************************************************************
   * name: answer_validate
   * created by: uli
   * parameters:
   * returns:
   **************************************************************************/
   function answer_validate(&$d) {
    global $lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $valid=True;

    if (!$d["info_subject"]) {
      $d["error"]=$error_str_127;
      $valid=False;
    }

    if (!$d["info_detail"]) {
      $d["error"] .=$error_str_128;
      $valid=False;
    }
  
    return $valid;
  }
  

 /**************************************************************************
   * name: ticket_status_set
   * created by: uli
   * parameters:
   * returns: $ticket_return

   **************************************************************************/
  function ticket_status_set(&$d) {
    global $ps_vendor_id,$lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $db = new ps_DB;
    
    $timestamp = time();

    $q = "UPDATE tickets SET";
    $q .= " ticket_status='" . $d["ticket_status"] . "'";
    $q .= ", mdate='$timestamp' ";
    $q .= "WHERE ticket_id='" . $d["ticket_id"] . "'";

    $db->query($q);
    $db->next_record();

    $ticket_id=$d["ticket_id"];
    $ticket_status=$d["ticket_status"];

    if ($d["ticket_status"]=="2") {
      $q = "SELECT * FROM ticket_status WHERE ";
      $q .= "ticket_status_id='$ticket_status' ";
      $q .= "AND language='$lang' AND vendor_id='$ps_vendor_id'";
      $db->query($q);
      $db->next_record();
      $status_name=$db->f("ticket_status_name");    

      $q = "SELECT * FROM tickets WHERE";
      $q .= " ticket_id = '$ticket_id'";
      $db->query($q);
      $db->next_record();

      $userid = $db->f("user_id");

      $q = "SELECT * FROM vendor ";
      $q .= "WHERE vendor_id='$ps_vendor_id' ";
//    $q .= "AND language='$lang'";
      $db->query($q);
      $db->next_record();

      $vendor_email=$db->f("contact_email");
      $vendor_store_name=$db->f("vendor_store_name");

      $from = "From: " . $vendor_store_name . "<" . $vendor_email . ">";

      $q="SELECT * FROM user_info WHERE user_id = '$userid'";
      $db->query($q);
      $db->next_record();

      $message .= "$ticket_list_id\n ";
      $message .= $dbw->f("ticket_id") ."\n";
      $message .= "$ftp_list_status: $status_name\n";

      $message .= "____________________________________________________________\n";
      $message .= "$bmsg_str_7\n";        
      $message .= $vendor_store_name . " " . $vendor_email . "\n";

      if (mail($db->f("user_email"), "Ticket-Info $ticket_id", $message, $from)) {
        $mail_success .= "$sent_to_str ". $db->f("user_email") ."<br>";
      }

      else {
        $mail_success .= "$bmsg_str_11 ". $db->f("user_email") . "&gt;<br>";
      }
    }

    $d["ticket_success"]=$mail_success;    

    return $True;
  }

   /**************************************************************************
   * name: ticket_list
   * created by: uli
   * description: shows a listbox of tickets
   * parameters: set to ticket_id
   * returns:
   **************************************************************************/
  function ticket_list() {
    global $ps_vendor_id, $auth;
    $db = new ps_DB;

    $i = 0;

    $q = "SELECT * FROM tickets,ticket_status ";
    $q .= "WHERE tickets.vendor_id='$ps_vendor_id' ";
    $q .= "AND ticket_status.vendor_id='$ps_vendor_id' ";
    $q .= "AND ticket_status_id=ticket_status ";
    $q .= "AND ticket_status.language=tickets.language ";
    $q .= "AND user_id='" . $auth["user_id"] . "' "; 
    $q .= "ORDER BY ticket_status ASC";
    $db->query($q);

    echo "<SELECT NAME=ticket_id SIZE=" . MAX_ROWS . ">";

    while ($db->next_record()) {
      $i++;
      echo "<option value=" . $db->f("ticket_id") . ">";
      echo $db->f("ticket_id");
      echo "&nbsp;&nbsp;&nbsp;&nbsp;";
      echo date("dMY.H:i", $db->f("mdate"));
      echo "&nbsp;&nbsp;&nbsp;&nbsp;";
      echo $db->f("ticket_subject");
      echo "&nbsp;&nbsp;&nbsp;";
      echo $db->f("ticket_status_name");
      echo "&nbsp;&nbsp;";
      echo "</OPTION>";
    }

    if (!$i) {
      echo "<option value=''>-------</option>\n";
    }

    echo "</SELECT>\n";    
  }

  /********************************************************************
  ** name: ticket_val_delete()
  ** created by: uli
  ** description:  ticket_val form values
  ** parameters: $d
  ** returns:  True - validation passed
  **          False - validation failed
  ********************************************************************/
  function ticket_val_delete(&$d) {
    global $lang;

    if(!$d["ticket_id"]) {
       include(PS_BASE . "languages/lang_$lang.inc");
       $d["error"] = $error_str_164;
       return False;
    }

    return True;
  }

 /***********************************************************************
  ** name: ticket_delete()
  ** created by: uli
  ** description:  Delete the ticket
  ** parameters: $d
  ** returns:  True - delete succeeded
  **          False - delete failed
  **********************************************************************/
  function ticket_delete(&$d) {
    $db = new ps_DB;
  
    $ticket_id=$d["ticket_id"];

    if (!$this->ticket_val_delete($d)) {
      return False;
    }

    $q = "DELETE from tickets where ticket_id='$ticket_id' ";
    $db->query($q);
    $db->next_record();

    $q = "DELETE from ticket_answer where ticket_id='$ticket_id' ";
    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE ticket";
    $db->query($q);
    $db->next_record();

    $q="OPTIMIZE TABLE ticket_answer";
    $db->query($q);
    $db->next_record();
  }

  /********************************************************************
  ** name: answer_val_delete()
  ** created by: uli
  ** description:  ticket_val form values
  ** parameters: $d
  ** returns:  True - validation passed
  **          False - validation failed
  ********************************************************************/
  function answer_val_delete(&$d) {
    global $lang;

    if(!$d["ticket_id"]) {
      include(PS_BASE . "languages/lang_$lang.inc");
       $d["error"]=$error_str_165;
       return False;
    }

    return True;
  }

/***********************************************************************
  ** name: answer_delete()
  ** created by: uli
  ** description:  Delete an answer
  ** parameters: $d
  ** returns:  True - delete succeeded
  **          False - delete failed
  **********************************************************************/
  function answer_delete(&$d) {
    $db = new ps_DB;
  
    $answer_id=$d["answer_id"];

    if (!$this->answer_val_delete($d)) {
      return False;
    }

    $q = "DELETE from ticket_answer where answer_id='$answer_id' ";
    $db->query($q);
    $db->next_record();


    $q="OPTIMIZE TABLE ticket_answer";
    $db->query($q);
    $db->next_record();

    return True;
  }

/**************************************************************************
  * name: new_ticket
  * created by: uli
  * description: submits a new ticket
  * parameters:
  * returns:$ticket_success
  **************************************************************************/
  function new_ticket(&$d) {
    global $auth, $ticket_success, $ps_vendor_id, $lang;

    if (!$this->ticket_validate($d)) {
      return False;
    }

    include(PS_BASE . "languages/lang_$lang.inc");

    $db = new ps_DB;
    $dbl=new ps_DB;

    $timestamp = time();

    $user_id=$auth["user_id"];

    $db = new ps_DB;
    $q = "SELECT * FROM user_info WHERE user_id='$user_id' "; 
    $db->query($q);
    $db->next_record();

    $user_info_id=$db->f(user_info_id);
    $from = "From: ";
    $fr = $db->f("first_name");
    $fr .= " ";
    $fr .= $db->f("last_name");
    $fr .="<" . $db->f("user_email") . ">";

    $from .= $fr;

    $ticket_id=md5(uniqid(HASH_SECRET));

    $ticket_status="1";
 
    $ticket_subject = $d["ticket_subject"];
    $ticket_content = nl2br($d["ticket_content"]);

    $q = "INSERT INTO tickets SET";
    $q .=" ticket_id = '$ticket_id' ,"; 
    $q .=" user_id='$user_id' ,";
    $q .=" vendor_id='$ps_vendor_id' ,";
    $q .=" ticket_status='$ticket_status' ,";
    $q .=" cdate='$timestamp' ,";
    $q .=" mdate='$timestamp' ,";
    $q .=" ticket_subject='$ticket_subject' ,";
    $q .=" ticket_content='$ticket_content', ";
    $q .=" language='$lang'";
    $db->query($q);
    $db->next_record();

    $q = "SELECT * FROM vendor ";
    $q .= "WHERE vendor_id='$ps_vendor_id' ";
//    $q .= "AND language='$lang'";
    $db->query($q);
    $db->next_record();

    $vendor_email=$db->f("contact_email");
    $vendor_store_name=$db->f("vendor_store_name");

//    $ql="SELECT * FROM languages WHERE vendor_id='$ps_vendor_id' AND shop_name='$lang'";
//    $dbl->query($ql);
//    $dbl->next_record();

//    $language_name=$dbl->f("language_name");
//    $language_code=$dbl->f("shop_name");
//    $lg_code=$dbl->f("code");
//    $direction=$dbl->f("direction");
//    $charset=$dbl->f("charset");
    $charset="UTF-8";
    $direction="LTR";

    $headers  = "MIME-Version: 1.0\r\n";
    $headers .= "$from\r\n";
    $headers .= "Content-type: text/html; charset=$charset\r\n";

    $message_body = "$ticket_print_po_lbl &nbsp $from_lbl $nbsp $fr<br>\n";
    $message_body .="$subject_lbl: $ticket_subject<br>\n";
    $message_body .="$ticket_content\n";

    $message = "<html><head><title>$ticket_print_po_lbl</title></head><body><table width=100%><tr><td>\n";
    $message .="<tr><td>\n";
    $message .=$message_body;
    $message .= "</td></tr></table></body></html>\n";

    mail($vendor_email, "$ticket_list_id: $ticket_id", $message, $headers);
    $d["ticket_success"]="$ticket_list_id &nbsp $ticket_id &nbsp $topic_success_str_2";

    return True;
  }

/**************************************************************************
  * name: ticket_answer
  * created by: uli
  * description: submits an answer
  * parameters:
  * returns:$answer_success

  **************************************************************************/
  function ticket_answer(&$d) {
    global $ps_vendor_id,$auth, $lang;

    if (!$this->answer_validate($d)) {
      return False;
    }

    include(PS_BASE . "languages/lang_$lang.inc");

    $timestamp = time();
    $answer_subject=$d[info_subject];
    $answer_content = nl2br($d[info_detail]);
    $ticket_id=$d[ticket_id];

    $db = new ps_DB;
    $q = "SELECT * FROM tickets WHERE ticket_id='$ticket_id' AND vendor_id='$ps_vendor_id'"; 
    $db->query($q);
    $db->next_record();
    $uid = $db->f(user_id);

    $answer_id=md5(uniqid(HASH_SECRET));
    $answer_status="1";

    $q = "INSERT INTO ticket_answer SET";
    $q .=" answer_id = '$answer_id',"; 
    $q .=" ticket_id = '$ticket_id',"; 
    $q .=" user_id='$uid',";
    $q .=" vendor_id='$ps_vendor_id',";
    $q .=" answer_status='$answer_status',";
    $q .=" cdate='$timestamp',";
    $q .=" mdate='$timestamp',";
    $q .=" answer_subject='$answer_subject',";
    $q .=" answer_content='$answer_content', ";
    $q .=" language='$lang'";

    $db->query($q);
    $db->next_record();

    $d["ticket_success"]="$answer_success_str_1 $answer_success_str_2";

    return True;
  }

  /**************************************************************************
   * name: answer_list
   * created by: uli
   * description: shows a listbox of tickets
   * parameters: set to answer_id
   * returns:
   **************************************************************************/
  function answer_list() {
    global $ps_vendor_id, $auth,$lang;
    $db = new ps_DB;

    $i = 0;

    $q = "SELECT * FROM ticket_answer,ticket_status ";
    $q .= "WHERE ticket_answer.vendor_id='$ps_vendor_id' ";
    $q .= "AND ticket_status.vendor_id='$ps_vendor_id' ";
    $q .= "AND ticket_status_id=answer_status ";
    $q .= "AND ticket_status.language=ticket_answer.language ";
    $q .= "AND user_id='" . $auth["user_id"] . "' "; 
    $q .= "ORDER BY answer_status ASC";

    $db->query($q);
    echo "<SELECT NAME=answer_id SIZE=" . MAX_ROWS . ">";

    while ($db->next_record()) {
      $i++;
      echo "<option value=" . $db->f("answer_id") . ">";
      echo $db->f("answer_id");
      echo "&nbsp;&nbsp;&nbsp;&nbsp;";
      echo date("dMY.H:i", $db->f("cdate"));
      echo "&nbsp;&nbsp;&nbsp;";
      echo $db->f("ticket_status_name");
      echo "&nbsp;&nbsp;";
      echo "</OPTION>";
    }

    if (!$i) {
      echo "<option value=''>-------</option>\n";
    }

    echo "</SELECT>\n";    
  }


 /**************************************************************************
   * name: answer_status_set
   * created by: uli
   * parameters:
   * returns: $answer_return

   **************************************************************************/
  function answer_status_set(&$d) {
    global $ps_vendor_id,$answer_id,$ticket_status,$lang;

    include(PS_BASE . "languages/lang_$lang.inc");

    $db = new ps_DB;
    $timestamp = time();

    $q = "UPDATE ticket_answer SET";
    $q .= " answer_status='" . $d["ticket_status"] . "'";
    $q .= ", mdate='$timestamp' ";
    $q .= "WHERE answer_id='" . $d["answer_id"] . "'";

    $db->query($q);
    $db->next_record();

    $answer_id=$d["answer_id"];
    $answer_status=$d["ticket_status"];

    if ($d["ticket_status"]=="2") {
      $q = "SELECT * FROM ticket_status WHERE";
      $q .= " ticket_status_id = '$answer_status'";
      $db->query($q);
      $db->next_record();
      $status_name=$db->f("ticket_status_name");

      $q = "SELECT * FROM ticket_answer WHERE";
      $q .= " answer_id = '$answer_id'";
      $db->query($q);
      $db->next_record();

      $userid = $db->f("user_id");

      $q = "SELECT * FROM vendor ";
      $q .= "WHERE vendor_id='$ps_vendor_id' ";
//    $q .= "AND language='$lang'";
      $db->query($q);
      $db->next_record();

      $vendor_email=$db->f("contact_email");
      $vendor_store_name=$db->f("vendor_store_name");

      $from = "From: " . $vendor_store_name . "<" . $vendor_email . ">";

      $q="SELECT * FROM user_info WHERE user_id = '$userid'";
      $db->query($q);
      $db->next_record();

      $message .= "$answer_list_id\n ";
      $message .= $dbw->f("anwser_id") ."\n";
      $message .= "$ftp_list_status: $ticket_status_name\n";

      $message .= "____________________________________________________________\n";
      $message .= "$bmsg_str_7\n";        
      $message .= $vendor_store_name . " " . $vendor_store_email . "\n";

      if (mail($db->f("user_email"), "$answer_id_str $answer_id", $message, $from)) {
        $mail_success .= "$sent_to_str ". $db->f("user_email") ."<br>";
      }

      else {
        $mail_success .= "$bmsg_str_11 ". $db->f("user_email") . "&gt;<br>";
      }
    }

    $this->ticket_answer($d);
    $d["ticket_success"]=$mail_success;    
    return True;
  }


  /************************************************************************
  ** name: ticket_mail()
  ** created by: uli
  ** description: admin-ticket-answer
  ** parameters:
  ** returns:
  ************************************************************************/ 
  function ticket_mail(&$d) {
    global $ps_vendor_id,$auth,$lang;

    include(PS_BASE . "languages/lang_$lang.inc");
    $userid=$d["user_id"];
    $ticket_id=$d["ticket_id"];

    $db = new ps_DB;
    $q = "SELECT * FROM vendor ";
    $q .= "WHERE vendor_id='$ps_vendor_id' ";
//    $q .= "AND language='$lang'";
    $db->query($q);
    $db->next_record();
    $vendor_email=$db->f("contact_email");
    $vendor_store_name=$db->f("vendor_store_name");

    $q = "SELECT * FROM user_info WHERE user_id='" . $auth["user_id"] . "' "; 
    $db->query($q);
    $db->next_record();

    $from = "From: " . $vendor_store_name . "<" . $vendor_email . ">";

    $mail_success = "";
    $email=$d[to_email] ."\n\n";
    $message = $d["info_pre"] . "\n\n";
    $message .= $d[info_detail] ."\n\n";
    $message .= "$bmsg_str_7\n";        
    $message .= $vendor_store_name . " " . $vendor_email . "\n";
    $message .= "____________________________________________________________\n";
    $message .= $ticket_info_lbl . " ". $vendor_store_name;

    if (mail($d["to_email"], $d[info_subject], $message, $from)) {
      $mail_success .= "$sent_to_str ". $d["to_email"] ."<br>";
    }

    else {
      $mail_success .= "$bmsg_str_11 ". $d["to_email"] . "&gt;<br>";
    }

    $d["ticket_success"]=$mail_success;    
    return True;

  }
}
?>
