/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorLogic.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorLogic.h"
#include <commonlib/commonlib.h>
#include <stdlib.h>

#include "../../../dm/gen/Impl/CppCodeGeneratorDataFactory.h"
#include "../../../dm/gen/Impl/CppCodeGeneratorImplType.h"
#include "../../../dm/gen/Impl/CppCodeGeneratorInterfaceDataFactory.h"
#include "../../../dm/gen/Impl/CppCodeGeneratorInterfaceDeclarations.h"
#include "../../../dm/gen/Impl/CppCodeGeneratorInterfaceType.h"
#include "../../../dm/gen/Impl/Helpers.h"
#include "../../../dm/gen/Impl/Patterns.h"
#include "../../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {


/*************************************************************************/
CppCodeGeneratorLogic::CppCodeGeneratorLogic(const DM::DataFactory* pDataFactory,
										     const String& strBaseDir) {
	IAS_TRACER;

	this->pDataFactory=pDataFactory;

	this->strBaseDir=strBaseDir;
	this->strBaseDir+="/";

	strAutoGenURI = "http://www.esb.raiffeisen.pl";

	Helpers::URIToPrefix(strAutoGenURI,strAutoGenNS);

	String strTmp;

	Helpers::URIToFilePath(strAutoGenURI,strTmp);

	strAutoGenFile="";
	strAutoGenFile+=strTmp;

	mkDir(strBaseDir);
	String strImplDir=strBaseDir+"/Impl";
	mkDir(strImplDir);

	strAutoGenFile+="/MainFactory";

	strAutoGenFileHeader=strAutoGenFile;
	strAutoGenFileHeader+=".h";

	lstStandardNamespaces.push_back("IAS");
	lstStandardNamespaces.push_back("DM");
	lstStandardNamespaces.push_back("AG");
	lstStandardNamespaces.push_back("Impl");

	strUniq=TypeTools::IntToString(time(NULL));

}
/*************************************************************************/
CppCodeGeneratorLogic::~CppCodeGeneratorLogic() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGeneratorLogic::NamespaceInfo::init(){};
/*************************************************************************/
void CppCodeGeneratorLogic::setSingleDataObjectFile(bool bValue){
	IAS_TRACER;
	this->bSingleDataObjectFile=bValue;
}
/*************************************************************************/
bool CppCodeGeneratorLogic::hasPrefix(const StringList& lstNamespaces, const String strURI){
	IAS_TRACER;

	for(StringList::const_iterator it = lstNamespaces.begin(); it != lstNamespaces.end(); it++){
		if(strURI.substr(0,(*it).length()).compare(*it) == 0)
			return true;
	}

	return false;
}
/*************************************************************************/
void CppCodeGeneratorLogic::buildNamespacesMap(const StringList& lstNamespaces){
	IAS_TRACER;


	//TODO sorting types within the same namespace
	IAS_CHECK_IF_VALID(pDataFactory);

	const DM::TypeList& lstTypes = pDataFactory->getTypes();

	int iNumTypes = lstTypes.getSize();

	for(int iIdx=0; iIdx<iNumTypes; iIdx++){
		const Type* pType = lstTypes[iIdx];

		if(DataFactory::BuildInTypesNamespace.compare(pType->getURI())==0)
			continue;
		if(DataFactory::RootTypeName.compare(pType->getName())==0)
			continue;

		if(!lstNamespaces.empty() && !hasPrefix(lstNamespaces,pType->getURI())){
			IAS_LOG(true, "Skipping: "<<pType->getURI());
			continue;
		}

		if(hmNamespaces.count(pType->getURI()) == 0){

			hmNamespaces[pType->getURI()] = IAS_DFT_FACTORY<NamespaceInfo>::Create();

			Helpers::URIToList(pType->getURI(),
					           hmNamespaces[pType->getURI()]->lstNSParts);
		}

		buildForType(hmNamespaces[pType->getURI()],pType);
	}
}

