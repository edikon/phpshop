<?php
// Copyright (C) 1996-2004 Edikon Corporation. All rights reserved.
//
// This source file is part of phpShop(R).
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

// $Id: index.php,v 1.1.1.1 2004/07/27 14:58:07 pablo Exp $

// EDIT
define('PS_BASE', './WEB-INF/');

// DO NOT EDIT FROM HERE ON
//**************************************************

// Set error reporting level
error_reporting(E_ALL ^ E_NOTICE);

// force register_globals off
ini_set("register_globals", 0);

// check if magic quotes is enabled, die if not
/*
if (!get_magic_quotes_gpc()) {
	die("You must enable magic_quotes_gpc in php.ini in order to run phpShop. Read <a href=\"http://www.php.net/manual/en/ref.info.php#ini.magic-quotes-gpc\"> the docs</a>.");
}
*/

// Set global path
ini_set("include_path", ".".PATH_SEPARATOR.PS_BASE.PATH_SEPARATOR.PS_BASE."modules"); 

// define webroot so that image uploads work
define("WEBROOT",dirname($_SERVER['SCRIPT_FILENAME']));

// left for backwards compatibility
define("MODROOT",PS_BASE."modules/"); 

// Compatibility patch to be able to leave Register_globals = off
// &&
// XSS fixes
if (function_exists ("import_request_variables") &&
  False == ini_get('register_globals')) {
  import_request_variables ("CGP","");  // php >=4.1
  $HTTP_GET_VARS = $_GET;
  $HTTP_POST_VARS = $_POST;
  $HTTP_COOKIE_VARS = $_COOKIE;
  $PHP_SELF = $_SERVER["PHP_SELF"];
  $SERVER_NAME = $_SERVER["SERVER_NAME"];
  $REMOTE_ADDR = $_SERVER["REMOTE_ADDR"];
  $HTTP_X_FORWARDED_FOR = $_SERVER["HTTP_X_FORWARDED_FOR"];
  $HTTP_VIA = $_SERVER["HTTP_VIA"];
  foreach($_FILES as $k=>$v) {
    $$k = $v['tmp_name'];
    $k_name = $k . "_name";
    $$k_name = $v['name'];
    $k_size = $k . "_size";
    $$k_size = $v['size'];
  }
} else {
  //http://de.php.net/manual/de/function.import-request-variables.php
  //if you're stuck using a pre-4.10 version of php
  extract($HTTP_GET_VARS, EXTR_PREFIX_ALL, "");
  extract($HTTP_POST_VARS, EXTR_PREFIX_ALL, "");
}

// Load Required Files
require(PS_BASE. "etc/config.php");
require(PS_BASE . "db/db_mysql.inc");
require("admin/lib/ps_main.inc");
require("admin/lib/ps_include.inc");

// Timer Start
if (DEBUG) {
  $start = utime();
}

// some input validation for offset
if (!empty($_REQUEST['offset'])) {
  if (is_string($_REQUEST['offset']) and $_REQUEST['offset'] == (string)(int) $_REQUEST['offset']) {
   }
   else die('Please provide an permitted value for offset');
}

// basic SQL inject detection
$my_insecure_array = array('keyword' => $_REQUEST['keyword'],
               'category_id' => $_REQUEST['category_id'],
               'product_id' => $_REQUEST['product_id'],
               'user_id' => $_REQUEST['user_id'],
               'user_info_id' => $_REQUEST['user_info_id'],
               'page' => $_REQUEST['page'],
               'func' => $_REQUEST['func']);
               
while(list($key,$value)=each($my_insecure_array)) {
   if (stristr($value,'FROM ') ||
       stristr($value,'UPDATE ') ||
       stristr($value,'WHERE ') ||
       stristr($value,'ALTER ')  ||
       stristr($value,'SELECT ')  ||
       stristr($value,'SHUTDOWN ') ||
       stristr($value,'CREATE ') ||
       stristr($value,'DROP ') ||
       stristr($value,'DELETE FROM') ||
       stristr($value,'script') ||
       stristr($value,'<>') ||
       stristr($value,'=') ||
       stristr($value,'SET ')) 
           die('Please provide a permitted value for '.$key);
}

// Load module definitions
$module = array();
$label = array();

// Instantiate db and session class
$db = new ps_DB;
$sess = new ps_session;
$perm = new ps_perm;
$vars = array();

// In case someone tries to be sneaky
$run_dir=0;
$run_func=0;

// Set default language as specified in phpshop.cfg
if (!isset($lang)) {
  $lang = LANGUAGE;
  $sess->register("lang");
}	

// Save current page call
$this_page=$page;

// Register previous page
if (!isset($last_page)) {
  $sess->register("last_page");
}
// Register the cart
if (!isset($cart)) {
  $cart = array();
  $cart["idx"] = 0;
  $sess->register("cart");
}
// Register the auth array
if (!isset($auth)) {
  $auth = array();
  $sess->register("auth");
}

// This is what we work with.
$vars = $_REQUEST;

