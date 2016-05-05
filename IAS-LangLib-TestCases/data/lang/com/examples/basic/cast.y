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

PROGRAM com::examples::basic::cast(VAR p1 AS Integer, 
			 			    		   VAR input AS Customer  : "http://www.examples.org/akc", 
			 			    		   VAR output AS Customer : "http://www.examples.org/akc")
BEGIN
 
 output = NEW Customer : "http://www.examples.org/akc";
 
 output.birth= ("2013-09-08T12:46:39+0200" AS DateTime) + 10*365*24*3600;
 output.firstname = "100" + 100;
 output.lastname =  ((("100" AS Integer)  + 10*365*24*3600+100) AS Date);
 
 output.someDate=((output.lastname AS Date) AS Integer);
 output.someTime=(((output.birth AS String) AS DateTime) AS Integer);
 
 VAR anything AS AnyType;
 VAR a AS Address:"http://www.examples.org/akc";
 
 anything = NEW Address:"http://www.examples.org/akcf";
 a=anything;
 
  a.street="Street";
  a.block=1;
  
 a.street=a.street + "#" + a.street + "% "+ (anything AS Address:"http://www.examples.org/akcf").street;
 (anything AS Address:"http://www.examples.org/akcf").country="Far, far away";
 (anything AS Address:"http://www.examples.org/akcf").street =a.street + "!"; 
 output.address=anything;
 
END;
