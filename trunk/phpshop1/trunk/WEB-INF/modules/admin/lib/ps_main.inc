<?php
/*
 * ps_main file
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_main.inc,v 1.1.1.1 2004/07/27 14:58:34 pablo Exp $
 *
 */


/**************************************************************************
** name: validate_image
** created by: jep
** description: Validates an uploaded image. Creates UNIX commands to be used
**              by the process_images function, which has to be called after
**              the validation.
**
** parameters: 
**   - $d             The array containing a the image upload information.
**       - $d[$field_name] : PHP passes the local temp filename for the image
**                           upload here.
**       - $d[$field_name . "_name"] : PHP passes the original filename of the
**                                     uploaded  file here.
**       - $d[$field_name . "_curr"] : This must be passed by the form that
**                                     uploads the images.  It must contain
**                                     the filename of the current image for
**                                     the field_name.
**
**   - $field_name    The name of the field in the data base that is used to
**                    store the image filename.  This name has to be the one
**                    used in the Upload Form Object so that all image upload
**                    vars can be accessed from the $d array.
**
**   - $table_name    The name of the table where the image belongs.  This 
**                    variable indicates the subdirectory where the image 
**                    files will be placed. This directory is based on the
**                    vendor_image_path value found on the vendor table in
**                    the database.
**
** returns:
**   - If an image upload was not requested for field_name, the function
**     returns TRUE.
**
**   - If an image upload was requested for field_name:
**       - TRUE if image was uploaded to the local drive, the file is readable,
**         the image type is valid, and the destination directory is writeable.
**       - FALSE otherwise.
**
**   - If an image delete was requested:
**       - TRUE if the directory is writeable.
**       - FALSE otherwise.
**
**   - $d["$field_name"] : The filename (without path) to where
**                         the image was saved is returned here.
**
**   - $d["image_commands"] : The commands to be executed by the process_images
**                           function are returned as a string here.  The
**                           commands are EVAL commands separated by ";"
**
**   - $d["error"] : Error messages returned here.
**                         
***************************************************************************/  
function validate_image(&$d,$field_name,$table_name) {
 	global $ps_vendor_id;
 	require_once("vendor/lib/ps_vendor.inc");
 	$ps_vendor = new ps_vendor;

 	global $_FILES;

 	//$temp_file = $d[$field_name];
 	//$orig_file = $d[$field_name . "_name"];
 	//$file_size = $d[$field_name . "_size"];

 	$curr_file = $d[$field_name . "_curr"];
 	$temp_file = $_FILES[$field_name]["tmp_name"];
 	$orig_file = $_FILES[$field_name]["name"];
 	$file_size = $_FILES[$field_name]["size"];

 	if ($d["vendor_image_path"]) {
 		$d["vendor_image_path"]=str_replace("//","/","/" .$d["vendor_image_path"]);
 	} 
 	elseif ($ps_vendor_id) {
 		$d["vendor_image_path"]=str_replace("//","/","/" .$ps_vendor->get_field($ps_vendor_id,"vendor_image_path"));
 	} 
 	elseif ($d["vendor_id"]) {
 		$d["vendor_image_path"]=str_replace("//","/","/" .$ps_vendor->get_field($d["vendor_id"],"vendor_image_path"));
 	}

  /* If nothing was entered in the Upload box, there is no image to
  ** process */
  if (!$orig_file) {
    $d[$field_name] = $curr_file;
    return true;
  } 

  /* Generate text to dispaly in error messages */
  if (eregi("thumb",$field_name)) {
    $image_type = "thumbnail image";
  } elseif (eregi("full",$field_name))  {
    $image_type = "full image";
  } else {
    $image_type = ereg_replace("_"," ",$field_name);
  }

  /* Generate the path to images */
  $path  = WEBROOT;
  if ($d["vendor_image_path"]) {
    $path .= $d["vendor_image_path"];
  } elseif ($ps_vendor_id) {
    $path .= $ps_vendor->get_field($ps_vendor_id,"vendor_image_path");
  } elseif ($d["vendor_id"]) {
    $path .= $ps_vendor->get_field($d["vendor_id"],"vendor_image_path");
  } else {
    $d["error"] .= "ERROR:process_image: Could not resolve vendor image ";
    $d["error"] .= "path.<br />";
    return false;
  }
  $path .= $table_name . "/";

  /* If User types "none" in Image Upload Field */
  if ($orig_file == "none") {
    /* If there is a current image file */
    if ($curr_file) {
      /* Check permissions to delete from $path */
      if (!is_writeable($path)) {
         $d["error"] .= "ERROR: Cannot delete from $image_type directory.";
         $d["error"] .= "<br />$path<br />";
         return false;
      } else {
        $d["image_commands"] .= "\$ret = unlink(\"$path$curr_file\");";
      }

    }
  $d[$field_name] = "";
  return true;
  }

  /* If upload fails */
  elseif($orig_file and $temp_file == "none") {
    $d["error"] .= "ERROR: $image_type upload failed.";
    return false;
  }

  /* Check permissions to read temp file */
  if (!is_readable($temp_file)) {
    $d["error"] .= "ERROR: Cannot read uploaded $image_type temp file.<br />";
    return false;
  }

  /* Generate Image Destination File Name */
  $to_file = md5(uniqid("PHPShop"));

  /* Check image file format */
  $image_info = getimagesize($temp_file);
  switch($image_info[2]) {
    case 1:
         $to_file .= ".gif";
         break;
    case 2:
         $to_file .= ".jpg";
         break;
    case 3:
 	 $to_file .= ".png";
         break;
    default:
         $d["error"] .= "ERROR: $image_type file is invalid.<br />";
	 return false;
  }

  /*
  ** If it gets to this point then there is an uploaded file in the system
  ** and it is a valid image file.
  */

  /* Check permissions to write to destination directory */
  if (!is_writeable($path)) {
    $d["error"] .= "ERROR: Cannot write to $image_type destination ";
    $d["error"] .= "directory.<br />$path<br />";
    return false;
  }

  /* If Updating */

  if ($curr_file) {
    /* Command to remove old image file */
    $d["image_commands"] .= "\$ret = unlink(\"$path$curr_file\");";
  }

  /* Command to move uploaded file into destination directory */
  $d["image_commands"] .= "\$ret = copy(\"$temp_file\", \"$path$to_file\");";



  /* Return new image file name */
  $d[$field_name] = $to_file;
  return true;
}

