/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorLogic.h
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
#ifndef _IAS_DM_Gen_CppCodeGeneratorLogic_H_
#define _IAS_DM_Gen_CppCodeGeneratorLogic_H_

#include <commonlib/commonlib.h>

#include <map>
#include <vector>
#include <dm/gen/Impl/Patterns.h>
#include <dm/datamodel.h>

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {


/*************************************************************************/
class CppCodeGeneratorLogic {
public:

	virtual ~CppCodeGeneratorLogic() throw();

	void generate(const StringList& lstNamespaces);


	typedef std::vector<const DM::Type*> TypesList;

	//TODO (M) Use IAS Types

	struct NamespaceInfo{

		virtual ~NamespaceInfo(){};
		TypesList lstTypes;
		std::map<const DM::Type*,bool> hmTypes;
		StringList                      lstNSParts;
		std::map<String,bool> lstDependentNamespaces;

		void init();
	};

	typedef HashMapStringToPointer<NamespaceInfo> NamespacesMap;

	void setSingleDataObjectFile(bool bValue);

	const String& getUniq()const{return strUniq;};

protected:

	CppCodeGeneratorLogic(const DM::DataFactory* pDataFactory, const String& strBaseDir);

	const DM::DataFactory* pDataFactory;

	NamespacesMap hmNamespaces;

	void buildNamespacesMap(const StringList& lstNamespaces);
	void buildForType(NamespaceInfo* pInfo,
						const DM::Type*);

	void generateGlobals();

	void generateHeader(const NamespacesMap::const_iterator& itNamespace);
	void generateCode(const NamespacesMap::const_iterator& itNamespace);

	String getBaseFileName(const NamespacesMap::const_iterator& itNamespace);

	String strBaseDir;

	void printNamespace(std::ostream& os,
						 Template *pTemplate,
						 const StringList& lstParts,
						 bool bBackwards=false);


	String getPropertyTypeString(const DM::Type* pType,
								   const DM::Property* pProperty);

	void analizeDMMethod(const DM::Property* pProperty,
							String& strName,
							bool& bHasLength);

	void mkDir(const String& strDirName);
	OutputFile* openFile(const String& strName);


	bool hasPrefix(const StringList& lstNamespaces, const String strURI);

private:

	IAS_DFT_FACTORY<Template>::PtrHolder ptrPreamble;

	Patterns patterns;

	String strAutoGenDir;
	String strAutoGenURI;
	String strAutoGenNS;
	String strAutoGenFile;
	String strAutoGenFileHeader;

	String strUniq;
	StringList lstStandardNamespaces;

	bool bSingleDataObjectFile;

	friend class CppCodeGeneratorFriend;
	friend class ::IAS::Factory<CppCodeGeneratorLogic>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DMWrap_Cpp_CPPCODEGENERATORLOGIC_H_ */


