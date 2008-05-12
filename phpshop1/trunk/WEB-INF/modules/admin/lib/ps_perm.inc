<?php
/*
 * ps_perm Class
 *
 * Copyright (c) Edikon Corporation.  All rights reserved.
 * Distributed under the phpShop Public License (pSPL) Version 1.0.
 *
 * $Id: ps_perm.inc,v 1.1.1.1 2004/07/27 14:58:34 pablo Exp $
 *
 */




class ps_perm {

  var $permissions = array(
			   "shopper" 	=>  "1",
			   "demo" 	=>  "2",
			   "storeadmin" =>  "4",
			   "admin" 	=>  "8" 
			);

   function check($perms) {
     global $auth;
     $db = new ps_DB;

     // Parse all permissions in argument, comma separated
     // It is assumed auth_user only has one group per user.
     if ($perms == "none") {
	return True;
     }
     else {
       $p1 = explode(",", $auth["perms"]);
       $p2 = explode(",", $perms);
       while (list($key1, $value1) = each($p1)) {
	 while (list($key2, $value2) = each($p2)) {
	   if ($value1 == $value2) {
	     return True;
	   }
	 }
       }
     }
     return False;    
   }


}


?>
