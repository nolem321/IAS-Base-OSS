/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/cast.y
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
IMPORT std::default;

DEFINE Address : "abc" AS BEGIN
 street AS String;
 block  AS String;
END;

DEFINE Customer : "abc" AS BEGIN
 firstname AS String;
 lastname  AS String;
 lost      AS String;
 age       AS String;
 address   AS ARRAY OF Address : "abc";
END;
				  				 
PROGRAM com::examples::basic::merge(VAR p1     AS Integer, 
			 			    	    VAR input  AS Customer : "http://www.examples.org/akc", 
			 			    	    VAR output AS Customer : "http://www.examples.org/akc")
BEGIN
 
  VAR i AS Integer;
  
  FOR i = 1 TO 5 DO 
   output.address = NEW Address:"http://www.examples.org/akc" BEGIN       
       street="Nowa"+(100-i);
       block=100-i;
  END;

  FOR i = 0 TO 20 DO 
   output.address = NEW Address:"http://www.examples.org/akc" BEGIN       
       street="Nowab"+(50-i);
       block=50-i;
  END;
  
  FOR i = 0 TO 20 DO 
   output.address = NEW Address:"http://www.examples.org/akc" BEGIN       
       street="Nowaa"+(21-i);
       block=21-i;
  END;

  VAR c AS Customer : "abc";
  
  c ?= input;
  
  c.firstname = c.firstname + " something new.";
  c.lost = " do not expect this !!!";
  
  std::save("stdout",c);
  
  output ?= c;
  
END;
