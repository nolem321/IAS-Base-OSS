
IMPORT std::default;
IMPORT wrap::fetch;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.examples.org/akc")
RETURNS Customer : "http://www.examples.org/akc" 			    	  			 			    	  			 			    	 
BEGIN

  wrap::fetchCustomer(ctx,data);
  wrap::fetchAddresses(ctx,data);
     	
  RETURN data; 
  
END;