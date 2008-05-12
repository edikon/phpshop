<?php
/*
 * ps_html Class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_html.inc,v 1.1.1.1 2004/07/27 14:58:33 pablo Exp $
 *
 */

class ps_html {
  var $classname = "ps_html";

  /**************************************************************************
  ** name: dropdown_display()
  ** created by: gday
  ** description:  Print an HTML dropdown box named $name using $arr to
  **               load the drop down.  If $value is in $arr, then $value
  **               will be the selected option in the dropdown.
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function dropdown_display($name, $value, $arr) {

      echo "<select name=\"$name\" size=\"1\">\n";

      while (list($key, $val) = each($arr)) {
         if(strcmp($value, $key) == 0) {
            echo "<option value=\"$key\" selected=\"selected\">$val\n";
         }
         else {
            echo "<option value=\"$key\">$val</option>\n";
         }
      }

      echo "</select>\n";

      return True;
   }


  /**************************************************************************
  ** name: list_month($list_name)
  ** created by: pfmartin
  ** description:  Print an HTML dropdown box for the credit cards 
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_month($list_name) {
       $list = array("MONTH",
                    "1" => "January",
                    "2" => "February",
                    "3" => "March",
                    "4" => "April",
                    "5" => "May",
                    "6" => "June",
                    "7" => "July",
                    "8" => "August",
                    "9" => "September",
                    "10" => "October",
                    "11" => "November",
                    "12" => "December");
       $this->dropdown_display($list_name, "", $list);
       return 1;
   }


  /**************************************************************************
  ** name: list_year($list_name)
  ** created by: pfmartin
  ** description:  Print an HTML dropdown box for the credit cards
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_year($list_name) {
        $year = date("Y",time()); 
        $arr = array(); 
        for ($i=0; $i < 7; $i++) { 
          $arr[$year] = $year++; 
        } 
       $this->dropdown_display($list_name, "", $arr);
       return 1;
   }


  /**************************************************************************
  ** name: list_weight_uom($list_name)
  ** created by: pfmartin
  ** description:  Print an HTML dropdown box for the weight uom's
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_weight_uom($list_name) {
       $list = array("-",
                    "LBS" => "Pounds",
                    "KGS" => "Kilograms",
                    "G" => "Grams");
       $this->dropdown_display($list_name, "", $list);
       return 1;
   }



  /**************************************************************************
  ** name: list_country($list_name)
  ** created by: pfmartin
  ** description:  Print an HTML dropdown box for the countries
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_country($list_name, $value="") {
     $db = new ps_DB;
     
     $q = "SELECT * from country ORDER BY country_name ASC";
     $db->query($q);
     echo "<select name=\"$list_name\">\n";
     echo "<option value=\"\"> - </option>\n";
     while ($db->next_record()) {
       echo "<option value=\"" . $db->f("country_3_code") . "\"";
	if ($value == $db->f("country_3_code"))
		echo " selected=\"selected\"";
	echo ">" . $db->f("country_name") . "</option>\n";
     }
     echo "</select>\n";
     return True;
   }
   
  /**************************************************************************
  ** name: list_currency($list_name, $value)
  ** created by: pfmartin
  ** description:  Print an HTML dropdown box for the countries
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_currency($list_name, $value="") {
     $db = new ps_DB;
     
     $q = "SELECT * from currency ORDER BY currency_name ASC";
     $db->query($q);
     echo "<select name=\"$list_name\">\n";
     echo "<option value=\"\"> - </option>\n";
     while ($db->next_record()) {
       echo "<option value=\"" . $db->f("currency_code") . "\"";
    if ($value == $db->f("currency_code"))
		echo " selected=\"selected\"";
	echo ">" . $db->f("currency_name") . "</option>\n";
     }
     echo "</select>\n";
     return True;
   }

  /**************************************************************************
  ** name: list_language($list_name, $value)
  ** created by: pfmartin
  ** description:  Print an HTML dropdown box for the countries
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_language($list_name, $value="") {
     $db = new ps_DB;
     
     $q = "SELECT * from language ORDER BY language_name ASC";
     $db->query($q);
     echo "<select name=\"$list_name\">\n";
     echo "<option value=\"\"> - </option>\n";
     while ($db->next_record()) {
       echo "<option value=\"" . $db->f("language_code") . "\"";
	if ($value == $db->f("language_code"))
		echo " selected=\"selected\"";
	echo ">" . $db->f("language_name") . " - (" . $db->f("language_code") . ")</option>\n";
     }
     echo "</select>\n";
     return True;
   }
}
 
?>
