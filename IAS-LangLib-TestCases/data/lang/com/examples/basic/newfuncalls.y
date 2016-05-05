/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/newfuncalls.y
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

PROGRAM com::examples::basic::testnull(VAR p1 AS Integer,
	                                   VAR p2 AS Integer,
	                                   VAR p3 AS Integer)
BEGIN

 IF NOT ISSET (p1) THEN
   THROW "Expected P1";

 IF NOT ISNULL (p3) THEN
   THROW "Expected null in P3:"+p3;
    
END;	                                
        
PROGRAM com::examples::basic::newfuncalls(VAR p1 AS Integer, 
			 			    		 	  VAR input AS Customer : "http://www.examples.org/akc", 
			 			    		 	  VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

	VAR a AS Integer;
	VAR b AS Integer;
	VAR c AS Integer;
   
    c = NULL;
    
   com::examples::basic::testnull(a,b,c);
   
END;
