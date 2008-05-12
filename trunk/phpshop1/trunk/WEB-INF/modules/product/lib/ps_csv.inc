<?php
/*
 * The ps_csv class
 *
 * By John Syben
 * webme.co.nz
 *
 * This class allows for the adding of multiple
 * products and categories from a csv file
 *************************************************************************/

class ps_csv {
  var $classname = "ps_csv";

  /**************************************************************************
  ** name: upload_csv()
  ** created by: John Syben
  ** modified by: nhyde
  ** A db table named 'csv' must exist with the product fields
  ** allocated their relative positions in the csv line
  ***************************************************************************/

  function upload_csv(&$d) {
  	// handle the upload here
 	/* fix by heiko 05.04.2005 */
 	global $_FILES;
 	$d["file_name"] = $_FILES["file"]["name"];
 	$d["file_type"] = $_FILES["file"]["type"];
 	$d["file_tmp_name"] = $_FILES["file"]["tmp_name"];
 	$d["file"] =$_FILES["file"]["tmp_name"];
 	$d["file_size"] =$_FILES["file"]["size"];
 	/* end fix by heiko 05.04.2005 */

 	// handle the upload here
 	if (False == $this->handle_csv_upload($d) ) {
 		return False;
 	}

    // Get row positions of each element as set in csv table
    $db = new ps_DB;
    $q = "SELECT * FROM csv ";
    $db->query($q);
    $db->next_record();

    // Open csv file
    $file = $d["file"]; 
    $fp = fopen ($file,"r");
    $error="";
    $line=1;
      // Run through each line of file
      while ($data = fgetcsv ($fp, 1000, ",")) {

          // Check for SKU - required
          if (!$data[$db->f("csv_product_sku")-1]) 
            $this_error .= "No SKU, ";
          else 
            $product_sku = $data[$db->f("csv_product_sku")-1];

          // Check for Product Name - required
          if (!$data[$db->f("csv_product_name")-1]) 
            $this_error .= "No Product Name, ";
          else 
            $product_name = $data[$db->f("csv_product_name")-1];

          // Check for Price - required
          if (!$data[$db->f("csv_product_price")-1]) 
            $this_error .= "No Price, ";
          else 
            $product_price = $data[$db->f("csv_product_price")-1];

          // Check for Category Path - required
          if (!$data[$db->f("csv_category_path")-1]) 
            $this_error .= "No Category Path, ";
          else 
            $category_path = $data[$db->f("csv_category_path")-1];

          // If a required field was missing, add to error to main message and start next line
          // Otherwise add or update product
          if ($this_error) {
            $d["message"] .= "Line $line $this_error<br />";
            $this_error = "";
          }
          else { 
            $timestamp = time();

            // See if sku exists. If so, update product - otherwise add product
            $dbp = new ps_DB;
            $q = "SELECT * FROM product ";
            $q .= "WHERE product_sku='$product_sku'";
            $dbp->query($q);
              if ($dbp->next_record()) { // SKU exists - update product
                // Update product information
                $q = "UPDATE product SET ";
                $q .= "product_s_desc='" . $data[$db->f("csv_product_s_desc")-1] . "',";
                $q .= "product_desc='" . $data[$db->f("csv_product_desc")-1] . "',";
                $q .= "product_thumb_image='" . $data[$db->f("csv_product_thumb_image")-1] . "',";
                $q .= "product_full_image='" . $data[$db->f("csv_product_full_image")-1] . "',";
                $q .= "product_weight='" . $data[$db->f("csv_product_weight")-1] . "',";
                $q .= "product_weight_uom='" . $data[$db->f("csv_product_weight_uom")-1] . "',";
                $q .= "product_length='" . $data[$db->f("csv_product_length")-1] . "',";
                $q .= "product_width='" . $data[$db->f("csv_product_width")-1] . "',";
                $q .= "product_height='" . $data[$db->f("csv_product_height")-1] . "',";
                $q .= "product_lwh_uom='" . $data[$db->f("csv_product_lwh_uom")-1] . "',";
                $q .= "product_in_stock='" . $data[$db->f("csv_product_in_stock")-1] . "',";
                $q .= "product_available_date='" . $data[$db->f("csv_product_available_date")-1] . "',";
                $q .= "product_special='" . $data[$db->f("csv_product_special")-1] . "',";
                $q .= "product_discount_id='" . $data[$db->f("csv_product_discount_id")-1] . "',";
                $q .= "product_name='" . $product_name . "', ";
                $q .= "mdate='" . $timestamp . "' ";
                $q .= "WHERE product_sku='" . $product_sku . "'";
                $dbu = new ps_DB;
                $dbu->query($q);

                // Get default shopper group ID
                $q = "SELECT shopper_group_id FROM shopper_group ";
                $q .= "WHERE shopper_group_name='-default-'";
                $dbsg = new ps_DB;
                $dbsg->query($q);
                $dbsg->next_record();

                // Update product price for default shopper group   
                $q = "UPDATE product_price SET ";
                $q .= "product_price='" . $product_price . "',";
                $q .= "shopper_group_id='" . $dbsg->f("shopper_group_id") . "', ";
                $q .= "mdate='" . $timestamp . "' ";
                $q .= "WHERE product_id='" . $dbp->f("product_id") . "'";
                $dbpp = new ps_DB;
                $dbpp->query($q);

                // Add report for this line to message
                $d["message"] .= "Line: $line Updated Product SKU: $product_sku<br />";
              }
              else { // SKU does not exist - add new product
                // Add product information
                $q  = "INSERT INTO product (vendor_id,product_parent_id,product_sku,";
                $q .= "product_name,product_desc,product_s_desc,";
                $q .= "product_thumb_image,product_full_image,";
                $q .= "product_publish,product_weight,product_weight_uom,";
                $q .= "product_length,product_width,product_height,product_lwh_uom,";
                $q .= "product_in_stock,";
                $q .= "product_available_date,product_special,product_discount_id,";
                $q .= "cdate,mdate) ";
                $q .= "VALUES ('1','0','";
                $q .= $data[$db->f("csv_product_sku")-1] . "','" . $data[$db->f("csv_product_name")-1] . "','";
                $q .= $data[$db->f("csv_product_desc")-1] . "','" . $data[$db->f("csv_product_s_desc")-1] . "','";
                $q .= $data[$db->f("csv_product_thumb_image")-1] . "','";
                $q .= $data[$db->f("csv_product_full_image")-1] . "','Y','";
                $q .= $data[$db->f("csv_product_weight")-1] . "','" . $data[$db->f("csv_product_weight_uom")-1] . "','";
                $q .= $data[$db->f("csv_product_length")-1] . "','" . $data[$db->f("csv_product_width")-1] . "','";
                $q .= $data[$db->f("csv_product_height")-1] . "','" . $data[$db->f("csv_product_lwh_uom")-1] . "','";
                $q .= $data[$db->f("csv_product_in_stock")-1] . "','";
                $q .= $data[$db->f("csv_product_available_date")-1] . "','";
                $q .= $data[$db->f("csv_product_special")-1] . "','";
                $q .= $data[$db->f("csv_product_discount_id")-1] . "','$timestamp','$timestamp')";
                $dbu = new ps_DB;
                $dbu->query($q);

                // Get the product ID we just created
                $q  = "SELECT product_id FROM product ";
                $q .= "WHERE product_sku = '" . $product_sku . "' ";
                $q .= "AND vendor_id = '1' ";
                $q .= "AND cdate = $timestamp";
                $dbpi = new ps_DB;
                $dbpi->query($q);
                $dbpi->next_record();
                $product_id = $dbpi->f("product_id");

                // Use csv_category() method to confirm/add category tree for this product
                $category_id = $this->csv_category($data[$db->f("csv_category_path")-1]);

                // Create product/category xref
                $q  = "INSERT INTO product_category_xref ";
                $q .= "(category_id,product_id) ";
                $q .= "VALUES ('" . $category_id . "','";
                $q .=  $product_id . "')";
                $dbcat = new ps_DB;
                $dbcat->query($q);

                // Get default shopper group ID
                $q = "SELECT shopper_group_id FROM shopper_group ";
                $q .= "WHERE shopper_group_name='-default-'";
                $dbsg = new ps_DB;
                $dbsg->query($q);
                $dbsg->next_record();

                // Add  product price for default shopper group
                $q = "INSERT INTO product_price ";
                $q .= "(product_price,product_id,shopper_group_id,mdate) ";
                $q .= "VALUES ('";
                $q .= $product_price . "','";
                $q .= $product_id . "','";
                $q .= $dbsg->f("shopper_group_id") . "','";
                $q .= $timestamp . "') ";
                $dbpp = new ps_DB;
                $dbpp->query($q);

                // Add report for this line to message
                $d["message"] .= "Line: $line Added Product SKU: $product_sku<br />";
              }
          }
        $line++;
      } // End while
    fclose ($fp);
    return True;

  } //End function upload_csv


