/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/CatchList.cpp
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
#include "CatchList.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Catch.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
CatchList::CatchList(){
	IAS_TRACER;
}
/*************************************************************************/
CatchList::~CatchList() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CatchList::addCatch(Catch* pCatch){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pCatch);

	lstCatchSections.push_back(pCatch);
	phcCatches.addPointer(pCatch);
}
/*************************************************************************/
bool CatchList::match(const DM::Type* pType, Catch* &refPtrCatch)const{
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Check: "<<pType->getName());

	for(CatchSectionsList::const_iterator it = lstCatchSections.begin();
		it != lstCatchSections.end();
		it++){

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Check: "<<(*it)->getCatchType()->getName());

		if(pType->isAssignableTo((*it)->getCatchType())){
			refPtrCatch=*it;
			return true;
		}
	}

	return false;
}
/*************************************************************************/
}
}
}
}
}
