/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/multi.y
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
PROGRAM com::examples::multi(VAR p1 AS Integer) RETURNS Integer
BEGIN
  WHILE 1==1 DO
  	RETURN p1 * p1 + 100;
  RETURN p1 * p1 + 300;
END;

PROGRAM com::examples::multi(VAR p1 AS Integer, VAR p2 AS Integer) RETURNS Integer
BEGIN
  RETURN p1 * p2;
END;
