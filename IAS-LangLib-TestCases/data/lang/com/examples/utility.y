/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/utility.y
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
IMPORT com::examples::printer;

PROGRAM com::examples::utility(VAR p1 AS Integer , 
			 				   VAR input AS Customer : "http://www.examples.org/akc")
BEGIN
 VAR tab AS ARRAY OF Integer;
 
 IF p1 == 1 THEN BEGIN
    input.age=100;
    input.address[0].block=100;
 	THROW input;
 END;	
 
 TRY BEGIN 
	com::examples::utility(p1-1,input);
 END
 CATCH (VAR e AS Customer : "http://www.examples.org/akc") BEGIN
 	e.age=e.age+1; 
 END;
 
  input.address[0].block=input.address[0].block+1;
END;
