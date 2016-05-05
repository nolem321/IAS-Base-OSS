/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/datetime.y
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

PROGRAM com::examples::basic::datetime(VAR p1 AS Integer, 
			 			    		   VAR input AS Customer  : "http://www.examples.org/akc", 
			 			    		   VAR output AS Customer : "http://www.examples.org/akc")
BEGIN
 
 output = COPYOF (input);
 
 output.birth="2013-09-08T12:46:39+0200";
 
 VAR i AS Integer;
   
   FOR i=1 TO 10 DO
     BEGIN
       VAR a AS Address:"http://www.examples.org/akc";
       a =  NEW Address:"http://www.examples.org/akcf";
   
       a.street=output.birth + i;
       a.block=i;
       
       output.address=a;        
  END;
  
  
  output.address[1].street=output.birth+10*365*24*3600;
  
  output.address[2] =  NEW Address:"http://www.examples.org/akc";
  output.address[2].street=std::modifytime(output.birth, 10, 10 ,10);
  
  output.address[3].street=std::modifydate(output.birth, 10, 10 ,10);
  
  output.address[4].street=output.birth-10*365*24*3600;
  
  output.someDate="2001-02-03";
  output.someTime="10:20:30";
  
  output.someDate = output.someDate + 10*24*3600;
  output.someTime = output.someTime + 3600*3 + "01:02:03";
	
  output.info  = "Date: " + output.someDate +  
  				 ", Time: " + output.someTime +
  				 ", TS: "   + output.birth;
  
END;
