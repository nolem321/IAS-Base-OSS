/*
 * File: IAS-LangLib/src/lang/interpreter/proc/CallbackRegister.cpp
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
#include "CallbackRegister.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "NodeHandler.h"
#include "ExternalProgramNodeHandler.h"
#include "StandardProgramNodeHandler.h"

#include "dec/DeclarationNodeHandler.h"
#include "dec/ResultDeclarationNodeHandler.h"
#include "dec/ParametersNodeHandler.h"
#include "dec/TypeDefinitionNodeHandler.h"

#include "expr/CastNodeHandler.h"
#include "expr/ConstNodeHandler.h"
#include "expr/ConstructorNodeHandler.h"
#include "expr/CopyOfNodeHandler.h"
#include "expr/DetachNodeHandler.h"
#include "expr/DivisionNodeHandler.h"
#include "expr/ExprNodeHandler.h"
#include "expr/ExprListNodeHandler.h"
#include "expr/FunCallNodeHandler.h"
#include "expr/GetTypeNodeHandler.h"
#include "expr/GetTypeNSNodeHandler.h"
#include "expr/RelationalDiffNodeHandler.h"
#include "expr/RelationalEqGtNodeHandler.h"
#include "expr/RelationalEqLessNodeHandler.h"
#include "expr/RelationalEqNodeHandler.h"
#include "expr/RelationalGtNodeHandler.h"
#include "expr/RelationalIsInstanceNodeHandler.h"
#include "expr/RelationalIsTypeNodeHandler.h"
#include "expr/RelationalLessNodeHandler.h"
#include "expr/SizeOfNodeHandler.h"
#include "expr/IsSetNodeHandler.h"
#include "expr/IsNullNodeHandler.h"
#include "expr/SubtractionNodeHandler.h"
#include "expr/ModuloNodeHandler.h"
#include "expr/MultiplyNodeHandler.h"
#include "expr/NegativeNodeHandler.h"
#include "expr/LogicalNotNodeHandler.h"
#include "expr/LogicalAndNodeHandler.h"
#include "expr/LogicalOrNodeHandler.h"
#include "expr/OperNodeHandler.h"
#include "expr/AdditionNodeHandler.h"
#include "expr/StrLenNodeHandler.h"
#include "expr/UnaryOperNodeHandler.h"
#include "expr/xpath/XPathAccessNodeHandler.h"
#include "expr/xpath/XPathExprAccessNodeHandler.h"
#include "expr/xpath/XPathVariableAccessNodeHandler.h"
#include "expr/xpath/XPathExprNodeHandler.h"
#include "expr/xpath/XPathNodeHandler.h"

#include "stmt/AssignmentNodeHandler.h"
#include "stmt/CallNodeHandler.h"
#include "stmt/CatchListNodeHandler.h"
#include "stmt/CatchNodeHandler.h"
#include "stmt/DeleteNodeHandler.h"
#include "stmt/ForLoopNodeHandler.h"
#include "stmt/IfThenElseNodeHandler.h"
#include "stmt/LeftSideNodeHandler.h"
#include "stmt/ReturnNodeHandler.h"
#include "stmt/StatementNodeHandler.h"
#include "stmt/StatementsListNodeHandler.h"
#include "stmt/ThrowNodeHandler.h"
#include "stmt/TryCatchNodeHandler.h"
#include "stmt/WhileLoopNodeHandler.h"
#include "stmt/WithNodeHandler.h"
namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/

//template<>
//IAS::InstanceFeature<CallbackRegister>::TheInstanceType
//IAS::InstanceFeature<CallbackRegister>::TheInstance(NULL);

/*************************************************************************/
CallbackRegister::CallbackRegister(){
	IAS_TRACER;
	init();
}
/*************************************************************************/
CallbackRegister::~CallbackRegister() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CallbackRegister::init(){
	IAS_TRACER;
	registerCallback<Model::Node>(IAS_DFT_FACTORY<NodeHandler>::Create());

	registerCallback<Model::ExternalProgramNode>(IAS_DFT_FACTORY<ExternalProgramNodeHandler>::Create());
	registerCallback<Model::StandardProgramNode>(IAS_DFT_FACTORY<StandardProgramNodeHandler>::Create());

	registerCallback<Model::Dec::DeclarationNode>(IAS_DFT_FACTORY<Dec::DeclarationNodeHandler>::Create());
	registerCallback<Model::Dec::ResultDeclarationNode>(IAS_DFT_FACTORY<Dec::ResultDeclarationNodeHandler>::Create());

	registerCallback<Model::Dec::ParametersNode>(IAS_DFT_FACTORY<Dec::ParametersNodeHandler>::Create());

	registerCallback<Model::Dec::TypeDefinitionNode>(IAS_DFT_FACTORY<Dec::TypeDefinitionNodeHandler>::Create());

	registerCallback<Model::Expr::CastNode>(IAS_DFT_FACTORY<Expr::CastNodeHandler>::Create());
	registerCallback<Model::Expr::ConstNode>(IAS_DFT_FACTORY<Expr::ConstNodeHandler>::Create());
	registerCallback<Model::Expr::ConstructorNode>(IAS_DFT_FACTORY<Expr::ConstructorNodeHandler>::Create());
	registerCallback<Model::Expr::DivisionNode>(IAS_DFT_FACTORY<Expr::DivisionNodeHandler>::Create());

	registerCallback<Model::Expr::ExprNode>(IAS_DFT_FACTORY<Expr::ExprNodeHandler>::Create());
	registerCallback<Model::Expr::ExprListNode>(IAS_DFT_FACTORY<Expr::ExprListNodeHandler>::Create());
	registerCallback<Model::Expr::FunCallNode>(IAS_DFT_FACTORY<Expr::FunCallNodeHandler>::Create());

	registerCallback<Model::Expr::RelationalDiffNode>(IAS_DFT_FACTORY<Expr::RelationalDiffNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalEqGtNode>(IAS_DFT_FACTORY<Expr::RelationalEqGtNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalEqLessNode>(IAS_DFT_FACTORY<Expr::RelationalEqLessNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalEqNode>(IAS_DFT_FACTORY<Expr::RelationalEqNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalGtNode>(IAS_DFT_FACTORY<Expr::RelationalGtNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalLessNode>(IAS_DFT_FACTORY<Expr::RelationalLessNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalIsInstanceNode>(IAS_DFT_FACTORY<Expr::RelationalIsInstanceNodeHandler>::Create());
	registerCallback<Model::Expr::RelationalIsTypeNode>(IAS_DFT_FACTORY<Expr::RelationalIsTypeNodeHandler>::Create());

	registerCallback<Model::Expr::IsSetNode>(IAS_DFT_FACTORY<Expr::IsSetNodeHandler>::Create());
	registerCallback<Model::Expr::IsNullNode>(IAS_DFT_FACTORY<Expr::IsNullNodeHandler>::Create());

	registerCallback<Model::Expr::SizeOfNode>(IAS_DFT_FACTORY<Expr::SizeOfNodeHandler>::Create());
	registerCallback<Model::Expr::GetTypeNode>(IAS_DFT_FACTORY<Expr::GetTypeNodeHandler>::Create());
	registerCallback<Model::Expr::GetTypeNSNode>(IAS_DFT_FACTORY<Expr::GetTypeNSNodeHandler>::Create());

	registerCallback<Model::Expr::LogicalNotNode>(IAS_DFT_FACTORY<Expr::LogicalNotNodeHandler>::Create());
	registerCallback<Model::Expr::LogicalAndNode>(IAS_DFT_FACTORY<Expr::LogicalAndNodeHandler>::Create());
	registerCallback<Model::Expr::LogicalOrNode>(IAS_DFT_FACTORY<Expr::LogicalOrNodeHandler>::Create());

	registerCallback<Model::Expr::CopyOfNode>(IAS_DFT_FACTORY<Expr::CopyOfNodeHandler>::Create());
	registerCallback<Model::Expr::DetachNode>(IAS_DFT_FACTORY<Expr::DetachNodeHandler>::Create());
	registerCallback<Model::Expr::NegativeNode>(IAS_DFT_FACTORY<Expr::NegativeNodeHandler>::Create());

	registerCallback<Model::Expr::AdditionNode>  (IAS_DFT_FACTORY<Expr::AdditionNodeHandler>::Create());
	registerCallback<Model::Expr::MultiplyNode>(IAS_DFT_FACTORY<Expr::MultiplyNodeHandler>::Create());
	registerCallback<Model::Expr::OperNode>(IAS_DFT_FACTORY<Expr::OperNodeHandler>::Create());
	registerCallback<Model::Expr::SubtractionNode>(IAS_DFT_FACTORY<Expr::SubtractionNodeHandler>::Create());
	registerCallback<Model::Expr::ModuloNode>(IAS_DFT_FACTORY<Expr::ModuloNodeHandler>::Create());

	registerCallback<Model::Expr::UnaryOperNode>(IAS_DFT_FACTORY<Expr::UnaryOperNodeHandler>::Create());
	registerCallback<Model::Expr::XPath::XPathExprNode>(IAS_DFT_FACTORY<Expr::XPath::XPathExprNodeHandler>::Create());
	registerCallback<Model::Expr::XPath::XPathExprAccessNode>(IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNodeHandler>::Create());
	registerCallback<Model::Expr::XPath::XPathVariableAccessNode>(IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNodeHandler>::Create());
	registerCallback<Model::Expr::XPath::XPathAccessNode>(IAS_DFT_FACTORY<Expr::XPath::XPathAccessNodeHandler>::Create());
	registerCallback<Model::Expr::XPath::XPathNode>(IAS_DFT_FACTORY<Expr::XPath::XPathNodeHandler>::Create());

	registerCallback<Model::Expr::StrLenNode>(IAS_DFT_FACTORY<Expr::StrLenNodeHandler>::Create());

	registerCallback<Model::Stmt::AssignmentNode>(IAS_DFT_FACTORY<Stmt::AssignmentNodeHandler>::Create());
	registerCallback<Model::Stmt::CallNode>(IAS_DFT_FACTORY<Stmt::CallNodeHandler>::Create());
	registerCallback<Model::Stmt::CatchNode>(IAS_DFT_FACTORY<Stmt::CatchNodeHandler>::Create());
	registerCallback<Model::Stmt::CatchListNode>(IAS_DFT_FACTORY<Stmt::CatchListNodeHandler>::Create());
	registerCallback<Model::Stmt::DeleteNode>(IAS_DFT_FACTORY<Stmt::DeleteNodeHandler>::Create());
	registerCallback<Model::Stmt::ForLoopNode>(IAS_DFT_FACTORY<Stmt::ForLoopNodeHandler>::Create());
	registerCallback<Model::Stmt::IfThenElseNode>(IAS_DFT_FACTORY<Stmt::IfThenElseNodeHandler>::Create());
	registerCallback<Model::Stmt::LeftSideNode>(IAS_DFT_FACTORY<Stmt::LeftSideNodeHandler>::Create());
	registerCallback<Model::Stmt::ReturnNode>(IAS_DFT_FACTORY<Stmt::ReturnNodeHandler>::Create());
	registerCallback<Model::Stmt::StatementNode>(IAS_DFT_FACTORY<Stmt::StatementNodeHandler>::Create());
	registerCallback<Model::Stmt::StatementsListNode>(IAS_DFT_FACTORY<Stmt::StatementsListNodeHandler>::Create());
	registerCallback<Model::Stmt::ThrowNode>(IAS_DFT_FACTORY<Stmt::ThrowNodeHandler>::Create());
	registerCallback<Model::Stmt::TryCatchNode>(IAS_DFT_FACTORY<Stmt::TryCatchNodeHandler>::Create());
	registerCallback<Model::Stmt::WhileLoopNode>(IAS_DFT_FACTORY<Stmt::WhileLoopNodeHandler>::Create());
	registerCallback<Model::Stmt::WithNode>(IAS_DFT_FACTORY<Stmt::WithNodeHandler>::Create());

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Registered "<<hmCallbacks.size()<<" callbacks.");
}
/*************************************************************************/
void CallbackRegister::Call(const Model::Node* pNode,
							   ExecStore*       pExecStore,
							   DM::DataFactory *pDataFactory,
							   CallbackSignature::Result&      aResult){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);

	CallbackSignature::CallbackCtx ctx(pDataFactory,pExecStore);

	GetInstance()->getCallback(pNode)->call(pNode, &ctx, aResult);
}
/*************************************************************************/
void CallbackRegister::SubCall(const Model::Node* pNode,
								  CallbackSignature::CallbackCtx* pCtx,
								  CallbackSignature::Result&      aResult){
	IAS_TRACER;
	GetInstance()->getCallback(pNode)->call(pNode, pCtx, aResult);
}
/*************************************************************************/
}
}
}
}
