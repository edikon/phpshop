<?php 

loadController('Languages');

class LanguagesControllerTestCase extends UnitTestCase {
	var $object = null;

	function setUp() {
		$this->object = new LanguagesController();
	}

	function tearDown() {
		unset($this->object);
	}

	/*
	function testMe() {
		$result = $this->object->doSomething();
		$expected = 1;
		$this->assertEqual($result, $expected);
	}
	*/
}
?>