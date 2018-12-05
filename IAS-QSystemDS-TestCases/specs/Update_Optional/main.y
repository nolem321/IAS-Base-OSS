
IMPORT std::default;
IMPORT wrap::fetch;
IMPORT wrap::update;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.examples.org/akc")
RETURNS Customer : "http://www.examples.org/akc"	 			    	  			 			    	  			 			    	 
BEGIN

  VAR update AS Customer : "http://www.examples.org/akc";
  
  update.id=data.id;
  update.lastname="Novacek";
  update.age=71;
  
  wrap::updateCustomer(ctx,update);

  wrap::fetchCustomer(ctx,data);
  wrap::fetchAddresses(ctx,data);
     	
  RETURN data; 
  
END;