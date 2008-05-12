<?php 

loadController('TaxRates');

class TaxRatesControllerTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new TaxRatesController();
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