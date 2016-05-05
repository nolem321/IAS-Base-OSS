/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorInterfaceType.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorInterfaceType.h"
#include <commonlib/commonlib.h>
#include <stdlib.h>

#include "../../../dm/gen/Impl/CppCodeGeneratorLogic.h"
#include "../../../dm/gen/Impl/Helpers.h"
#include "../../../dm/gen/Impl/Patterns.h"
#include "../../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {


/*************************************************************************/
CppCodeGeneratorInterfaceType::CppCodeGeneratorInterfaceType(CppCodeGeneratorLogic* pParent):
		CppCodeGeneratorFriend(pParent){
	IAS_TRACER;
}
/*************************************************************************/
CppCodeGeneratorInterfaceType::~CppCodeGeneratorInterfaceType() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGeneratorInterfaceType::generateHeader(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
													    const Type* pType){
	IAS_TRACER;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Namespace.");

	String strFileName;
	Helpers::URIToFilePath(pNamespaceInfo->lstNSParts,strFileName);

	std::map<String,bool> hmIncludedNS;

	mkDir(strFileName);

	if(!strFileName.empty())
		strFileName+="/";

	strFileName+=pType->getName();
	strFileName+=".h";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;
	mapArgs.add("file",Helpers::convertToSymbol(strFileName,'_',true));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_ifndef->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_commonlib->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_dm->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_defaultTypes->evaluate(mapArgs, ptrFile->getStreamRef());

	if(!pType->isRootType()){
		Template::Arguments argBaseInclude;
		const Type* pBaseType = pType->getBaseType();
		String strIncludeFile;
		if(pBaseType->getURI().compare(DataFactory::BuildInTypesNamespace)){
			Helpers::URIToFilePath(pBaseType->getURI(),strIncludeFile);
		}else{
			strIncludeFile+="dm/default";
		}

		strIncludeFile+="/";
		strIncludeFile+=pBaseType->getName();
		strIncludeFile+=".h";

		argBaseInclude.add("file",strIncludeFile);
		getPatterns().ptrHeader_include_local->evaluate(argBaseInclude, ptrFile->getStreamRef());
	}

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

			const PropertyList& lstProperties = pComplexType->getProperties();
			for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++){
				const Property* pProperty = lstProperties.getProperty(iIdx);
				const Type* pPropertyType=pProperty->getType();

				if( pPropertyType->getURI().compare(DataFactory::BuildInTypesNamespace) != 0 &&
					hmIncludedNS.count(pPropertyType->getURI())== 0){
					String strIncludeFile;
					Template::Arguments argBaseInclude;
					Helpers::URIToFilePath(pPropertyType->getURI(),strIncludeFile);
					strIncludeFile+="/Declarations.h";
					argBaseInclude.add("file",strIncludeFile);
					getPatterns().ptrHeader_include_local->evaluate(argBaseInclude, ptrFile->getStreamRef());

				}
			}

		}

	beginTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);

	mapArgs.add("type",pType->getName());
	mapArgs.add("typens",Helpers::URIToPrefix(pType->getURI()));

	if(pType->isRootType()){
		getPatterns().ptrInterfaceType_headerPart01->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		mapArgs.add("base",pType->getBaseType()->getName());
		mapArgs.add("basens",Helpers::URIToPrefix(pType->getBaseType()->getURI()));
		getPatterns().ptrInterfaceType_headerPart01withBase->evaluate(mapArgs, ptrFile->getStreamRef());
	}

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=getStartingProperty(pType); iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments argGetterSetter;

			argGetterSetter.add("checker",Helpers::PropertyToMethod("isSet",pProperty->getName()));
			argGetterSetter.add("getter",Helpers::PropertyToMethod("get",pProperty->getName()));
			argGetterSetter.add("setter",Helpers::PropertyToMethod("set",pProperty->getName()));
			argGetterSetter.add("creator",Helpers::PropertyToMethod("create",pProperty->getName()));

			argGetterSetter.add("retType",computeReturnType(pProperty->getType()));
			argGetterSetter.add("setType",computeSetterType(pProperty->getType()));

			if(pProperty->isMulti()){
				argGetterSetter.add("retList",computeReturnListType(pProperty->getType()));
				getPatterns().ptrInterfaceType_headerGetterMany->evaluate(argGetterSetter, ptrFile->getStreamRef());
			}else{
				getPatterns().ptrInterfaceType_headerGetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
				if(hasDataObjectMethods(pProperty->getType())){
					argGetterSetter.add("retType",computeDataObjectType(pProperty->getType(),true));
					argGetterSetter.add("getter",Helpers::PropertyToMethod("get",pProperty->getName())+="DataObject");
					getPatterns().ptrInterfaceType_headerGetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
				}

			}
			getPatterns().ptrInterfaceType_headerChecker->evaluate(argGetterSetter, ptrFile->getStreamRef());
			getPatterns().ptrInterfaceType_headerSetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
			getPatterns().ptrInterfaceType_headerUnsetter->evaluate(argGetterSetter, ptrFile->getStreamRef());

			if(hasDataObjectMethods(pProperty->getType())){

				argGetterSetter.add("setType",computeDataObjectType(pProperty->getType(),true));
				argGetterSetter.add("setter",Helpers::PropertyToMethod("set",pProperty->getName())+="DataObject");
				getPatterns().ptrInterfaceType_headerSetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
			}else{
				if(pProperty->getType()->getTypeEnum() != Type::AnyType){
					argGetterSetter.add("retType",computeReturnType(pProperty->getType()));
					getPatterns().ptrInterfaceType_headerCreator->evaluate(argGetterSetter, ptrFile->getStreamRef());
				}
			}

		}

	}

	getPatterns().ptrInterfaceType_headerPart02a->evaluate(mapArgs, ptrFile->getStreamRef());
	if(pType->isDataObjectType()){
		getPatterns().ptrInterfaceType_headerPart02DataObject->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		Template::Arguments argList(mapArgs);
		argList.add("setType",computeSetterType(pType));
		argList.add("retType",computeReturnType(pType));
		getPatterns().ptrInterfaceType_headerPart02SimpleType->evaluate(argList, ptrFile->getStreamRef());
	}

	if(pType->isRootType()){
		getPatterns().ptrInterfaceType_headerPart02Type->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		getPatterns().ptrInterfaceType_headerPart02TypeWithBase->evaluate(mapArgs, ptrFile->getStreamRef());
	}

	mapArgs.add("setType",computeSetterType(pType));
	getPatterns().ptrInterfaceType_headerCreateType->evaluate(mapArgs, ptrFile->getStreamRef());

	if (pType->isDataObjectType()) {
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for (int iIdx=getStartingProperty(pType); iIdx < lstProperties.getSize(); iIdx++) {
			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments args;
			args.add("property", Helpers::PropertyToMethod("", pProperty->getName()));
			getPatterns().ptrInterfaceType_headerGetProperty->evaluate(args, ptrFile->getStreamRef());

		}
	}

	getPatterns().ptrInterfaceType_headerPart03->evaluate(mapArgs, ptrFile->getStreamRef());

	endTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);
	getPatterns().ptrHeader_endif->evaluate(mapArgs, ptrFile->getStreamRef());

}
/*************************************************************************/
void CppCodeGeneratorInterfaceType::generate(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating DataFactorySource.");

		for(CppCodeGeneratorLogic::NamespacesMap::const_iterator it = getNSMap().begin();
		it != getNSMap().end();
		it++){

			const CppCodeGeneratorLogic::TypesList& lstTypes=it->second->lstTypes;

			for(int i=0; i<lstTypes.size(); i++){
				const Type* pType = lstTypes[i];

				generateHeader(it->second, pType);

			}/* FOR: types */


		}/* FOR: namespaces */
}
/*************************************************************************/
}
}
}
}
