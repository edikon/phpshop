<div class="payment">
<h2><?php __('Payment');?></h2>

<?php
// $action = https://www.paypal.com/cgi-bin/webscr";
$action = "https://www.sandbox.paypal.com/cgi-bin/webscr";
$business = "edikon_1187818606_biz@gmail.com";
$currency_code = "USD";
?>
<form action="<?php echo $action ?>" method="post">

<input type="hidden" name="cmd" value="_cart">
<input type="hidden" name="upload" value="1">
<input type="hidden" name="business" value="<?php echo $business ?>">
<input type="hidden" name="currency_code" value="<?php echo $currency_code ?>">

<input type="hidden" name="email" value="<?php echo $order['Order']['email'] ?>">
<input type="hidden" name="first_name" value="<?php echo $order['Order']['billing_first_name'] ?>">
<input type="hidden" name="last_name" value="<?php echo $order['Order']['billing_last_name'] ?>">
<input type="hidden" name="address1" value="<?php echo $order['Order']['billing_address_1'] ?>">
<input type="hidden" name="address2" value="<?php echo $order['Order']['billing_address_2'] ?>">
<input type="hidden" name="city" value="<?php echo $order['Order']['billing_city'] ?>">
<input type="hidden" name="country" value="<?php echo $order['Order']['billing_country'] ?>">
<input type="hidden" name="state" value="<?php echo $order['Order']['billing_state'] ?>">
<input type="hidden" name="zip" value="<?php echo $order['Order']['billing_zip'] ?>">

<input type="hidden" name="shipping_1" value="<?php echo $order['Order']['shipping'] ?>">
<input type="hidden" name="tax_cart" value="<?php echo $order['Order']['zone_tax']+$order['Order']['country_tax'] ?>">

<?php foreach ($items as $key => $value): ?>
<input type="hidden" name="<?php echo $key ?>" value="<?php echo $value ?>">
<?php endforeach; ?>

<input type="submit" value="PayPal">
</form>
</div>