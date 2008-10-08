<?php
/* SVN FILE: $Id: install_controller.php 418 2008-01-31 22:37:17Z pablo $ */
/**
 *
 * PHP versions 4 and 5
 *
 * phpShop(tm) :  A Simple Shopping Cart <http://www.phpshop.org/>
 * Copyright 1998-2008,	Edikon Corporation
 *			3455 Peachtree Road Suite 500
 *			Atlanta, Georgia 30326
 *
 * Licensed under The GNU General Public License
 * Redistributions of files must retain the above copyright notice.
 *
 * @filesource
 * @copyright		Copyright 1998-2008, Edikon Corporation
 * @link		http://www.edikon.com/ phpShop(tm) Project
 * @package		phpshop
 * @subpackage		phpshop.app.controllers
 * @since		phpShop(tm)
 * @version		$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license		http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */

/**
 * InstallController for phpShop
 *
 * The controller class to install the phpShop application.
 * Adapted this this file from - Cheesecake Photoblog 
 * http://cakeforge.org/projects/cheesecake/
 *
 */
class InstallController extends AppController
{
   var $autoRender = false;

   var $uses = array();
   
   function beforeFilter() {
	  $this->components = array();
   }

   function afterFilter() {}

   function index() {
		$this->step1();
   }

   /*
	* check filesystem
	*/
   function step1() {
	   //check for database.php file,if file exits then display a message to user.
	   if ($this->__dbFileExists()){
		  echo $this->render(null,null,'db_error');
		  exit;
	   }
	   if (!function_exists('gd_info'))
	   {
		  echo $this->render(null,null,'gd_error');
		  exit;	   	
	   }
	   if($this->__testFileSystem()) {
		   echo $this->redirect('/install/step2');
		   exit;
	   }
   }
   /*
	* get the database details from user and create the database.php file
	*/
   function step2() {
		if (!$this->__dbFileExists()) {
		   $this->errors = '';
		   if($this->__createDatabase()) {
			   $this->redirect('/install/step3');
		   }
		}
		echo $this->render(null,null,'db_error');
   }

   /*
	* get admin details and create tables.
	*/
   function step3() {

	  if ($this->__createUser()) {
		 echo $this->render(null, null, 'success');
		 exit;
	  }
   }


   function __createUser()
   {
		$this->errors= '';
		@ $values['username']= ($_POST['username']) ? $_POST['username'] : '';
		@ $values['password']= ($_POST['password']) ? $_POST['password'] : '';
		@ $values['name']= ($_POST['name']) ? $_POST['name'] : '';
		@ $values['email']= ($_POST['email']) ? $_POST['email'] : '';

		if (isset ($_POST['username']) && !empty ($_POST))
		{
			if (trim($_POST['username'] == '' || $_POST['password'] == ''))
			{
				$this->errors= "It is much better for you to provide a 'username' and a 'password' for the admin.<br /><br />";
			}
			elseif (trim($_POST['email']) == '')
			{
				$this->errors .= "Please provide email address";
			}
			elseif (!preg_match('/^([_a-zA-Z0-9.]+@[-a-zA-Z0-9]+(\.[-a-zA-Z0-9]+)+)*$/', $_POST['email']))
			{
				$this->errors .= "Please provide valid email address";
			}
			else
			{
				$this->__createTables();

				return true;
				exit;
			}
		}

		$this->set('values', $values);
		$this->set('errors', $this->errors);
		$this->set(array (
			'title' => 'Install phpShop'
		));
		echo $this->render(null, null, 'admin');
		exit;
   }
   function __createDatabase()
   {

		@ $values['dbserver']= ($_POST['dbserver']) ? $_POST['dbserver'] : 'localhost';
		@ $values['dbname']= ($_POST['dbname']) ? $_POST['dbname'] : '';
		@ $values['dbuser']= ($_POST['dbuser']) ? $_POST['dbuser'] : '';
		@ $values['dbpass']= ($_POST['dbpass']) ? $_POST['dbpass'] : '';
		@ $values['table_prefix']= ($_POST['table_prefix']) ? $_POST['table_prefix'] : 'ps_';

		 if (isset ($_POST) && !empty ($_POST))
		 {
				$this->errors= '';
				$this->__testSqlConnection();
				if ($this->errors == '')
				{

					$this->__createDatabaseConfigFile();

					if ($this->errors == '')
					{
						return true;
					}
				}

		}

		$this->set('values', $values);
		$this->set('errors', $this->errors);
		$this->set(array (
			'title' => 'Install phpShop'
		));
		echo $this->render(null, null, 'database');
		exit;
   }
   function __testFileSystem()
   {
		$configDir= ROOT . '/app/config/';
		$tmpDir= ROOT . '/app/tmp/';
		$photosDir= WWW_ROOT . 'img/products';
		$thumbnailsDir= WWW_ROOT . 'img/thumbnails';
		$categoriesDir= WWW_ROOT . 'img/categories';
		$writableDirs= array (
			$configDir,
			$tmpDir,
			$photosDir,
			$thumbnailsDir,
			$categoriesDir
		);
		$areNotWriteable= array ();

		foreach ($writableDirs as $dir)
		{
			if (!is_writable($dir))
			{
				$areNotWriteable[]= $dir;
			}
		}
		if (count($areNotWriteable))
		{
			$this->set('areNotWriteable', $areNotWriteable);
			$this->set(array (
				'title' => 'Install phpShop'
			));
			echo $this->render(null, null, 'fileSystem');
			exit;
		}
		return true;
  }


