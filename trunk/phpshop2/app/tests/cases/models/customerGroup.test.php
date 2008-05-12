<?php 

loadModel('CustomerGroup');

class CustomerGroupTestCase extends UnitTestCase {
	var $object = null;

	function setUp() {
		$this->object = new CustomerGroup();
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