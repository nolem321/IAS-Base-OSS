/*
 * File: IAS-LangLib/src/lang/model/ProgramNode.h
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
#ifndef _IAS_AS_Lang_Model_ProgramNode_H_
#define _IAS_AS_Lang_Model_ProgramNode_H_

#include <commonlib/commonlib.h>
#include "Node.h"
#include "dec/DeclarationBlockFeature.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {
class ParametersNode;
class QualifiedNameNode;
}

/*************************************************************************/
/** The class. */
 class ProgramNode :
	public Node,
	protected IAS::Lang::Model::Dec::DeclarationBlockFeature	{
public:

	virtual ~ProgramNode() throw();

	Dec::QualifiedNameNode*   getQualifiedNameNode() const { return ptrQualifiedNameNode; };
	Dec::ParametersNode*      getParametersNode() const { return ptrParametersNode; };


	bool isReturningResult()const {return bIsReturningResult; } ;

protected:
	ProgramNode(Dec::QualifiedNameNode*    pQualifiedNameNode,
			    Dec::ParametersNode*      pParametersNode);

	IAS_DFT_FACTORY<Dec::QualifiedNameNode>::PtrHolder   ptrQualifiedNameNode;
	IAS_DFT_FACTORY<Dec::ParametersNode>::PtrHolder      ptrParametersNode;

	void addResultDeclarationNode(Dec::DeclarationNode*     pResultDeclartionNode);

	bool bIsReturningResult;

	friend class ::IAS::Factory<ProgramNode>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_AS_Lang_Model_ProgramNode_H_ */
