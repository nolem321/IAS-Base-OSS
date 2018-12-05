PROGRAM wrap::updateCustomer(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"UPDATE CUSTOMER SET 
   ? data.firstname  => firstname,
   ? data.middlename => middlename,
   ? data.lastname   => lastname,  
   ? data.age        => age 
 WHERE 
   id = data.id
");
