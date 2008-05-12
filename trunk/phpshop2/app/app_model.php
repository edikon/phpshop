<?php
/* SVN FILE: $Id: app_model.php 409 2008-01-24 18:04:51Z pablo $ */
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
 * @subpackage		phpshop.app
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

class AppModel extends Model{


	function saveFullImage($full_image) {
		$fimage = null;
		if (isset($full_image['name'])&&(!empty($full_image['name']))) {
			$fimage =  $full_image['name'];
			move_uploaded_file($full_image['tmp_name'],WWW_ROOT . "img/products/".$fimage);
		}
		return $fimage;
	}

	function saveThumbImage($thumb_image) {
		$timage = null;
		if (isset($thumb_image['name'])&&(!empty($thumb_image['name']))) {
			$timage = $thumb_image['name'];
			move_uploaded_file($thumb_image['tmp_name'],WWW_ROOT . "img/products/".$timage);
		}
		return $timage;
	}

}
?>
