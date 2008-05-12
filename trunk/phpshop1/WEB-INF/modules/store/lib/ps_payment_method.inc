<?php
/*
* The ps_payment_method class
*
* Copyright (c) Edikon Corporation.  All rights reserved.
* Distributed under the phpShop Public License (pSPL) Version 1.0.
*
* $Id: ps_payment_method.inc,v 1.1.1.1 2004/07/27 14:59:48 pablo Exp $
*
*************************************************************************/
class ps_payment_method {
	var $classname = "ps_payment_method";
	
	/**************************************************************************
	** name: validate_add()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	function validate_add(&$d) {
		
		if (!$d["payment_method_name"]) {
			$d["error"] = "Please enter a payment method name.";
			return False;
		}
		if (!$d["payment_method_code"]) {
			$d["error"] = "Please enter a payment method code.";
			return False;
		}
		return true;
	}
	
	/**************************************************************************
	** name: validate_delete()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	function validate_delete(&$d) {
		
		if (!$d["payment_method_id"]) {
			$d["error"] = "Please select a payment method to delete.";
			return False;
		}
		
		return True;
	}
	
	/**************************************************************************
	** name: validate_update()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	function validate_update(&$d) {
		
		if (!$d["payment_method_code"]) {
			$d["error"] = "Please enter a payment method code.";
			return False;
		}
		
		if (!$d["payment_method_name"]) {
			$d["error"] = "Please enter a payment method name.";
			return False;
		}
		
		if (!$d["payment_method_id"]) {
			$d["error"] = "Please select a payment method to update.";
			return False;
		}
		
		return True;
	}
	
	/**************************************************************************
	* name: add()
	* created by: pablo
	* description:
	* parameters:
	* returns:
	**************************************************************************/
	function add(&$d) {
		global $ps_vendor_id;
		$db = new ps_DB;
		
		if (!$this->validate_add($d)) {
			return False;
		}
		
		if (!$d["shopper_group_id"]) {
			$q =  "SELECT * from shopper_group WHERE ";
			$q .= "shopper_group_name='-default-'";
			$q .= "AND vendor_id='$ps_vendor_id'";
			$db->query($q);
			$db->next_record();
			$d["shopper_group_id"] = $db->f("shopper_group_id");
		}
		
		$q = "INSERT INTO payment_method (vendor_id, ";
		$q .= "payment_method_name, shopper_group_id, ";
		$q .= "payment_method_discount, payment_method_code, enable_processor, list_order) VALUES (";
		$q .= "'$ps_vendor_id',";
		$q .= "'" . $d["payment_method_name"] . "', ";
		$q .= "'" . $d["shopper_group_id"] . "', ";
		$q .= "'" . $d["payment_method_discount"] . "',";
		$q .= "'" . $d["payment_method_code"] . "',";
		$q .= "'" . $d["enable_processor"] . "',";
		$q .= "'" . $d["list_order"] . "')";
		
		$db->query($q);
		
		return True;
		
	}
	
