csv product upload script for phpShop
Created by John Syben (webme.co.nz)
Version 0.3 13 Sept 2002
Comments/Questions: john@webme.co.nz

OVERVIEW
This script allows for the bulk addition of products to the phpShop database.
It will create categories as required and will update product if it's sku alreay exists.

HOW TO USE IT
First you need a csv file with the required product information.
See test.csv for an example.

The following product information can be included:
  product_sku
  product_s_desc
  product_desc
  product_thumb_image
  product_full_image
  product_weight
  product_weight_uom
  product_length
  product_width
  product_height
  product_lwh_uom
  product_in_stock
  product_available_date
  product_special
  product_discount_id
  product_name
  product_price
  category_path

Minimum required information is
  product_sku
  product_name
  product_price
  category_path

category_path is a slash delimited string which begins
with a top-level category and follows with sub-categories,
e.g. category/sub-category_1/sub_category_2

product_thumb_image and product_full_image
are the names of the respective image files. You will
need to FTP the image directly to the image folder.

In the csv table, each of the above product fields
is assigned a number which represents it's position
in the delimited line. You can change these to suit the
positions in your own lines. The positions set in the
mycsv.sql file relate to the included test.csv so you
can test your installation.

No just go to products/csv_upload.ihtml,
browse to the csv file and hit submit.
##############################################
ADDITIONAL FILE
confirm_images.ihtml

This is a companion to the csv_upload script

After you use the csv_upload script you need to
FTP your images to the shop_image/product directory
to match the image names from the csv file.
This script will get all the image names from the product
table and check if the images are in the shop_image/product
folder and report which files are missing.

Simply put this file in the product/html folder
and make a link to it in the menu.