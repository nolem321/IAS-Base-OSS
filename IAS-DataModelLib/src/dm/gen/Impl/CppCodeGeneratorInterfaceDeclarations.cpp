/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorInterfaceDeclarations.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorInterfaceDeclarations.h"
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
CppCodeGeneratorInterfaceDeclarations::CppCodeGeneratorInterfaceDeclarations(CppCodeGeneratorLogic* pParent):
				CppCodeGeneratorFriend(pParent){
	IAS_TRACER;
}
/*************************************************************************/
CppCodeGeneratorInterfaceDeclarations::~CppCodeGeneratorInterfaceDeclarations() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGeneratorInterfaceDeclarations::declareNamespace(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo){
	IAS_TRACER;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Namespace.");

	String strFileName;
	Helpers::URIToFilePath(pNamespaceInfo->lstNSParts,strFileName);

	mkDir(strFileName);

	if(!strFileName.empty())
		strFileName+="/";

	strFileName+="Declarations.h";
	ptrFile=openFile(strFileName);

	Template::Arguments mapArgs;
	mapArgs.add("file",Helpers::convertToSymbol(strFileName,'_',true));

	getPatterns().ptrFilePreamble->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_ifndef->evaluate(mapArgs, ptrFile->getStreamRef());
	getPatterns().ptrHeader_include_commonlib->evaluate(mapArgs, ptrFile->getStreamRef());
	beginTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);

	const CppCodeGeneratorLogic::TypesList& lstTypes=pNamespaceInfo->lstTypes;

	for(int i=0; i<lstTypes.size(); i++){
		const Type* pType = lstTypes[i];


		Template::Arguments argType;
		argType.add("type",pType->getName());
		getPatterns().ptrDeclaration_typeDeclarations->evaluate(argType, ptrFile->getStreamRef());


	}/* FOR: types */

	endTypeNamespaces(ptrFile,pNamespaceInfo->lstNSParts);
	getPatterns().ptrHeader_endif->evaluate(mapArgs, ptrFile->getStreamRef());

}
/*************************************************************************/
void CppCodeGeneratorInterfaceDeclarations::generate(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating DataFactorySource.");

		for(CppCodeGeneratorLogic::NamespacesMap::const_iterator it = getNSMap().begin();
		it != getNSMap().end();
		it++){

			declareNamespace(it->second);

		}/* FOR: namespaces */
}
/*************************************************************************/
}
}
}
}
