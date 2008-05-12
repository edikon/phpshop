CREATE TABLE tax_rate (
   tax_rate_id int(11) NOT NULL auto_increment,
   vendor_id int(11),
   tax_state varchar(64),
   tax_country varchar(64),
   tax_rate decimal(10,4),
   mdate int,
   PRIMARY KEY(tax_rate_id)
);
