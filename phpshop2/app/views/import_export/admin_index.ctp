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
<div class="import">

<h2>Export/Import Data</h2>

<p>You can export data for use with other systems or to update your current catalog offline.</p>


<h3>Category Data</h3>

<p>You can import/export categories using a comma separated value file.</p>
<br />
<p><?php echo $html->link('Export Categories', array('action'=>'export', 'categories')) ?></p>
<br />

<h4>Import Categories</h4>

<?php echo $form->create(null,array('url'=>array('action'=>'import', 'categories'), 'enctype'=>'multipart/form-data')); ?>
<?php echo $form->input('csv_file', array('type'=>'file')); ?><?php echo $form->submit('Upload');?>
</form>

<h3>Product Data</h3>

<p>You can import/export products using a CSV file.</p>
<br />
<p><?php echo $html->link('Export Products', array('action'=>'export', 'products')) ?></p>

<br />

<h4>Import Products</h4>
<?php echo $form->create(null,array('url'=>array('action'=>'import', 'products'), 'enctype'=>'multipart/form-data')); ?>
<?php echo $form->input('csv_file', array('type'=>'file')); ?><?php echo $form->submit('Upload');?>
</form>

</div>

