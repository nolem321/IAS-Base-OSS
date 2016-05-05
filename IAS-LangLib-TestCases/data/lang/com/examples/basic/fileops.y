/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/fileops.y
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

        
PROGRAM com::examples::basic::fileops(VAR p1 AS Integer, 
			 			    		  VAR input AS Customer : "http://www.examples.org/akc", 
			 			    		  VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

   VAR a AS Address:"http://www.examples.org/akc";
   VAR c AS Customer : "http://www.examples.org/akc";
   VAR o AS AnyType;
   
   std::save("stdout",1);
   std::save("stdout",input);
   std::save("/tmp/sdo.out",input);
   
   c=std::load("/tmp/sdo.out");
   
   output=COPYOF(input);
   output.misc=c;
   
      
END;
