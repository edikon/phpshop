<?php  
/** 
 * Tree Helper. 
 * 
 * Used the generate nested representations of hierarchial data 
 * 
 * PHP versions 4 and 5 
 * 
 * Copyright (c), Andy Dawson 
 * 
 * Licensed under The MIT License 
 * Redistributions of files must retain the above copyright notice. 
 * 
 * @filesource 
 * @copyright    Copyright (c) 2007, Andy Dawson 
 * @package      noswad 
 * @subpackage   noswad.app.views.helpers 
 * @since        Noswad site version 3 
 * @version      $Revision: 206 $ 
 * @created      24/01/2008 
 * @modifiedby   $LastChangedBy: andy $ 
 * @lastmodified $Date: 2008-01-24 18:29:29 +0100 (Thu, 29 Nov 2007) $ 
 * @license      http://www.opensource.org/licenses/mit-license.php The MIT License 
 */ 

/** 
 * Tree helper 
 * 
 * Helper to generate tree representations of MPTT or recursively nested data 
 */ 
class TreeHelper extends AppHelper { 

    var $helpers = array ('Html'); 

/** 
 * Tree generation method. 
 * 
 * Accepts the results of  
 *     find('all', array('fields' => array('lft', 'rght', 'whatever'), 'order' => 'lft ASC'));
 *     children(); // if you have the tree behavior of course! 
 * or     findAllThreaded(); and generates a tree structure of the data. 
 * 
 * Settings (2nd parameter): 
 *    'model' => name of the model (key) to look for in the data array. defaults to the first model for the current
 * controller. 
 *    'alias' => the array key to output for a simple ul (not used if element is specified) 
 *    'type' => type of output defaults to ul 
 *    'itemType => type of item output default to li 
 *    'class' => class for top level 'item' 
 *    'element' => path to an element to render to get node contents. 
 * 
 * @param array $data data to loop on 
 * @param array $settings 
 * @return string html representation of the passed data 
 * @access public 
 */ 
    function generate ($data, $settings = array ()) { 
        $element = false; 
        $class = false; 
        $model = false; 
        $options = ''; 
        $alias = 'name'; 
        $left = 'lft'; 
        $right = 'rght'; 
        $type = 'ul'; 
        $itemType = 'li'; 
        extract($settings); 

        $view =& ClassRegistry:: getObject('view'); 
        if (!$model) { 
            $model = Inflector::classify($view->params['models'][0]); 
        } 
        $stack = array(); 
        if ($class) { 
            $options .= ' class="' . $class . '" '; 
        } 
        $return = "\r\n" . '<' . $type . $options. '>'; 
        foreach ($data as $i => $result) { 
            // Prefix 
            while ($stack && ($stack[count($stack)-1] < $result[$model][$right])) { 
                array_pop($stack); 
                $return .= "\r\n" . str_repeat("\t",count($stack) + 1) . '</' . $type . '>';
                $return .= '</' . $itemType . '>'; 
            } 
            $return .= "\r\n" . str_repeat("\t",count($stack) + 1) . '<' . $itemType . '>'; 

            // Main Content 
            if ($element) { 
                $return .= $view->renderElement($element,array('data' => $result)); 
            } else { 
                $return .= $this->Html->link($result[$model][$alias], array('controller' => 'store', 'action' => 'browse', $result[$model]['handle'])); 
            } 

            // Suffix 
            if (!isset($result[$model][$right]) || !isset($result[$model][$left]) || isset($result['children'])) { 
                if (isset($result['children'])) { 
                    unset($settings['class']); 
                    $return .= $this->generate($result['children'], $settings); 
                } 
                $return .= '</' . $itemType . '>'; 
            } elseif ($result[$model][$right] == $result[$model][$left] + 1) { // Has no children 
                $return .= '</' . $itemType . '>'; 
            } else { 
                $return .= '<' . $type . '>'; 
                $stack[] = $result[$model][$right]; 
            } 
        } 
        while ($stack) { 
            array_pop($stack); 
            $return .= "\r\n" . str_repeat("\t",count($stack) + 1) . '</' . $type . '>'; 
            $return .= '</' . $itemType . '>'; 
        } 
        $return .= "\r\n" . '</' . $type . '>' . "\r\n"; 
        return $return; 
    } 
} 
?>