/*************************************************************************/
void CppCodeGeneratorLogic::buildForType(NamespaceInfo* pInfo, const DM::Type* pType){
	IAS_TRACER;

	if(pInfo->hmTypes.count(pType) > 0)
		return;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Type:"<<pType->getName()<<":"<<pType->getURI()<<", isRoot="<<pType->isRootType());

	if( !pType->isRootType() &&
	    pType->getURI().compare(pType->getBaseType()->getURI()) == 0)
	buildForType(pInfo,pType->getBaseType());

	pInfo->lstTypes.push_back(pType);
	pInfo->hmTypes[pType]=true;

	if(pType->isDataObjectType()){
		const PropertyList& lstProperties = pType->asComplexType()->getProperties();

		for(int iPropertyIdx = 0; iPropertyIdx<lstProperties.getSize(); iPropertyIdx++){
			if(lstProperties[iPropertyIdx]->getType()->getURI().compare(DataFactory::BuildInTypesNamespace) != 0)
				pInfo->lstDependentNamespaces[lstProperties[iPropertyIdx]->getType()->getURI()]=true;
		}

	}

	if(!pType->isRootType() && pType->getBaseType()->isDataObjectType()){
		pInfo->lstDependentNamespaces[pType->getBaseType()->getURI()]=true;
	}

}
/*************************************************************************/
void CppCodeGeneratorLogic::printNamespace(std::ostream& os,
											   Template *pTemplate,
											   const StringList& lstParts,
											   bool bBackwards){
	IAS_TRACER;

	Template::Arguments argNS;

	if(!bBackwards)
		for(StringList::const_iterator it=lstParts.begin();
				it!=lstParts.end();
				it++){
			argNS.add("ns",*it);
			pTemplate->evaluate(argNS, os);
		}
	else{
		StringList::const_iterator it=lstParts.end();
		while(it!=lstParts.begin()){
				it--;
				argNS.add("ns",*it);
				pTemplate->evaluate(argNS, os);
		}
	}
}
/*************************************************************************/
void CppCodeGeneratorLogic::generate(const StringList& lstNamespaces){
	IAS_TRACER;

	buildNamespacesMap(lstNamespaces);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating Globals.");


	IAS_DFT_FACTORY<CppCodeGeneratorDataFactory>::PtrHolder ptrGeneratorDataFactory(IAS_DFT_FACTORY<CppCodeGeneratorDataFactory>::Create(this));

	ptrGeneratorDataFactory->generateDataFactoryHeader();
	ptrGeneratorDataFactory->generateDataFactorySource();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating Declarations.");

	IAS_DFT_FACTORY<CppCodeGeneratorInterfaceDeclarations>::PtrHolder ptrGeneratorInterfaceDeclarations(IAS_DFT_FACTORY<CppCodeGeneratorInterfaceDeclarations>::Create(this));
	ptrGeneratorInterfaceDeclarations->generate();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating Interface Data Factories.");

	IAS_DFT_FACTORY<CppCodeGeneratorInterfaceDataFactory>::PtrHolder ptrGeneratorInterfaceDataFactory(IAS_DFT_FACTORY<CppCodeGeneratorInterfaceDataFactory>::Create(this));
	ptrGeneratorInterfaceDataFactory->generate();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating Interface Types.");

	IAS_DFT_FACTORY<CppCodeGeneratorInterfaceType>::PtrHolder ptrGeneratorInterfaceType(IAS_DFT_FACTORY<CppCodeGeneratorInterfaceType>::Create(this));
	ptrGeneratorInterfaceType->generate();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Generating Implementation Types.");

	IAS_DFT_FACTORY<CppCodeGeneratorImplType>::PtrHolder ptrGeneratorImplType(IAS_DFT_FACTORY<CppCodeGeneratorImplType>::Create(this));


	if(bSingleDataObjectFile)
		ptrGeneratorImplType->generateWithCommonSourceFiles();
	else
		ptrGeneratorImplType->generate();


}
/*************************************************************************/
void CppCodeGeneratorLogic::mkDir(const String& strDirName){

	IAS_TRACER;
	//TODO mkdir -p
	String strMkdir = "mkdir -p ";
	strMkdir+=strBaseDir;
	strMkdir+="/";
	strMkdir+=strDirName;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"MKDIR:"<<strMkdir);

	system(strMkdir.c_str());
}
/*************************************************************************/
OutputFile* CppCodeGeneratorLogic::openFile(const String& strName){
	IAS_TRACER;

	String strFileName=strBaseDir+"/"+strName;

	IAS_DFT_FACTORY<OutputFile>::PtrHolder ptrFile(IAS_DFT_FACTORY<OutputFile>::Create(strFileName));
	ptrFile->open();

	return ptrFile.pass();
}
/*************************************************************************/
}
}
}
}
