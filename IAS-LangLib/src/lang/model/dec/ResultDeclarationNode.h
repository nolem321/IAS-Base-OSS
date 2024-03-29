/*
 * File: IAS-LangLib/src/lang/model/dec/ResultDeclarationNode.h
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
#ifndef _IAS_AS_Lang_Model_Dec_ResultDeclarationNode_H_
#define _IAS_AS_Lang_Model_Dec_ResultDeclarationNode_H_

#include <commonlib/commonlib.h>
#include "DeclarationNode.h"
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {

/*************************************************************************/
/** The class. */
 class ResultDeclarationNode : public DeclarationNode{
public:

	virtual ~ResultDeclarationNode() throw();

	static const String& CStrResultVariable;

protected:

	ResultDeclarationNode(const String& strType,
						  const String& strNamespace=DM::DataFactory::BuildInTypesNamespace);

	friend class ::IAS::Factory<ResultDeclarationNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Dec_DECLARATIONNODE_H_ */