   function __dbFileExists() {
		$db_file = ROOT.'/app/config/database.php';
		if (file_exists($db_file)) {
			return true;
		}
		return false;

   }
   function __testSqlConnection()
	{
		if (isset ($_POST) && !empty ($_POST))
		{
			if (!function_exists('mysql_connect'))
			{
				$this->errors .= "PHP does not have MySQL support enabled.";
			}
			elseif (!$connect_id= @ mysql_connect($_POST['dbserver'], $_POST['dbuser'], $_POST['dbpass']))
			{
				$this->errors .= "Could not create a mySQL connection, please check the values entered<br />MySQL error was : " . mysql_error() . "<br /><br />";
			}
			elseif (!mysql_select_db($_POST['dbname'], $connect_id))
			{
				$this->errors .= "MySQL database called '{$_POST['dbname']}' could not be connected using the details provided, please check the values entered for these are correct";
			}

		}
	}

	function __createDatabaseConfigFile()
	{

		$db_file= ROOT . '/app/config/database.php';
		$config_file= '/app/config/database.php';
		@ unlink($db_file);
		$config= $this->__buildCfgFile();
		if ($fd= @ fopen($db_file, 'wb'))
		{
			fwrite($fd, $config);
			fclose($fd);

		}
		else
		{
			$this->errors .= "<hr /><br />Unable to write config file '{$config_file}'<br /><br />";

		}
	}

	// ---------------------- CONFIGURATION FILE TEMPLATE ---------------------- //
	function __buildCfgFile()
	{

return<<<EOT
<?php
class DATABASE_CONFIG
{
	 var \$default = array('driver' => 'mysql',
						   'connect' => 'mysql_connect',
						   'host' => '{$_POST['dbserver']}',
						   'login' => '{$_POST['dbuser']}',
						   'password' => '{$_POST['dbpass']}',
						   'database' => '{$_POST['dbname']}',
						   'prefix' => '{$_POST['table_prefix']}');


}
define('PS_INSTALLED', 1);
?>
EOT;
	}

	function __createTables()
	{

		App::import('Model', 'ConnectionManager');
		$db= & ConnectionManager :: getDataSource('default');

		$prefix= $db->config['prefix'];
		$sqlFile= ROOT . DS . APP_DIR . DS . 'config/sql/phpshop.sql';

		$sql= file_get_contents($sqlFile);

		$sql .= "INSERT INTO `ps_users` (`username`, `password`, `role`, `name`, `email`, `created`, `modified`) VALUES ('{$_POST['username']}','{$_POST['password']}','Admin','{$_POST['name']}','{$_POST['email']}',NOW(),NOW());";

		$sql_query= preg_replace('/ps_/', $prefix, $sql);
		$sql_query= $this->__removeRemarks($sql_query);
		$sql_query= $this->__splitSqlFile($sql_query, ';');

		foreach ($sql_query as $q)
		{
			$db->query($q);
		}

	}

