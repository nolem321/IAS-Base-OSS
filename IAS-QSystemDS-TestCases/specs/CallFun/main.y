
IMPORT std::default;
IMPORT wrap::fun;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data   AS Customer : "http://www.examples.org/akc")
RETURNS Customer : "http://www.examples.org/akc"	 			    	  			 			    	  			 			    	 
BEGIN

  data.age = wrap::callfun(data);
  
  RETURN data; 
  
END;