<?php 

loadController('Manufacturers');

class ManufacturersControllerTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new ManufacturersController();
	}

	function tearDown() {
		unset($this->TestObject);
	}

	/*
	function testMe() {
		$result = $this->TestObject->index();
		$expected = 1;
		$this->assertEqual($result, $expected);
	}
	*/
}
?>