  /**************************************************************************
  ** name: csv_category()
  ** created by: John Syben
  ** Creates categories from slash delimited line
  ***************************************************************************/
  function csv_category($line) {
    // Explode slash delimited category tree into array
    $category_list = explode("/", $line);
    $category_count = count($category_list);

    $db = new ps_DB;
    $category_parent_id = '0';

      // For each category in array
      for($i = 0; $i < $category_count; $i++) {
        // See if this category exists with it's parent in xref
        $q = "SELECT category.category_id FROM category,category_xref ";
        $q .= "WHERE category.category_name='" . $category_list[$i] . "' ";
        $q .= "AND category_xref.category_child_id=category.category_id ";
        $q .= "AND category_xref.category_parent_id='$category_parent_id'";
        $db->query($q);
          // If it does not exist, create it
          if ($db->next_record()) { // Category exists
            $category_id = $db->f("category_id");
          }
          else { // Category does not exist - create it
            $hash_secret="PHPShopIsCool";
            $category_id = md5(uniqid($hash_secret));
            $timestamp = time();

		   $cat_url = strtolower($category_list[$i]);
		   $cat_url = str_replace(" ", "",$cat_url);

            // Add category
            $q = "INSERT INTO category ";
            $q .= "(category_id,vendor_id,category_name,category_url,category_publish,cdate,mdate) ";
            $q .= "VALUES ('";
            $q .= $category_id . "','";
            $q .= "1', '";
            $q .= $category_list[$i] . "', '";
            $q .= "$cat_url', '";
            $q .= "Y', '";
            $q .= $timestamp . "', '";
            $q .= $timestamp . "')";
            $db->query($q);

            // Create xref with parent
            $q = "INSERT INTO category_xref ";
            $q .= "(category_parent_id, category_child_id) ";
            $q .= "VALUES ('";
            $q .= $category_parent_id . "', '";
            $q .= $category_id . "')";
            $db->query($q);
          }
        // Set this category as parent of next in line
        $category_parent_id = $category_id;
      } // end for

    // Return the last category_id which is where the product goes
    return $category_id;

  } // End function csv_category
	
