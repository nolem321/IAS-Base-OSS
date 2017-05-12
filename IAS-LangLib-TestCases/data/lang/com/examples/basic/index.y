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

				  				 
PROGRAM com::examples::basic::index(VAR p1     AS Integer, 
			 			    	   VAR input  AS Customer : "http://www.examples.org/akc", 
			 			    	   VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

 INDEX input.address USING street;
 
 CREATE input.address BEGIN
   block = 9991;
   street = "Nowacka";
 END;

 CREATE input.address BEGIN
   block = 9992;
   street = "Nowaczkowa";
 END;

 CREATE input.address BEGIN
   block = 9993;
   street = "Nowaczkowa1";
 END;
   
 VAR a AS AnyType;
  
 a = input.address [[ "Miodowa" ]];  
 output.address = COPYOF(a);
 
 a = input.address [[ "Nowaczkowa" ]];  
 output.address = COPYOF(a);

 IF ISSET(input.address [[ "Miodowa" ]]) THEN
  CREATE output.address BEGIN
   street = "ISSET";
  END;

 IF NOT ISSET(input.address [[ "Miodowa2" ]]) THEN
  CREATE output.address BEGIN
   street = "NOT ISSET";
  END;  
END;
