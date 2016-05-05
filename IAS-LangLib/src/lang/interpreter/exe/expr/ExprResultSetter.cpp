/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ExprResultSetter.cpp
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
#include "ExprResultSetter.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"

#include <lang/interpreter/exe/exception/InterpreterException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
ExprResultSetter::ExprResultSetter(DM::DataObject* ptrDM,
  	  	  	  	  	   const DM::Property* pProperty,
  	  	  	  	  	   int iIdx):
		ptrDM(ptrDM),
		pProperty(pProperty),
		iIdx(iIdx){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pProperty);

	if(iIdx > 0 && ! pProperty->isMulti())
		IAS_THROW(InterpreterException(String("An index given for non-array property: ")+=pProperty->getName()));

}
/*************************************************************************/
ExprResultSetter::ExprResultSetter(const ExprResultSetter& other):
		ptrDM(other.ptrDM),
		pProperty(other.pProperty),
		iIdx(other.iIdx){}
/*************************************************************************/
void ExprResultSetter::assign(DM::DataObject* dmValue){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"assign: "<<pProperty->getName()<<"["<<iIdx<<"]"<<", target: "
			<<pProperty->getType()->getFullName()<<" value:"<<(dmValue ? dmValue->getType()->getFullName() : "null"));

	if(!ptrDM){
		IAS_THROW(InterpreterException("Cannot assign a property of a null object :" + pProperty->getName()));
	}

	if(pProperty->isMulti() && iIdx >= 0){
		ptrDM->getList(pProperty).set(iIdx,dmValue);
	}else{
		ptrDM->setDataObject(pProperty,dmValue);
	}
}
/*************************************************************************/
void ExprResultSetter::assignList(DM::DataObjectList& refList){
	IAS_TRACER;

	if(iIdx > 0)
		IAS_THROW(InterpreterException(String("Cannot assign array to the other array element.")+=pProperty->getName()));

	DM::DataObjectList& refTargetList=ptrDM->getList(pProperty);
	refTargetList.clear();

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Coping list: " <<refList.size());

	for(int iIdx=0;iIdx<refList.size();iIdx++){
		refTargetList.add(refList.at(iIdx));
	}
}
/*************************************************************************/
const DM::Property* ExprResultSetter::getProperty()const{
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pProperty)
	return pProperty;
}
/*************************************************************************/
}
}
}
}
}
