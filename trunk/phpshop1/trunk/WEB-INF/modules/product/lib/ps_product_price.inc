<?php
/*
 * The ps_product_price class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_product_price.inc,v 1.1.1.1 2004/07/27 14:58:59 pablo Exp $
 *
****************************************************************************
*
* CLASS DESCRIPTION
*
* ps_product_price
*
* The class is is used to manage the function register.
*
* propeties:
*
* methods:
*
*
*************************************************************************/
class ps_product_price {
  var $classname = "ps_product_price";

  /**************************************************************************
  ** name: validate()
  ** created by:
  ** description:
  ** parameters:
  ** returns:
  ***************************************************************************/  
  function validate(&$d) {
    $valid = true;
    if (!$d["product_price"]) {
        $d["error"] .= "ERROR: A price must be entered.<br />";
        $valid = false;
    }
    if (!$d["product_currency"]) {
        $d["error"] .= "ERROR: A currency must be entered.<br />";
        $valid = false;
    }
    return $valid;
    return $valid;
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

    $timestamp = time();

    $db = new ps_DB;
    $q  = "INSERT INTO product_price (product_id,shopper_group_id,";
    $q .= "product_price,product_currency,product_price_vdate,";
    $q .= "product_price_edate,cdate,mdate) ";
    $q .= "VALUES ('" . $d["product_id"] . "','" . $d["shopper_group_id"];
    $q .= "','" . $d["product_price"] . "','" . $d["product_currency"] . "','";
    $q .= $d["product_price_vdate"] . "','" . $d["product_price_edate"] . "',";
    $q .= "'$timestamp','$timestamp')";

    $db->query($q);

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

    $timestamp = time();

    $db = new ps_DB;

    $q  = "UPDATE product_price SET ";
    $q .= "shopper_group_id='" . $d["shopper_group_id"] . "',";
    $q .= "product_id='" . $d["product_id"] . "',";
    $q .= "product_price='" . $d["product_price"] . "',";
    $q .= "product_currency='" . $d["product_currency"] . "',";
    $q .= "product_price_vdate='" . $d["product_price_vdate"] . "',";
    $q .= "product_price_edate='" . $d["product_price_edate"] . "',";
    $q .= "mdate='$timestamp' ";
    $q .= "WHERE product_price_id='" . $d["product_price_id"] . "' ";

    $db->query($q);
    
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
    $db = new ps_DB;

    $q  = "DELETE FROM product_price ";
    $q .= "WHERE product_price_id = '" . $d["product_price_id"] . "' ";

    $db->query($q);

    return True;
  }

  

}
?>
