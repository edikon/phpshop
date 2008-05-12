<?php
/*
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_include.inc,v 1.1.1.1 2004/07/27 14:58:55 pablo Exp $
 *
 */

// Load Classes
require_once("product/lib/ps_product.inc");
require_once("product/lib/ps_product_category.inc");
require_once("product/lib/ps_product_attribute.inc");
require_once("product/lib/ps_product_price.inc");

// Instantiate Classes
$ps_product = new ps_product;
$ps_product_category = new ps_product_category;
$ps_product_attribute = new ps_product_attribute;
$ps_product_price = new ps_product_price;

?>
