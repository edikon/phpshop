# Introduction #

This document describes the standard administration features of phpShop.  Anything beyond this feature set is out of scope and will be added via plugins.

# Details #

## Model Description ##

These are the models that are managed by the administrative interface by default.

  * Settings
  * Users
  * Countries
  * Zones
  * Shipping Rates  (by Zone; may be moved to plugin to allow for different calculators)
  * Orders
    * Order Items
    * Order Statuses
    * Order Payments
    * Order Shipments
  * Customers
    * Customer Addresses
  * Brands
  * Products
    * Product Items
    * Product Images
    * Product Types
  * Categories

Deletes will be recursive and will eliminate related data where appropriate.

## Import/Export Capabilities ##

In order to ensure ease of migration, an import and export utility is provided for the following models:

  * Products
    * Product items
    * Product Images
  * Categories
  * Orders (export only)

Documentation on the format will be forthcoming (sample files currently located in the docs/ folder of the distribution).

## Security ##

Administrative users are defined in the _User_ model.  Authentication will be form-based and will allow global access to the administrative interface.

## Payment Processing ##

In order to allow for multiple payment processors, we are going to place all payment processing into plugins.  Standard payment processor plugins to be in the distribution will be:

  * PayPal IPN (paypal)
  * Google Checkout (google)
  * Authorize.Net (authnet)

The plugin you want to use is enabled in the _Settings_ model using the _Payment.plugin_ variable where the value of this variable is the name of the plugin.  Each plugin can have its own set of variables using the convention of _PluginName.variable_.

## Changes ##

It is our intent to not change the scope of functionality of the phpShop administrative interface from what is listed above.   Future releases will be focused on fixing bugs or issues with this core functionality.  We also plan to improve the interface design over time for usability.