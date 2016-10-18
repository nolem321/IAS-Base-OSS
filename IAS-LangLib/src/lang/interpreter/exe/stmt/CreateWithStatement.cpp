/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/CreateWithStatement.cpp
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
#include "CreateWithStatement.h"

#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../expr/Expr.h"
#include "../expr/ExprList.h"
#include "../Context.h"
#include "../expr/xpath/XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
CreateWithStatement::CreateWithStatement(Expr::XPath::XPathExprFamily *pXPathExprFamily):
		Create(pXPathExprFamily){
	IAS_TRACER;

	//TODO (M) repair DM!
	pType=const_cast<DM::Type*>(pXPathExprFamily->getType());

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
CreateWithStatement::~CreateWithStatement() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CreateWithStatement::setStatement(Statement* pStatement){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pStatement);
	ptrStatement=pStatement;
}
/*************************************************************************/
void CreateWithStatement::execute(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject *dmContext = ptrXPathExprFamily->createDataObject(pCtx);

	AutoPopUp autoPopUp(pCtx,dmContext);
	ptrStatement->execute(pCtx);

}
/*************************************************************************/
}
}
}
}
}
