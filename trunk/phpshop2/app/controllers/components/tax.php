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

class TaxComponent extends Object {

	/**
 	* Place holder for the controller
 	*
 	* @var boolean
 	* @access private
 	*/
    var $controller = true;
    
	/**
 	* Place holder for the sanitize object
 	*
 	* @var boolean
 	* @access private
 	*/
    var $sanitize = true;
    
    var $components = array('Session');
    
    var $uses = array('Zone', 'Country');
    
    /**
     * Make sure that we can access parent controller models, etc.
     *
     * @param unknown_type $controller
     */
	function startup(&$controller) { 
        $this->Controller =& $controller; 
    } 
    
	/**
	* Returns the tax rate for the given zone_id
	* 
 	* @param integer $zone_id
 	*/
	function zone_tax_rate($zone_id) {
		
		$zone =& new Zone();
		
		// get the zone for the shipping state, also gets the country
		$z = $zone->findById($zone_id);
		
		$zone_tax_rate = $z['Zone']['tax_rate'];
		return $zone_tax_rate;
	}
	
	/**
	* Returns the total tax for the current shopping cart (session).
	* 
	* Bases finding on country_id
	* 
 	* @param integer $country_id
 	*/
	function country_tax_rate($country_id) {

		$country =& new Country();
		
		// get the zone for the shipping state, also gets the country
		$c = $country->findById($country_id);
		
		$country_tax_rate = $c['Country']['tax_rate'];
		return $country_tax_rate;
	}
	
	/**
	 * Return tax calculation for given zone and money amount.
	 *
	 * @param integer $zone_id
	 * @param float $amount
	 */
	function zone_tax_total($zone_id, $amount) {
		return round($this->zone_tax_rate($zone_id) * $amount, 2);
	}
	
	/**
	 * Return tax total for given country and money amount.
	 *
	 * @param unknown_type $country_id
	 * @param unknown_type $amount
	 * @return unknown
	 */
	function country_tax_total($country_id, $amount) {
		return round($this->country_tax_rate($country_id) * $amount, 2);
		
	}
}
?>