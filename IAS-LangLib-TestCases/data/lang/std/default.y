/*
 * File: IAS-LangLib-TestCases/data/lang/std/default.y
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
PROGRAM std::substring(VAR strArgument AS String,
					   VAR iStart      AS Integer,
					   VAR iLenght     AS Integer) RETURNS String
EXTERNAL "libIASLangLib:SubString3"();

PROGRAM std::substring(VAR strArgument AS String,
					   VAR iStart      AS Integer) RETURNS String
EXTERNAL "libIASLangLib:SubString2"();


PROGRAM std::find(VAR strArgument AS String,
				  VAR iStart      AS Integer) RETURNS Integer
EXTERNAL "libIASLangLib:Find"();

PROGRAM std::replace(VAR strArgument AS String,
					 VAR strPattern  AS String,
					 VAR strNewText  AS String) RETURNS String
EXTERNAL "libIASLangLib:Replace"();

/* ********************************************************************************* */

PROGRAM std::gettime() RETURNS DateTime
EXTERNAL "libIASLangLib:GetTime"();

PROGRAM std::getTime() RETURNS DateTime
EXTERNAL "libIASLangLib:GetTime"();

/* ********************************************************************************* */

PROGRAM std::getYear(VAR date AS Date) RETURNS Integer
EXTERNAL "libIASLangLib:GetYear"();

PROGRAM std::getMonth(VAR date AS Date) RETURNS Integer
EXTERNAL "libIASLangLib:GetMonth"();

PROGRAM std::getDay(VAR date AS Date) RETURNS Integer
EXTERNAL "libIASLangLib:GetDay"();

/* ********************************************************************************* */

PROGRAM std::modifydate(VAR tTime AS DateTime,
					     VAR iDeltaYears   AS Integer,
					     VAR iDeltaMonths  AS Integer,
					     VAR iDeltaDays    AS Integer) RETURNS String
EXTERNAL "libIASLangLib:ModifyDate"();

PROGRAM std::modifytime(VAR tTime AS DateTime,
					     VAR iDeltaHours   AS Integer,
					     VAR iDeltaMinutes  AS Integer,
					     VAR iDeltaSeconds AS Integer) RETURNS String
EXTERNAL "libIASLangLib:ModifyTime"();

PROGRAM std::load(VAR file AS String) RETURNS AnyType
EXTERNAL "libIASLangLib:Load"();

PROGRAM std::save(VAR file AS String,
				  VAR value  AS AnyType)
EXTERNAL "libIASLangLib:Save"();

PROGRAM std::rand() RETURNS Integer
EXTERNAL "libIASLangLib:GetRandom"();
