/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/Patterns.h
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
#ifndef _IAS_DM_Gen_Patterns_H_
#define _IAS_DM_Gen_Patterns_H_

#include <commonlib/commonlib.h>

namespace IAS {

namespace DM {
namespace Gen {
namespace Impl {

/*************************************************************************/
class Patterns {
public:

	IAS_DFT_FACTORY<Template>::PtrHolder ptrFilePreamble;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_ifndef;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_endif;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrUsingNamespaceIAS;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_local;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_local_h;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_global;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_commonlib;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_dm;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_dmgen;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_globalImplDataFactory;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_impl;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_implBulitIn;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_defaultTypes;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrHeader_include_defaultTypesImpl;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrNamespace_start;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrNamespace_end;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrNamespace_prefix;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobals_header;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobalImplDataFactory_header;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobalImplDataFactory_implPart01;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobalImplDataFactory_implPart02;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobalImplDataFactory_implDefine;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobalImplDataFactory_implDeclare;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrDeclaration_typeDeclarations;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceDataFactory_headerPart01;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceDataFactory_headerPart02;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceDataFactory_headerTypeMethods;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceDataFactory_sourcePart01;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceDataFactory_sourceTypeMethods;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart01;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart01withBase;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart02a;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart02DataObject;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart02SimpleType;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart02Type;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart02TypeWithBase;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerPart03;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPtrList;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerChecker;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerGetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerGetterMany;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerSetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerCreator;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerUnsetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerCreateType;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrInterfaceType_headerGetProperty;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart01;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart02;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart02withBase;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart02withBaseBuiltIn;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart03;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04a;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04DataObject;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04SimpleType;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04Type;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04TypeWithBase;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04TypeWithBaseBuildIn;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart04TypeBody;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart05;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPart06;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_includeSuperclasses;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerChecker;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerGetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerGetterMany;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerSetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerCreator;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerUnsetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerGetProperty;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_headerPropertyMember;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart01;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart02;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart02withBase;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart02withBaseBulitIn;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart03a;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart03DataObject;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart03SimpleType;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart03b;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart04;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart05;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourcePart06;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceChecker;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceGetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceGetterMany;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceConstructorManyInit;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceGetterDM;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceSetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceCreator;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceUnsetter;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceDefineType;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceDefineTypeWithBase;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceDefineTypeWithBuildIn;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceDefineProperty;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceInheritProperty;
	IAS_DFT_FACTORY<Template>::PtrHolder ptrImplType_sourceGetProperty;

	IAS_DFT_FACTORY<Template>::PtrHolder ptrGlobals_header_incImpl;


	Patterns();

	void addInclude(OutputFile* pOutputFile, const String& strFileToInclude) const;
	void addGlobalInclude(OutputFile* pOutputFile, const String& strFileToInclude) const;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DMWrap_Cpp_PATTERNS_H_ */

