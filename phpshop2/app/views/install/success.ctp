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
 * @subpackage		phpshop.app.views.install
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
 <div>
  <div id="successMessage" class="message">
  phpShop has been installed successfully.
  </div>
  <div class="image-info">
  <p>For the better security please change the permissions of config directory to 755. Also be sure to change 
  settings to suit your site.</p>
  <form method="post" action="<?php echo $this->webroot; ?>">
  <p align="center">
  <input type="submit" value="Continue" name="Continue"/>
  </p>
  </div>
  </form>
</div>