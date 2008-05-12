<?php
class nh_report {
  var $classname = "nh_report";
  
  /**************************************************************************
  ** name: make_date_popups
  ** created by: nhyde
  ** description: prints month, day, and year popups
  ** parameters: menu_name string to append to select names
  **             sel_date int in YYYYMMDD format
  ** returns: True
  ***************************************************************************/  
  
  function make_date_popups ($menu_name='', $sel_date = '') {
  // prepare vars for printing select menus
	$yr = date("Y");
	if ($sel_date) {
		$eta_yr = substr($sel_date,0,4);
		$eta_month = substr($sel_date,4,2);
		$eta_day = substr($sel_date,6,2);
	} else {
		$eta_yr = $yr;
		$eta_month = date("m");
		$eta_day = date("d");
		$eta_auto_set = 1;
	}
	$popup = '<select name="'. $menu_name . 'month">';
	// BEGIN print month popup
		for ($i = 1; $i <= 12; $i++) {
			$t_month = sprintf("%02d", $i);
			$popup .= "\n\t".'<option value="'.$t_month.'"';
			if ($t_month == $eta_month) { $popup .= " selected=\"selected\""; }
			$popup .= '>'.date("F", mktime(0,0,0,$t_month,01,$eta_year)) . "</option>";
		}
		$popup .= "\n";
	// end print month popup

	$popup .= "</select>\n\t".'<select name="'. $menu_name . 'day">';
		for ($i=1;$i<=31;$i++) {
			$t_day = sprintf("%02d", $i);
			$popup .= "\n\t<option value=\"".$t_day.'"';
			if ($t_day == $eta_day) { $popup .= " selected=\"selected\""; }
			$popup .= '>'.$i . "</option>";
		}
		$popup .= "\n";
	$popup .= "</select>\n\t".'<select name="'. $menu_name . 'year">';
		for ($i = -3; $i<=0; $i++) {
			$print_year = ($yr+$i);
			$popup .= "\n\t".'<option value="'.$print_year.'"';
			if ($print_year == $eta_yr) { $popup .= " selected=\"selected\""; }
			$popup .= '>'.$print_year . "</option>";
		}
		$popup .= "\n";
	$popup .= '</select><br />';
	echo $popup;
  return True;
  }
}

?>