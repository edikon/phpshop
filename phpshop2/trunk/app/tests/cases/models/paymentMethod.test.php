<?php 

loadModel('PaymentMethod');

class PaymentMethodTestCase extends CakeTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new PaymentMethod();
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