/* start fixing security hole */
function harden_parse($vars){
  $vars2=trim($vars);
  $vars2=strip_tags($vars2);
  $vars2=str_replace("#","&#35;",$vars2);
  $vars2=str_replace("(","&#40;",$vars2);
  $vars2=str_replace(")","&#41;",$vars2);
  $vars2=str_replace("[","&#91;",$vars2);
  $vars2=str_replace("]","&#93;",$vars2);
  $vars2=str_replace("%","&#37;",$vars2);
  return $vars2;
}
if (count($vars) && $auth["perms"]!="admin" && $auth["perms"]!="storeadmin"){
  while (list($key, $value) = each ($vars)) {
    if (is_array($value)){
      while (list($keyA, $valueA) = each ($value)) {
        $varsA[$keyA]=harden_parse($valueA);
      } $vars2[$key] = $varsA; unset ($varsA);
    }
    else { $vars2[$key]=harden_parse($value); }
    if ($HTTP_POST_VARS[$key]){ $HTTP_POST_VARS[$key]=$vars2[$key]; }
    if ($HTTP_GET_VARS[$key]){ $HTTP_GET_VARS[$key]=$vars2[$key]; }
    $$key = harden_parse($vars2[$key]);
  }
  $vars = $vars2;
  $QUERY_STRING = harden_parse($QUERY_STRING);
}
if ($page=="shop/flypage" and !$product_id){ $page="shop/browse"; }
unset($vars2);
/* end fixing security hole */

// Get Function Permissions
// Sets $run_func if func is registered and have permission
// Displays error if function is not registered
if ($func) {
  $func_list = $ps_function->get_function($func);
  if ($func_list) {
    if ($perm->check($func_list["perms"])) {
      $run_func = 1;
      $func_perms = $func_list["perms"];
      $func_class = $func_list["class"];
      $func_method = $func_list["method"];      
    }
    else {
      $error_type = "Insufficient Access Rights";
      $error = "You do not have permission to execute $func.";
      $page = ERRORPAGE;          
      $run_func = 0;
    }
  }
  else {
    $error_type = "Function Not Registered";
    $error = "$func is not a valid phpShop function.";
    $page = ERRORPAGE;    
    $run_func = 0;
  }
}

// Get Page/Directory Permissions
// Sets $run_dir if we can run it
// Displays error if directory is not registered, 
// no permission, or file does not exist
if (!$page) {
  $page = HOMEPAGE;
}

$modulename = dirname("$page");
$pagename = basename("$page");

if (empty($modulename)) {
  $modulename=dirname(HOMEPAGE);	
  $pagename = basename(HOMEPAGE);
}

$dir_list = $ps_module->get_dir($modulename);
if ($dir_list) {
  if ($perm->check($dir_list["perms"])) {
    if (!file_exists(PS_BASE."modules/$modulename/html/$pagename.ihtml")) {
      $error_type = "Page Does Not Exist";
      $error =  "Given filename does not exist. Cannot find file:<br />";
      $error .= $modulename."/html/".$pagename.".ihtml";
      $page = ERRORPAGE;
    }
  }
  else {
    if ($func != "userLogin") {
      unset($error);
      $page = $last_page;
      $vars["login"]=1;
    }
  }

  // Load MODULE
  $module = load_module($modulename);
  require("$modulename/lib/ps_include.inc");
  $label = load_labels($modulename);  
}
else {
  $error_type = "Module Not Registered";
  $error = "$modulename is not a valid phpShop module.";
  $page = ERRORPAGE;
}

// Run the function if we have permission
if ($run_func) {

  $q = "SELECT module.module_name FROM module,function WHERE ";
  $q .= "module.module_id=function.module_id AND ";
  $q .= "function.function_method='$func_method' AND ";
  $q .= "function.function_class='$func_class'";
  $db->query($q);
  $db->next_record();

  // Load class definition file and run function
  require_once($db->f("module_name")."/lib/$func_class.inc");
  $$func_class = new $func_class;
  $ok = $$func_class->{$func_method}($vars);
  
  // for debug
  $cmd = $func_class.'->'.$func_method.'()';
  
  if (!$ok) {
    if ($vars["login"] == "1") {
      $error = $vars["error"];
      $vars["login"]=1;
    }
    else {
      $no_last=1;
      $page = $last_page;
      $error = $vars["error"];
    }
  }
  else {
    $no_last = 0;
    unset($error);
    $page = $vars["page"];
  }
}

// LOAD PAGE

// If this is a login, then load the approprate module information based on wher
// the login page is.
if ($vars["login"] == "1" || $page==LOGINPAGE || !$perm->check($dir_list["perms"])) {
  $last_page = $this_page;
  $page = LOGINPAGE;
  $modulename = dirname($page);
  $module = load_module($modulename);
  require("$modulename/lib/ps_include.inc");
  $label = load_labels($modulename);
}

if (!$no_last) {
  $last_page = $this_page;
}
if (!$page) {
  $page = HOMEPAGE;
}
// Show the page!
$modulename = dirname($page);
$pagename = basename($page) . ".ihtml";

// Load global file
require("templates/global.inc");

// Load language file for this module

if (file_exists(MODROOT."$modulename/lib/lang_$lang.inc")) {
  include(MODROOT."$modulename/lib/lang_$lang.inc");
}
else {
  //Default to english if not set.
  include(MODROOT."$modulename/lib/lang_eng.inc");
}

// Load Header
if ($module[$modulename]["module_header"] && $print!="1") {
  include("templates/".$module[$modulename]["module_header"]);
}
// Load PAGE
include("$modulename/html/$pagename");

// Load footer
if ($module[$modulename]["module_footer"] && $print!="1") {
  include("templates/".$module[$modulename]["module_footer"]);
}

// Save the session variables for the next run
$sess->save();

// Set debug option on/off
if (DEBUG) {
  $end = utime();
  $runtime = $end - $start;
  $messages = dirname(DEBUGPAGE);
  $pagename = basename(DEBUGPAGE) . ".ihtml";  
  include("$messages/html/$pagename");
}
?>
