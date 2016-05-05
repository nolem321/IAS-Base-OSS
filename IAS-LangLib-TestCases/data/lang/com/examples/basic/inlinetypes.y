/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/withsingle.y
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

IMPORT com::examples::utility;
IMPORT com::examples::printer;
IMPORT com::examples::multi;
IMPORT com::examples::newaddress;
        
PROGRAM com::examples::basic::inlinetypes(VAR p1 AS Integer, 
			 			    		 	  VAR input AS Customer : "http://www.examples.org/akc", 
			 			    		      VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

   VAR i AS Integer;
   VAR i2 AS Integer;
   
   output=COPYOF(input);
   
   output.employment.company = "Monsters Inc.";
   output.employment.address =  NEW Address:"http://www.examples.org/akc" BEGIN
  							street = "Scary";
  							block  = 123;
  							city   = "Hellstone";
  						 END;
   
   output.someText = "ABC";
   
END;
