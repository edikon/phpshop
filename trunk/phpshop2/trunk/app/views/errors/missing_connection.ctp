<?php
/* SVN FILE: $Id: missing_connection.ctp 4605 2007-03-09 23:26:37Z phpnut $ */
?>
<h1><?php __('phpShop Requires a Database Connection'); ?></h1>
<?php echo sprintf(__('Confirm you have created the file : %s.', true), APP_DIR.DS."config".DS."database.php");?>
<p class="error"><?php echo sprintf(__('Missing Database Connection: %s requires a database connection', true), $model);?></p>
<p><span class="notice"><strong><?php __('Fatal'); ?>: </strong>
<?php echo sprintf(__('Confirm you have created the file : %s.', true), APP_DIR.DS."config".DS."database.php");?></span></p>

<h2><a href='install'>Install phpShop Now</h2>
