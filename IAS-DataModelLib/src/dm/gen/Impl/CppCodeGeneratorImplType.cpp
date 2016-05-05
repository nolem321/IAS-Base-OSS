/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorImplType.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorImplType.h"
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
CppCodeGeneratorImplType::CppCodeGeneratorImplType(CppCodeGeneratorLogic* pParent):
	CppCodeGeneratorFriend(pParent){
	IAS_TRACER;
}
/*************************************************************************/
CppCodeGeneratorImplType::~CppCodeGeneratorImplType() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGeneratorImplType::generateHeader(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
												   const Type* pType){
	IAS_TRACER;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"***Type:"<<pType->getName()<<":"<<pType->getURI());

	String strFileName;
	strFileName+="Impl/";
	strFileName+=Helpers::URIToFilePath(pNamespaceInfo->lstNSParts);

	std::map<String,bool> hmIncludedNS;

	mkDir(strFileName);
	strFileName+="/";
	strFileName+=pType->getName();
	strFileName+=".h";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;
	mapArgs.add("stdns",Helpers::URIToPrefix(getStandardNamespaces()));

	mapArgs.add("file",Helpers::convertToSymbol(strFileName,'_',true));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_ifndef->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_commonlib->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_dmgen->evaluate(mapArgs, ptrFile->getStreamRef());

	{
		Template::Arguments argInclude;
		String strFileName = Helpers::URIToFilePath(pNamespaceInfo->lstNSParts);
		strFileName+="/";
		strFileName+=pType->getName();
		strFileName+=".h";
		argInclude.add("file",strFileName);
		getPatterns().ptrHeader_include_global->evaluate(argInclude, ptrFile->getStreamRef());
	}

	if(!pType->isRootType()){
		Template::Arguments argInclude;
		const Type* pBaseType = pType->getBaseType();

		argInclude.add("filebase",pBaseType->getName());

		if(pBaseType->getURI().compare(DataFactory::BuildInTypesNamespace)){
			argInclude.add("path",Helpers::URIToFilePath(pBaseType->getURI()));
			getPatterns().ptrHeader_include_impl->evaluate(argInclude, ptrFile->getStreamRef());
		}else{
			getPatterns().ptrHeader_include_implBulitIn->evaluate(argInclude, ptrFile->getStreamRef());
		}

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

	mapArgs.add("class",computeImplClass(pType));
	getPatterns().ptrImplType_includeSuperclasses->evaluate(mapArgs, ptrFile->getStreamRef());

	beginStandardNamespaces(ptrFile);
	beginTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);

	mapArgs.add("type",pType->getName());
	mapArgs.add("typens",Helpers::URIToPrefix(pType->getURI()));

	getPatterns().ptrImplType_headerPart01->evaluate(mapArgs, ptrFile->getStreamRef());

	if(pType->isRootType()){
		getPatterns().ptrImplType_headerPart02->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		mapArgs.add("base",pType->getBaseType()->getName());
		if(pType->getBaseType()->getURI().compare(DataFactory::BuildInTypesNamespace)){
			mapArgs.add("basens",Helpers::URIToPrefix(pType->getBaseType()->getURI()));
			getPatterns().ptrImplType_headerPart02withBase->evaluate(mapArgs, ptrFile->getStreamRef());
		}else{
			getPatterns().ptrImplType_headerPart02withBaseBuiltIn->evaluate(mapArgs, ptrFile->getStreamRef());
		}
	}

	getPatterns().ptrImplType_headerPart03->evaluate(mapArgs, ptrFile->getStreamRef());

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
				getPatterns().ptrImplType_headerGetterMany->evaluate(argGetterSetter, ptrFile->getStreamRef());
			}else{
				getPatterns().ptrImplType_headerGetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
				if(hasDataObjectMethods(pProperty->getType())){
					argGetterSetter.add("retType",computeDataObjectType(pProperty->getType(),true));
					argGetterSetter.add("getter",Helpers::PropertyToMethod("get",pProperty->getName())+="DataObject");
					getPatterns().ptrImplType_headerGetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
				}

			}
			getPatterns().ptrImplType_headerChecker->evaluate(argGetterSetter, ptrFile->getStreamRef());
			getPatterns().ptrImplType_headerSetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
			getPatterns().ptrImplType_headerUnsetter->evaluate(argGetterSetter, ptrFile->getStreamRef());

			if(hasDataObjectMethods(pProperty->getType())){
				argGetterSetter.add("setType",computeDataObjectType(pProperty->getType(),true));
				argGetterSetter.add("setter",Helpers::PropertyToMethod("set",pProperty->getName())+="DataObject");
				getPatterns().ptrImplType_headerSetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
			}else{
				if(pProperty->getType()->getTypeEnum() != Type::AnyType){
					argGetterSetter.add("retType",computeReturnType(pProperty->getType()));
					getPatterns().ptrImplType_headerCreator->evaluate(argGetterSetter, ptrFile->getStreamRef());
				}
			}
		}

	}

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();
		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=getStartingProperty(pType); iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);
				Template::Arguments argListPtr;
				if(pProperty->isMulti()){
					argListPtr.add("propertyNS",Helpers::URIToPrefix(pProperty->getType()->getURI()));
					argListPtr.add("property",Helpers::PropertyToMethod("",pProperty->getName()));
					argListPtr.add("retList",computeReturnListType(pProperty->getType()));
					getPatterns().ptrImplType_headerPtrList->evaluate(argListPtr, ptrFile->getStreamRef());
				}
			}

		}


	mapArgs.add("setType",computeSetterType(pType));
	mapArgs.add("typeclass",computeImplClass(pType));


	getPatterns().ptrImplType_headerPart04a->evaluate(mapArgs, ptrFile->getStreamRef());
	if(pType->isDataObjectType()){
		getPatterns().ptrImplType_headerPart04DataObject->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		Template::Arguments argList(mapArgs);
		argList.add("setType",computeSetterType(pType));
		argList.add("retType",computeReturnType(pType));
		getPatterns().ptrImplType_headerPart04SimpleType->evaluate(argList, ptrFile->getStreamRef());
	}


	if(pType->isRootType()){
		getPatterns().ptrImplType_headerPart04Type->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		if(pType->getBaseType()->getURI().compare(DataFactory::BuildInTypesNamespace))
			getPatterns().ptrImplType_headerPart04TypeWithBase->evaluate(mapArgs, ptrFile->getStreamRef());
		else
			getPatterns().ptrImplType_headerPart04TypeWithBaseBuildIn->evaluate(mapArgs, ptrFile->getStreamRef());
	}

	getPatterns().ptrImplType_headerPart04TypeBody->evaluate(mapArgs, ptrFile->getStreamRef());

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=getStartingProperty(pType); iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments args;
			args.add("property",Helpers::PropertyToMethod("",pProperty->getName()));
			getPatterns().ptrImplType_headerGetProperty->evaluate(args, ptrFile->getStreamRef());

		}
	}

	mapArgs.add("setType",computeSetterType(pType));

	getPatterns().ptrImplType_headerPart05->evaluate(mapArgs, ptrFile->getStreamRef());

	if (pType->isDataObjectType()) {
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for (int iIdx=getStartingProperty(pType); iIdx < lstProperties.getSize(); iIdx++) {

			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments args;
			args.add("property", Helpers::PropertyToMethod("", pProperty->getName()));
			getPatterns().ptrImplType_headerPropertyMember->evaluate(args, ptrFile->getStreamRef());

		}
	}

	getPatterns().ptrImplType_headerPart06->evaluate(mapArgs, ptrFile->getStreamRef());

	endTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);
	endStandardNamespaces(ptrFile);
	getPatterns().ptrHeader_endif->evaluate(mapArgs, ptrFile->getStreamRef());

}

