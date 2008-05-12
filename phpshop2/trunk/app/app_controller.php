<?php
/* SVN FILE: $Id: app_controller.php 423 2008-05-12 22:28:15Z pablo $ */
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

 class AppController extends Controller {
	
 	var $helpers = array('Html','Javascript');
	
 	/**
 	 * Called before every controller action.
 	 * A useful place to check for active sessions and check roles.
 	 *
 	 */
 	 function beforeFilter() {	
	
		// load configuration settings and save them globally
		
		// need to check if the database has already been configured
		// PS_INSTALLED needs to be defined in database.php.  this is done by the installer
		if (defined('PS_INSTALLED')) {
			
			App::import('Model', 'Setting');
			$setting =& new Setting();
		
			$SA = $setting->findAll();
			$settings = Set::combine($SA, "{n}.Setting.key", "{n}.Setting.value");
			Configure::write($settings);
		}
	
	 	// request login if admin route
 	 	if (isset($this->params[Configure::read('Routing.admin')])) {
			$this->checkAdminSession();
 	 	}
 	 }

 	/**
 	 * Called before every render.
 	 *
 	 */	
 	 function beforeRender() {

 	 	// select admin or default layout
 	 	if (isset($this->params[Configure::read('Routing.admin')])) {
 	 		$this->layout = "admin";
 	 	}
 	 }


	/**
	* Validation for admin users 
	*/
	function checkAdminSession()
    {
        // If the session info hasn't been set...
        if (!$this->Session->check('User'))
        {
            // Force the user to login
            $this->redirect('/users/login');
            exit();
        }
        else return true;
    }


	/**
	* Customer validation
	*/
    function checkSession()
    {
        // If the session info hasn't been set...
        if (!$this->Session->check('Customer'))
        {
            // Force the user to login
            $this->redirect('/store/login');
            exit();
        }
    }
 }
 ?>
