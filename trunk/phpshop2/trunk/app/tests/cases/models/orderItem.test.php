<?php 

loadModel('OrderItem');

class OrderItemTestCase extends CakeTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new OrderItem();
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