/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorInterfaceDataFactory.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorInterfaceDataFactory.h"
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
CppCodeGeneratorInterfaceDataFactory::CppCodeGeneratorInterfaceDataFactory(CppCodeGeneratorLogic* pParent):
						CppCodeGeneratorFriend(pParent){
	IAS_TRACER;
}
/*************************************************************************/
CppCodeGeneratorInterfaceDataFactory::~CppCodeGeneratorInterfaceDataFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGeneratorInterfaceDataFactory::generateHeader(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo){
	IAS_TRACER;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Namespace.");

	String strFileName;
	Helpers::URIToFilePath(pNamespaceInfo->lstNSParts,strFileName);

	mkDir(strFileName);

	if(!strFileName.empty())
		strFileName+="/";

	strFileName+="DataFactory.h";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;
	mapArgs.add("file",Helpers::convertToSymbol(strFileName,'_',true));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_ifndef->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_commonlib->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_dm->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_dmgen->evaluate(mapArgs, ptrFile->getStreamRef());

	Template::Arguments argInc;
	argInc.add("file","Declarations.h");
	getPatterns().ptrHeader_include_local->evaluate(argInc, ptrFile->getStreamRef());



	beginTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);

	getPatterns().ptrInterfaceDataFactory_headerPart01->evaluate(mapArgs, ptrFile->getStreamRef());

	const CppCodeGeneratorLogic::TypesList& lstTypes=pNamespaceInfo->lstTypes;

	for(int i=0; i<lstTypes.size(); i++){
		const Type* pType = lstTypes[i];

			Template::Arguments argType;
			argType.add("type",pType->getName());
			argType.add("setType",computeSetterType(pType));
			getPatterns().ptrInterfaceDataFactory_headerTypeMethods->evaluate(argType, ptrFile->getStreamRef());

	}/* FOR: types */

	getPatterns().ptrInterfaceDataFactory_headerPart02->evaluate(mapArgs, ptrFile->getStreamRef());

	endTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);
	getPatterns().ptrHeader_endif->evaluate(mapArgs, ptrFile->getStreamRef());

}
/*************************************************************************/
void CppCodeGeneratorInterfaceDataFactory::generateSource(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo){
	IAS_TRACER;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Namespace.");

	String strFileName;
	Helpers::URIToFilePath(pNamespaceInfo->lstNSParts,strFileName);

	mkDir(strFileName);

	if(!strFileName.empty())
		strFileName+="/";

	strFileName+="DataFactory.cpp";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;

	mapArgs.add("stdns",Helpers::URIToPrefix(getStandardNamespaces()));
	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_commonlib->evaluate(mapArgs, ptrFile->getStreamRef());

	Template::Arguments argDataFactoryInc;
	argDataFactoryInc.add("file","DataFactory.h");
	getPatterns().ptrHeader_include_local->evaluate(argDataFactoryInc, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_globalImplDataFactory->evaluate(mapArgs, ptrFile->getStreamRef());

	const CppCodeGeneratorLogic::TypesList& lstTypes=pNamespaceInfo->lstTypes;

	for(int i=0; i<lstTypes.size(); i++){
		const Type* pType = lstTypes[i];


		Template::Arguments argInc;
		String strIncFile="Impl/";
		strIncFile+=Helpers::URIToFilePath(pNamespaceInfo->lstNSParts);
		strIncFile+="/";
		strIncFile+=pType->getName();
		strIncFile+=".h";
		argInc.add("file",strIncFile);
		getPatterns().ptrHeader_include_local->evaluate(argInc, ptrFile->getStreamRef());


	}/* FOR: types */

	getPatterns().ptrUsingNamespaceIAS->evaluate(mapArgs, ptrFile->getStreamRef());

	beginTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);

	for(int i=0; i<lstTypes.size(); i++){
		const Type* pType = lstTypes[i];


		Template::Arguments argType;
		argType.add("type",pType->getName());
		argType.add("stdns",Helpers::URIToPrefix(getStandardNamespaces()));
		argType.add("typens",Helpers::URIToPrefix(pNamespaceInfo->lstNSParts));
		argType.add("setType",computeSetterType(pType));
		getPatterns().ptrInterfaceDataFactory_sourceTypeMethods->evaluate(argType, ptrFile->getStreamRef());


	}/* FOR: types */

	mapArgs.add("uniq",getUniq());

	getPatterns().ptrInterfaceDataFactory_sourcePart01->evaluate(mapArgs, ptrFile->getStreamRef());

	endTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);


}
/*************************************************************************/
void CppCodeGeneratorInterfaceDataFactory::generate(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating DataFactorySource.");

		for(CppCodeGeneratorLogic::NamespacesMap::const_iterator it = getNSMap().begin();
		it != getNSMap().end();
		it++){

			generateHeader(it->second);
			generateSource(it->second);

		}/* FOR: namespaces */
}
/*************************************************************************/
}
}
}
}
