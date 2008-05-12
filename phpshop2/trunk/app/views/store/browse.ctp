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
<?php if (isset($categories)): ?>
<h1>Categories</h1>

<p>Washupito's Tiendita carries the products that you need.  We are proud to bring you the best line of products for your use and enjoyment.  If you need any assistance with your purchase, please do not hesitate to contact us.</p> 
<p>You can browse our products by selecting from our categories below.</p>
 
<br>
<?php foreach ($categories as $category): ?>
	<?php echo $html->link($category['Category']['name'], 
		array('action'=>'browse', $category['Category']['handle'])); ?>&nbsp; &nbsp;
<?php endforeach; ?>



<?php else: ?>

<h1><?php echo $category['Category']['name'] ?></h1>

<?php if (isset($category['Category']['description'])): ?>
<div class="description">
	<?php echo $category['Category']['description'] ?>
</div>
<?php endif; ?>


<?php if (isset($category['Product'])): ?>

<div id="results">

<ul>
<?php $i=0; foreach ($category['Product'] as $product): ?>
<?php if ($product['active']): ?>
<li>
<?php
	echo $html->link( 
		 $html->image('products/' . $product['ProductImage'][0]['image'], array("alt"=>$product['name'])), 
		 array('action'=>'flypage', $product['handle']), null, null,false); 
	?>
	<br><?php echo $html->link($product['name'], array('action'=>'flypage', $product['handle'])); ?>
	<?php echo $currency->format($product['ProductItem'][0]['sell_price']); ?> 
</li>
<?php endif; ?>
<?php endforeach; ?>
</ul>
</div>
<?php endif; ?>

<?php endif; ?>




