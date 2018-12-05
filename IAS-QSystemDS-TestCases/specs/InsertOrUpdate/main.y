
IMPORT std::default;
IMPORT wrap::fetch;
IMPORT wrap::insertOrUpdate;
IMPORT wrap::insert;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.examples.org/akc")
RETURNS Customer : "http://www.examples.org/akc"	 			    	  			 			    	  			 			    	 
BEGIN

  
  VAR customer AS Customer : "http://www.examples.org/akc";
  
  customer.id=data.id;
  customer.lastname="Oldman";
  
  customer.age=25;
  
  customer.birthDate = "1999-01-02";
  customer.wakeup    = "02:03:45";
  customer.updated   = "2015-06-07T05:30:55";
  
  wrap::insertOrUpdateCustomer(ctx,customer);
  wrap::fetchCustomer(ctx,data);
  
 
  IF NOT ISSET(data.lastname) OR customer.lastname <> data.lastname THEN
   	BEGIN
   	  VAR e AS Exception : "http://www.invenireaude.org/qsystem/workers";
   	  e.name="TestErrorException";
   	  e.info="The lastname does not match:";
   	END;
  	
  IF NOT ISSET(data.age) OR customer.age <> data.age THEN
    BEGIN
   	  VAR e AS Exception : "http://www.invenireaude.org/qsystem/workers";
   	  e.name="TestErrorException";
   	  e.info="The age does not match.";
   	  THROW e;
   	END;
   	
 
   IF NOT ISSET(data.wakeup) OR customer.wakeup <> data.wakeup THEN
    BEGIN
   	  VAR e AS Exception : "http://www.invenireaude.org/qsystem/workers";
   	  e.name="TestErrorException";
   	  e.info="The wakeup does not match. " + customer.wakeup + " " + data.wakeup + " " + (data.wakeup AS Time);
   	  THROW e;
   	END;
   	 
  
  customer = NEW Customer : "http://www.examples.org/akc";
  
  customer.id=data.id;
  
  customer.lastname="New";
  customer.age=35;
  
  wrap::insertOrUpdateCustomer(ctx,customer);
  
  wrap::fetchCustomer(ctx,data);
     	
  RETURN data; 
  
END;