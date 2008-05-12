<?php
/*
 * The ps_product_attribute class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_product_attribute.inc,v 1.1.1.1 2004/07/27 14:58:58 pablo Exp $
 *
****************************************************************************
*
* CLASS DESCRIPTION
*
* ps_product_attribute
*
* The class is is used to manage the function register.
*
* propeties:
*
* methods:
*
*
*************************************************************************/
class ps_product_attribute {
  var $classname = "ps_product_attribute";

  /**************************************************************************
  ** name: validate()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  
  function validate(&$d) {
    $valid = true;
    if ($d["attribute_name"] == "") {
        $d["error"] .= "An attribute name must be entered.<br />";
        $valid = false;
    }
    elseif ($d["old_attribute_name"] != $d["attribute_name"]) {
      $db = new ps_DB;
      $q  = "SELECT attribute_name FROM product_attribute_sku ";
      $q .= "WHERE attribute_name = '" . $d["attribute_name"] . "'";
      $q .= "AND product_id = '" . $d["product_id"] . "'";
      $db->query($q);
      if ($db->next_record()) {
        $d["error"] .= "A unique attribute name must be entered.<br />";
        $valid = false;                                                         
      }
    }
    return $valid;
  }
  
  /**************************************************************************
  ** name: validate_delete()
  ** created by:
  ** description: 
  ** parameters:
  ** returns:
  ***************************************************************************/  
  function validate_delete(&$d) {
    require_once("product/lib/ps_product.inc");
    $ps_product = new ps_product;

    $db = new ps_DB;
    $q  = "SELECT * FROM product_attribute_sku ";
    $q .= "WHERE product_id = '" . $d["product_id"] . "' ";
    $db->query($q);
    if ($db->num_rows() == 1 and 
             $ps_product->parent_has_children($d["product_id"])) {
      $d["error"] .= "ERROR: Cannot delete last attribute while product has ";
      $d["error"] .= "Items.<br />Delete all Items first.<br />";
      return false;                                                         
    }
  
    return true;

  }
  /**************************************************************************
  ** name: add()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  
  function add(&$d) {
    if (!$this->validate($d)) {
      return false; 
    }

    $db = new ps_DB;
    $q  = "INSERT INTO product_attribute_sku (product_id,attribute_name,";
    $q .= "attribute_list) VALUES ('" . $d["product_id"] . "','";
    $q .= $d["attribute_name"] . "','" . $d["attribute_list"] . "')";

    $db->query($q);

    /** Insert new Attribute Name into child table **/
    $ps_product = new ps_product;
    $child_pid = $ps_product->get_child_product_ids($d["product_id"]);

    for($i = 0; $i < count($child_pid); $i++) {
      $q  = "INSERT INTO product_attribute (product_id,attribute_name) ";
      $q .= "VALUES ('$child_pid[$i]','" . $d["attribute_name"] . "')";
      $db->query($q);
    }

    return true;
  }

  /**************************************************************************
  ** name: update()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function update(&$d) {
    if (!$this->validate($d)) {
      return false;
    }

    $db = new ps_DB;

    $q  = "UPDATE product_attribute_sku SET ";
    $q .= "attribute_name='" . $d["attribute_name"] . "',";
    $q .= "attribute_list='" . $d["attribute_list"] . "' ";
    $q .= "WHERE product_id='" . $d["product_id"] . "' ";
    $q .= "AND attribute_name='" . $d["old_attribute_name"] . "' ";

    $db->query($q);
    
    if ($d["old_attribute_name"] != $d["attribute_name"]) {
      $ps_product = new ps_product;
      $child_pid = $ps_product->get_child_product_ids($d["product_id"]);

      for($i = 0; $i < count($child_pid); $i++) {
        $q  = "UPDATE product_attribute SET ";
        $q .= "attribute_name='" . $d["attribute_name"] . "' ";
        $q .= "WHERE product_id='$child_pid[$i]' ";
        $q .= "AND attribute_name='" . $d["old_attribute_name"] . "' ";
        $db->query($q);
      }
    }
    return true;
  }

  /**************************************************************************
  ** name: delete()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  
  function delete(&$d) {
    if (!$this->validate_delete($d)) {
      return false;
    }                                                                           

 
    $db = new ps_DB;

    $q  = "DELETE FROM product_attribute_sku ";
    $q .= "WHERE product_id = '" . $d["product_id"] . "' ";
    $q .= "AND attribute_name = '" . $d["attribute_name"] . "'";

    $db->query($q);
    $ps_product = new ps_product;
    $child_pid = $ps_product->get_child_product_ids($d["product_id"]);

    for($i = 0; $i < count($child_pid); $i++) {
      $q  = "DELETE FROM product_attribute ";
      $q .= "WHERE product_id = '$child_pid[$i]' ";
      $q .= "AND attribute_name = '" . $d["attribute_name"] . "' ";
      $db->query($q);
    }
    return True;
  }

  /**************************************************************************
   ** name: list_attribute($product_id, $attribute_name)
   ** created by: pablo
   ** description: 
   ** parameters: product_id (may be a product or item)
   ** returns:
   ***************************************************************************/
  function list_attribute($product_id) {

    require_once("product/lib/ps_product.inc");
    $ps_product = new ps_product;

    $db = new ps_DB;    
    $db_sku = new ps_DB;
    $db_item = new ps_DB;



    $html = "<select name=\"product_id\">\n";
    // Get list of children
    $q = "SELECT * from product WHERE product_parent_id='$product_id'";
    $db->query($q);
    while ($db->next_record()) {
      $has_attributes = True;

      // Get item price
      $price = $ps_product->get_price($db->f("product_id"));
      
      // Start row for this child
      $html .= "<option value=\"";
      $html .= $db->f("product_id") . "\">";	
      $html .= $db->f("product_name") . " - ";	
      
      // For each child get attribute values by looping through attribute list
      $q = "SELECT attribute_name FROM ";
      $q .= "product_attribute_sku ";
      $q .= "WHERE product_id='$product_id' ";
      $q .= "ORDER BY attribute_list ASC";
      $db_sku->query($q);
      while ($db_sku->next_record()) {
	$q = "SELECT attribute_name, ";
	$q .= "attribute_value, product_id ";
	$q .= "FROM product_attribute WHERE ";
	$q .= "product_id='" . $db->f("product_id") . "' AND ";
	$q .= "attribute_name='" . $db_sku->f("attribute_name") . "'";
	$db_item->query($q);
	while ($db_item->next_record()) {
	  $html .= $db_item->f("attribute_name") . " ";
	  $html .= "(" . $db_item->f("attribute_value") . ") - ";
	}
      }
      // Attributes for this item are done.
      $html .= $price["product_price"] . $price["product_currency"];
      $html .= "</option>\n";
    }
    $html .= "</select>\n";

    // Check to see if product has attributes and show generated HTML.  
    // Otherwise, insert hidden product_id field
    if ($has_attributes) {
      echo $html;
    }
    else {
      echo "<input type=\"hidden\" name=\"product_id\" value=\"$product_id\" />\n";
    }
  }
  
}
?>
