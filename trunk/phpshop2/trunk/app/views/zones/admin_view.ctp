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
<div class="zones view">
<h2><?php  __('Zone');?></h2>
	<dl><?php $i = 0; $class = ' class="altrow"';?>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Id'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $zone['Zone']['id']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Country'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $html->link($zone['Country']['name'], array('controller'=> 'countries', 'action'=>'view', $zone['Country']['id'])); ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Name'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $zone['Zone']['name']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Code'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $zone['Zone']['code']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Tax Rate'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $zone['Zone']['tax_rate']; ?>
			&nbsp;
		</dd>
		<dt<?php if ($i % 2 == 0) echo $class;?>><?php __('Active'); ?></dt>
		<dd<?php if ($i++ % 2 == 0) echo $class;?>>
			<?php echo $zone['Zone']['active']; ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<ul>
		<li><?php echo $html->link(__('Edit Zone', true), array('action'=>'edit', $zone['Zone']['id'])); ?> </li>
		<li><?php echo $html->link(__('Delete Zone', true), array('action'=>'delete', $zone['Zone']['id']), null, sprintf(__('Are you sure you want to delete # %s?', true), $zone['Zone']['id'])); ?> </li>
		<li><?php echo $html->link(__('List Zones', true), array('action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Zone', true), array('action'=>'add')); ?> </li>
		<li><?php echo $html->link(__('List Countries', true), array('controller'=> 'countries', 'action'=>'index')); ?> </li>
		<li><?php echo $html->link(__('New Country', true), array('controller'=> 'countries', 'action'=>'add')); ?> </li>
	</ul>
</div>
