# Introduction #

**This document is incomplete. Working on it still...**
This guide explains how to install phpShop 2.0 as it is currently in the source code repository.  It is important to point out that the code in SVN is simply the application code.  You still need to install the CakePHP library in order to get it to work correctly.  Instructions follow:


# Details #

In order to install phpShop 2.0 you will need to follow 3 primary steps:
  * Download CakePHP 1.2
  * Checkout phpShop 2.0 code from SVN
  * Run installer

## Download CakePHP ##

  1. Download CakePHP 1.2 by visiting: http://cakeforge.org/frs/?group_id=23.  Be sure to grab the most recent version of CakePHP 1.2.
  1. Uncompress CakePHP inside your web directory.  This will create a folder along the lines of cake-1.2...something/
```
unzip cake-1.2.XXX.zip
```
  1. Rename the folder to phpshop/ (or whatever you prefer; for the purposes of this guide, we use phpshop/).
```
mv cake-1.2/ phpshop/
```
  1. Remove the app/ folder inside the phpshop/ directory.
```
rm -rf phpshop/app
```

## Checkout phpShop 2.0 from SVN ##

  1. Change to the phpshop/ directory.
```
cd phpshop/
```
  1. Checkout app/ folder from SVN.
```
svn checkout https://phpshop.googlecode.com/svn/trunk/phpshop2/app app
```
  1. Run the set\_permissions.sh script.
```
# sh app/set_permissions.sh
```
  1. Open browser and point to the installation folder.
  1. Launch installation.  Follow instructions.

## Installation ##

  1. The installer checks that requirements are met.
  1. The installer checks if database exists, if not gives you the option to create it.
  1. You must have a database with a user/password that has access to it.
  1. The installer will create tables with demo data.
  1. The installer will create the configuration file and write it directly to disk.
  1. You are done.  Happy testing!