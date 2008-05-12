<?php 

loadModel('ProductDescription');

class ProductDescriptionTestCase extends UnitTestCase {
	var $object = null;

	function setUp() {
		$this->object = new ProductDescription();
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