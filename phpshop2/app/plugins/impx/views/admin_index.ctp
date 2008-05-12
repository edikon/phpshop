<div class="import">
<h2>Export/Import Data</h2>

<h3>Export Data</h3>

<p>You can export data for use with other systems or to update your current catalog offline.</p>

<ul>
<li><?php echo $html->link('Export Categories', array('action'=>'export', 'categories')) ?></li>
<li><?php echo $html->link('Export Products', array('action'=>'export', 'products')) ?></li>
</ul>


<h3>Import Data</h3>

<p>You can import your data from other systems or a previous export.</p>




<ul>
<li>Import Categories

<?php echo $form->create(null,array('url'=>array('action'=>'import', 'categories'), 'enctype'=>'multipart/form-data')); ?>
<?php echo $form->input('csv_file', array('type'=>'file')); ?><?php echo $form->submit('Upload');?>
</form>

</li>

<li>Import Products

<?php echo $form->create(null,array('url'=>array('action'=>'import', 'products'), 'enctype'=>'multipart/form-data')); ?>
<?php echo $form->input('csv_file', array('type'=>'file')); ?><?php echo $form->submit('Upload');?>
</form>

</li>
</ul>

</div>

