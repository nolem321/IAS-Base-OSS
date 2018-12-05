

PROGRAM wrap::insertCustomer(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.examples.org/akc")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"INSERT INTO CUSTOMER
   data.id  => id,
   ? data.firstname  => firstname,
   ? data.middlename => middlename,
   ? data.lastname   => lastname,
   ? data.age        => age,
   ? data.birthDate  => birthDate,
   ? data.wakeup     => wakeup,
   ? data.updated    => updated
");

//   ? data            => rawdata
PROGRAM getCode(VAR a AS Address:"http://www.examples.org/akc")
RETURNS String
BEGIN
   IF a ISTYPE(Address:"http://www.examples.org/akcf") THEN BEGIN
       RETURN "F";
 	 END ELSE BEGIN
       RETURN "C";
     END;
END;


PROGRAM wrap::insertAddress(VAR ctx       AS Context  : "http://www.invenireaude.org/qsystem/workers",
							VAR cid       AS String,
				            VAR address   AS Address  : "http://www.examples.org/akc",
				            VAR type       AS String)
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"INSERT INTO ADDRESS
   cid => 'CUSTOMER_ID',
   address.street =>  STREET,
   address.block  =>  BLOCK,
   type   =>  TYPE
");
