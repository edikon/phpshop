<?php
/**
 * ImpxController for phpShop
 *
 * @copyright Edikon Corporation, http://www.edikon.com
 * @license http://opensource.org/licenses/gpl-license.php GNU General Public License V2
 * @package phpShop
 * @version $Id: import_export_controller.php 336 2007-08-17 15:54:09Z pablo $
 *
 */
class ImpxController extends ImpxAppController
{
  	var $helpers = array('html', 'form');

	var $uses = array('Product', 'Category', 'ProductsCategory', 'Brand');

	function admin_index() {
		// view displays import options
	}
	
	function admin_export($type=null) {
				
		if ($type == 'products') {
			$csv = $this->Product->exportCSV(null,"|"); 
		}
		elseif ($type == 'categories') {
			$csv = $this->Category->exportCSV(null,"|"); 
		}
		$this->set('csv', $csv);	
	}

	/*
	* Deletes all existing records during import 
	*
	*/
	function admin_import($type=null) {
		
		// Get the CSV data from the uploaded file
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
						
			if ($csv_file['error']==0) {
				$rows = $this->Product->importCSV($csv, "|");	
				$this->Product->deleteAll('1=1');
				$this->CategoriesProduct->deleteAll('1=1');

				foreach($rows as $row) {
					// parse and save brands
					if (isset($row['Product']['brand_id'])) {
						$brand_id = $this->Brand->findByCode("{$row['Product']['brand_id']}");
						$row['Product']['brand_id'] = $brand_id['Brand']['id'];
					}
					
					// parse and save tax codes
					if (isset($row['Product']['tax_class_id'])) {
						$tax_class_id = $this->TaxClass->findByCode("{$row['Product']['tax_class_id']}");
						$row['Product']['tax_class_id'] = $tax_class_id['TaxClass']['id'];
					}

					// save the products
					$this->cleanUpFields();
					$this->Product->create();
				    if (!$this->Product->save($row['Product'])) {
						$this->Session->setFlash('The Product import failed. Please, try again.');
						$this->redirect(array('action'=>'index'), null, true);
					}


					// parse and save categories
					if (isset($row['Product']['category_codes'])) {
						$categories = explode(',', $row['Product']['category_codes']);
						foreach ($categories as $code) {
							$category = $this->Category->findByCode($code);
							$category_id = $category['Category']['id'];
							$product_id = $row['Product']['id'];
							
							if (!empty($category_id)) {
								
								$this->CategoriesProduct->create();
								$record = array(
									'category_id' => $category_id,
									'product_id' => $product_id
								);
								$this->CategoriesProduct->save($record);
							}
						}
					}

					
				}
				$this->Session->setFlash('The Product import succeeded. ');
				$this->redirect(array('controller' => 'products', 'action'=>'index'), null, true);
				
			}

		}
		elseif ($type == 'categories') {

			if ($csv_file['error']==0) {
				$this->Category->deleteAll('1=1');
				$rows = $this->Category->importCSV($csv, "|");

				foreach($rows as $row) {
					
					// check for parent category, maps code to id
					if (isset($row['Category']['parent_id'])) {
						$parent_id = $this->Category->findByCode("{$row['Category']['parent_id']}");
						$row['Category']['parent_id'] = $parent_id['Category']['id'];
					}
					$this->cleanUpFields();
					$this->Category->create();
				    if (!$this->Category->save($row['Category'])) {
						$this->Session->setFlash('The Categories import failed. Please, try again.');
						$this->redirect(array('action'=>'index'), null, true);
					}
				}
				$this->Session->setFlash('The Categories import succeeded. ');
				$this->redirect(array('controller' => 'categories', 'action'=>'index'), null, true);
				
			}
		}
		else {
			$this->Session->setFlash('Import failed.  No type selected.');
			$this->redirect(array('action'=>'index'), null, true);			
		}
	}
	

}
