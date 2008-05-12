<?php
/*
 * The ps_product class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_product.inc,v 1.1.1.1 2004/07/27 14:58:56 pablo Exp $
 *
****************************************************************************
*
* CLASS DESCRIPTION
*
* ps_product
*
* The class is is used to manage the function register.
*
* propeties:
*
* methods:
*
*
*************************************************************************/
class ps_product {
  var $classname = "ps_product";

  /**************************************************************************
  ** name: validate()
  ** created by:
  ** description: Validates fields and uploaded image files.
  ** parameters:
  ** returns:
  ***************************************************************************/  
  function validate(&$d) {
    $valid = true;
    $db = new ps_DB;

    /** Validate Fields **/

    $q = "SELECT * FROM product WHERE product_sku='";
    $q .= $d["product_sku"] . "'";
    $db->query($q);
    if ($db->next_record()&&($db->f("product_id") != $d["product_id"])) {
      $d["error"] .= "ERROR: A Product with that SKU already exists.<br />";
      $valid = false;
    }

    if (!$d["product_sku"]) {
      $d["error"] .= "ERROR: A Product Sku must be entered.<br />";
      $valid = false;
    }
    if (!$d["product_name"]) {
      $d["error"] .= "ERROR: A name must be entered.<br />";
      $valid = false;
    }
    if ($d["product_available_date"]) {
      $date = explode("/",$d["product_available_date"]);
      if (checkdate($date[0],$date[1],$date[2])) {
        $d["product_available_date_timestamp"] = 
               mktime("","","",$date[0],$date[1],$date[2]);
      } else {
        $d["error"] .= "ERROR: Availability date is invalid.<br />";
        $valid = false;
      }
    }

    /** Validate Product Specific Fields **/
    if (!$d["product_parent_id"]) {
      if (!$d["category_id"]) {
        $d["error"] .= "ERROR: A category must be selected.<br />";
        $valid = false;
      } 
    }

    /** Validate Images **/
    if (!validate_image($d,"product_thumb_image","product")) {
      $valid = false;
    }
    if (!validate_image($d,"product_full_image","product")) {
      $valid = false;
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

    /* Check that ps_vendor_id and product_id match */
    if (!$this->check_vendor($d)) {
      $d["error"] = "ERROR: Cannot delete product. Wrong product or vendor." ;
      return false;
    }

    /* Get the image filenames from the database */
    $db = new ps_DB;
    $q  = "SELECT product_thumb_image,product_full_image ";
    $q .= "FROM product ";
    $q .= "WHERE product_id='" . $d["product_id"] . "'";
    $db->query($q);
    $db->next_record();

    /* Validate product_thumb_image */
    $d["product_thumb_image_curr"] = $db->f("product_thumb_image");
    $d["product_thumb_image_name"] = "none";
    if (!validate_image($d,"product_thumb_image","product")) {
      return false;
    }

    /* Validate product_full_image */
    $d["product_full_image_curr"] = $db->f("product_full_image");
    $d["product_full_image_name"] = "none";
    if (!validate_image($d,"product_full_image","product")) {
      return false;
    }
  
    return true;

  }

  /**************************************************************************
  ** name: add()
  ** created by: jep
  ** description: 
  ** parameters:
  ** returns:
  ***************************************************************************/
  function add(&$d) {
    global $ps_vendor_id;
    if (!$this->validate($d)) {
      return false;
    }

    if (!process_images($d)) {
      return false;
    }

    $timestamp = time();
    $db = new ps_DB;

    if ($d["product_publish"] == "") {
      $d["product_publish"] = "N";
    }
    if ($d["product_special"] == "") {
      $d["product_special"] = "N";
    }

    $q  = "INSERT INTO product (vendor_id,product_parent_id,product_sku,";
    $q .= "product_name,product_desc,product_s_desc,";
    $q .= "product_thumb_image,product_full_image,";
    $q .= "product_publish,product_weight,product_weight_uom,";
    $q .= "product_length,product_width,product_height,product_lwh_uom,";
    $q .= "product_url,product_in_stock,";
    $q .= "product_available_date,product_special,product_discount_id,";
    $q .= "cdate,mdate) ";
    $q .= "VALUES ('";
    $q .= $ps_vendor_id . "','" . $d["product_parent_id"] . "','";
    $q .= $d["product_sku"] . "','" . $d["product_name"] . "','";
    $q .= $d["product_desc"] . "','" . $d["product_s_desc"] . "','";
    $q .= $d["product_thumb_image"] . "','";
    $q .= $d["product_full_image"] . "','" . $d["product_publish"] . "','";
    $q .= $d["product_weight"] . "','" . $d["product_weight_uom"] . "','";
    $q .= $d["product_length"] . "','" . $d["product_width"] . "','";
    $q .= $d["product_height"] . "','" . $d["product_lwh_uom"] . "','";
    $q .= $d["product_url"] . "','" . $d["product_in_stock"] . "','";
    $q .= $d["product_available_date_timestamp"] . "','";
    $q .= $d["product_special"] . "','";
    $q .= $d["product_discount_id"] . "','$timestamp','$timestamp')";

    $db->query($q);

    // Get the assigned product_id //
    $q  = "SELECT product_id FROM product ";
    $q .= "WHERE product_sku = '" . $d["product_sku"] . "' ";
    $q .= "AND vendor_id = '" . $ps_vendor_id . "' ";
    $q .= "AND cdate = $timestamp";
    $db->query($q);
    $db->next_record();
    $d["product_id"] = $db->f("product_id");

    // If is Item, add attributes from parent //
    if ($d["product_parent_id"]) {
      $q  = "SELECT attribute_name FROM product_attribute_sku ";
      $q .= "WHERE product_id='" . $d["product_parent_id"] . "' ";
      $q .= "ORDER BY attribute_list,attribute_name";

      $db->query($q);

      $db2 = new ps_DB;
      $i = 0;
      while($db->next_record()) {
        $i++;
        $q2  = "INSERT INTO product_attribute ";
        $q2 .= "(product_id,attribute_name,attribute_value) ";
        $q2 .= "VALUES ('" . $d["product_id"] . "','";
        $q2 .=  $db->f("attribute_name") . "','" . $d["attribute_$i"] . "')";
        $db2->query($q2);
      }
    } 
    /* If is Product, Insert category ids */
    elseif ($d["category_id"]) {
      $q  = "INSERT INTO product_category_xref ";
      $q .= "(category_id,product_id) ";
      $q .= "VALUES ('" . $d["category_id"] . "','";
      $q .=  $d["product_id"] . "')";
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
    global $ps_vendor_id;

    if (!$this->validate($d)) {
      return false;
    }

    if (!process_images($d)) {
      return false;
    }

    $timestamp = time();
    $db = new ps_DB;

    if ($d["product_publish"] == "") {
      $d["product_publish"] = "N";
    }
    if ($d["product_special"] == "") {
      $d["product_special"] = "N";
    }
    
    $q  = "UPDATE product SET ";
    $q .= "product_sku='" . $d["product_sku"] . "',";
    $q .= "product_name='" . $d["product_name"] . "',";
    $q .= "product_s_desc='" . $d["product_s_desc"] . "',";
    $q .= "product_desc='" . $d["product_desc"] . "',";
    $q .= "product_publish='" . $d["product_publish"] . "',";
    $q .= "product_weight='" . $d["product_weight"] . "',";
    $q .= "product_weight_uom='" . $d["product_weight_uom"] . "',";
    $q .= "product_length='" . $d["product_length"] . "',";
    $q .= "product_width='" . $d["product_width"] . "',";
    $q .= "product_height='" . $d["product_height"] . "',";
    $q .= "product_lwh_uom='" . $d["product_lwh_uom"] . "',";
    $q .= "product_url='" . $d["product_url"] . "',";
    $q .= "product_in_stock='" . $d["product_in_stock"] . "',";
    $q .= "product_available_date='";
    $q .= $d["product_available_date_timestamp"] . "',";
    $q .= "product_special='" . $d["product_special"] . "',";
    $q .= "product_discount_id='" . $d["product_discount_id"] . "',";
    $q .= "product_thumb_image='" . $d["product_thumb_image"] . "',";
    $q .= "product_full_image='" . $d["product_full_image"] . "',";
    $q .= "mdate='$timestamp' ";
    $q .= "WHERE product_id='" . $d["product_id"] . "'";
    $q .= "AND vendor_id='" . $ps_vendor_id . "'";

    $db->query($q);

    /* If is Item, update attributes */
    if ($d["product_parent_id"]) {
      $q  = "SELECT attribute_name FROM product_attribute_sku ";
      $q .= "WHERE product_id='" . $d["product_parent_id"] . "' ";
      $q .= "ORDER BY attribute_list,attribute_name";

      $db->query($q);

      $db2 = new ps_DB;
      $i = 0;
      while($db->next_record()) {
        $i++;
        $q2  = "UPDATE product_attribute SET ";
        $q2 .= "attribute_value='" . $d["attribute_$i"] . "' ";
        $q2 .= "WHERE product_id = '" . $d["product_id"] . "' ";
        $q2 .= "AND attribute_name = '" . $db->f("attribute_name") . "' "; 
        $db2->query($q2);
      }
    /* If it is a Product, update Category */
    } elseif ($d["category_id"]) {
      $q  = "UPDATE product_category_xref ";
      $q .= "SET category_id = '" . $d["category_id"] . "' ";
      $q .= "WHERE product_id = '" . $d["product_id"] . "' ";
      $db->query($q);
    }
    return true;
  }

  /**************************************************************************
  ** name: delete()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function delete(&$d) {
    if (!$this->validate_delete($d)) {
      return false;
    }

    $db = new ps_DB;
    $product_id = $d["product_id"];

    /* If is Product */
    if ($this->is_product($product_id)) {
      /* Delete all items first */
      $q  = "SELECT product_id FROM product ";
      $q .= "WHERE product_parent_id='$product_id'";
      $db->query($q);
      while($db->next_record()) {
        $d2["product_id"] = $db->f("product_id");
        if (!$this->delete($d2)) {
          $d["error"] = $d2["error"];
          return false;
        }
      }

      /* Delete attributes */
      $q  = "DELETE FROM product_attribute_sku ";
      $q .= "WHERE product_id='$product_id' ";
      $db->query($q);

      /* Delete categories xref */
      $q  = "DELETE FROM product_category_xref ";
      $q .= "WHERE product_id = '$product_id' ";
      $db->query($q);
    } 
    /* If is Item */
    else {
      /* Delete attribute values */
      $q  = "DELETE FROM product_attribute WHERE product_id='$product_id'";
      $db->query($q);
    }
    /* For both Product and Item */

    /* Delete Image files */
    if (!process_images($d)) {
      return false;
    }

    /* Delete Prices */
    $q  = "DELETE FROM product_price WHERE product_id = '$product_id'";
    $db->query($q);

    /* Delete entry from product table */
    $q  = "DELETE FROM product WHERE product_id = '$product_id'";
    $db->query($q);

    /* If only deleting an item, go to the parent product page after
    ** the deletion. This had to be done here because the product id
    ** of the item to be deleted had to be passed as product_id */
    if ($d["product_parent_id"]) {
      $d["product_id"] = $d["product_parent_id"];
      $d["product_parent_id"] = "";
    }

    return true;
  }

  /**************************************************************************
  ** name: check_vendor()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function check_vendor($d) {
    global $ps_vendor_id;
    $db = new ps_DB;
    $q  = "SELECT vendor_id  FROM product ";
    $q .= "WHERE vendor_id = '$ps_vendor_id' ";
    $q .= "AND product_id = '" . $d["product_id"] . "' ";
    $db->query($q);
    if ($db->next_record()) {
      return true;
    } else {
      return false;
    }
  }


  /**************************************************************************
  ** name: sql()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function sql($product_id) {
    $db = new ps_DB;

    $q  = "SELECT * FROM product WHERE product_id='$product_id' ";

    $db->query($q);
    return $db;
  }
 
  /**************************************************************************
  ** name: items_sql()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function items_sql($product_id) {
    $db = new ps_DB;

    $q  = "SELECT * FROM product ";
    $q .= "WHERE product_parent_id='$product_id' ";
    $q .= "ORDER BY product_name";

    $db->query($q);
    return $db;
  }
 
  /**************************************************************************
  ** name: is_product()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function is_product($product_id) {
    $db = new ps_DB;
 
    $q  = "SELECT product_parent_id FROM product ";
    $q .= "WHERE product_id='$product_id' ";
 
    $db->query($q);
    $db->next_record();
    if ($db->f("product_parent_id") == 0) {
      return true;
    }
    else {
      return false;
    }
  }

  /**************************************************************************
  ** name: attribute_sql()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function attribute_sql($item_id="",$product_id="",$attribute_name="") {
    $db = new ps_DB;
    if ($item_id and $product_id) {
      $q  = "SELECT * FROM product_attribute,product_attribute_sku ";
      $q .= "WHERE product_attribute.product_id = '$item_id' ";
      $q .= "AND product_attribute_sku.product_id ='$product_id' ";
      if ($attribute_name) {
        $q .= "AND product_attribute.attribute_name = $attribute_name ";
      }
      $q .= "AND product_attribute.attribute_name = ";
      $q .=     "product_attribute_sku.attribute_name ";
      $q .= "ORDER BY attribute_list,product_attribute.attribute_name";
    } elseif ($item_id) {
      $q  = "SELECT * FROM product_attribute ";
      $q .= "WHERE product_id = '$item_id' ";
      if ($attribute_name) {
        $q .= "AND attribute_name = $attribute_name ";
      }
    } elseif ($product_id) {
      $q  = "SELECT * FROM product_attribute_sku ";
      $q .= "WHERE product_id ='$product_id' ";
      if ($attribute_name) {
        $q .= "AND product_attribute.attribute_name = $attribute_name ";
      }
      $q .= "ORDER BY attribute_list,attribute_name";
    } else {
      /* Error: no arguments were provided. */
      return 0;
    }
    
