/*
 * File: IAS-LangLib/src/lang/model/dec/TypeDefinitionNode.h
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
#ifndef _IAS_AS_Lang_Model_Dec_TypeDefinition_H_
#define _IAS_AS_Lang_Model_Dec_TypeDefinition_H_

#include <commonlib/commonlib.h>
#include "../Node.h"
#include "DeclarationBlockFeature.h"
#include "TypeInfoNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {

/*************************************************************************/
/** The class. */
 class TypeDefinitionNode : public Node, public DeclarationBlockFeature{
public:

	virtual ~TypeDefinitionNode() throw();

	void setBaseTypeNode(TypeInfoNode* pTypeInfoNode);
	void setName(const String& strName);
	void setNamespace(const String& strNamespace);

	bool hasBaseType()const{
		return ! !ptrBaseTypeNode;
	}

	const TypeInfoNode* getBaseType()const{
		return ptrBaseTypeNode;
	}

	inline const String& getName()const{return strName;}
	inline const String& getNamespace()const{return strNamespace;}

protected:
	TypeDefinitionNode();

	String strName;
	String strNamespace;

	IAS_DFT_FACTORY<TypeInfoNode>::PtrHolder ptrBaseTypeNode;
	friend class ::IAS::Factory<TypeDefinitionNode>;

};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Dec_PARAMETERSNODE_H_ */
