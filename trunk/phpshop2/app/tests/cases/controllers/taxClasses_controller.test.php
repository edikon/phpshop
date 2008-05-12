<?php 

loadController('TaxClasses');

class TaxClassesControllerTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new TaxClassesController();
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