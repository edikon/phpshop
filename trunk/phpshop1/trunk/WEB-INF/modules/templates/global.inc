<?php

# phpShop Variables

# Global links
$search_box_title = "Search";

$module_topmenu            = "$modulename/html/topmenu.ihtml";
$module_leftmenu            = "$modulename/html/leftmenu.ihtml";

$cart_header_color = "#77bb77";

$q = "SELECT * from module WHERE module_name='$modulename'";
$db->query($q);
$db->next_record();
$module_description = $db->f("module_description");

# Some database values we will need throughout
# Get Vendor Information
$q = "SELECT * from vendor";
$db->query($q);
$db->next_record();

if (!isset($ps_vendor_id)) {
   $ps_vendor_id = $db->f("vendor_id");
   $sess->register("ps_vendor_id");
}
$vendor_name = $db->f("vendor_name");

if ($SERVER_PORT == "443")
   $url = SECUREURL;
else
   $url = URL;

$vendor_image = "<img border=\"0\" src=\"" . $url . 
                $db->f("vendor_image_path") .
                "vendor/" . $db->f("vendor_full_image") . "\" alt=\"$vendor_name\" />";

$vendor_address = $db->f("vendor_address_1");
$vendor_city = $db->f("vendor_city");
$vendor_state = $db->f("vendor_state");
$vendor_zip = $db->f("vendor_zip");
$vendor_phone = $db->f("vendor_phone");
$vendor_store_desc = $db->f("vendor_store_desc");

?>
