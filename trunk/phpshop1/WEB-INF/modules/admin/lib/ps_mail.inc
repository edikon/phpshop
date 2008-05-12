<?php

require_once('admin/lib/ps_smtp.inc');

class ps_mail {
	
	function ps_mail() {
		
		$this->params['host'] = SMTP_HOST;				// The smtp server host/ip
		$this->params['port'] = SMTP_PORT;				// The smtp server port
		$this->params['helo'] = exec('hostname');		// What to use when sending the helo command. Typically, your domain/hostname
		$this->params['auth'] = SMTP_AUTH;				// Whether to use basic authentication or not
		$this->params['user'] = SMTP_USER;				// Username for authentication
		$this->params['pass'] = SMTP_PASS;

	}

	function send($to, $subject, $message, $from) {
	
		if (SMTP_ENABLED) {
			// Use SMTP
			$send_params['recipients']	= array($to);							// The recipients (can be multiple)
			$send_params['headers']		= array("From: $from", "To: $to", "Subject: $subject");
			$send_params['from']		= $from;									// This is used as in the MAIL FROM: cmd																							// It should end up as the Return-Path: header
			$send_params['body']		= $message;										// The body of the email
	
	
			if(is_object($smtp = smtp::connect($this->params)) AND $smtp->send($send_params)){
				return True;
			} else {
				$GLOBALS['vars']['error'] =  'Error sending mail'."\r\n\r\n";
				// The reason for failure should be in the errors variable
				print_r($smtp->errors);
			}
		}
		else {
			// Use the PHP mail command
			mail($to, $subject, $message,"From: $from");
		}
	}
	
}

?>
