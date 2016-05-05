
DEFINE SubAddress : "http://www.examples.org/types" AS 
 EXTENSION OF Address : "http://www.examples.org/akc"
BEGIN
   info AS String;
   alternate AS Address : "http://www.examples.org/akc" ;
END;
