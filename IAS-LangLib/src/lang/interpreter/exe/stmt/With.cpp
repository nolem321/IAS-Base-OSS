/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/With.cpp
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
#include "With.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "../expr/xpath/XPathExprFamily.h"
#include "../expr/xpath/XPathAccessor.h"
#include "Statement.h"
#include "LeftSide.h"
#include "../exception/NullObjectReferenceException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
With::With(Expr::XPath::XPathExprFamily *pExpr):
				ptrExpr(pExpr),
				pVariableProperty(0),
				bDeclareBlockVariables(false){
	IAS_TRACER;

	//TODO (M) repair DM!
	pType=const_cast<DM::Type*>(pExpr->getType());

	const DM::ComplexType *pComplexType=pType->asComplexType();

	const DM::PropertyList& lstProperties(pComplexType->getProperties());

	for(int iIdx=0;iIdx<lstProperties.getSize();iIdx++)
		addVariable(IAS_DFT_FACTORY<Dec::VariableDeclaration>::Create(
						lstProperties[iIdx]->getName(),
						lstProperties[iIdx]->getType(),
						lstProperties[iIdx]->isMulti())
		);

}
/*************************************************************************/
With::With(const String& strVarName,Expr::XPath::XPathExprFamily *pExpr):
		ptrExpr(pExpr),
		pVariableProperty(0),
		bDeclareBlockVariables(true){

	IAS_TRACER;

	addVariable(IAS_DFT_FACTORY<Dec::VariableDeclaration>::Create(strVarName, ptrExpr->getType(), false));

}
/*************************************************************************/
With::~With() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void With::declareBlockVariables(DM::DataFactory *pDataFactory){
	IAS_TRACER;

	if(bDeclareBlockVariables){
		Exe::Dec::DeclarationBlockFeature::declareBlockVariables(pDataFactory);
		pVariableProperty=pType->asComplexType()->getProperties().getProperty(0);
	}else
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Nothing to declare :)");
}
/*************************************************************************/
void With::setStatement(Statement* pStatement){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pStatement);
	ptrStatement=pStatement;
}
/*************************************************************************/
void With::execute(Context *pCtx, DM::DataObjectPtr dmValue) const{
	IAS_TRACER;

	DM::DataObjectPtr dmContext;

	if(bDeclareBlockVariables){
		dmContext=createAndInitializeVariables();
		IAS_CHECK_IF_NULL(pVariableProperty);
		dmContext->setDataObject(pVariableProperty,dmValue);
	}else {

		if(!dmValue)
			IAS_THROW(NullObjectReferenceException(String(" WITH" )));

		dmContext=dmValue;
	}
	AutoPopUp autoPopUp(pCtx,dmContext);
	ptrStatement->execute(pCtx);

}
/*************************************************************************/
WithArray::WithArray(Expr::XPath::XPathExprFamily *pExpr):
		With(pExpr){
	IAS_TRACER;
	if(!pExpr->isArray())
		IAS_THROW(InternalException("Expression is not an array !"));
}
/*************************************************************************/
WithArray::WithArray(const String& strVarName,Expr::XPath::XPathExprFamily *pExpr):
	With(strVarName,pExpr){
	IAS_TRACER;
	if(!pExpr->isArray())
		IAS_THROW(InternalException("Expression is not an array !"));
}
/*************************************************************************/
WithArray::~WithArray()throw(){}
/*************************************************************************/
void WithArray::execute(Context *pCtx) const{
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"WITH:"<<(void*)this);


	DM::DataObjectList& dmList(ptrExpr->getTargetObjectList(pCtx));

	for(int iIdx=0; iIdx < dmList.size() && !pCtx->isInterrupted(); iIdx++)
		With::execute(pCtx,dmList.at(iIdx));

}
/*************************************************************************/
WithNonArray::WithNonArray(Expr::XPath::XPathExprFamily *pExpr):
		With(pExpr){
	IAS_TRACER;
	if(pExpr->isArray())
		IAS_THROW(InternalException("Expression is an array !"));
}
/*************************************************************************/
WithNonArray::WithNonArray(const String& strVarName,Expr::XPath::XPathExprFamily *pExpr):
	With(strVarName,pExpr){
	IAS_TRACER;
	if(pExpr->isArray())
		IAS_THROW(InternalException("Expression is an array !"));
}
/*************************************************************************/
WithNonArray::~WithNonArray()throw(){}
/*************************************************************************/
void WithNonArray::execute(Context *pCtx) const{

	DM::DataObjectPtr dmValue;
	ptrExpr->evaluate(pCtx,dmValue);

	if(!pCtx->isInterrupted()){
		With::execute(pCtx,dmValue);
	}

}
/*************************************************************************/
}
}
}
}
}
