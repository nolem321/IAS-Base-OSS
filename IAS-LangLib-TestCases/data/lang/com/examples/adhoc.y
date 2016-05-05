/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/catch01.y
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

PROGRAM com::examples::test(VAR o   AS Customer : "http://www.examples.org/akc",
	                        VAR count AS Integer)
	                       
BEGIN

 IF count > 0 THEN BEGIN
   com::examples::test(o, count - 1 );
   RETURN;
 END;

  DELETE o.address;
 
 o.address = NULL; 
// o.address[0].street = "s";
 
END;

PROGRAM com::examples::adhoc(VAR ctx  AS Context    : "http://www.invenireaude.org/qsystem/workers",
			 			     VAR input AS Customer : "http://www.examples.org/akc")
RETURNS Customer : "http://www.examples.org/akc"
BEGIN


 VAR o AS Customer : "http://www.examples.org/akc";
 
/// o.age[1]=" 1234" - 1234; 
 o=COPYOF(input);

 com::examples::test(o, 3);
 o.firstname = o.age;
 
 IF "123" == 123 THEN
   o.firstname="TAK";
   
 RETURN o;
END;