/*************************************************************************/
void CppCodeGeneratorImplType::generateSource(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
												  const Type* pType){

	IAS_TRACER;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;

	String strFileName;
	strFileName+="Impl/";
	strFileName+=Helpers::URIToFilePath(pNamespaceInfo->lstNSParts);

	mkDir(strFileName);
	strFileName+="/";
	strFileName+=pType->getName();
	strFileName+=".cpp";
	ptrFile=openFile(strFileName);

	Template::Arguments argInclude;
	getPatterns().ptrHeader_include_defaultTypesImpl->evaluate(argInclude, ptrFile->getStreamRef());

	std::map<const Type*, bool> hmIncludedTypes;

	generateSourceImpl(pNamespaceInfo, pType, ptrFile, hmIncludedTypes);
}

/*************************************************************************/
void CppCodeGeneratorImplType::generateSourceImpl(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
													   const Type* pType,
													   IAS_DFT_FACTORY<OutputFile>::PtrHolder& ptrFile,
													   std::map<const Type*, bool>& hmIncludedTypes){

	IAS_TRACER;

	Template::Arguments mapArgs;
	mapArgs.add("class",computeImplClass(pType));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());

	Template::Arguments argInclude;
	argInclude.add("file",pType->getName());

	mapArgs.add("stdns",Helpers::URIToPrefix(getStandardNamespaces()));

	getPatterns().ptrHeader_include_local_h->evaluate(argInclude, ptrFile->getStreamRef());

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);
			const Type*     pPropertyType = pProperty->getType();

			if(isGeneratedType(pPropertyType) && hmIncludedTypes.count(pPropertyType) == 0){
				Template::Arguments argInclude;

				argInclude.add("path",Helpers::URIToFilePath(pPropertyType->getURI()));
				argInclude.add("filebase",pPropertyType->getName());
				getPatterns().ptrHeader_include_impl->evaluate(argInclude, ptrFile->getStreamRef());
				hmIncludedTypes[pPropertyType] = true;
			}

		} /* FOR: properties */
	} /* IF: complex */


	beginStandardNamespaces(ptrFile);
	beginTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);

	mapArgs.add("type",pType->getName());
	mapArgs.add("typens",Helpers::URIToPrefix(pType->getURI()));


	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=getStartingProperty(pType); iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments argGetterSetter(mapArgs);

			argGetterSetter.add("checker",Helpers::PropertyToMethod("isSet",pProperty->getName()));
			argGetterSetter.add("getter",Helpers::PropertyToMethod("get",pProperty->getName()));
			argGetterSetter.add("setter",Helpers::PropertyToMethod("set",pProperty->getName()));
			argGetterSetter.add("creator",Helpers::PropertyToMethod("create",pProperty->getName()));

			argGetterSetter.add("property",Helpers::PropertyToMethod("",pProperty->getName()));
			argGetterSetter.add("dmMethod",computeDMSetterMethod(pProperty->getType()));
			argGetterSetter.add("retType",computeReturnType(pProperty->getType()));
			argGetterSetter.add("setType",computeSetterType(pProperty->getType()));
			argGetterSetter.add("propertyNS",Helpers::URIToPrefix(pProperty->getType()->getURI()));
			argGetterSetter.add("propertyType",pProperty->getType()->getName());
			argGetterSetter.add("cast","");

			getPatterns().ptrImplType_sourceChecker->evaluate(argGetterSetter, ptrFile->getStreamRef());
			getPatterns().ptrImplType_sourceSetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
			getPatterns().ptrImplType_sourceUnsetter->evaluate(argGetterSetter, ptrFile->getStreamRef());

			if(pProperty->isMulti()){
					argGetterSetter.add("retType",computeReturnListType(pProperty->getType()));
					if(pProperty->getType()->getURI().compare(DataFactory::BuildInTypesNamespace)){
						getPatterns().ptrImplType_sourceGetterMany->evaluate(argGetterSetter, ptrFile->getStreamRef());
					}else{
						//TODO remove the hack for propretyNS!!
						argGetterSetter.add("propertyNS","::IAS::DM::Impl::Default");
						getPatterns().ptrImplType_sourceGetterMany->evaluate(argGetterSetter, ptrFile->getStreamRef());
					}

				}else{



					if(hasDataObjectMethods(pProperty->getType())){
						getPatterns().ptrImplType_sourceGetter->evaluate(argGetterSetter, ptrFile->getStreamRef());

						argGetterSetter.add("retType",computeDataObjectType(pProperty->getType(),true));
						argGetterSetter.add("dmMethod","DataObject");
						//TODO remove the hack for propretyNS!!
						if(pProperty->getType()->getURI().compare(DataFactory::BuildInTypesNamespace)==0)
							argGetterSetter.add("propertyNS","::IAS::DM::Impl::Default");

						argGetterSetter.add("getter",Helpers::PropertyToMethod("get",pProperty->getName())+="DataObject");
					}

					if(pProperty->getType()->getTypeEnum() != Type::AnyType){
						getPatterns().ptrImplType_sourceGetterDM->evaluate(argGetterSetter, ptrFile->getStreamRef());
					}else{
						argGetterSetter.add("cast","(DM::DataObject*)");
						getPatterns().ptrImplType_sourceGetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
						}
					}

			if(hasDataObjectMethods(pProperty->getType())){
				argGetterSetter.add("dmMethod","DataObject");
				argGetterSetter.add("setType",computeDataObjectType(pProperty->getType(),true));
				argGetterSetter.add("setter",Helpers::PropertyToMethod("set",pProperty->getName())+="DataObject");
				getPatterns().ptrImplType_sourceSetter->evaluate(argGetterSetter, ptrFile->getStreamRef());
			}else{
				if(pProperty->getType()->getTypeEnum() != Type::AnyType){
					argGetterSetter.add("retType",computeReturnType(pProperty->getType()));
					getPatterns().ptrImplType_sourceCreator->evaluate(argGetterSetter, ptrFile->getStreamRef());
				}
			}
		}

	}

	getPatterns().ptrImplType_sourcePart01->evaluate(mapArgs, ptrFile->getStreamRef());

	if(pType->isRootType()){
		getPatterns().ptrImplType_sourcePart02->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		mapArgs.add("base",pType->getBaseType()->getName());

		if(pType->getBaseType()->getURI().compare(DataFactory::BuildInTypesNamespace)){
			mapArgs.add("basens",Helpers::URIToPrefix(pType->getBaseType()->getURI()));
			getPatterns().ptrImplType_sourcePart02withBase->evaluate(mapArgs, ptrFile->getStreamRef());
		}else{
			getPatterns().ptrImplType_sourcePart02withBaseBulitIn->evaluate(mapArgs, ptrFile->getStreamRef());
		}
	}

	if(pType->isDataObjectType()){

		const ComplexType *pComplexType = pType->asComplexType();
		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=getStartingProperty(pType); iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);
			Template::Arguments argGetterSetter(mapArgs);
			argGetterSetter.add("property",Helpers::PropertyToMethod("",pProperty->getName()));
			argGetterSetter.add("propertyType",pProperty->getType()->getName());
			argGetterSetter.add("propertyNS",Helpers::URIToPrefix(pProperty->getType()->getURI()));
			if(pProperty->isMulti()){

				//TODO see todo above about hacking propertyNS.
				if(!pProperty->getType()->getURI().compare(DataFactory::BuildInTypesNamespace))
					argGetterSetter.add("propertyNS","::IAS::DM::Impl::Default");

				getPatterns().ptrImplType_sourceConstructorManyInit->evaluate(argGetterSetter, ptrFile->getStreamRef());

			}/* IF: multi */
		}/* FOR: properties */

	}/*IF: dataobject */


	getPatterns().ptrImplType_sourcePart03a->evaluate(mapArgs, ptrFile->getStreamRef());
	if(pType->isDataObjectType()){
		getPatterns().ptrImplType_sourcePart03DataObject->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		Template::Arguments argList(mapArgs);
		argList.add("setType",computeSetterType(pType));
		argList.add("retType",computeReturnType(pType));
		getPatterns().ptrImplType_sourcePart03SimpleType->evaluate(argList, ptrFile->getStreamRef());
	}
	getPatterns().ptrImplType_sourcePart03b->evaluate(mapArgs, ptrFile->getStreamRef());


	mapArgs.add("typeclass",computeImplClass(pType));
	mapArgs.add("uri",pType->getURI());
	if(pType->isRootType()){
		getPatterns().ptrImplType_sourceDefineType->evaluate(mapArgs, ptrFile->getStreamRef());
	}else{
		if(pType->getBaseType()->getURI().compare(DataFactory::BuildInTypesNamespace)){
			mapArgs.add("basens",Helpers::URIToPrefix(pType->getBaseType()->getURI()));
			getPatterns().ptrImplType_sourceDefineTypeWithBase->evaluate(mapArgs, ptrFile->getStreamRef());
		}else{
			getPatterns().ptrImplType_sourceDefineTypeWithBuildIn->evaluate(mapArgs, ptrFile->getStreamRef());
		}

	}


	getPatterns().ptrImplType_sourcePart04->evaluate(mapArgs, ptrFile->getStreamRef());

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		int iIdxStartingProperty=getStartingProperty(pType);

		for(int iIdx=0;iIdx < iIdxStartingProperty;iIdx++){
				const Property* pProperty = lstProperties.getProperty(iIdx);
				Template::Arguments args;
				args.add("property",pProperty->getName());
				args.add("propertySymbol",Helpers::PropertyToMethod("",pProperty->getName()));
				getPatterns().ptrImplType_sourceInheritProperty->evaluate(args, ptrFile->getStreamRef());
			}

		for(int iIdx=iIdxStartingProperty; iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments args;
			args.add("property",pProperty->getName());
			args.add("propertySymbol",Helpers::PropertyToMethod("",pProperty->getName()));
			args.add("propertytype",pProperty->getType()->getName());
			args.add("propertyuri",pProperty->getType()->getURI());
			args.add("multi", pProperty->isMulti() ? "true" : "false");
			args.add("xmlattr", pProperty->isXMLAttribute() ? "true" : "false");
			getPatterns().ptrImplType_sourceDefineProperty->evaluate(args, ptrFile->getStreamRef());

		}
	}

	mapArgs.add("setType",computeSetterType(pType));
	mapArgs.add("setter",computeDMSetterMethod(pType));

	getPatterns().ptrImplType_sourcePart05->evaluate(mapArgs, ptrFile->getStreamRef());

	if(pType->isDataObjectType()){
		const ComplexType *pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();

		for(int iIdx=getStartingProperty(pType); iIdx<lstProperties.getSize(); iIdx++){
			const Property* pProperty = lstProperties.getProperty(iIdx);

			Template::Arguments args(mapArgs);
			args.add("property",Helpers::PropertyToMethod("",pProperty->getName()));
			getPatterns().ptrImplType_sourceGetProperty->evaluate(args, ptrFile->getStreamRef());

		}
	}

	getPatterns().ptrImplType_sourcePart06->evaluate(mapArgs, ptrFile->getStreamRef());

	endTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);
	endStandardNamespaces(ptrFile);

}
/*************************************************************************/
void CppCodeGeneratorImplType::generate(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating DataFactorySource.");

		for(CppCodeGeneratorLogic::NamespacesMap::const_iterator it = getNSMap().begin();
		it != getNSMap().end();
		it++){

			const CppCodeGeneratorLogic::TypesList& lstTypes=it->second->lstTypes;

			for(int i=0; i<lstTypes.size(); i++){
				const Type* pType = lstTypes[i];

				generateHeader(it->second, pType);
				generateSource(it->second, pType);

			}/* FOR: types */


		}/* FOR: namespaces */
}
/*************************************************************************/
void CppCodeGeneratorImplType::generateWithCommonSourceFiles(){

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

			IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;
			String strFileName;
			strFileName+="Impl/";
			strFileName+=Helpers::URIToFilePath(it->second->lstNSParts);
			strFileName+="/DataObjects.cpp";
			ptrFile=openFile(strFileName);
			Template::Arguments argInclude;
			getPatterns().ptrHeader_include_defaultTypesImpl->evaluate(argInclude, ptrFile->getStreamRef());
			std::map<const Type*, bool> hmIncludedTypes;

			for(int i=0; i<lstTypes.size(); i++){
				const Type* pType = lstTypes[i];

				generateSourceImpl(it->second, pType, ptrFile, hmIncludedTypes);

			}/* FOR: types */


		}/* FOR: namespaces */
}
/*************************************************************************/
}
}
}
}
