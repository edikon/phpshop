<?php
/*
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_include.inc,v 1.1.1.1 2004/07/27 14:58:48 pablo Exp $
 *
 */

// Load classes
require_once("order/lib/ps_order.inc");
require_once("order/lib/ps_order_status.inc");

// Instantiate Classes
$ps_order = new ps_order;
$ps_order_status = new ps_order_status;


?>
