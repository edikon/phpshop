<?php
// +----------------------------------------------------------------------+
// | Advanced Cart                                                        |
// | Copyright (c) 2001 BrettODonnell.com. All rights reserved.           |
// +----------------------------------------------------------------------+
// | The contents of this file are subject to the Mozilla Public License  |
// | Version 1.1 (the "License"); you may not use this file except in     |
// | compliance with the License. You may obtain a copy of the License at |
// | http://www.mozilla.org/MPL/                                          |
// |                                                                      |
// | Software distributed under the License is distributed on an "AS IS"  |
// | basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See  |
// | the License for the specific language governing rights and           |
// | limitations under the License.                                       |
// |                                                                      |
// | The Original Code is Advanced Cart and contains portions of          |
// | phpShop.                                                             |
// |                                                                      |
// | The Initial Developer of the Original phpShop Code is Edikon Corp.   |
// | Portions created by Edikon Corp. are Copyright (C) 2001 Edikon Corp. |
// | All Rights Reserved.                                                 |
// |                                                                      |
// | The Initial Developer of the Advanced Cart Code is                   |
// | BrettODonnell.com. Portions created by BrettODonnell.com are         |
// | Copyright (C) 2001 BrettODonnell.com. All Rights Reserved.           |
// +----------------------------------------------------------------------+

/*
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_cart.inc,v 1.1.1.1 2004/07/27 14:59:39 pablo Exp $
 *
*
* CLASS DESCRIPTION
*
* ps_cart
*
* The cart class is used to store products and carry them through the user's
* session in the store.
* propeties:
*       item() - an array of items
*       idx - the current count of items in the cart
*       error - the error message returned by validation if any
* methods:
*       add()
*       update()
*       delete()
*
*
*************************************************************************/
class ps_cart {
  var $classname="ps_cart";


  /**************************************************************************
  ** name: add()
  ** created by: brett odonnell
  ** description: updates the quantity of all product_ids in the cart
  ** parameters:
  ** returns:
  ***************************************************************************/
  function add(&$d) {
    global $cart;
    $db = new ps_DB;

    $return=True;
    $d["error"]="";

    if(is_array($d["products"])){
      for ($i=0;$i<count($d["products"]);$i++) {
        if(!$this->add_item($d["products"][$i]["product_id"], $d["products"][$i]["quantity"])){
          $d["error"] = $this->error;
          $return=False;
        }
      }
    }
    else{
      if(!$this->add_item($d["product_id"], $d["quantity"])){
        $d["error"] = $this->error;
        $return=False;
      }
    }

    return $return;
  }

  /**************************************************************************
  ** name: add_item()
  ** created by: brett odonnell
  ** description: adds an item to the shopping cart
  ** parameters:
  ** returns:
  ***************************************************************************/
  function add_item($product_id,$quantity) {
    global $cart;

    $return=True;
    $db = new ps_DB;

    $this->error ="";

    if(!$quantity){
      $quantity=1;
    }

    // Check for negative quantity
    if ($quantity < 1) {
        $this->error = "(qty:$quantity) - To delete an item please click the 'Delete' link.";
        return False;
    }

    if (!ereg("^[0-9]*$", $quantity)) {
      $this->error .= "Please enter a valid quantity for this item.<br />";
      $return=False;
    }

    //If the product publish is No then it will not display the item even if you
    //enter or change the product_id in the URL bar.
    $q = "SELECT product_name,product_publish FROM product WHERE product_id='$product_id'";
    $db->query($q);
    $db->next_record();
    // if the product isn't publishable, don't allow the add or update
    if ('N' == $db->f("product_publish") ) {
              // set your "not available" error message here
             $d["error"] = "We're sorry but ".$db->f("product_name")." is not available at this time.";
             // when in ps_cart->update, you probably want to uncomment
            // the line below to remove the product from the cart
            //$this->delete($d);
             return False;
    } //end if prodcut_publish


    // Check to see if checking stock quantity
    if (CHECK_STOCK) {
      $q = "SELECT product_in_stock ";
      $q .= "FROM product where product_id=";
      $q .= $product_id;
      $db->query($q);
      $db->next_record();
      $product_in_stock = $db->f("product_in_stock");
      if ($quantity > $product_in_stock) {
        $this->error .= "Quantity selected exceeds available stock. - ";
        $this->error .= "Currently have $product_in_stock items available.";
        $return=False;
      }
    }

    // If no quantity sent them assume 1
    if ($quantity == "")
      $quantity = 1;
    // Check to see if we already have it


    if(!$return){ return FALSE; }else{

      $updated = 0;
      // Check for duplicate and do not add to current quantity
      for ($i=0;$i<$cart["idx"];$i++) {
        if ($cart[$i]["product_id"] == $product_id) {
          $updated = 1;
        }
      }
      // If we did not update then add the item
      if (!$updated) {
        $cart[$cart["idx"]]["product_id"] = $product_id;
        $cart[$cart["idx"]]["quantity"]   = $quantity;
        $cart["idx"]++;
      }

    }
    return True;
  }

