/*
 * File: IAS-LangLib/src/lang/model/Model.cpp
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
#include "Model.h"
#include<lang/log/LogLevel.h>
#include "ProgramNode.h"
#include "dec/QualifiedNameNode.h"

#include <org/invenireaude/lang/builtin/DataFactory.h>

using namespace org::invenireaude::lang;

namespace IAS {
namespace Lang {
namespace Model {

/*************************************************************************/
void Model::RegisterBuildInTypes() {
	IAS_TRACER;
	builtin::DataFactory::GetInstance()->getContaingDataFactory();
}
/*************************************************************************/
Model::Model() {
	IAS_TRACER;
}
/*************************************************************************/
Model::~Model() throw () {
	IAS_TRACER;

	for(SourcesMap::const_iterator it=hmSources.begin(); it!=hmSources.end();it++)
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),it->first<<"="<<it->second);

	for(SourcesByIDMap::const_iterator it=hmSourcesByID.begin(); it!=hmSourcesByID.end();it++)
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),it->first<<"="<<it->second);

}
/*************************************************************************/
void Model::addTypeDefinition(Dec::TypeDefinitionNode* pTypeDefinitionNode){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pTypeDefinitionNode);

	const String& strName=pTypeDefinitionNode->getName();
	const String& strNamespace=pTypeDefinitionNode->getNamespace();

	//TODO (MH) add count(key) method.
	if(hmTypes.count(strName,strNamespace))
		IAS_THROW(BadUsageException(strNamespace+"#"+strName+" already defined in model."));

	TypeDefinitionListsMap::Key key(strName,strNamespace);
	hmTypes[key]=pTypeDefinitionNode;
}
/*************************************************************************/
void Model::addNamespaceAliasDefinition(Dec::NamespaceDeclarationNode* pNamespaceDeclarationNode){
	IAS_TRACER;

	const String& strAlias(pNamespaceDeclarationNode->getAlias());
	const String& strNamespace(pNamespaceDeclarationNode->getNamespace());

	if(strAlias.empty() || strNamespace.empty())
		IAS_THROW(BadUsageException("Namespace nor alias cannot be empty !"));

	if(hmNamespaceDeclarations.count(strAlias) > 0 &&
		strNamespace.compare(hmNamespaceDeclarations[strAlias]->getNamespace()) != 0)
			IAS_THROW(BadUsageException("Alias [" + strAlias + "] already defined."));

	hmNamespaceDeclarations[strAlias] = pNamespaceDeclarationNode;
}
/*************************************************************************/
bool Model::getNamespaceAliasDefinition(const String& strAlias,
									        String& strNamespace)const{
	IAS_TRACER;

	if(hmNamespaceDeclarations.count(strAlias) == 0)
		return false;

	strNamespace = hmNamespaceDeclarations.at(strAlias)->getNamespace();

	return true;
}
/*************************************************************************/
const Dec::TypeDefinitionNode* Model::getTypeDefinitionNode(const String& strName,
														       const String& strNamespace)const{
	IAS_TRACER;

		TypeDefinitionListsMap::Key key(strName,strNamespace);

		if(hmTypes.count(strName,strNamespace) > 0)
			return hmTypes.at(key);

	IAS_THROW(BadUsageException(strNamespace+"#"+strName+" was not found."));
}
/*************************************************************************/
void Model::addProgram(ProgramNode* pProgramNode) {
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pProgramNode);

	phcProgramNodes.addPointer(pProgramNode);

	const String& strName = pProgramNode->getQualifiedNameNode()->getQualifiedName();

	hmProgramLists[strName].push_back(pProgramNode);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Add program["<<phcProgramNodes.size()<<"]: "<<strName);

}
/*************************************************************************/
const Model::ProgramList& Model::getPrograms(const String& strName) const {
	IAS_TRACER;

	ProgramListsMap::const_iterator it=hmProgramLists.find(strName);

	if(it == hmProgramLists.end()) {
		IAS_THROW(ItemNotFoundException("Program: \""+strName+"\""));
	}

	return it->second;

}
/*************************************************************************/
void Model::getAllPrograms(Model::ProgramList& refOutput) const {
	IAS_TRACER;
	refOutput.clear();

	for(ProgramNodesCollection::const_iterator it = phcProgramNodes.begin();
			it != phcProgramNodes.end(); it++) {

		const ProgramNode* pProgramNode = *it;
		refOutput.push_back(pProgramNode);
	}


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"getAllPrograms "<<phcProgramNodes.size()<<" ? "<<refOutput.size());
}
/*************************************************************************/
Tools::Parser::SourceLocation::SourceID Model::registerSource(const String& strName){

	IAS_TRACER;

	SourcesMap::const_iterator it=hmSources.find(strName);

	if(it == hmSources.end()){
		int iID=hmSources.size();
		hmSources[strName]=iID;
		hmSourcesByID[iID]=strName;

		return iID;
	}

	return it->second;
}
/*************************************************************************/
const String& Model::resolve(Tools::Parser::SourceLocation::SourceID iID)const{
	IAS_TRACER;

	SourcesByIDMap::const_iterator it=hmSourcesByID.find(iID);

	if(it == hmSourcesByID.end()) {
		IAS_THROW(ItemNotFoundException(TypeTools::IntToString(iID) +
						" <= source file for this id was not found."));
	}

	return it->second;


}
/*************************************************************************/
}
}
}
