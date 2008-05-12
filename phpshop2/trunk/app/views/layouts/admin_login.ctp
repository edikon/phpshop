<?php
/* SVN FILE: $Id:$ */
/**
 *
 * PHP versions 4 and 5
 *
 * phpShop(tm) :  A Simple Shopping Cart <http://www.phpshop.org/>
 * Copyright 1998-2008, 	Edikon Corporation
 *							3455 Peachtree Road Suite 500
 *							Atlanta, Georgia 30326
 *
 * Licensed under The GNU General Public License
 * Redistributions of files must retain the above copyright notice.
 *
 * @filesource
 * @copyright		Copyright 1998-2008, Edikon Corporation
 * @link			http://www.edikon.com/ phpShop(tm) Project
 * @package			phpshop
 * @subpackage		phpshop.app.controllers
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<?php echo $html->docType('html4-strict'); ?>
<html>
<head>
	<title>phpShop : <?php echo $title_for_layout;?></title>
	<link rel="icon" href="<?php echo $this->webroot . 'favicon.ico';?>" type="image/x-icon" />
	<link rel="shortcut icon" href="<?php echo $this->webroot . 'favicon.ico';?>" type="image/x-icon" />

	<!--reset-fonts-grids.css & base.css --> 
	<link rel="stylesheet" type="text/css" href="<?php echo ini_get('session.cookie_path') ?>yui/build/reset-fonts-grids/reset-fonts-grids.css"> 
	<link rel="stylesheet" type="text/css" href="<?php echo ini_get('session.cookie_path') ?>yui/build/reset-fonts-grids/base.css"> 

	<!-- Custom CSS -->
	<?php echo $html->css(array('admin')); ?>
    
</head>
<body>
<div id="doc3" class="yui-t7">

	<div id="hd">
		<div id="yui-g">
			<div id="yui-u">
				<h1>&nbsp;</h1>
			</div>
		</div>
	</div>
	
	<div id="bd">
		
			<?php if ($session->check('Message.flash'))
					{
						$session->flash();
					}
					echo $content_for_layout;
			?>

	</div>
	
	<div id="ft">
			&nbsp;
			<a href="http://www.phpshop.org/" target="_new">phpShop : A Simple Shopping Cart</a><br />
			&copy; <?php echo $html->link("edikon", 'http://www.edikon.com'); ?>
	</div>
</div>
</body>
</html>
