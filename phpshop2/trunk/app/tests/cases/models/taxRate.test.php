<?php 

loadModel('TaxRate');

class TaxRateTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new TaxRate();
	}

	function tearDown() {
		unset($this->TestObject);
	}

	/*
	function testMe() {
		$result = $this->TestObject->findAll();
		$expected = 1;
		$this->assertEqual($result, $expected);
	}
	*/
}
?>