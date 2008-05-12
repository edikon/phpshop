<?php

class thumbnailsGen {

  var $new_size;
  var $aspect;
  
  function  thumbnailsGen($ns=100,$asp ='sq')
  {
	$this->new_size = $ns;
	$this->aspect = $asp;
  }

  function generate($src_file, $dest_file)
  {
  	if (!function_exists('imagecreatefromjpeg')) {
  		echo 'PHP running on your server does not support the GD image library.';
  		exit;
  	}
  	if (!function_exists('imagecreatetruecolor')) {
  		echo 'PHP running on your server does not support GD version 2.x.';
  		exit;
  	}

  	$info = getimagesize($src_file);

  	if ($info == null) {
  		return false;
  	}

  	if ($info[2] < 1 || $info[2] > 3 ) {
  		return false;
  	}

  	switch ($this->aspect) {
  		case 'ht':
  			$ratio = $info[1] / $this->new_size;
  			break;
  		case 'wd':
  			$ratio = $info[0] / $this->new_size;
  			break;
  		case 'sq':
  			$ratio = min($info[0], $info[1]) / $this->new_size;;
  			break;
  		default:
  			$ratio = max($info[0], $info[1]) / $this->new_size;  			
  	}

  	$clipX = 0;
  	$clipY = 0;

  	$ratio = max($ratio, 1.0);
  	if ($this->aspect == 'sq'){
  		$new_width = (int)(min($info[0],$info[1]) / $ratio);
  		$new_height = (int)(min($info[0],$info[1]) / $ratio);
  		if($info[1] > $info[0]){
  			$clipX = 0;
  			$clipY = ((int)($info[1] - $info[0])/2);
  			$info[1] = $info[0];
  		}elseif($info[0] > $info[1]){
  			$clipX = ((int)($info[0] - $info[1])/2);
  			$clipY = 0;
  			$info[0] = $info[1];
  		}
  	}else{
  		$new_width = (int)($info[0] / $ratio);
  		$new_height = (int)($info[1] / $ratio);
  	}


  	if ($info[2] == 1 )
  		$original = imagecreatefromgif($src_file);
  	elseif ($info[2] == 2)
  		$original = imagecreatefromjpeg($src_file);
  	else
  		$original = imagecreatefrompng($src_file);
  		
  	if (!$original){
  		return false;
  	}
  	
  	if ($info[2] == 1 ) {
  		$dst_img = imagecreate($new_width, $new_height);
  	} else {
  		$dst_img = imagecreatetruecolor($new_width, $new_height);
  	}

  	imagecopyresampled($dst_img, $original, 0, 0, $clipX, $clipY, (int)$new_width, (int)$new_height, $info[0], $info[1]);
  	imagejpeg($dst_img, $dest_file, 80);
  	imagedestroy($original);
  	imagedestroy($dst_img);

  	$info = getimagesize($dest_file);
  	if ($info == null) {
  		@unlink($dest_file);
  		return false;
  	} else {
  		return true;
  	}
  }
}
?>