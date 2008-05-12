<?php 

loadModel('OrderPayment');

class OrderPaymentTestCase extends CakeTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new OrderPayment();
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