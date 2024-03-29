#!/bin/bash

IAS_TEST_DS_SQLITE_DB=/tmp/test.db

sqlite3 ${IAS_TEST_DS_SQLITE_DB} <<EOF

   DELETE FROM ADDRESS;
   DELETE FROM CUSTOMER;
  
   INSERT INTO CUSTOMER(ID,FIRSTNAME,LASTNAME,MIDDLENAME,AGE) VALUES
	(1,'Johny','Kowalski','Koval',41);

   INSERT INTO CUSTOMER(ID,FIRSTNAME,LASTNAME,MIDDLENAME,AGE) VALUES
	(2,'Walter','Smith','Junior',14);

   INSERT INTO CUSTOMER(ID,FIRSTNAME,LASTNAME,MIDDLENAME,AGE) VALUES
	(3,'Sammy','Novak','Nova',24);

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE,COUNTRY) VALUES
        (1,'Eastwoods',123,'N',NULL);

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE,COUNTRY) VALUES
        (1,'Westwoods',321,'F','Canada');

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE,COUNTRY) VALUES
        (2,'Sunset',1009,'F','USA');

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE,COUNTRY) VALUES
        (3,'Sunrise',91,'N',NULL);


  -- SELECT COUNT(1) CUSTOMERS FROM CUSTOMER;
  -- SELECT COUNT(1) ADDRESSES FROM ADDRESS;

EOF
