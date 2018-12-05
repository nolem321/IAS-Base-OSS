
IMPORT std::default;
IMPORT wrap::keyvalue;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.examples.org/akc")
RETURNS Customer : "http://www.examples.org/akc"
BEGIN


 VAR i AS Integer;

 FOR i = 0 TO 10 DO BEGIN
  VAR customer AS Customer : "http://www.examples.org/akc";

  customer.id=(data.id AS Integer) + i;
  customer.lastname="Novacek";
  customer.age=71 + i;

  customer.birthDate = "1999-01-02";
  customer.wakeup    = "05:30:55";
  customer.updated   = "2015-06-07T05:30:55";

  VAR address AS Address : "http://www.examples.org/akc";
  address.street="Fresh fruits";
  address.block=12 + 3*i;
  customer.address=address;

  address = NEW Address : "http://www.examples.org/akcf";
  address.street="Old potatoes";
  address.block=21+ 2*i;
  customer.address=address;

  wrap::keyvalue::insertCustomer(customer);

 END;

 RETURN wrap::keyvalue::fetchCustomer(data.id);

END;