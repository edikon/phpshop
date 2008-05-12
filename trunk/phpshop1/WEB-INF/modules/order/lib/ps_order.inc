<?php
/*
 * The ps_order class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_order.inc,v 1.1.1.1 2004/07/27 14:58:48 pablo Exp $
 *

****************************************************************************
*
* CLASS DESCRIPTION
*                   
* ps_order
*
* The class handles orders from an adminstrative perspective.  Order
* processing is handled in the ps_process_order.
* 
* propeties:  
* 	
*       error - the error message returned by validation if any
* methods:
*       validate_add()
*	validate_delete()
*	validate_update()
*       add()
*       update()
*       delete()
*	
*
*************************************************************************/
class ps_order {
  var $classname = "ps_order";
  var $error;
  

  /**************************************************************************
   * name: find
   * created by: pablo
   * description: find an order by its order_id
   * parameters:
   * returns:
   **************************************************************************/
  function find(&$d, $start=0) {
    $db = new ps_DB;
    

    $q = "SELECT * from orders where ";
    $q .= "order_id = '" . $d["order_id"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      return True;
    }
    else {
      $d["error"] = "ORDER NOT FOUND:  The order number you entered was not found.";
      return False;
    }
  }


   /**************************************************************************
   * name: order_status_update
   * created by: pablo
   * description: changes the status of an order.  Can be 3 statuses:
   *              default: P - pending
   *                       C - complete
   *                       X - canceled
   * parameters:
   * returns:
   **************************************************************************/
  function order_status_update(&$d) {
    $db = new ps_DB;
    $timestamp = time();
 
    $q = "UPDATE orders SET";
    $q .= " order_status='" . $d["order_status"] . "' ";
    $q .= ", mdate='" . $timestamp . "' ";
    $q .= "WHERE order_id='" . $d["order_id"] . "'";
    $db->query($q);
    $db->next_record();
    $d["order_status"] = "P";

    return True;

  }

   /**************************************************************************
   * name: list_order
   * created by: pablo
   * description: shows a listbox of orders which can be used in a form
   * parameters: set to order_id
   * returns:
   **************************************************************************/
  function list_order($order_status=A, $secure=0) {
    global $ps_vendor_id, $auth;
    $db = new ps_DB;
    $i = 0;

    $q = "SELECT * FROM orders ";
    $q .= "WHERE vendor_id='$ps_vendor_id' ";
    if ($order_status != "A") {
      $q .= "AND order_status='$order_status' ";
    }
    if ($secure) {
      $q .= "AND user_id='" . $auth["user_id"] . "' "; 
    }
    $q .= "ORDER BY cdate DESC";
    $db->query($q);
    echo "<select name=\"order_id\" size=\"" . MAX_ROWS . "\">";;
    while ($db->next_record()) {
      $i++;
      echo "<option value=\"" . $db->f("order_id") . "\">";
      printf("%08d", $db->f("order_id"));
      echo "&nbsp;&nbsp;&nbsp;&nbsp;";
      echo date("dMY.H:i", (int)$db->f("cdate"));
      echo "&nbsp;&nbsp;&nbsp;";
      echo $db->f("order_status") . "&nbsp; &nbsp;";
      echo "&nbsp;&nbsp;";
      $order_total = $db->f("order_subtotal") + 
                     $db->f("order_tax") + 
                     $db->f("order_shipping_tax") + 
                     $db->f("order_shipping");
      printf("%.2f", $order_total);
      echo "&nbsp; &nbsp;";
      echo "</option>";
    }
    if (!$i) {
      echo "<option>---------------------- No Orders to Display ------------------</option>\n";
    }
    echo "</select>\n";    
  }

  /********************************************************************
  ** name: validate_delete()
  ** created by: gday
  ** description:  Validate form values prior to delete
  ** parameters: $d
  ** returns:  True - validation passed
  **          False - validation failed
  ********************************************************************/
  function validate_delete($d) {

    if(!$d["order_id"]) {
       $this->error = "Unable to delete without the order id.";
       return False;
    }

    return True;
  }

 /***********************************************************************
  ** name: delete()
  ** created by: gday
  ** description:  Delete the order in the database
  ** parameters: $d
  ** returns:  True - delete succeeded
  **          False - delete failed
  **********************************************************************/
  function delete(&$d) {
    $db = new ps_DB;
  
    if ($this->validate_delete($d)) {
      $q = "DELETE from orders where order_id=" . $d["order_id"];
      $db->query($q);
      $db->next_record();

      $q = "DELETE from order_item where order_id=" . $d["order_id"];
      $db->query($q);
      $db->next_record();

      $q = "DELETE from order_payment where order_id=" . $d["order_id"];
      $db->query($q);
      $db->next_record();

      return True;
    }
    else {
      return False;
    }
  }


  
}
$ps_order = new ps_order;
?>