	/**
	  * Handle the upload of file "file".
	  *
	  * Longer, multi-line description here.
	  * 
	  * @name handle_csv_upload
	  * @author Nathan Hyde <nhyde@bigdrift.com>
	  * @param array d posted items crammed into 1 arr
	  * @returns boolean True of False
	  */
	function handle_csv_upload(&$d) {
		$allowed_suffixes_arr = array(
			0=> 'csv'
			,1 => 'txt'
			// add more here if needed
		);
		
		$allowed_mime_types_arr = array(
			0=> 'text/html'
			,1 => 'text/plain'
   ,2 => 'application/octet-stream'
			// add more here if needed
		);
		
  $error = ""; 
  $strs = explode(".",$d["file_name"]); 
  $count= count($strs); 
  $extension = $strs[$count-1]; 

		if (False == in_array($extension, $allowed_suffixes_arr) ) {
			$d["error"] = "Suffix not allowed. Valid suffixes are: " . join(", ",$allowed_suffixes_arr);
	return False;
		}
		// test the mime type here
		if (False == in_array($d["file_type"], $allowed_mime_types_arr) ) {
			$d["error"] = "Mime type not accepted. Type for file uploaded: ".$d["file_type"];
	return False;
		}
		
		// do the moovin here :)
		// not necessary for us to do cause it's a temporary file, right?
		/** 
		if (is_uploaded_file($d['file_tmp_name']) ) {
			copy($d['file_tmp_name'], "/place/to/put/uploaded/file");
		} else {
			echo "Possible file upload attack. Filename: " . $_FILES['userfile']['name'];
		}
		// ...or... 
		move_uploaded_file($d["file_tmp_name"], "/place/to/put/uploaded/file");
		
		**/
		

	return True;
	}
}
?>