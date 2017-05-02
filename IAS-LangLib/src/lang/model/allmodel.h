/*
 * File: IAS-LangLib/src/lang/model/allmodel.h
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
#ifndef _IAS_AS_Lang_Model_ALLMODEL_H_
#define _IAS_AS_Lang_Model_ALLMODEL_H_

#include "Model.h"
#include "Node.h"
#include "ExternalProgramNode.h"
#include "StandardProgramNode.h"

#include "dec/DeclarationNode.h"
#include "dec/NamespaceNode.h"
#include "dec/ParametersNode.h"
#include "dec/QualifiedNameNode.h"
#include "dec/ResultDeclarationNode.h"
#include "dec/TypeInfoNode.h"
#include "dec/TypeDefinitionNode.h"

#include "expr/AdditionNode.h"
#include "expr/CastNode.h"
#include "expr/CondValueNode.h"
#include "expr/ConstNode.h"
#include "expr/ConstructorNode.h"
#include "expr/CopyOfNode.h"
#include "expr/DetachNode.h"
#include "expr/DivisionNode.h"
#include "expr/ExprNode.h"
#include "expr/ExprListNode.h"
#include "expr/FunCallNode.h"
#include "expr/GetTypeNode.h"
#include "expr/GetTypeNSNode.h"
#include "expr/LogicalAndNode.h"
#include "expr/LogicalBinaryOperNode.h"
#include "expr/LogicalExprNode.h"
#include "expr/LogicalOrNode.h"
#include "expr/LogicalNotNode.h"

#include "expr/ModuloNode.h"
#include "expr/MultiplyNode.h"
#include "expr/NegativeNode.h"
#include "expr/OperNode.h"
#include "expr/RelationalDiffNode.h"
#include "expr/RelationalEqGtNode.h"
#include "expr/RelationalEqLessNode.h"
#include "expr/RelationalEqNode.h"
#include "expr/RelationalGtNode.h"
#include "expr/RelationalLessNode.h"
#include "expr/RelationalIsTypeNode.h"
#include "expr/RelationalIsInstanceNode.h"
#include "expr/SizeOfNode.h"
#include "expr/IsSetNode.h"
#include "expr/IsNullNode.h"
#include "expr/StrLenNode.h"
#include "expr/SubtractionNode.h"
#include "expr/UnaryOperNode.h"
#include "expr/XPathOrValueNode.h"

#include "expr/xpath/XPathExprNode.h"
#include "expr/xpath/XPathExprAccessNode.h"
#include "expr/xpath/XPathVariableAccessNode.h"
#include "expr/xpath/XPathNode.h"

#include "stmt/AssignmentNode.h"
#include "stmt/CallNode.h"
#include "stmt/CatchListNode.h"
#include "stmt/CatchNode.h"
#include "stmt/ConditionalAssignmentNode.h"
#include "stmt/CreateNode.h"
#include "stmt/DeleteNode.h"
#include "stmt/ForLoopNode.h"
#include "stmt/IfThenElseNode.h"
#include "stmt/IndexNode.h"
#include "stmt/LeftSideNode.h"
#include "stmt/MergeNode.h"
#include "stmt/ReturnNode.h"
#include "stmt/SortNode.h"
#include "stmt/StatementNode.h"
#include "stmt/StatementsListNode.h"
#include "stmt/TryCatchNode.h"
#include "stmt/ThrowNode.h"
#include "stmt/WhileLoopNode.h"
#include "stmt/WithNode.h"

#endif /* _IAS_AS_Lang_Model_ALLMODEL_H_ */
