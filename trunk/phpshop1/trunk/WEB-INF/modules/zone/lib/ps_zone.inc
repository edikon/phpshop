<?php
/*
 *
 * Written By Mike Wattier - geek@devcompany.com
    Copyright (C) Mike Wattier  <geek@devcompany.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *
 * 
 * Welcome To The Shipping Zone =]
 */

class ps_zone {
  var $classname = "ps_zone";
  
  /*
  ** VALIDATION FUNCTIONS
  **
  */

  function validate_add(&$d) {
    
    $db = new ps_DB;
   
    $q = "SELECT * from zone_shipping WHERE zone_name='" . $d["zone_name"] . "'";
    $db->query($q);
    if ($db->next_record()) {
      $d["error"] = "ERROR:  This Zone Name already exists. Please select another name.";
      return False;
    } 
    if (!$d["zone_cost"]) {
      $d["error"] = "ERROR:  You must enter a per item zone cost. For Free shipping enter 0.00";
      return False;
    }
    if (!$d["zone_limit"]) {
      $d["error"] = "ERROR:  You must either enter a zone limit OR a 0.00 for no limit ";
      return False;
    }

    if ($d["zone_limit"] > "0") {
      if($d["zone_cost"] > $d["zone_limit"]) {
      $d["error"] = "ERROR:  The cost can not be higher than the limit.<br />";
      $d["error"] .= "If you wish to have no limit, enter 0.00 as your limit.";
      return False;
    }
   }
    if (!$d["zone_name"]) {
      $d["error"] = "ERROR:  You must enter a Zone Name.";
      return False;
    }
    return True;    
  }
  
  function validate_delete($d) {
    
    if (!$d["zone_id"]) {
      $d["error"] = "ERROR:  Please select a zone to delete.";
      return False;
    }
    else {
      return True;
    }
  }
  
  function validate_update(&$d) {
    $db = new ps_DB;

    if (!$d["zone_id"]) {
      $d["error"] = "ERROR:  You must select a zone to update.";
      return False;
    }
    if (!$d["zone_cost"]) {
      $d["error"] = "ERROR:  You must enter a per item zone cost.<br />";
      $d["error"] .= "For free shipping, enter 0.00.";
      return False;
    }

    if (!$d["zone_limit"]) {
      $d["error"] = "ERROR:  You must either enter a zone limit OR a 0.00 for no limit ";
      return False;
    }

    if ($d["zone_limit"] > "0") {
      if($d["zone_cost"] > $d["zone_limit"]) {
      $d["error"] = "ERROR:  The cost can not be higher than the limit.<br />";
      $d["error"] .= "If you wish to have no limit, enter 0 as your limit.";
      return False;
    }
   }

    if (!$d["zone_name"]) {
      $d["error"] = "ERROR:  You must enter a Zone Name.";
      return False;
    }
    return True;
  }
    function validate_assign(&$d) {

    if (!$d["zone_id"]) {
      $d["error"] = "ERROR:  You must select a zone.";
      return False;
    }
    if (!$d["country_id"]) {
      $d["error"] = "ERROR:  You must select a country.";
      return False;
    }
    return True;
  }
  
  /**************************************************************************
   * name: add()
   * created by: mike
   * description: creates a new zone rate record
   * parameters:
   * returns:
   **************************************************************************/
  function add(&$d) {
    $db = new ps_DB; 
    global $ps_vendor_id;
    $timestamp = time();
    
    if (!$this->validate_add($d)) {
      return False;
    }
    $q = "INSERT INTO zone_shipping (zone_name, zone_cost, ";
    $q .= "zone_limit, zone_description) VALUES ('";
    $q .= $d["zone_name"] . "','";
    $q .= $d["zone_cost"] . "','";
    $q .= $d["zone_limit"] . "','";
    $q .= $d["zone_description"] . "')";
    $db->query($q);
    $db->next_record();
    return True;

  }
  
  /**************************************************************************
   * name: update()
   * created by: mike
   * description: updates function information
   * parameters:
   * returns:
   **************************************************************************/
  function update(&$d) {
    $db = new ps_DB; 
    global $ps_vendor_id;
    $timestamp = time();

    if (!$this->validate_update($d)) {
      return False;	
    }
    $q = "UPDATE zone_shipping SET ";
    $q .= "zone_name='" . $d["zone_name"];
    $q .= "',zone_cost='" . $d["zone_cost"];
    $q .= "',zone_limit='" . $d["zone_limit"];
    $q .= "',zone_description='" . $d["zone_description"];
    $q .= "' WHERE zone_id='" . $d["zone_id"] . "'";
    $db->query($q);
    $db->next_record();
    return True;
  }

