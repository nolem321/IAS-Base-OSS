/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorDataFactory.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorDataFactory.h"
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
CppCodeGeneratorDataFactory::CppCodeGeneratorDataFactory(CppCodeGeneratorLogic* pParent):
	CppCodeGeneratorFriend(pParent){
	IAS_TRACER;
}
/*************************************************************************/
CppCodeGeneratorDataFactory::~CppCodeGeneratorDataFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGeneratorDataFactory::generateDataFactoryHeader(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating DataFactoryHeader.");


	String strFileName("Impl/");
	mkDir(strFileName);
	strFileName+="DataFactory.h";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;
	mapArgs.add("uniq",getUniq());
	mapArgs.add("file",Helpers::convertToSymbol(strFileName,'_',true));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_ifndef->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_commonlib->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_dm->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_dmgen->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrGlobals_header_incImpl->evaluate(mapArgs, ptrFile->getStreamRef());

	beginStandardNamespaces(ptrFile);

	getPatterns().ptrGlobalImplDataFactory_header->evaluate(mapArgs, ptrFile->getStreamRef());

	endStandardNamespaces(ptrFile);

	getPatterns().ptrHeader_endif->evaluate(mapArgs, ptrFile->getStreamRef());

}
/*************************************************************************/
void CppCodeGeneratorDataFactory::declareType(const DM::Type* pType){
	IAS_TRACER;

	if(hmDeclaredTypes.count(pType) > 0 || !isGeneratedType(pType))
		return;

	if(!pType->isRootType()){
		declareType(pType->getBaseType());
		defineType(pType->getBaseType());
	}

	Template::Arguments mapArgs;
	mapArgs.add("type",pType->getName());
	mapArgs.add("typens",Helpers::URIToPrefix(pType->getURI()));
	getPatterns().ptrGlobalImplDataFactory_implDeclare->evaluate(mapArgs, ptrFile->getStreamRef());

	hmDeclaredTypes[pType]=true;
}
/*************************************************************************/
void CppCodeGeneratorDataFactory::defineType(const DM::Type* pType){
	IAS_TRACER;

	if(hmDefinedTypes.count(pType) > 0 || !isGeneratedType(pType))
		return;

	if(pType->isDataObjectType()){
		const ComplexType* pComplexType = pType->asComplexType();

		const PropertyList& lstProperties = pComplexType->getProperties();
		for(int iIdx=0; iIdx < lstProperties.getSize(); iIdx++){
			const Type* pPropertyType=lstProperties[iIdx]->getType();
			declareType(pPropertyType);
		}
	}

	Template::Arguments mapArgs;
	mapArgs.add("type",pType->getName());
	mapArgs.add("typens",Helpers::URIToPrefix(pType->getURI()));
	getPatterns().ptrGlobalImplDataFactory_implDefine->evaluate(mapArgs, ptrFile->getStreamRef());

	hmDefinedTypes[pType]=true;
}
/*************************************************************************/
void CppCodeGeneratorDataFactory::generateDataFactorySource(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating DataFactorySource.");

	String strFileName("Impl/");
	strFileName+="DataFactory.cpp";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;
	mapArgs.add("uniq",getUniq());
	mapArgs.add("stdns",Helpers::URIToPrefix(getStandardNamespaces()));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());

	getPatterns().addInclude(ptrFile,"DataFactory.h");
	getPatterns().addGlobalInclude(ptrFile,"dm/gen/DataFactory.h");

	for(CppCodeGeneratorLogic::NamespacesMap::const_iterator it = getNSMap().begin();
		it != getNSMap().end();
		it++){

		const CppCodeGeneratorLogic::TypesList& lstTypes=it->second->lstTypes;

		for(int i=0; i<lstTypes.size(); i++){
			const Type* pType = lstTypes[i];

			if(isGeneratedType(pType)){
				Template::Arguments argInclude;
				argInclude.add("path",Helpers::URIToFilePath(pType->getURI()));
				argInclude.add("filebase",pType->getName());
				getPatterns().ptrHeader_include_impl->evaluate(argInclude, ptrFile->getStreamRef());
			}

			}/* FOR: types */
		}/* FOR: namespaces */


	beginStandardNamespaces(ptrFile);

	getPatterns().ptrGlobalImplDataFactory_implPart01->evaluate(mapArgs, ptrFile->getStreamRef());

	for(CppCodeGeneratorLogic::NamespacesMap::const_iterator it = getNSMap().begin();
		it != getNSMap().end();
		it++){

		const CppCodeGeneratorLogic::TypesList& lstTypes=it->second->lstTypes;

		for(int i=0; i<lstTypes.size(); i++){
			const Type* pType = lstTypes[i];

			declareType(pType);
			defineType(pType);
		}/* FOR: types */
	}/* FOR: namespaces */


	getPatterns().ptrGlobalImplDataFactory_implPart02->evaluate(mapArgs, ptrFile->getStreamRef());

	endStandardNamespaces(ptrFile);
}
/*************************************************************************/
}
}
}
}
