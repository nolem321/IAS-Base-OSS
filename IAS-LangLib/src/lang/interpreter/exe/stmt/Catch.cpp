/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Catch.cpp
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
#include "Catch.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
Catch::Catch() throw(){
	IAS_TRACER;
	pCatchType=NULL;
	pCatchVariableProperty=NULL;
}
/*************************************************************************/
Catch::~Catch() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Catch::setCatchVariable(Dec::VariableDeclaration* pVariableDeclaration){
	IAS_TRACER;
	addVariable(pVariableDeclaration);
}
/*************************************************************************/
void Catch::setCatchStatement(Statement *pStatement){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pStatement);
	ptrStatement=pStatement;
}
/*************************************************************************/
void Catch::declareBlockVariables(DM::DataFactory *pDataFactory){
	IAS_TRACER;
	DeclarationBlockFeature::declareBlockVariables(pDataFactory);
	pCatchVariableProperty = pType->asComplexType()->getProperties().getProperty(0);
	pCatchType=pCatchVariableProperty->getType();
}
/*************************************************************************/
void Catch::execute(Context *pCtx, const DM::DataObjectPtr& ptrException) const{
	IAS_TRACER;

	AutoPopUp autoPopUp(pCtx,createAndInitializeVariables());
	pCtx->getBlockVariables(0)->setDataObject(pCatchVariableProperty,ptrException);
	ptrStatement->execute(pCtx);
}
/*************************************************************************/
const DM::Type* Catch::getCatchType()const{
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pCatchType)
	return pCatchType;
}
/*************************************************************************/
}
}
}
}
}
