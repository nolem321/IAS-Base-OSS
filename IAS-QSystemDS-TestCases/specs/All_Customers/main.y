
IMPORT std::default;
IMPORT wrap::fetch;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS  GetCustomerList : "http://www.examples.org/akc")
RETURNS GetCustomerList : "http://www.examples.org/akc"	 			    	  			 			    	  			 			    	 
BEGIN

  data.customers=wrap::fetchCustomerList(ctx);
  
  WITH c AS data.customers DO BEGIN
   wrap::fetchAddresses(ctx,c);
  END;
  
  RETURN data; 
  
END;