  /**************************************************************************
   * name: delete()
   * created by: mike
   * description: Should delete a category and and categories under it.
   * parameters: 
   * returns:
   **************************************************************************/
  function delete(&$d) {
    $db = new ps_DB;
    global $ps_vendor_id;
    
    if (!$this->validate_delete($d)) {
      return False;
    }
    $q = "DELETE from zone_shipping where zone_id='" . $d["zone_id"] . "'";
    $db->query($q);
    $db->next_record();
    return True;
  }
  /**************************************************************************
   * name: assign()
   * created by: mike
   * description: Assigns a zone to a country
   * parameters:
   * returns:
   **************************************************************************/
  function assign(&$d) {
    $db = new ps_DB; 
    $timestamp = time();

    if (!$this->validate_assign($d)) {
      return False;	
    }
    $q = "UPDATE zone_country SET ";
    $q .= "zone_id='" . $d["zone_id"];
    $q .= "' WHERE country_id='" . $d["country_id"] . "'";
    $db->query($q);
    $db->next_record();
    return True;
  }
  /**************************************************************************
  ** name: list_zones($list_name,$value)
  ** created by: pfmartin/mwattier
  ** description:  Print an HTML dropdown box for the countries
  ** parameters: $name - name of the HTML dropdown element
  **             $value - Drop down item to make selected
  **             $arr - array used to build the HTML drop down element
  ** returns: prints HTML drop down element to standard output
  ***************************************************************************/
   function list_zones($list_name,$value) {
     $db = new ps_DB;


     $q = "SELECT * from zone_shipping ORDER BY zone_name ASC";
     $db->query($q);

       echo "<select name=\"$list_name\">\n";
      while ($db->next_record()) {
       echo "<option value=\"" . $db->f("zone_id") . "\"";
       if ($value == $db->f("zone_id")) {
	 echo " selected=\"selected\"";
       }
       echo ">" . $db->f("zone_name") . "</option>\n";
     }
     echo "</select>\n";
     return True;
   }
  /**************************************************************************
  ** name: get_rate($ship_to_info_id,$zone_qty)
  ** created by: mwattier <geek@devcompany.com>
  ** description:  Get the rate according to what is in the basket AND
  **               the zone charge unless it hits the limit, then return that
  **               
  ** parameters: $ship_to_info_id - Where are we shipping to
  **             $zone_qty - This is what we use to see if we need to apply
  **             the limit or a per item cost
  ** returns: the cost to ship this order
  ***************************************************************************/
   function get_rate($d) {
       $db = new ps_DB;
      $db2 = new ps_DB;
      $db3 = new ps_DB;
    
      $q = "SELECT country FROM user_info WHERE user_info_id='";
      $q .= $d["ship_to_info_id"] . "'";
      $db->query($q);
      $db->next_record(); 
      $country = $db->f("country");
    
      $q2 = "SELECT zone_id FROM zone_country WHERE country_3_code='$country' ";
      $db2->query($q2);
      $db2->next_record(); 
      $the_zone = $db2->f("zone_id");

     $q3 = "SELECT * FROM zone_shipping WHERE zone_id ='$the_zone' ";
      $db3->query($q3);
      $db3->next_record(); 

     $cost_low = $db3->f("zone_cost") * $d["zone_qty"];

      if($cost_low < $db3->f("zone_limit")) {
         return $cost_low;
        } 
         else {
         return $db3->f("zone_limit");
        }
   }

 /**************************************************************************
  ** name: per_item($zone_id)
  ** created by: mwattier <geek@devcompany.com>
  ** description:  get the per item limit
  ** parameters: 
  **             
  **             
  ** returns: the cost limit for this zone
  ***************************************************************************/
   function per_item($zone_id) {
       $db = new ps_DB;

     $q = "SELECT zone_cost FROM zone_shipping WHERE zone_id ='$zone_id' ";
      $db->query($q);
      $db->next_record(); 

         return $db->f("zone_cost");
        
   }

  /**************************************************************************
  ** name: zone_limit($zone_id)
  ** created by: mwattier <geek@devcompany.com>
  ** description:  get the per item limit
  ** parameters: 
  **             
  **             
  ** returns: the cost limit for this zone
  ***************************************************************************/
   function zone_limit($zone_id) {
       $db = new ps_DB;

     $q = "SELECT zone_limit FROM zone_shipping WHERE zone_id ='$zone_id' ";
      $db->query($q);
      $db->next_record(); 

         return $db->f("zone_limit");
        
   }

     /**************************************************************************
  ** name: get_weight()
  ** created by: Matt Oberpriller
  ** description: Calculate product weight in ounces
  ** parameters: product_id
  ** returns: weight in ounces
  ***************************************************************************/  
  function get_weight($pid) {
    global $ps_vendor_id;

    $db = new ps_DB;

    $q  = "SELECT * FROM product ";
    $q .= "WHERE product_id='$pid' ";
    $q .= "AND vendor_id='$ps_vendor_id'";
    $db->query($q);
    $db->next_record();

    if ($db->f("product_weight") == 0 && $db->f("product_parent_id")) {
       $q = "SELECT * from product WHERE product_id=";
       $q .= $db->f("product_parent_id");
       $db->query($q);
       $db->next_record();       
    }

    if ($db->f("product_weight") > 0) {
      if (eregi("LB",$db->f("product_weight_uom")) || eregi("PO",$db->f("product_weight_uom")))
        $weight = $db->f("product_weight") * 16;
      elseif (eregi("KG",$db->f("product_weight_uom")) || eregi("KILO",$db->f("product_weight_uom")))
        $weight = $db->f("product_weight") * 35.27396194958041;
      elseif (eregi("G",$db->f("product_weight_uom")))
        $weight = $db->f("product_weight") * 0.035273961949580414;
      elseif (eregi("OZ",$db->f("product_weight_uom")) || eregi("OU",$db->f("product_weight_uom")))
        $weight = $db->f("product_weight");
      else
        $this->error="Unknown weight UOM in product " . $db->f("product_sku");
    } else {
      $this->error="Weight not specified for product " . $db->f("product_sku");
    }

    if ($weight)
     return($weight);
    else
     return 0;
  }

}
?>
