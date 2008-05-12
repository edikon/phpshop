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
	
<h1><?php echo $product['Product']['name']?> by <?php echo $product['Brand']['name']; ?></h1>

<table id="flypage">
<tr>
<td valign="top">
	<div>
	<?php echo $product['Product']['description'] ?>
	</div>

	<div>
	<form action="<?php echo $html->url("/store/cart"); ?>" method="get">
	<h3>Select Item</h3>
	<?php $i=0; foreach ($product['ProductItem'] as $product_item): ?>	
<p>		<?php // $i is used to check the first item in the list. ?>
		<input type="radio" name="product_item_id" value="<?php echo $product_item['id'] ?>" 
		<?php if ($i++==0): echo "checked";else: echo ""; endif;?>> 
		<strong><?php echo $currency->format($product_item['sell_price']) ?></strong> 
		- <?php echo $product_item['label']; ?><?php if ($product_item['regular_price'] > 0): ?>, Regular Price: <?php echo $currency->format($product_item['regular_price']) ?>
		<?php endif; ?>
	</p><?php endforeach; ?>
	</div>
	<input type="hidden" name="action" value="add">
	<div><input type="submit" name="submit" value="Add to Cart"></div>
	
	</form>

	<?php if (isset($product['Category']) && count($product['Category'])): ?>
	<div>
	<h3>Related Categories</h3>
	<?php
	foreach ($product['Category'] as $category) {
		if ($category['handle'] != 'home') {
			echo $html->link($category['name'], array('action'=>'browse', $category['handle'])) . "&nbsp;&nbsp;&nbsp;";
		}
	}
	?>
	</div>
	<?php endif; ?>

</td>

<td>
<?php echo $html->image('products/' . $product['ProductImage'][0]['image'], array("alt"=> $product['ProductImage'][0]['image'])); ?>
</td>


</tr></table>