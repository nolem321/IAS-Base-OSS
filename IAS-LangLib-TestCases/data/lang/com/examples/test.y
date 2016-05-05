/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/test.y
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

PROGRAM com::examples::test(VAR p1 AS Integer, 
			 			    VAR input AS Customer : "http://www.examples.org/akc", 
			 			    VAR output AS Customer : "http://www.examples.org/akc")
BEGIN


 VAR tab AS ARRAY OF Integer;
 tab=1;
 tab=2;
 tab=tab[1];

   
 input.firstname="President";
 input.address[0].street="Sezamkowa z taba" + tab[2];
 input.lastname=input.address[0].street;
 
 input.address[1].street = "nowa";
 input.address[2].street = input.address[1].street;
 
 VAR shadow AS Customer : "http://www.examples.org/akc";
 
 shadow = input;
 shadow.address[1].street = "cien";
 
 VAR test AS Address:"http://www.examples.org/akc";
 test=input.address[1];
 test.street="pocieniowana";
 
 VAR i AS Integer; 

 i="10"; 

 WHILE i>0 DO
  BEGIN
    VAR a AS Address:"http://www.examples.org/akcf";
    i=i-1;    

    BEGIN
        VAR aa AS Address:"http://www.examples.org/akcf";
    	aa = NEW Address : "http://www.examples.org/akcf";
    	aa.street = "pustynna" + " " + i;    	
    	a=aa;
    END;
    	
    a.block = i; 
    a.country = "";
    a.country = "Abisynia";
    a.backup.info = "Backup";
    input.address = a;
  END;
 
   VAR a1 AS Address:"http://www.examples.org/akcf";
   VAR a2 AS Address:"http://www.examples.org/akcf";
   VAR a3 AS Address:"http://www.examples.org/akcf";
 
   a1 = input.address[3];
   a1.block=54321; 
   a2 = input.address[4];

   a2.backup.info="zamiana";
   a1.backup.info=a2.backup.info;   
   a2.backup.info="zamiana 2";
   
   a3 = input.address[5];
   a3.backup.info="zamiana 5";
   input.attr="Atrybut testowy";
   
   VAR nowy AS Address:"http://www.examples.org/akc";
   nowy=COPYOF(input.address[4]);
   nowy.block=-nowy.block;
   input.address=nowy;
   
 
   input.age= com::examples::multi(100);
   
   input.address = com::examples::newaddress();

   input.age = SIZEOF(tab);
   
   i=0;
   WHILE i < SIZEOF(input.address) DO
     BEGIN
        VAR tmp AS Address:"http://www.examples.org/akc";
        tmp = input.address[i];
        
        IF tmp ISINSTANCE (Address:"http://www.examples.org/akc") THEN
        	BEGIN
        		tmp.street = TYPE(tmp) + ":" + TYPENS(tmp);	
        	END;                
        tmp.block = STRLEN(tmp.street) + i;
        i=i+1;
        
     END;
     
  DELETE input.address[13];
      
 input.firstname=std::substring("1234567890",5);
   
 VAR name AS Name:"http://www.examples.org/akc";
 name="lepszy";
 input.lastname=name+"gorszy";
  
 input.age = com::examples::multi(2) +  com::examples::multi(10,5);
 
 input.lastname=std::replace(input.lastname,"go","GO GO ");
 
 TRY BEGIN
 	com::examples::utility(10,input);
 END 
   CATCH (VAR e AS Integer )BEGIN
   	input.age = p1;
   END
   CATCH (VAR a AS Customer:"http://www.examples.org/akc" )BEGIN
   	input = a;
   END;
 
 output = input;
END;
