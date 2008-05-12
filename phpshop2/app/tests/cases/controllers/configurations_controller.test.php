<?php 

loadController('Configurations');

class ConfigurationsControllerTestCase extends UnitTestCase {
	var $TestObject = null;

	function setUp() {
		$this->TestObject = new ConfigurationsController();
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