<?php
/* SVN FILE: $Id:$ */
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
?>
<div id="adminmenu" class="yuimenubar yuimenubarnav">
<div class="bd">
   <ul class="first-of-type">
   <li class="yuimenubaritem first-of-type"><a class="yuimenubaritemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/settings">Home</a>
   </li>
   <li class="yuimenubaritem"><a class="yuimenubaritemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/orders">Orders</a>                            
     </li>
    <li class="yuimenubaritem"><a class="yuimenubaritemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/customers">Customers</a>                           
     </li>
    <li class="yuimenubaritem"><a class="yuimenubaritemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/products">Products</a>
         <div id="products" class="yuimenu">
         <div class="bd">                    
         <ul>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/products">Products</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/brands">Brands</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/product_types">Product Types</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/categories">Categories</a></li>
         </ul>
         </div>
         </div>                                 
     </li>
    <li class="yuimenubaritem"><a class="yuimenubaritemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/settings">Settings</a>
		 <div id="settings" class="yuimenu">
         <div class="bd">
         <ul>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/settings">Settings</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>admin/users">Users</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/countries">Countries</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/shipping_rates">Shipping</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/order_statuses">Order Statuses</a></li>
         <li class="yuimenuitem"><a class="yuimenuitemlabel" href="<?php echo ini_get('session.cookie_path') ?>/admin/import_export">Import/Export</a></li>
         </ul>
         </div>
         </div>                  
    </li>
     </ul>            
</div>
</div>
