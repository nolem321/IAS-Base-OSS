/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/assign01.y
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

PROGRAM com::examples::basic::assign01(VAR p1 AS Integer, 
			 			    		   VAR input AS Customer  : "http://www.examples.org/akc", 
			 			    		   VAR output AS Customer : "http://www.examples.org/akc")
BEGIN
 
 output = input;
 
 output.age=10;
 output.firstname="test1";
 output.birth="2000-02-03T10:12:49+0300";
 
 VAR name AS Name  : "http://www.examples.org/akc";
  
 name= ""  +  output.birth;
 VAR date AS DateTime;
 date=name;
 name= date + ("100" AS Integer);
 output.age=date;
 output.middlename=name;
END;
