

PROGRAM wrap::keyvalue::insertCustomer(VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"INSERT INTO table
  data.id => key
, data    => value
");


PROGRAM wrap::keyvalue::updateCustomer(VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"
UPDATE table SET
  data => data
WHERE key = data.id
");


PROGRAM wrap::keyvalue::fetchCustomer(VAR id AS String)
RETURNS Customer : "http://www.examples.org/akc"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"
SELECT ONCE
 data => result
FROM table
WHERE key = id
");

PROGRAM wrap::keyvalue::deleteCustomer(VAR id AS String)
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"
DELETE
FROM table
WHERE key = id
");


PROGRAM wrap::keyvalue::fetchCustomerList()
RETURNS ARRAY OF Customer : "http://www.examples.org/akc"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"
SELECT ARRAY INTO result
   key => id
 , data => ''
FROM table
");
