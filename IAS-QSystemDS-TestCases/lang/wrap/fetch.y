PROGRAM wrap::fetchCustomer(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ONCE 
   firstname  => data.firstname,
   middlename => data.middlename,
   lastname   => data.lastname,
?  birthDate  => data.birthDate,
?  wakeup     => data.wakeup,
?  updated    => data.updated,
   age   	  => data.age
 FROM 'CUSTOMER_VW'
 WHERE 
   id = data.id
");

PROGRAM wrap::fetchCustomerForUpdate(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ONCE 
   firstname  => data.firstname,
   middlename => data.middlename,
   lastname   => data.lastname,
 ? birthDate  => data.birthDate,
 ? wakeup     => data.wakeup,
 ? updated    => data.updated,
   age        => data/age
 FROM 'CUSTOMER_VW'
 WHERE 
   id = data.id
 FOR UPDATE
");

// ? rawdata    => data.misc

PROGRAM wrap::fetchCustomerList(VAR ctx        AS Context  : "http://www.invenireaude.org/qsystem/workers")
RETURNS ARRAY OF Customer : "http://www.examples.org/akc"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result 
   id         => id,
   firstname  => firstname,
   middlename => middlename,
   lastname   => lastname,
?  birthDate  => birthDate,
?  wakeup     => wakeup,
?  updated    => updated, 
   age        => age
 FROM 'CUSTOMER_VW'
");

PROGRAM wrap::fetchCustomerList(VAR ctx        AS Context  : "http://www.invenireaude.org/qsystem/workers",
                                VAR offset     AS Integer,
                                VAR page       AS Integer)
RETURNS ARRAY OF Customer : "http://www.examples.org/akc"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result PAGE(offset,page) 
   id         => id,
   firstname  => firstname,
   middlename => middlename,
   lastname   => lastname,
?  birthDate  => birthDate,
?  wakeup     => wakeup,
?  updated    => updated,    
   age        => age
 FROM 'CUSTOMER_VW'
");


PROGRAM wrap::fetchAddresses(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				              VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO data.address 
	MAP type (
		F     => Address : 'http://www.examples.org/akcf'(
           ? country => country
		),
	    _     => Address : 'http://www.examples.org/akc'
   )
   street => street,
   block  => block 
 FROM 'ADDRESS_VW'
 WHERE 'CUSTOMER_ID' = data.id
");
