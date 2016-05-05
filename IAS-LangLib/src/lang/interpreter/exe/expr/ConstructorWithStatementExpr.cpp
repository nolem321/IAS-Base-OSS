/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ConstructorWithStatementExpr.cpp
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
#include "ConstructorWithStatementExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/interpreter/exe/stmt/Statement.h>
#include <lang/interpreter/exe/exception/InterpreterException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
/*************************************************************************/
ConstructorWithStatementExpr::ConstructorWithStatementExpr(const IAS::DM::Type *pType):
 ConstructorExpr(pType){
	IAS_TRACER;

	if(!pType->isDataObjectType())
		IAS_THROW(InterpreterException("BEGIN ... END allowed only for a data object types in the NEW constructor call."));

	const DM::ComplexType *pComplexType=pType->asComplexType();

	const DM::PropertyList& lstProperties(pComplexType->getProperties());

	for(int iIdx=0;iIdx<lstProperties.getSize();iIdx++)
		addVariable(
				IAS_DFT_FACTORY<Dec::VariableDeclaration>::Create(
						lstProperties[iIdx]->getName(),
						lstProperties[iIdx]->getType(),
						lstProperties[iIdx]->isMulti())
		);

	//TODO (M) repair DM!
	Dec::TypeCreator::pType=const_cast<DM::Type*>(pType);
}
/*************************************************************************/
void ConstructorWithStatementExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
	IAS_TRACER;

	refResult = ConstructorExpr::getType()->createDataObject();

	Dec::DeclarationBlockFeature::AutoPopUp autoPopUp(pCtx, refResult);
	ptrStatement->execute(pCtx);
}
/*************************************************************************/
void ConstructorWithStatementExpr::setStatement(Stmt::Statement* pStatement){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pStatement);
	ptrStatement=pStatement;
}
/*************************************************************************/
}
}
}
}
}
