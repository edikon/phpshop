<?php
/* SVN FILE: $Id: import_export_controller.php 418 2008-01-31 22:37:17Z pablo $ */
/**
 *
 * PHP versions 4 and 5
 *
 * phpShop(tm) :  A Simple Shopping Cart <http://www.phpshop.org/>
 * Copyright 1998-2008, 	Edikon Corporation
 *							3455 Peachtree Road Suite 500
 *							Atlanta, Georgia 30326
 *
 * Licensed under The GNU General Public License
 * Redistributions of files must retain the above copyright notice.
 *
 * @filesource
 * @copyright		Copyright 1998-2008, Edikon Corporation
 * @link			http://www.edikon.com/ phpShop(tm) Project
 * @package			phpshop
 * @subpackage		phpshop.app.controllers
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

class ImportExportController extends AppController
{
	var $helpers = array('html', 'form');

	var $uses = array('Product', 'Category', 'Brand', 'ProductsCategory', 'ProductImage', 'ProductType', 'ProductItem');

	function admin_index() {
		// view displays import options
	}

	/**
	 * Export function handles export for different import types
	 *
	 * @param unknown_type $type
	 * @param unknown_type $where
	 * @param unknown_type $field_delimeter
	 * @param unknown_type $complex_delimiter
	 */
	function admin_export($type=null) {

		/* Product Export, Does not support multiple items */
		if ($type == 'products') {
			$csv = $this->product_export();
		}
		elseif ($type == 'categories') {
			$csv = $this->category_export();
		}
		$this->set('csv', $csv);
	}

	/**
	 * Import handler, will call corresponding import method based on type.
	 *
	 * @param unknown_type $type
	 */
	function admin_import($type=null) {
			
		// Handle CSV file upload
		$csv_file = $this->data['Product']['csv_file'];
		if (isset($type)) {
			$fimage = null;
			if (isset($csv_file['name'])&&(!empty($csv_file['name']))) {
				$fimage =  $csv_file['name'];
				move_uploaded_file($csv_file['tmp_name'], TMP . "imports/".$fimage);
				$csv = file_get_contents(TMP . "imports/".$fimage);
			}
		}
			
		if ($type == 'products') {
			$this->product_import($csv);
		}
		elseif ($type == 'categories') {
			$this->category_import($csv);
		}
	}

	/**
	 * Exports products to CSV format.
	 *
	 * Primary product contains default product item.
	 * All other product items are exported on separate lines using the parent_handle field.
	 *
	 * @param unknown_type $where
	 * @param unknown_type $field_delimeter
	 * @param unknown_type $complex_delimiter
	 * @return unknown
	 */
	function product_export($field_delimeter = '|', $complex_delimiter = ';') {

		$csv = '';

		$products = $this->Product->find('all');

		foreach($products as $product) {

			$row = array();

			// Product
			$row['name'] = $product['Product']['name'];
			$row['handle'] = $product['Product']['handle'];
			$row['parent_handle'] = null;
			$row['active'] = $product['Product']['active'];
			$row['brand'] = $product['Brand']['name'];
			$row['product_type'] = $product['ProductType']['name'];

			// Categories
			$categories=null;
			foreach ($product['Category'] as $category) {
				$categories[] = $category['handle'];
			}
			$row['categories'] = implode($complex_delimiter, $categories);

			$row['tags'] = $product['Product']['tags'];
			$row['description'] = trim(str_replace("\n", "", str_replace("\r", "", $product['Product']['description'])));

			// Product Item
			$row['sku'] = $product['ProductItem'][0]['sku'];
			$row['label'] = $product['ProductItem'][0]['label'];
			$row['sell_price'] = $product['ProductItem'][0]['sell_price'];
			$row['regular_price'] = $product['ProductItem'][0]['regular_price'];
			$row['weight'] = $product['ProductItem'][0]['weight'];
			$row['quantity'] = $product['ProductItem'][0]['quantity'];
			$row['track_stock'] = $product['ProductItem'][0]['track_stock'];

			// Images
			$images=null;
			foreach ($product['ProductImage'] as $image) {
				$images[] = $image['image'];
			}
			$row['images'] = implode($complex_delimiter, $images);

			$row = str_replace('\\', '\\\\', $row);
			$row = str_replace($field_delimeter, '\\' . $field_delimeter, $row);
			$csv .= implode($field_delimeter, $row) . chr(13);

			// Additional Product Items
			// Only create if there is more than 1 product item
			if (count($product['ProductItem']) > 1) {
				for ($i=1;$i<count($product['ProductItem']);$i++) {
					// Product Item
					$row['name'] = null;
					$row['handle'] = null;
					$row['description'] = null;
					$row['brand'] = null;
					$row['product_type'] = null;
					$row['categories'] = null;
					$row['tags'] = null;
					$row['images'] = null;

					$row['parent_handle'] = $product['Product']['handle'];
					$row['sku'] = $product['ProductItem'][$i]['sku'];
					$row['label'] = $product['ProductItem'][$i]['label'];
					$row['sell_price'] = $product['ProductItem'][$i]['sell_price'];
					$row['regular_price'] = $product['ProductItem'][$i]['regular_price'];
					$row['weight'] = $product['ProductItem'][$i]['weight'];
					$row['quantity'] = $product['ProductItem'][$i]['quantity'];
					$row['track_stock'] = $product['ProductItem'][$i]['track_stock'];

					$row = str_replace('\\', '\\\\', $row);
					$row = str_replace($field_delimeter, '\\' . $field_delimeter, $row);
					$csv .= implode($field_delimeter, $row) . chr(13);

				}
			}
		}
		$csv = trim($csv);

		// build header row
		$headers=null;
		foreach($row as $key=>$value) {
			$headers[] = $key;
		}
		$header = implode($field_delimeter, $headers) . chr(13);

		return $header . $csv;

	}

	/**
	 * Product import from csv file
	 *
	 * Imports Brands, Product Types, Product Items and Products
	 *
	 */
	function product_import($csv, $terminator = "\n", $field_delimiter ="|", $complex_delimiter = ';') {


		$keys = array('name','handle','parent_handle','active','brand','product_type','categories','tags','description','sku','label','sell_price','regular_price','weight','quantity', 'track_stock','images');

		$rows = array();
		$csv = trim($csv);

		$csv_rows = explode($terminator, $csv);

		$line_number = 1;     // we don't want to import the first line.

		foreach($csv_rows as $csv_row) {
			if ($line_number++ > 1)  {
				$csv_row = str_replace('\\\\', '\\', $csv_row);
				$csv_row = str_replace('\\' . $field_delimiter, chr(26), $csv_row);
				$row = explode($field_delimiter, $csv_row);
				$row = str_replace(chr(26), $field_delimiter, $row);
				$row = array_combine($keys, $row);
				$rows = array_merge_recursive($rows, array(array('Product' => $row)));
			}
		}

		// $rows contains each product record

		// Import Brands ------------------------
		// Brands are imported directly from the CSV file.
		foreach($rows as $row) {
			if (isset($row['Product']['brand']) && !empty($row['Product']['brand'])) {
				$brands[] = $row['Product']['brand'];
			}
		}
		$brands = array_unique($brands);

		$this->Brand->deleteAll('1=1');
		foreach ($brands as $brand) {
			// check for empty record
			if (!empty($brand)) {
				$record = array();
				$record['handle'] = strtolower(str_replace(" ", "-", ereg_replace("[^ A-Za-z0-9]", "", $brand)));
				$record['name'] = $brand;

				$this->Brand->create();
				if (!$this->Brand->save($record)) {
					$this->Session->setFlash('The Brand import failed. Please, try again.');
					$this->redirect(array('action'=>'index'), null, true);
				}
			}
		}
		// End Brands --------------------------

		// Import Product Types  ------------------------
		// Product Types are imported directly from the CSV file.
		foreach($rows as $row) {
			$types[] = array(
				'name' => $row['Product']['product_type'],
			);
		}
		$types = array_unique($types);

		$this->ProductType->deleteAll('1=1');
		foreach ($types as $type) {
			if (!empty($type)) {
				$this->ProductType->create();
				if (!$this->ProductType->save($type)) {
					$this->Session->setFlash('The ProductType import failed. Please, try again.');
					$this->redirect(array('action'=>'index'), null, true);
				}
			}
		}
		// End Product Types --------------------------


		// Import Products ---------------------

		// Cleanup first
		$this->Product->deleteAll('1=1');
		$this->ProductItem->deleteAll('1=1');
		$this->ProductImage->deleteAll('1=1');
		$this->ProductsCategory->deleteAll('1=1');

		// loop through each product row
		foreach($rows as $row) {

			// Check of this is a Product Item
			if (isset($row['Product']['parent_handle']) && !empty($row['Product']['parent_handle'])) {
				$product = $this->Product->findByHandle($row['Product']['parent_handle']);
				$row['Product']['product_id'] = $product['Product']['id'];

				// Product Item
				$this->ProductItem->create();
				if (!$this->ProductItem->save($row['Product'])) {
					$this->Session->setFlash('The Product import failed. Please, try again.');
					$this->redirect(array('action'=>'index'), null, true);
				}

			}
			else {
				// NOT PRODUCT ITEM, regular Product
				// parse and save brand
				if (isset($row['Product']['brand'])) {
					$brand = $this->Brand->findByName("{$row['Product']['brand']}");
					$row['Product']['brand_id'] = $brand['Brand']['id'];
				}

				// parse and save product type
				if (isset($row['Product']['product_type'])) {
					$type = $this->ProductType->findByName("{$row['Product']['product_type']}");
					$row['Product']['product_type_id'] = $type['ProductType']['id'];
				}

				// Product
				$this->cleanUpFields();
				$this->Product->create();
				if (!$this->Product->save($row['Product'])) {
					$this->Session->setFlash('The Product import failed. Please, try again.');
					$this->redirect(array('action'=>'index'), null, true);
				}

				// this is the product id we just created
				$product_id = $this->Product->id;

				// Product Item
				$this->ProductItem->create();
				$row['Product']['product_id'] = $product_id;
				if (!$this->ProductItem->save($row['Product'])) {
					$this->Session->setFlash('The Product import failed. Please, try again.');
					$this->redirect(array('action'=>'index'), null, true);
				}

				// Product Categories
				if (isset($row['Product']['categories'])) {
					$categories = explode($complex_delimiter, $row['Product']['categories']);
					foreach ($categories as $code) {
						$category = $this->Category->findByHandle($code);
						$category_id = $category['Category']['id'];

						if (!empty($category_id)) {
							// check for existance of entry
							$this->ProductsCategory->create();
							$record = array(
									'category_id' => $category_id,
									'product_id' => $product_id
							);
							$this->ProductsCategory->save($record);
						}
					}
				}

				// Product Images
				if (isset($row['Product']['images'])) {
					$images = explode($complex_delimiter, $row['Product']['images']);
					$priority = 0;

					foreach ($images as $image) {
						$this->ProductImage->create();
						$record = array(
									'image' => $image,
									'product_id' => $product_id,
									'priority' => $priority++
						);
						$this->ProductImage->save($record);
					}
				}


			}
			// End Products --------------------------
		}
		$this->Session->setFlash('The Product import succeeded. ');
		$this->redirect(array('controller' => 'products', 'action'=>'index'), null, true);

	}

	/**
	 * Exports categories to CSV format.
	 *
	 * @param unknown_type $where
	 * @param unknown_type $field_delimeter
	 * @param unknown_type $complex_delimiter
	 * @return unknown
	 */
	function category_export($field_delimeter = '|', $complex_delimiter = ';') {

		$csv = '';

		$categories = $this->Category->findAll(null, null, 'Category.lft ASC');

		foreach($categories as $category) {

			// Category
			$row['name'] = $category['Category']['name'];
			$row['category_parent'] = $category['ParentCategory']['handle'];
			$row['handle'] = $category['Category']['handle'];
			$row['description'] = trim(str_replace("\n", "", str_replace("\r", "", $category['Category']['description'])));
			$row['active'] = $category['Category']['active'];
			$row['image'] = $category['Category']['image'];

			$row = str_replace('\\', '\\\\', $row);
			$row = str_replace($field_delimeter, '\\' . $field_delimeter, $row);
			$csv .= implode($field_delimeter, $row) . chr(13);
		}
		$csv = trim($csv);

		// build header row
		$headers=null;
		foreach($row as $key=>$value) {
			$headers[] = $key;
		}
		$header = implode($field_delimeter, $headers) . chr(13);

		return $header . $csv;

	}


	/**
	 * Category import from csv file
	 *
	 */
	function category_import($csv, $terminator = "\n", $field_delimiter ="|", $complex_delimiter = ';') {


		$keys = array('name','category_parent','handle','description','active','image');

		$rows = array();
		$csv = trim($csv);

		$csv_rows = explode($terminator, $csv);

		$line_number = 1;     // we don't want to import the first line.

		foreach($csv_rows as $csv_row) {
			if ($line_number++ > 1)  {
				$csv_row = str_replace('\\\\', '\\', $csv_row);
				$csv_row = str_replace('\\' . $field_delimiter, chr(26), $csv_row);
				$row = explode($field_delimiter, $csv_row);
				$row = str_replace(chr(26), $field_delimiter, $row);
				$row = array_combine($keys, $row);
				$rows = array_merge_recursive($rows, array(array('Category' => $row)));
			}
		}

		// $rows contains each product record


		// Import Categories ---------------------
		$this->Category->deleteAll('1=1');

		// loop through each product row
		foreach($rows as $row) {
			// parse and save parent
			if (isset($row['Category']['category_parent'])) {
				$parent = $this->Category->findByHandle("{$row['Category']['category_parent']}");
				$row['Category']['parent_id'] = $parent['Category']['id'];
				pr($row);
			}

			// Category
			$this->cleanUpFields();
			$this->Category->create();
			if (!$this->Category->save($row['Category'])) {
				$this->Session->setFlash('The Category import failed. Please, try again.');
				$this->redirect(array('action'=>'index'), null, true);
			}
			
		}
		// End Categories --------------------------

		$this->Session->setFlash('The Categories import succeeded. ');
		$this->redirect(array('controller' => 'categories', 'action'=>'index'), null, true);

	}
}
?>