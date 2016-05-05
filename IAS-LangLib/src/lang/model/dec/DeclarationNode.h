/*
 * File: IAS-LangLib/src/lang/model/dec/DeclarationNode.h
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
#ifndef _IAS_AS_Lang_Model_Dec_DECLARATIONNODE_H_
#define _IAS_AS_Lang_Model_Dec_DECLARATIONNODE_H_

#include <commonlib/commonlib.h>
#include "../Node.h"

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {

/*************************************************************************/
/** The class. */
 class DeclarationNode : public Node{
public:

	virtual ~DeclarationNode() throw();

	inline const String& getVariable() const { return strVariable; };
	inline const String& getType() const { return strType; };
	inline const String& getNamespace() const { return strNamespace; };

	void setIsArray(bool bIsArray);
	bool isArray() const { return bIsArray; };
	bool hasNamespace() const { return ! strNamespace.empty(); };

protected:

	DeclarationNode(const String& strVariable,
				    const String& strType,
					const String& strNamespace=DM::DataFactory::BuildInTypesNamespace);

	String strVariable;
	String strType;
	String strNamespace;

	bool bIsArray;

	friend class ::IAS::Factory<DeclarationNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Dec_DECLARATIONNODE_H_ */
