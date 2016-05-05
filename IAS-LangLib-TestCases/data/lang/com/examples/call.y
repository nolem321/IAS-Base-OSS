/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/call.y
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

PROGRAM com::examples::call(VAR p1     AS Integer, 
			 			    VAR input  AS Customer : "http://www.examples.org/akc",
			 			    VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

 
 TRY BEGIN
 	input.age = p1;
 	input.firstname="President";
 	input.address[0].street="Sezamkowa";
 	input.lastname=input.address[0].street;
 END 
   CATCH (VAR e AS Integer )BEGIN
   	input.age = p1;
   END
   CATCH (VAR e AS Integer )BEGIN
   	input.age = p1;
   END;
 
  com::examples::printer(5+1,input);
 
  VAR aa AS Address:"http://www.examples.org/akcf";
  aa = NEW Address : "http://www.examples.org/akcf";
  aa.street="Bursztynowa";

 input.age = SIZEOF(input.address);
 input.age = STRLEN("abcdef");
 input.age = STRLEN(aa.street);
 input.age = TYPE(aa.street);
 input.age = TYPENS(aa.street);
 
 DELETE input.age;
 DELETE input.address[2];
 
 THROW 2;
 
END;
