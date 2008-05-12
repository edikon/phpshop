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
<?php 
/**
 * Currency Helper, responsible for formatting currency correctly.
 * This class uses the NumberHelper class, but was necessary in order to apply options globally.
 */
class CurrencyHelper extends Helper 
{

/**
 * Helpers
 *
 * @var array
 * @access private
 */
    var $helpers = Array('Number');

/**
 * Returns a currency formatted string.
 *
 * @param float $number a number representing a currency amount
 * @return boolean
 */
    function format($amount)
    {
		return $this->Number->currency($amount, Configure::read('Store.currency'));
		
    }
}
?> 
