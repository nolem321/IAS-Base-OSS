/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/ConstNodeHandler.cpp
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
#include "ConstNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/ConstExprFamily.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
ConstNodeHandler::ConstNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
ConstNodeHandler::~ConstNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const DM::Type* ConstNodeHandler::getDMType(const DM::DataFactory* pDataFactory,
											  Model::Expr::ConstNode::Type iType) const{
	IAS_TRACER;

	switch(iType){

		case Model::Expr::ConstNode::CN_INTEGER:
			return pDataFactory->getDefaultType(DM::Type::IntegerType);

		case Model::Expr::ConstNode::CN_STRING:
				return pDataFactory->getDefaultType(DM::Type::TextType);

		case Model::Expr::ConstNode::CN_BOOLEAN:
				return pDataFactory->getDefaultType(DM::Type::BooleanType);

		case Model::Expr::ConstNode::CN_FLOAT:
				return pDataFactory->getDefaultType(DM::Type::FloatType);

		case Model::Expr::ConstNode::CN_NULL:
			return pDataFactory->getDefaultType(DM::Type::AnyType);

		}

	IAS_THROW(InternalException("No case for value in: ConstNodeHandler::getType"));
}

/*************************************************************************/
void ConstNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::ConstNode, pNode);
	const Model::Expr::ConstNode *pConstNode = IAS_DYNAMICCAST_CONST(Model::Expr::ConstNode, pNode);

	const DM::DataFactory* pDataFactory = pCtx->getDataFactory();

	aResult.pExpr=Exe::Expr::ConstExprFamily::Create(getDMType(pDataFactory, pConstNode->getType()),
													 pConstNode->getOriginalText());
}
/*************************************************************************/
}
}
}
}
}