    $db->query($q);

    return $db;
  }

  /**************************************************************************
  ** name: get_child_product_ids()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function get_child_product_ids($pid) {
    $db = new ps_DB;
    $q  = "SELECT product_id FROM product ";
    $q .= "WHERE product_parent_id='$pid' ";

    $db->query($q);

    $i = 0;
    while($db->next_record()) {
      $list[$i] = $db->f("product_id");
      $i++;
    }
    return $list;
  }

  /**************************************************************************
  ** name: parent_has_children()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function parent_has_children($pid) {
    $db = new ps_DB;

    $q  = "SELECT * FROM product WHERE product_parent_id='$pid' ";
    $db->query($q);
    if ($db->next_record()) {
      return True;
    }
    else {
      return False;
    }
  }

  /**************************************************************************
  ** name: product_has_attributes()
  ** created by: jep
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function product_has_attributes($pid) {
    $db = new ps_DB;

    $q  = "SELECT * FROM product_attribute_sku WHERE product_id='$pid' ";
    $db->query($q);
    if ($db->next_record()) {
      return True;
    }
    else {
      return False;
    }
  }


  /**************************************************************************
  ** name: get_field()
  ** created by: pablo
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/
  function get_field($product_id, $field_name) {
    $db = new ps_DB;

    $q = "SELECT $field_name FROM product WHERE product_id='$product_id'";
    $db->query($q);
    if ($db->next_record()) {
       return $db->f($field_name);
    }
    else {
       return False;
    }
  }

  /**************************************************************************
  ** name: get_flypage()
  ** created by: pablo
  ** description:  Determines flypage for given product_id by looking at
  **               the product category.  If no flypage is specified for this
  ** 		   category, then the default FLYPAGE (in phpshop.cfg) is 
  **		   returned.
  ** parameters:
  ** returns:
  ***************************************************************************/
  function get_flypage($product_id) {
    $db = new ps_DB;

    $q = "SELECT category.category_flypage FROM category, product_category_xref, product ";
    $q .= "WHERE product.product_id='$product_id' ";
    $q .= "AND product_category_xref.product_id=product.product_id ";
    $q .= "AND product_category_xref.category_id=category.category_id";

    $db->query($q);
    $db->next_record();
    if ($db->f("category_flypage")) {
      return $db->f("category_flypage");
    }
    else {
      return FLYPAGE;
    }
  }


  /**************************************************************************
  ** name: show_image()
  ** created by: pablo
  ** description:  Shows the image send in the $image field.
  **               $args are appended to the IMG tag.
  ** parameters:
  ** returns:
  ***************************************************************************/
  function show_image($image, $args="") {
    
    require_once("vendor/lib/ps_vendor.inc");
    $ps_vendor = new ps_vendor;

    global $ps_vendor_id;
    global $SERVER_PORT;

    if ($SERVER_PORT == "443")
	$url = SECUREURL;
    else
        $url = URL;

    $url .= $ps_vendor->get_field($ps_vendor_id,"vendor_image_path");
    $url .= "product/";
    if (!isset($image) || ($image == "")) {
    	$url .= "noimage.gif";
    } else {
    	$url .= $image;
    }
    echo "<img border=\"0\" src=\"$url\" $args />";
    
    return True;
  }

  /**************************************************************************
   ** name: get_price($product_id)
   ** created by:
   ** description: gets price for a given product Id based on
   **              the shopper group a user belongs to and whether
   **              and item has a price or it must grab it from the 
   **              parent.
   ** parameters:
   ** returns:
   ***************************************************************************/
  function get_price($product_id) {
    global $auth;
    $db = new ps_DB;
    
    // Get the discount value
    $q = "SELECT * from product WHERE product_id='$product_id'";
    $db->query($q);
    if ($db->next_record()) {
      $discount=$db->f("product_discount_id");
    }
	
    // Get the vendor id for this product.
    $q = "SELECT vendor_id FROM product WHERE product_id='$product_id'";
    $db->query($q);
    $db->next_record();
    $vendor_id = $db->f("vendor_id");
    
    // Get the shopper group id for this product and user
    $q = "SELECT shopper_group_id FROM shopper_vendor_xref WHERE ";
    $q .= "user_id='";
    $q .= $auth["user_id"] . "' AND vendor_id='$vendor_id'";
    $db->query($q);
    $db->next_record();
    $shopper_group_id = $db->f("shopper_group_id");
    
    // Get the default shopper group id for this product and user
    $q = "SELECT * FROM shopper_group WHERE ";
    $q .= "vendor_id='$vendor_id' AND ";
    $q .= "shopper_group_name='-default-'";
    $db->query($q);
    $db->next_record();
    $default_shopper_group_id = $db->f("shopper_group_id");
    
    // Get the product_parent_id for this product/item
    $product_parent_id = $this->get_field($product_id, "product_parent_id");
    
    
    // Getting prices
    //
    // If the shopper group has a price then show it, otherwise
    // show the default price.
    $q = "SELECT * from product_price WHERE product_id='$product_id' AND ";
    $q .= "shopper_group_id='$shopper_group_id'";
    $db->query($q);
    if ($db->next_record()) {
      $price_info["product_price"]=sprintf("%.2f",$db->f("product_price")*(100-$discount)/100);
      $price_info["product_currency"]=$db->f("product_currency");
      $price_info["item"]=True;
      return $price_info;
    }
    
    // Get default price
    $q = "SELECT * from product_price WHERE product_id='$product_id' AND ";
    $q .= "shopper_group_id='$default_shopper_group_id'";
    $db->query($q);
    if ($db->next_record()) {
      $price_info["product_price"]=sprintf("%.2f",$db->f("product_price")*(100-$discount)/100);
      $price_info["product_currency"]=$db->f("product_currency");
      $price_info["item"]=True;
      return $price_info;
    }
    
    // Maybe its an item with no price, check again with product_parent_id
    $q = "SELECT * from product_price WHERE product_id='$product_parent_id' AND ";
    $q .= "shopper_group_id='$shopper_group_id'";
    $db->query($q);
    if ($db->next_record()) {
      $price_info["product_price"]=sprintf("%.2f",$db->f("product_price")*(100-$discount)/100);
      $price_info["product_currency"]=$db->f("product_currency");
      return $price_info;
    }
    
    $q = "SELECT * from product_price WHERE product_id='$product_parent_id' AND ";
    $q .= "shopper_group_id='$default_shopper_group_id'";
    $db->query($q);
    if ($db->next_record()) {
      $price_info["product_price"]=sprintf("%.2f",$db->f("product_price")*(100-$discount)/100);
      $price_info["product_currency"]=$db->f("product_currency");
      return $price_info;
    }
    
    // No price found
    return False;
  }

  /**************************************************************************
   ** name: show_snapshot($product_sku)
   ** created by:
   ** description: display a snapshot of a product based on the product sku.
   **              This was written to privde a quick way to display a product on
   **              a side navigation bar.
   ** parameters:
   ** returns:
   ***************************************************************************/
  function show_snapshot($product_sku) {
    global $ps_vendor_id, $sess;
    $db = new ps_DB;

    $q = "SELECT * from product WHERE product_sku='$product_sku'";
    $db->query($q);
    if ($db->next_record()) {
      $price = $this->get_price($db->f("product_id"));
      echo "<b>".$db->f("product_name")."</b>\n";
      echo "<br />\n";
      $url = "?page=".$this->get_flypage($db->f("product_id"));
      if ($db->f("product_parent_id")) {
      $url = "?page=".$this->get_flypage($db->f("product_parent_id"));
      $url .= "&amp;product_id=" . $db->f("product_parent_id");
      } else {
      $url = "?page=".$this->get_flypage($db->f("product_id"));
      $url .= "&amp;product_id=" . $db->f("product_id");
      }
      echo "<a href=\"". $sess->url(URL . $url)."\">";
      $this->show_image($db->f("product_thumb_image"), 
      "width=\"80\" alt=\"".$db->f("product_name")."\"");
      echo "</a>";
      echo "<br />\n";
      if($db->f("product_discount_id")>"0"){
        echo "<font color=\"red\"><strike><b>Was:</b> $";
        printf("%.2f", $price["product_price"]/(100-$db->f("product_discount_id"))*100);
        echo "</strike></font><br />";
      }
      echo "Price:" . $price["product_price"] . " " . $price["product_currency"];
      echo "<br />\n";
      $url = "?page=shop/cart&amp;func=cartAdd&amp;product_id=" .  $db->f("product_id");
      echo "<a href=\"". $sess->url(URL . $url)."\">Add to Cart</a><br />\n";
    }

    else {
      // Product SKU not found
      return False;
    }
    

  }
  
}
?>
