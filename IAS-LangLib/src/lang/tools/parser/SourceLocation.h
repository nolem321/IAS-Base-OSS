/*
 * File: IAS-LangLib/src/lang/tools/parser/SourceLocation.h
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
#ifndef _IAS_AS_Lang_Tools_Parser_SourceLocation_MODEL_H_
#define _IAS_AS_Lang_Tools_Parser_SourceLocation_MODEL_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {


/*************************************************************************/
/** The class. */
 class SourceLocation {
public:

	 typedef unsigned short int SourceID;
	 typedef unsigned short int LineNumber;

	 inline LineNumber getLineNumber()const{
		 return iLineNumber;
	 }

	 inline SourceID getSourceID()const{
		 return iSourceId;
	 }

	SourceLocation(	SourceID    iSourceId = SHRT_MAX,
					LineNumber  iLineNumber = SHRT_MAX);
	SourceLocation(const SourceLocation& other);
	SourceLocation& operator=(const SourceLocation& other);

	SourceID    iSourceId;
	LineNumber  iLineNumber;
};
 /*************************************************************************/
 class ISourceLocationStore{
 	 public:
	 virtual ~ISourceLocationStore(){};

	 virtual SourceLocation::SourceID registerSource(const String& strName)=0;
	 virtual const String& resolve(SourceLocation::SourceID iID)const=0;

 };
/*************************************************************************/
}
}
}
}
#endif /* _IAS_AS_Lang_SourceLocation_MODEL_H_ */
