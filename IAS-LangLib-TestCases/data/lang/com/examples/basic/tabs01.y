/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/tabs01.y
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
IMPORT com::examples::utilitytab;
IMPORT com::examples::utilitytabresult; 

PROGRAM com::examples::basic::tabs01(VAR p1 AS Integer, 
			 			    		 VAR input AS Customer : "http://www.examples.org/akc", 
			 			    		 VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

 VAR tab1 AS ARRAY OF Integer;
 tab1=1;
 tab1=1;
 tab1=1;
 tab1=1;
 
 VAR tab2 AS ARRAY OF String;
 tab2=1;
 tab2=2;
 tab2=tab2[1];
 
 output = input; 
 com::examples::utilitytab(tab1,output);
 
 output.address = com::examples::utilitytabresult(12,"Pierwsza tura.");
 VAR list AS ARRAY OF Address:"http://www.examples.org/akc";
 list = com::examples::utilitytabresult(16,"Druga tura.");
 
 VAR a AS  Address:"http://www.examples.org/akc";
 a = NEW Address:"http://www.examples.org/akcf";
 output.address[3] = a;  
 a.street="testowa";
 a.block=111;
 
 output.address[2].block = 102; 
 output.address = list[15];
 output.address[8] = list[14];
 output.address[9] = COPYOF(list[15]); 
 
END;
