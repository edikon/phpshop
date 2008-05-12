<?php 

loadModel('CustomerBasket');

class CustomerBasketTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new CustomerBasket();
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