/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathExprFamily.cpp
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
#include "XPathExprFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "XPathIntegerExpr.h"
#include "XPathFloatExpr.h"
#include "XPathBooleanExpr.h"
#include "XPathStringExpr.h"
#include "XPathDataObjectExpr.h"
#include "XPathDataObjectListExpr.h"
#include "XPathDateTimeExpr.h"
#include "XPathDateExpr.h"
#include "XPathTimeExpr.h"

#include "XPathAccessor.h"
#include "../../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathExprFamily::XPathExprFamily(Expr* pExpr, XPathAccessor  *pXPathAccessor){
	IAS_TRACER;
	this->ptrExpr=pExpr;
	ptrXPathAccessor=pXPathAccessor;
}
/*************************************************************************/
XPathExprFamily::~XPathExprFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DM::DataObject* XPathExprFamily::getTargetObject(Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dm;
	ptrExpr->evaluate(pCtx,dm);
	return ptrXPathAccessor->getTargetObject(dm,pCtx);

}
/*************************************************************************/
DM::DataObjectList& XPathExprFamily::getTargetObjectList(Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dm;
	ptrExpr->evaluate(pCtx,dm);

	return ptrXPathAccessor->getTargetObjectList(dm,pCtx);
}
/*************************************************************************/
bool XPathExprFamily::isSet(Context* pCtx)const{
	IAS_TRACER;

	DM::DataObjectPtr dm;
	ptrExpr->evaluate(pCtx,dm);

	return ptrXPathAccessor->isSet(dm,pCtx);
}
/*************************************************************************/
bool XPathExprFamily::isNull(Context* pCtx)const{
	IAS_TRACER;

	DM::DataObjectPtr dm;

	ptrExpr->evaluate(pCtx,dm);

	return ptrXPathAccessor->isNull(dm,pCtx);
}
/*************************************************************************/
void XPathExprFamily::deleteDataObject(Context* pCtx)const{
	IAS_TRACER;

	DM::DataObjectPtr dm;
	ptrExpr->evaluate(pCtx,dm);

	ptrXPathAccessor->deleteDataObject(dm,pCtx);
}
/*************************************************************************/
DM::DataObject* XPathExprFamily::createDataObject(Context* pCtx)const{
	IAS_TRACER;

	DM::DataObjectPtr dm;
	ptrExpr->evaluate(pCtx,dm);

	DM::DataObjectPtr dmNew(getType()->createDataObject());
	ptrXPathAccessor->getTargetObjectSetter(dm,pCtx).assign(dmNew);
	return dmNew;
}
/*************************************************************************/
bool XPathExprFamily::isArray() const{
	IAS_TRACER;
	return false;
}
/*************************************************************************/
ExprResultSetter XPathExprFamily::getTargetObjectSetter(Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dm;
	ptrExpr->evaluate(pCtx,dm);

	return ptrXPathAccessor->getTargetObjectSetter(dm,pCtx);
}
/*************************************************************************/
XPathExprFamily* XPathExprFamily::Create(Expr* pExpr,
								 	 	 	   XPathAccessor  *pXPathAccessor){
	IAS_TRACER;

	const DM::Property* pValueProperty=pXPathAccessor->getValueProperty();

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"XPathExpr:" << pValueProperty->getName() << ", multi=" <<pValueProperty->isMulti() << ", array=" <<pXPathAccessor->isArrayExp());

	IAS_DFT_FACTORY<XPathExprFamily>::PtrHolder ptrResult;

	if(pXPathAccessor->isArrayExp()){

		ptrResult = IAS_DFT_FACTORY<XPathDataObjectListExpr>::Create(pExpr,pXPathAccessor);

	}else switch(pValueProperty->getType()->getTypeEnum()){

	case DM::Type::IntegerType:
		ptrResult = IAS_DFT_FACTORY<XPathIntegerExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::FloatType:
		ptrResult = IAS_DFT_FACTORY<XPathFloatExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::BooleanType:
		ptrResult = IAS_DFT_FACTORY<XPathBooleanExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::TextType:
		ptrResult = IAS_DFT_FACTORY<XPathStringExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::DateTimeType:
		ptrResult = IAS_DFT_FACTORY<XPathDateTimeExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::DateType:
		ptrResult = IAS_DFT_FACTORY<XPathDateExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::TimeType:
		ptrResult = IAS_DFT_FACTORY<XPathTimeExpr>::Create(pExpr,pXPathAccessor);
		break;

	case DM::Type::DataObjectType:
	case DM::Type::AnyType:
		ptrResult = IAS_DFT_FACTORY<XPathDataObjectExpr>::Create(pExpr,pXPathAccessor);
		break;

	default:
		IAS_THROW(InternalException("No factory for operator!"));
	}

	ptrResult->setType(pValueProperty->getType());
	return ptrResult.pass();
}
/*************************************************************************/
}
}
}
}
}
}
