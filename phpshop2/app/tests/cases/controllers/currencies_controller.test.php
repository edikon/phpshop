<?php 

loadController('Currencies');

class CurrenciesControllerTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new CurrenciesController();
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