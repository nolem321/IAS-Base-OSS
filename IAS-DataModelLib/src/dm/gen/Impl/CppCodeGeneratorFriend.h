/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorFriend.h
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
#ifndef _IAS_DM_Gen_Impl_CppCodeGeneratorFriend_H_
#define _IAS_DM_Gen_Impl_CppCodeGeneratorFriend_H_

#include <commonlib/commonlib.h>
#include "../../../dm/gen/Impl/CppCodeGeneratorLogic.h"
namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {


/*************************************************************************/
class CppCodeGeneratorFriend {
public:

	virtual ~CppCodeGeneratorFriend() throw();

	protected:

	CppCodeGeneratorFriend(CppCodeGeneratorLogic* pParent);
	inline const Patterns& getPatterns() { return pParent->patterns;} ;
	inline OutputFile* openFile(const String& strName){ return pParent->openFile(strName);};
	inline void mkDir(const String& strDir) const { pParent->mkDir(strDir); };
	inline const StringList& getStandardNamespaces() const { return pParent->lstStandardNamespaces; };
	inline const CppCodeGeneratorLogic::NamespacesMap& getNSMap() const { return pParent->hmNamespaces; };

	void beginStandardNamespaces(OutputFile* pFile) const;
	void endStandardNamespaces(OutputFile* pFile) const;

	void beginTypeNamespaces(OutputFile* pFile, const StringList& strNSParts) const;
	void endTypeNamespaces(OutputFile* pFile, const StringList& strNSParts) const;

	bool isGeneratedType(const DM::Type* pType) const;

	String computeReturnType(const Type* pType) const;
	String computeReturnListType(const Type* pType) const;
	String computeSetterType(const Type* pType) const;
	String computeDMSetterMethod(const Type* pType) const;
	String computeImplClass(const Type* pType) const;

	String computeDataObjectType(const Type* pType, bool bPointer) const;

	bool hasDataObjectMethods(const DM::Type* pType) const;

	unsigned int getStartingProperty(const DM::Type* pType) const;

	const String& getUniq()const{return pParent->getUniq();};

	private:
		CppCodeGeneratorLogic* pParent;

	friend class ::IAS::Factory<CppCodeGeneratorFriend>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DM_Gen_Impl_CppCodeGeneratorFriend_H_ */