/**************************************************************************
** name: process_images
** created by: jep
** description: 
** parameters:
** returns:
***************************************************************************/  
function process_images(&$d) {

  if ($d["image_commands"]) {
    $commands = explode(";",ereg_replace(";$","",$d["image_commands"]));
    $d["image_commands"] = "";
    $cnt = count($commands);
    for ($i=0;$i<$cnt;$i++) {
	 	/* fix by heiko 08.04.2005 */
	 	$psfile = explode("\"",$commands[$i]);
	 	/* first check if there is a file to delete */
	 	if (!($handle = @fopen ("$psfile[1]", "r")) and strpos ($psfile[0], "unlink") !== false){
	 		$ret = true; // if unlink file - and file does not exists
	 	}
	 	else { 
			eval($commands[$i] . ";"); 
		}
	
      if ($ret == False) {
        $d["error"] .= "ERROR: Image Update command failed.<br />";
        $d["error"] .= $commands[$i] . "<br />";
        return false;
      }

    }
  }
  return true;
}

/**************************************************************************
** name: process_date_time
** created by: jep
** description: 
** parameters:
** returns:
***************************************************************************/  
function process_date_time(&$d,$field,$type="") {
  $month = $d["$field" . "_month"];
  $day = $d["$field" . "_day"];
  $year = $d["$field" . "_year"];
  $hour = $d["$field" . "_hour"];
  $minute = $d["$field" . "_minute"];
  $use = $d["$field" . "_use"];
  $valid = true;

  /* If user unchecked "Use date and time" then time = 0 */
  if (!$use) {
    $d[$field] = 0;
    return true;
  }
  if (!checkdate($month,$day,$year)) {
    $d["error"] .= "ERROR: $type date is invalid.";
    $valid = false;
  }
  if (!$hour and !$minute) {
    $hour = 0;
    $minute = 0;
  } elseif ($hour < 0 or $hour > 23 or $minute < 0 or $minute > 59) {
    $d["error"] .= "ERROR: $type time is invalid.";
    $valid = false;
  }

  if ($valid) {
    $d[$field] = mktime($hour,$minute,0,$month,$day,$year);
  }

  return $valid;   
}

/****************************************************************************
 *    function: validate_email
 *  created by: Gregory Day
 * description: Validates an e-mail address.  Only checks that the format
 *              is valid.  It does not validate that the address will
 *              work.
 *  parameters: $email: Email address to validate
 *     returns: true: Email address is valid
 *             false: Email address is not valid
 ****************************************************************************/
function validate_email ( $email ) {

   if(ereg('^[_a-z0-9A-Z+-]+(\.[_a-z0-9A-Z+-]+)*@[a-z0-9A-Z-]+(\.[a-z0-9A-Z-]+)*$', $email)) {      return(true);
   }
   else {
      return(false);
   }
} // validate_email()


/****************************************************************************
 *    function:  list_user_title
 *  created by: pablo
 * description: Lists some titles.
 ****************************************************************************/
