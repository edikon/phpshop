<?php
/*
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_include.inc,v 1.1.1.1 2004/07/27 14:59:45 pablo Exp $
 *
 */

// Load Classes
require_once("store/lib/ps_payment_method.inc");
require_once("store/lib/nh_report.inc");

// Instantiate Classes
$ps_payment_method = new ps_payment_method;
$nh_report = new nh_report;

?>
