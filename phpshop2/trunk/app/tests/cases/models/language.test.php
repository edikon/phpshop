<?php 

loadModel('Language');

class LanguageTestCase extends UnitTestCase {
	var $object = null;

	function setUp() {
		$this->object = new Language();
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