function list_user_title($t) {
 
   $title = array("Mr.", "Mrs.", "Ms.", "Dr.");
   echo "<select name=\"title\">\n";
   echo "<option value=\"\">None&nbsp;</option>\n";
   for ($i=0;$i<count($title);$i++) {
      echo "<option value=\"" . $title[$i] . "\"";
      if ($title[$i] == $t)
         echo " selected=\"selected\"";
      echo ">" . $title[$i] . "</option>\n";
   }
   echo "</select>\n";

}


function utime()
{
  $time = explode( " ", microtime());
  $usec = (double)$time[0];
  $sec = (double)$time[1];
  return $sec + $usec;
}

function in_list($list, $item) {
  for ($i=0;$i<$list["cnt"];$i++) {
    if (!strcmp($list[$i]["name"],$item)) {
       return $i;
    }
  }
  return False;
}

// New Stuff to make the page selection and search easier
function search_header($title, $modulename, $pagename) {
  global $sess;
  global $search_box_title;

  $header = "<form action=\"" . SECUREURL . "\" method=\"post\">\n";
  $header .= "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"4\" class=\"SearchTable\">\n";
  $header .= "<tr>\n";
  $header .= "<td align=\"left\"><p class=\"HeaderText\">$title</p></td>\n";
  $header .= "<td align=\"right\">\n";
  $header .= "<input type=\"text\" size=\"12\" name=\"keyword\" />\n";
  $header .= "<input type=\"hidden\" name=\"page\" value=\"". $modulename . "/" . $pagename . "\" />\n";
  $header .= "<input type=\"submit\" class=\"Button\" name=\"Search\" value=\"$search_box_title\" />\n";
  echo $header;
  $sess->hidden_session();
  $header = "</td></tr></table>\n";
  $header .= "</form><br />\n";
  echo $header;
}

function search_footer($modulename, $pagename, $offset, $num_rows, $keyword, $extra="") {
  global $sess;

  $footer = "<br />\n";
  $footer .= "<div align=\"center\">";

  // Get total pages
  $num_pages = intval($num_rows / SEARCH_ROWS);
  if ($num_rows % SEARCH_ROWS)
    $num_pages++;
  $page_num=($offset/SEARCH_ROWS)+1;

  $from = $offset + 1;
  $to = $offset + SEARCH_ROWS;
  if ($to > $num_rows)
  $to = $num_rows;

  $search_string="";
  if ($keyword) {
    $search_string.="&amp;keyword=" .urlencode($keyword) ."";
  }

  //print the page number
  if ($num_pages == 1)
    $footer .= "Page <b>1</b> of <b>1</b><br />";
  else
    $footer .= "Page <b>". $page_num ."</b> of <b>" .$num_pages. "</b><br />";

  $footer .= "<br />";

  //print the current record
  if ($num_rows == 1)
    $footer .= "Record <b>1</b> of <b>1</b>";
  elseif ($from == $to)
    $footer .= "Record <b>". $from ."</b> of <b>" .$num_rows. "</b>";
  else
    $footer .= "Record <b>". $from ."</b> to <b>" .$to. "</b> of <b>" .$num_rows. "</b>";

  $footer .= "<br />";

  //print the previous page link
  if ($offset >= SEARCH_ROWS) {
    $prevoffset=$offset-SEARCH_ROWS;
    $footer .= "<a href=\"";
    $footer .= $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;keyword=$keyword&amp;offset=$prevoffset$extra");
    $footer .= "\">PREV</a>&nbsp;\n";
  }
  else
    $footer .= "&nbsp;";

  //print links to the pages in range
  if ($num_pages != 1) {

    $start_page=$page_num-intval(SEARCH_PAGES/2);
    if($start_page<=0) $start_page=1;

    $end_page=$page_num+intval(SEARCH_PAGES/2);
    if($end_page>$num_pages) { $end_page=$num_pages; }

    for ($i=$start_page;$i<=$end_page;$i++) {
      if (($offset < $i*SEARCH_ROWS) && ($offset >= ($i-1)*SEARCH_ROWS)) {
        $footer .= "<b>" . $i . "</b>&nbsp;";
      }
      else {
        $pagenumber = $i;
        $newoffset = SEARCH_ROWS * ($i-1);
        $footer .= "<a href=\"";
        $footer .= $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;offset=$newoffset&amp;keyword=$keyword$extra");
        $footer .= "\" class=\"bLink\">$pagenumber</a>&nbsp;";
      }
    }
  }

  //print the next page link
  if (($offset+SEARCH_ROWS < $num_rows) && $num_pages != 1) {
      $newoffset = $offset + SEARCH_ROWS;
      $footer .= "<a href=\"";
      $footer .= $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;offset=$newoffset&amp;keyword=$keyword$extra");
      $footer .=  "\" class=\"bLink\">NEXT</a>\n";
  }
  else
    $footer .= "&nbsp;";

  $footer .= "<br />";

  // print the first page button
  if ($offset!=0) {
    $newoffset=0;
    $footer .= "<a href=\"". $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;offset=$newoffset&amp;keyword=$keyword$extra");
    $footer .= "\" class=\"bLink\">&lt; &lt; &lt; FIRST PAGE</a>&nbsp;";
  }

  // print the previous X pages button
  if ($offset-(SEARCH_ROWS*SEARCH_PAGES) >= 0) {
    $newoffset=$offset-(SEARCH_ROWS*SEARCH_PAGES);
    $footer .= "<a href=\"". $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;offset=$newoffset&amp;keyword=$keyword$extra");
    $footer .= "\" class=\"bLink\">&lt;&lt; PREV ".SEARCH_PAGES." PAGES</a>&nbsp;";
  }

  // print the next X pages button
  if ($offset+(SEARCH_ROWS*SEARCH_PAGES) < $num_rows) {
    $newoffset=$offset+(SEARCH_ROWS*SEARCH_PAGES);
    $footer .= "<a href=\"". $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;offset=$newoffset&amp;keyword=$keyword$extra");
    $footer .= "\" class=\"bLink\">NEXT ".SEARCH_PAGES." PAGES &gt;&gt;</a>&nbsp;";
  }

  // print the last page button
  if ($offset+SEARCH_ROWS<$num_rows) {
     $newoffset= ($num_pages - 1) * SEARCH_ROWS;
     $footer .= "<a href=\"". $sess->url(SECUREURL . "?page=$modulename/$pagename&amp;offset=$newoffset&amp;keyword=$keyword$extra");
    $footer .= "\" class=\"bLink\">LAST PAGE &gt; &gt; &gt;</a>&nbsp;";
  }

  $footer .= "</div>";

  echo $footer;
}


