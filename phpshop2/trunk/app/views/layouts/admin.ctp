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
 * @subpackage		phpshop.app.views.layout
 * @since			phpShop(tm)
 * @version			$Revision:$
 * @modifiedby		$LastChangedBy:$
 * @lastmodified	$Date:$
 * @license			http://www.opensource.org/licenses/gpl-license.php The GNU General Public License
 */
?>
<?php echo $html->docType('xhtml-strict'); ?>
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
	
	<!-- Dependencies -->  
	<script type="text/javascript" src="<?php echo ini_get('session.cookie_path') ?>yui/build/yahoo-dom-event/yahoo-dom-event.js"></script> 
	<script type="text/javascript" src="<?php echo ini_get('session.cookie_path') ?>yui/build/container/container_core-min.js"></script> 

	<!-- Menu  + CSS --> 
	<script type="text/javascript" src="<?php echo ini_get('session.cookie_path') ?>yui/build/menu/menu-min.js"></script> 
	<link rel="stylesheet" type="text/css" href="<?php echo ini_get('session.cookie_path') ?>yui/build/menu/assets/skins/sam/menu.css"> 	

	<!-- Button  + CSS --> 
	<script type="text/javascript" src="<?php echo ini_get('session.cookie_path') ?>yui/build/element/element-beta-min.js"></script> 
	<script type="text/javascript" src="<?php echo ini_get('session.cookie_path') ?>yui/build/button/button-min.js"></script> 
	<link rel="stylesheet" type="text/css" href="<?php echo ini_get('session.cookie_path') ?>yui/build/button/assets/skins/sam/button.css"> 	

	<!-- RTF Editor + CSS -->
	<script src="<?php echo ini_get('session.cookie_path') ?>yui/build/editor/editor-beta-min.js"></script>
	<link rel="stylesheet" type="text/css" href="<?php echo ini_get('session.cookie_path') ?>yui/build/editor/assets/skins/sam/editor.css"> 
		
	<!-- Additional JS -->		
	<?php if(isset($javascript)) { echo $javascript->link(array('prototype.js','scriptaculous.js?load=effects')); } ?>
	<?php if (isset($autoload)) echo $autoload->css(); ?>
	
	<!-- Yahoo Menu Class -->
     <script type="text/javascript">
         YAHOO.util.Event.onContentReady("adminmenu", function () {
         var oMenuBar = new YAHOO.widget.MenuBar("adminmenu", { 
                                                         autosubmenudisplay: true, 
                                                         hidedelay: 750, 
                                                         lazyload: true });
         oMenuBar.render();

         });
     </script>
    
</head>
<body class="yui-skin-sam">
<div id="doc3" class="yui-t7">

	<div id="hd">
	<div id="yui-g">
		<div id="yui-u">
				<h1>&nbsp;</h1>
		</div>
		<div id="yui-u" class="topnav">
			<a href="<?php echo ini_get('session.cookie_path') ?>">Store</a> -
			<a href="<?php echo ini_get('session.cookie_path') ?>users/logout">Logout</a>
		</div>
	</div>

		<?php echo $this->renderElement('admin_menu'); ?>	
				
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
			Build: 20080415<br />
			Copyright Edikon Corporation
	</div>
</div>
</body>
</html>