	/**************************************************************************
	** name: update()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	function update(&$d) {
		global $ps_vendor_id;
		
		$db = new ps_DB;
		
		if (!$this->validate_update($d)) {
			return False;
		}
		
		$q = "UPDATE payment_method SET ";
		$q .= "payment_method_name='" . $d["payment_method_name"] ."',";
		$q .= "shopper_group_id='" . $d["shopper_group_id"] . "',";
		$q .= "payment_method_discount='" . $d["payment_method_discount"] . "', ";
		$q .= "payment_method_code='" . $d["payment_method_code"] . "', ";
		$q .= "enable_processor='" . $d["enable_processor"] . "', ";
		$q .= "list_order='" . $d["list_order"] . "' ";
		$q .= "WHERE vendor_id='$ps_vendor_id' AND ";
		$q .= "payment_method_id='" . $d["payment_method_id"] . "'";
		
		$db->query($q);
		
		return True;
	}
	
	/**************************************************************************
	** name: delete()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	function delete(&$d) {
		global $ps_vendor_id;
		$db = new ps_DB;
		
		if (!$this->validate_delete($d)) {
			return False;
		}
		
		$q = "DELETE from payment_method WHERE payment_method_id='";
		$q .= $d["payment_method_id"] . "' AND ";
		$q .= "vendor_id='$ps_vendor_id'";
		
		$db->query($q);
		
		return True;
	}
	
	
	/**************************************************************************
	** name: list_method()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	function list_method($payment_method_id) {
		global $ps_vendor_id;
		$db = new ps_DB;
		
		require_once("shopper/lib/ps_shopper_group.inc");
		$ps_shopper_group = new ps_shopper_group;
		
		
		$q =  "SELECT * from shopper_group WHERE ";
		$q .= "shopper_group_name='-default-'";
		$q .= "AND vendor_id='$ps_vendor_id'";
		$db->query($q);
		$db->next_record();
		$default_shopper_group_id = $db->f("shopper_group_id");
		
		
		$q = "SELECT * from payment_method WHERE ";
		$q .= "vendor_id='$ps_vendor_id' AND ";
		$q .= "shopper_group_id='$default_shopper_group_id' ";
		if ($ps_shopper_group->get_id() != $default_shopper_group_id)
		$q .= "OR shopper_group_id='".$ps_shopper_group->get_id()."' ";
		$q .= "ORDER BY list_order";
		$db->query($q);
		
		// Start drop down list
		echo "<select name=\"payment_method_id\">\n";
		echo "<option value=\"0\">Please Select</option>\n";
		while ($db->next_record()) {
			echo "<option value=\"" . $db->f("payment_method_id") . "\" ";
			if ($db->f("payment_method_id") == $payment_method_id)
			echo "selected=\"selected\">\n";
			else
			echo ">\n";
			echo $db->f("payment_method_name") . "</option>\n";
		}
		
		// End drop down list
		echo "</select>\n";
	}
	
	/**************************************************************************
	** name: validate_payment()
	** created by:
	** description:
	** parameters:
	** returns:
	***************************************************************************/
	/**************************************************************************
	** This code was adapted from validateCC() by Brett Error.
	**
	** name: validate_cc()
	** created by: gday
	** description:  Validates credit card number format.  If $type is passed,
	**               the function ensures that $ccnum follows the proper format
	**               for that credit card type.  Valid $types are unknown -
	**               type not known or not supported (default), mc -
	**               Mastercard, visa - Visa, amex - American Express, and
	**               discover - Discover.  The function will also do a
	**               mod 10 check to verify that it could be a valid
	**               credit card number.
	** parameters: $payment_method_id - PK of payment_method table
	**             $ccnum - credit card number to validate
	**             $type - credit card type
	** returns:  True - credit card number is in a valid format
	**          False - credit card number is not in a valid format
	***************************************************************************/
	function validate_payment($payment_method_id, $ccnum) {
		global $sess;
		$db = new ps_DB;
		
		$q = "SELECT payment_method_code FROM payment_method WHERE ";
		$q .= "payment_method_id='$payment_method_id'";
		$db->query($q);
		$db->next_record();
		
		//Clean up input
		$type = strtolower($db->f("payment_method_code"));
		$ccnum = ereg_replace( '[-[:space:]]',  '',$ccnum);
		
		//Do type specific checks
		
		if ($type ==  'mc'){
			if (strlen($ccnum) != 16 || !ereg( '^5[1-5]', $ccnum)) {
				return(false);
			}
		}
		elseif ($type ==  'visa'){
			if ((strlen($ccnum) != 13 && strlen($ccnum) != 16) || substr($ccnum, 0, 1) !=  '4') {
				return(false);
			}
		}
		elseif ($type ==  'amex'){
			if (strlen($ccnum) != 15 || !ereg( '^3[47]', $ccnum)) {
				return(false);
			}
		}
		elseif ($type ==  'discover'){
			if (strlen($ccnum) != 16 || substr($ccnum, 0, 4) !=  '6011') {
				return(false);
			}
		}
		elseif ($type == '0') {
			return False;
		}
		else
		return True;
		
		// Start MOD 10 checks
		
		$dig = $this->to_char_array($ccnum);
		$numdig = sizeof ($dig);
		$j = 0;
		for ($i=($numdig-2); $i>=0; $i-=2){
			$dbl[$j] = $dig[$i] * 2;
			$j++;
		}
		$dblsz = sizeof($dbl);
		$validate =0;
		for ($i=0;$i<$dblsz;$i++){
			$add = $this->to_char_array($dbl[$i]);
			for ($j=0;$j<sizeof($add);$j++){
				$validate += $add[$j];
			}
			$add =  '';
		}
		for ($i=($numdig-1); $i>=0; $i-=2){
			$validate += $dig[$i];
		}
		if (substr($validate, -1, 1) ==  '0') {
			return(true);
		}
		else {
			return(false);
		} // validate_cc
	}
	/****************************************************************************
	* Copyright Information:
	*
	* This code was adapted from validateCC() by Brett Error.
	*
	* Credit card validation routine
	* May 15, 1998
	* By Brett Error
	* brett@interwebdesign.com
	*****************************************************************************/
	function to_char_array($input) {
		
		$len = strlen($input);
		
		for ($j=0;$j<$len;$j++){
			$char[$j] = substr($input, $j, 1);
		}
		return ($char);
	} // to_char_array()
	
	
	function get_field($payment_method_id, $field_name) {
		
		$db = new ps_DB;
		
		$q = "SELECT $field_name FROM payment_method WHERE payment_method_id='$payment_method_id'";
		$db->query($q);
		$db->next_record();
		return $db->f($field_name);
	}
	
	
}
?>