/****************************************************************************
 *    function: hide_vars
 *  created by: pablo
 * description: Puts the HTTP_POST_VARS or HTTP_GET_VARS in a form as hidden 
 *              fields.  Checks for "login" variable and does not set it.  If
 *              it did we would get stuck in a perpetual loop. Also check for
 *              "error" variable since this would look ugly... 
 *  parameters: none
 *     returns: echoes INPUT form fields
 ****************************************************************************/
function hide_vars() {
   global $vars;

   while (list($key, $value) = each($vars)) {
      if ($key != "login" && $key != "error")
         echo "<input type=\"hidden\" name=\"$key\" value=\"$value\" />\n";
   }
   reset($vars);
}



function load_module($module_name) {

  $db = new ps_DB;
  $q = "SELECT * FROM module WHERE module_name='$module_name'";
  $db->query($q);
 
  while ($db->next_record()) {    
    $module[$module_name]["module_header"]=$db->f("module_header");
    $module[$module_name]["module_footer"]=$db->f("module_footer");
    $module[$module_name][$db->f("language_code_1")]=$db->f("language_file_1");
    $module[$module_name][$db->f("language_code_2")]=$db->f("language_file_2");
    $module[$module_name][$db->f("language_code_3")]=$db->f("language_file_3");
    $module[$module_name][$db->f("language_code_4")]=$db->f("language_file_4");
    $module[$module_name][$db->f("language_code_5")]=$db->f("language_file_5");
    
    return $module;
  }
}


function load_labels($module_name) {
  $db = new ps_DB;
  $q = "SELECT * FROM module";
  $db->query($q);
  
  while ($db->next_record()) {
    $module_name = $db->f("module_name");    
    $label[$module_name][$db->f("language_code_1")]=$db->f("module_label_1");
    $label[$module_name][$db->f("language_code_2")]=$db->f("module_label_2");
    $label[$module_name][$db->f("language_code_3")]=$db->f("module_label_3");
    $label[$module_name][$db->f("language_code_4")]=$db->f("module_label_4");
    $label[$module_name][$db->f("language_code_5")]=$db->f("module_label_5");
  }
  return $label;
}

// Must be called with eval wrapper.
//   class is instantiate after load
function load_class($module, $class) {
  $class_inc = strtoupper($class) . "_INC";
  $file_inc = $class  . ".inc";

  if (!file_exists(PS_BASE."modules/$module/lib/$class.inc")) {
     echo "ERROR Loading Class: $class<br />";
     echo "      Loading Module: $module<br />";
     exit;
  }
  else {
  	include_once("$module/lib/$file_inc");
   } 
  return $load_class;
}


?>
