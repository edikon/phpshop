<?php
/**
 * Automatically loading controller- and action-specific JS and CSS files v. 0.2
 *
 * By Jiri Kupiainen (http://jirikupiainen.com/)
 *
 * You are free to do whatever you please with this code. Enjoy.
 */
class AutoloadHelper extends Helper {
	var $helpers = array('Html', 'Javascript');

	var $_controller = '';
	var $_action = '';

	function beforeRender() {
		$this->_controller = ife($this->params['controller'], $this->params['controller'], '');
		$this->_action = ife($this->params['action'], $this->params['action'], '');
	}

	/**
	 * Call this function inside your layout's head tag where you have your other external JS files
	 */
	function js() {
		return $this->_doJs($this->_controller).$this->_doJs($this->_controller.'_'.$this->_action);
	}

	/**
	 * Call this function inside your layout's head tag where you have your other external CSS files
	 */
	function css() {
		return $this->_doCss($this->_controller).$this->_doCss($this->_controller.'_'.$this->_action);
	}

	/**
	 * Check a CSS file exists and link to it
	 */
	function _doCss($name) {
		if (file_exists(WWW_ROOT.'css'.DS.$name.'.css')) {
			return $this->Html->css($name)."\n";
		}
		return false;
	}

	/**
	 * Check a JS file exists and link to it
	 */
	function _doJs($name) {
		$name = $name.'.js';

		if (file_exists(WWW_ROOT.'js'.DS.$name)) {
			return $this->Javascript->link($name)."\n";
		}

		return false;
	}
}
?>
