/*
 * File: IAS-LangLib/src/lang/model/dec/DeclarationBlockFeature.h
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
#ifndef _IAS_AS_Lang_Model_DeclarationBlockFeature_H_
#define _IAS_AS_Lang_Model_DeclarationBlockFeature_H_

#include <commonlib/commonlib.h>

#include <list>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {
class DeclarationNode;

/*************************************************************************/
/** The class. */
 class DeclarationBlockFeature {
public:


	typedef std::list< ::IAS::Lang::Model::Dec::DeclarationNode* > DeclarationNodesList;

	void addDeclaration(::IAS::Lang::Model::Dec::DeclarationNode* pDeclaration);

	//TODO (L) what is it?
	const DeclarationNodesList& getDeclarationsListAsConst() const;
	const DeclarationNodesList& getDeclarationsList() const;

	virtual ~DeclarationBlockFeature() throw();

protected:
	DeclarationBlockFeature()throw();
	void init();

	DeclarationNodesList                  lstDeclarations;
	IAS_DFT_FACTORY<Dec::DeclarationNode>::PtrHoldersCollection phcDeclarations;

};

/*************************************************************************/

}
}
}
}

#endif /* _IAS_AS_Lang_Model_STATEMENTSLISTNODE_H_ */
