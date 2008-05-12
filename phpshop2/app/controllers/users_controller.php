<?php
/* SVN FILE: $Id: users_controller.php 423 2008-05-12 22:28:15Z pablo $ */
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

class UsersController extends AppController {

	var $name = 'Users';
	var $helpers = array('Html', 'Form');

	function admin_index() {
		$this->User->recursive = 0;
		$this->set('users', $this->paginate());
	}

	function admin_view($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid User.', true));
			$this->redirect(array('action'=>'index'));
		}
		$this->set('user', $this->User->read(null, $id));
	}

	function admin_add() {
		if (!empty($this->data)) {
			$this->User->create();
			if ($this->User->save($this->data)) {
				$this->Session->setFlash(__('The User has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The User could not be saved. Please, try again.', true));
			}
		}
	}

	function admin_edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(__('Invalid User', true));
			$this->redirect(array('action'=>'index'));
		}
		if (!empty($this->data)) {
			if ($this->User->save($this->data)) {
				$this->Session->setFlash(__('The User has been saved', true));
				$this->redirect(array('action'=>'index'));
			} else {
				$this->Session->setFlash(__('The User could not be saved. Please, try again.', true));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->User->read(null, $id);
		}
	}

	function admin_delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(__('Invalid id for User', true));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->User->del($id)) {
			$this->Session->setFlash(__('User deleted', true));
			$this->redirect(array('action'=>'index'));
		}
	}

	function login()
    {
		$this->pageTitle = "Login";
		$this->layout = 'admin_login';
		
        //Don't show the error message if no data has been submitted.
        $this->set('error', false);

        // If a user has submitted form data:
        if (!empty($this->data))
        {
            // First, let's see if there are any users in the database
            // with the username supplied by the user using the form:

            $someone = $this->User->findByUsername($this->data['User']['username']);

            // At this point, $someone is full of user data, or its empty.
            // Let's compare the form-submitted password with the one in
            // the database.

            if(!empty($someone['User']['password']) && 
					$someone['User']['password'] == $this->data['User']['password'])
            {
                // Note: hopefully your password in the DB is hashed,
                // so your comparison might look more like:
                // md5($this->data['User']['password']) == ...

                // This means they were the same. We can now build some basic
                // session information to remember this user as 'logged-in'.

				// We do not want to store password in the session. 
				unset($someone['User']['password']);
                $this->Session->write('User', $someone['User']);

				// Confirm login was success
                $this->Session->setFlash('You\'ve successfully logged in.'); 


                // Now that we have them stored in a session, forward them on
                // to a landing page for the application.

                $this->redirect('/admin/orders/');
            }
            // Else, they supplied incorrect data:
            else
            {
                // Remember the $error var in the view? Let's set that to true:
                $this->set('error', true);
            }
        }
    }

    function logout()
    {
        // Redirect users to this action if they click on a Logout button.
        // All we need to do here is trash the session information:

        $this->Session->delete('User');

        $this->Session->setFlash('You\'ve successfully logged out.'); 

        // And we should probably forward them somewhere, too...
     
        $this->redirect('/');
    }
}
?>