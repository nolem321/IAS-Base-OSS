/*
 * File: IAS-LangLib/src/lang/export/json/SourceStore.cpp
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
#include "SourceStore.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/Model.h>

#include <lang/model/dec/QualifiedNameNode.h>
#include <lang/model/dec/DeclarationBlockFeature.h>
#include <lang/model/dec/DeclarationNode.h>
#include <lang/model/dec/ParametersNode.h>
#include <lang/model/ProgramNode.h>

#include "CallbackRegister.h"
#include "CallbackSignature.h"

#include "exception/ProcessorException.h"
#include "exception/ProcessorLinkedException.h"

#include <lang/printer/CallbackSignature.h>
#include <lang/printer/CallbackRegister.h>

namespace IAS {
namespace Lang {
namespace Export {
namespace Text {

/*************************************************************************/
SourceStore::SourceStore(const ::IAS::Lang::Model::Model* pModel,
								 const DM::DataFactory *pDataFactory)
:pModel(pModel),
 pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pModel);
}
/*************************************************************************/
SourceStore::~SourceStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String SourceStore::exportSource(const ::IAS::Lang::Model::ProgramNode* pProgramNode){
	IAS_TRACER;
	Exe::Program *pResult;

	if(hmExportSources.count(pProgramNode) == 0){
		build(pProgramNode);

    }

	return  hmExportSources[pProgramNode].strSource;
}
/*************************************************************************/
String SourceStore::exportDeclaration(const ::IAS::Lang::Model::ProgramNode* pProgramNode){
	IAS_TRACER;
	Exe::Program *pResult;

	if(hmExportSources.count(pProgramNode) == 0){
		build(pProgramNode);

    }

	return  hmExportSources[pProgramNode].strDeclaration;
}
/*************************************************************************/
String SourceStore::getExportedNamespace(const String& strNamespace)const{
  IAS_TRACER;
  String strResult(strNamespace);
  pModel->getNamespaceAlias(strNamespace, strResult);
  return strResult;
}
/*************************************************************************/
void SourceStore::build(const Model::ProgramNode* pProgramNode) {
	IAS_TRACER;

	CallbackSignature::Result aResultSource;
	CallbackSignature::Result aResultDeclaration;

	CallbackRegister::Call((pProgramNode),false, this, aResultSource);
	CallbackRegister::Call((pProgramNode),true, this, aResultDeclaration);

	hmExportSources[pProgramNode].strSource=aResultSource.ssOutput.str();
	hmExportSources[pProgramNode].strDeclaration=aResultDeclaration.ssOutput.str();
}
/*************************************************************************/
void SourceStore::buildSources(){
	IAS_TRACER;

	Model::Model::ProgramList lstPrograms;

	pModel->getAllPrograms(lstPrograms);

	for(Model::Model::ProgramList::const_iterator it=lstPrograms.begin();
		it != lstPrograms.end(); it++)
		build(*it);

}
/*************************************************************************/
const ::IAS::Lang::Model::ProgramNode*  SourceStore::findMatch(const String& strName,
				   	   	   	   	   	   	      	   	 	 	       const TypeList& lstParameters)const{
	IAS_TRACER;


	const Model::Model::ProgramList& lstProgramsForName=pModel->getPrograms(strName);

	  for(Model::Model::ProgramList::const_iterator it = lstProgramsForName.begin();
	   	it != lstProgramsForName.end();
	   	it++){

	   	const Model::ProgramNode* pProgramNode = *it;

	   	if(matchParameteres(pProgramNode, lstParameters)){
	    	return pProgramNode;
	    	}

	    }

	  IAS_THROW(ItemNotFoundException("Program not found:"+strName));
}
/*************************************************************************/
bool SourceStore::matchParameteres(const ::IAS::Lang::Model::ProgramNode* pProgramNode,
								 	   const TypeList& lstTypes)const{
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Program: "<<pProgramNode->getQualifiedNameNode()->getName());

	const Model::Dec::DeclarationBlockFeature::DeclarationNodesList& lstDeclaration(pProgramNode->getParametersNode()->getDeclarationsList());

	bool bSkipResult = pProgramNode->isReturningResult();

	if(lstDeclaration.size() - (bSkipResult ? 1 : 0) != lstTypes.size()){
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),(lstDeclaration.size()-(bSkipResult ? 1 : 0))<<"!="<<lstTypes.size());
		return false;
	}

	TypeList::const_iterator itParameters=lstTypes.begin();

	for(Model::Dec::DeclarationBlockFeature::DeclarationNodesList::const_iterator it=lstDeclaration.begin();
		it != lstDeclaration.end(); it++){

		String strType((*it)->getType());
		String strNamespace((*it)->getType());
		bool   isArray = (*it)->isArray();

		const DM::Type *pParameterType = pDataFactory->getType(strNamespace,strType);

		if((*itParameters)->isAssignableTo(pParameterType)){

			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),
					(*itParameters)->getFullName()<<"!="<<pParameterType->getFullName());

			return false;
		}

		itParameters++;
	}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Match ok!");
	return true;
}
/*************************************************************************/
}
}
}
}