	// __removeRemarks will strip the sql comment lines out of an uploaded sql file
	//Adapted this function from the - Coppermine Picture Gallery http://coppermine.sf.net
	function __removeRemarks($sql)
	{
		$lines= explode("\n", $sql);
		// try to keep mem. use down
		$sql= "";

		$linecount= count($lines);
		$output= "";

		for ($i= 0; $i < $linecount; $i++)
		{
			if (($i != ($linecount -1)) || (strlen($lines[$i]) > 0))
			{
				if (isset ($lines[$i][0]) && $lines[$i][0] != "#")
				{
					$output .= $lines[$i] . "\n";
				}
				else
				{
					$output .= "\n";
				}
				// Trading a bit of speed for lower mem. use here.
				$lines[$i]= "";
			}
		}

		return $output;
	}

	// __splitSqlFile will split an uploaded sql file into single sql statements.
	// Note: expects trim() to have already been run on $sql.
	//Adapted this function from the - Coppermine Picture Gallery http://coppermine.sf.net
	function __splitSqlFile($sql, $delimiter)
	{
		// Split up our string into "possible" SQL statements.
		$tokens= explode($delimiter, $sql);
		// try to save mem.
		$sql= "";
		$output= array ();
		// we don't actually care about the matches preg gives us.
		$matches= array ();
		// this is faster than calling count($oktens) every time thru the loop.
		$token_count= count($tokens);
		for ($i= 0; $i < $token_count; $i++)
		{
			// Don't wanna add an empty string as the last thing in the array.
			if (($i != ($token_count -1)) || (strlen($tokens[$i] > 0)))
			{
				// This is the total number of single quotes in the token.
				$total_quotes= preg_match_all("/'/", $tokens[$i], $matches);
				// Counts single quotes that are preceded by an odd number of backslashes,
				// which means they're escaped quotes.
				$escaped_quotes= preg_match_all("/(?<!\\\\)(\\\\\\\\)*\\\\'/", $tokens[$i], $matches);

				$unescaped_quotes= $total_quotes - $escaped_quotes;
				// If the number of unescaped quotes is even, then the delimiter did NOT occur inside a string literal.
				if (($unescaped_quotes % 2) == 0)
				{
					// It's a complete sql statement.
					$output[]= $tokens[$i];
					// save memory.
					$tokens[$i]= "";
				}
				else
				{
					// incomplete sql statement. keep adding tokens until we have a complete one.
					// $temp will hold what we have so far.
					$temp= $tokens[$i] . $delimiter;
					// save memory..
					$tokens[$i]= "";
					// Do we have a complete statement yet?
					$complete_stmt= false;

					for ($j= $i +1;(!$complete_stmt && ($j < $token_count)); $j++)
					{
						// This is the total number of single quotes in the token.
						$total_quotes= preg_match_all("/'/", $tokens[$j], $matches);
						// Counts single quotes that are preceded by an odd number of backslashes,
						// which means they're escaped quotes.
						$escaped_quotes= preg_match_all("/(?<!\\\\)(\\\\\\\\)*\\\\'/", $tokens[$j], $matches);

						$unescaped_quotes= $total_quotes - $escaped_quotes;

						if (($unescaped_quotes % 2) == 1)
						{
							// odd number of unescaped quotes. In combination with the previous incomplete
							// statement(s), we now have a complete statement. (2 odds always make an even)
							$output[]= $temp . $tokens[$j];
							// save memory.
							$tokens[$j]= "";
							$temp= "";
							// exit the loop.
							$complete_stmt= true;
							// make sure the outer loop continues at the right point.
							$i= $j;
						}
						else
						{
							// even number of unescaped quotes. We still don't have a complete statement.
							// (1 odd and 1 even always make an odd)
							$temp .= $tokens[$j] . $delimiter;
							// save memory.
							$tokens[$j]= "";
						}
					} // for..
				} // else
			}
		}

		return $output;
	}

}

?>
