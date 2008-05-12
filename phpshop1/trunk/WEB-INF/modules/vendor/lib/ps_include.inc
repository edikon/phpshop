<?php
/*
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_include.inc,v 1.1.1.1 2004/07/27 14:59:51 pablo Exp $
 *
 */

// Load Classes
require_once("vendor/lib/ps_vendor.inc");
require_once("vendor/lib/ps_vendor_category.inc");


// Instantiate Classes
$ps_vendor = new ps_vendor;
$ps_vendor_category = new ps_vendor_category;
?>