 /**************************************************************************
  ** name: update()
  ** created by: brett odonnell
  ** description: updates the quantity of all product_ids in the cart
  ** parameters:
  ** returns:
  ***************************************************************************/
  function update(&$d) {
    global $cart;
    $db = new ps_DB;

    for ($i=0;$i<$cart["idx"];$i++) {
      if(!$this->update_item($i, $d["quantity"][$i])){
        $d["error"] = $this->error;
        return False;
      }
    }

  }

 /**************************************************************************
  ** name: update_item()
  ** created by: pablo
  ** description: updates the entire shopping cart
  ** parameters:
  ** returns:
  ***************************************************************************/
  function update_item($idx, $quantity) {
    global $cart;
    $db = new ps_DB;

    // Check for negative quantity
    if ($quantity < 1) {
        $this->error = "(IDX:$idx|QTY:$quantity) To delete an item please click the 'Delete' link.";
        return False;
    }

    if (!ereg("^[0-9]*$", $quantity)) {
        $this->error = "Please enter a valid quantity for this item.";
        return False;
    }

    $product_id=$cart[$idx]["product_id"];

    // Check to see if checking stock quantity
    if (CHECK_STOCK) {
      $q = "SELECT product_in_stock ";
      $q .= "FROM product where product_id=";
      $q .= $product_id;
      $db->query($q);
      $db->next_record();
      $product_in_stock = $db->f("product_in_stock");
      if ($quantity > $product_in_stock) {
        $this->error = "Quantity selected exceeds available stock.<br />";
        $this->error .= "Currently have $product_in_stock items available.";
        return False;
      }
    }

    //If the product publish is No then it will not display the item even if you
    //enter or change the product_id in the URL bar.
    $q = "SELECT product_name,product_publish FROM product WHERE product_id='$product_id'";
    $db->query($q);
    $db->next_record();
    // if the product isn't publishable, don't allow the add or update
    if ('N' == $db->f("product_publish") ) {
      // set your "not available" error message here
      $d["error"] = "We're sorry but ".$db->f("product_name")." is not available at this time.";
      // when in ps_cart->update, you probably want to uncomment
      // the line below to remove the product from the cart
      $this->delete($d);
      return False;
     } //end if prodcut_publish



    if (!isset($idx)) {
      $this->error = "No IDX was selected.";
      return False;
    }

    $cart[$idx]["quantity"] = $quantity;
    return True;
  }

 /**************************************************************************
  ** name: delete()
  ** created by: pablo
  ** description: deletes a given product_id from the cart
  ** parameters:
  ** returns:
  ***************************************************************************/
  function delete($d) {
    global $cart;
    $temp = array();
    $product_id = $d["product_id"];

    if (!$product_id) {
      return False;
    }

    $j = 0;
    for ($i=0;$i<$cart["idx"];$i++) {
      if ($cart[$i]["product_id"] != $product_id) {
        $temp[$j++] = $cart[$i];
      }
    }
    $temp["idx"] = $j;
    $cart = $temp;
    return True;
  }


 /**************************************************************************
  ** name: reset()
  ** created by: pablo
  ** description: resets the cart (i.e. empty)
  ** parameters:
  ** returns:
  ***************************************************************************/
  function reset() {
    global $cart;
    $cart["idx"]=0;
    return True;
  }
}

?>
