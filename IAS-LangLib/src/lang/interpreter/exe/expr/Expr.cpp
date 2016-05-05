/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/Expr.cpp
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
#include "Expr.h"
#include<lang/log/LogLevel.h>

#include <lang/interpreter/exe/exception/NullObjectReferenceException.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "ExprResultSetter.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
Expr::Expr() throw():pType(NULL){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"NEW:"<<(void*)this);

}
/*************************************************************************/
Expr::~Expr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const DM::Type* Expr::getType()const{
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pType);
	return pType;
}
/*************************************************************************/
void Expr::setType(const DM::Type* pType){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pType);
	this->pType=pType;
}
/*************************************************************************
bool Expr::isArray()const{
	return false;
}
/*************************************************************************/
void Expr::evaluate(Context *pCtx,
				    ExprResultSetter& refResult) const{

	IAS_TRACER;

	const DM::Type *pNewObjectType;
    const DM::Property* pNewObjectProperty=refResult.getProperty();
	const DM::Type* pPropertyType = pNewObjectProperty->getType();

	if(getType()->getTypeEnum() == pPropertyType->getTypeEnum())
		pNewObjectType=getType();
	else
		pNewObjectType=pPropertyType;

	/* Try to implicitly up-cast basic types  - does it make sense ?     */
	/* We need this to initialize subclasses of Strings with string expressions.  */

	if(pPropertyType->getTypeEnum() != DM::Type::DataObjectType &&
	   pPropertyType->getTypeEnum() != DM::Type::AnyType ){

		if( pPropertyType->isAssignableTo(getType())
			//&& getType()->isRootType() -> reconsider and test
			){
			pNewObjectType=pPropertyType;
		}

	} else if(pPropertyType->getTypeEnum() == DM::Type::AnyType){
		pNewObjectType=getType();

	}

	DM::DataObjectPtr dmResult;

	try{

		switch(getType()->getTypeEnum()){

		case DM::Type::BooleanType:
			dmResult = pNewObjectType->createDataObject(evaluateBoolean(pCtx));
			break;

		case DM::Type::IntegerType:
			dmResult = pNewObjectType->createDataObject(evaluateInt(pCtx));
			break;

		case DM::Type::TextType:
			dmResult = pNewObjectType->createDataObject(evaluateString(pCtx));
			break;

		case DM::Type::FloatType:
			dmResult = pNewObjectType->createDataObject(evaluateFloat(pCtx));
			break;

		case DM::Type::DateTimeType:
			dmResult = pNewObjectType->createDataObject(evaluateDateTime(pCtx));
			break;

		case DM::Type::DateType:
			dmResult = pNewObjectType->createDataObject(evaluateDate(pCtx));
			break;

		case DM::Type::TimeType:
			dmResult = pNewObjectType->createDataObject(evaluateTime(pCtx));
			break;

		case DM::Type::DataObjectType:
		case DM::Type::AnyType:
			evaluate(pCtx,dmResult);
			break;

		default:
			IAS_THROW(InternalException("missing case for: switch(pType->getTypeEnum())"));
	}

	} catch (NullObjectReferenceException& e) {
		//TODO why is this ?
	}

	if(!pCtx->isInterrupted())
		refResult.assign(dmResult);

}
/*************************************************************************/
}
}
}
}
}
