<?php
/*
 * ps_include for admin module
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_include.inc,v 1.1.1.1 2004/07/27 14:58:33 pablo Exp $
 *
 */
// Load class files
require_once("admin/lib/ps_html.inc");
require_once("admin/lib/ps_function.inc");
require_once("admin/lib/ps_module.inc");
require_once("admin/lib/ps_perm.inc");
require_once("admin/lib/ps_user.inc");
require_once("admin/lib/ps_user_address.inc");
require_once("admin/lib/ps_session.inc");

// Instantiate classes
$ps_html = new ps_html;
$ps_function = new ps_function;
$ps_module= new ps_module;
$ps_perm= new ps_perm;
$ps_user= new ps_user;
$ps_user_address = new ps_user_address;
$ps_session = new ps_session;


?>
