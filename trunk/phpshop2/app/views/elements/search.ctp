<div id="search">
<?php echo $form->create('Search');?>
	<fieldset><legend><?php __('Search');?></legend>
	<?php
		echo $form->input('Text');
		echo $form->input('Field', array('options' => $fields));
		echo $ajax->submit('Search', array('url' => 'search', 'update'=>'list',
							 'loading'  => "Element.show('searching')",
							 'complete'=>"Element.hide('searching');
							"));

	?>
		<div id="searching" style="display:none; padding:4px;color:black;width:100px">
		<?php echo $html -> image("spinner.gif") ?></p><strong>Searching…</strong>
		</div>
	</fieldset>
	</form>
</div>
	
