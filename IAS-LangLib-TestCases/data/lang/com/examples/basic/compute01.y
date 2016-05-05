/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/compute01.y
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

PROGRAM com::examples::basic::compute01(VAR p1 AS Integer, 
			 			    		    VAR input AS Customer : "http://www.examples.org/akc", 
			 			    		    VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

   VAR i AS Integer;
  
   output = COPYOF(input);
    
   i=0;
   WHILE i < 10 DO
     BEGIN
       VAR aaaa AS Address:"http://www.examples.org/akc";
       
       aaaa =  NEW Address:"http://www.examples.org/akcf";
       
       aaaa.street=std::replace("_Stara_" + i,"Stara","Nowa");
              
       aaaa.block=10*i+SIZEOF(output.address)+10*5/2-100;
       
       output.address=aaaa;
       i=i+1;       
  	 END;
 
 	output.firstname = NULL ;
 	
 	VAR b1 AS Boolean;
 	VAR b2 AS Boolean;
 	
 	b1 = TRUE;
 	b2 = FALSE;
 	
 	output.lastname = output.lastname + " " + b1 + " " + b2;
END;
