<?php 

loadModel('ProductsCategory');

class ProductsCategoryTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new ProductsCategory();
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