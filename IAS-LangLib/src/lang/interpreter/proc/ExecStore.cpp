/*
 * File: IAS-LangLib/src/lang/interpreter/proc/ExecStore.cpp
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
#include "ExecStore.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/Model.h>
#include <lang/model/ProgramNode.h>
#include <lang/model/dec/QualifiedNameNode.h>

#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/ExprList.h>

#include <lang/interpreter/extern/ModuleStore.h>

#include "CallbackRegister.h"
#include "CallbackSignature.h"

#include "exception/ProcessorException.h"
#include "exception/ProcessorLinkedException.h"

#include <lang/printer/CallbackSignature.h>
#include <lang/printer/CallbackRegister.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {

/*************************************************************************/
ExecStore::ExecStore(const ::IAS::Lang::Model::Model* pModel, ::IAS::DM::DataFactory  *pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pModel);
	IAS_CHECK_IF_VALID(pDataFactory);

	this->pModel=pModel;
	this->pDataFactory=pDataFactory;

	ptrModuleStore=IAS_DFT_FACTORY<Extern::ModuleStore>::Create(pDataFactory);


}
/*************************************************************************/
ExecStore::~ExecStore() throw(){
	IAS_TRACER;
	//TODO why AIX/xlc needs this?
	hmExecutables.clear();
}
/*************************************************************************/
Exe::Program *ExecStore::createOrGetExecutable(const String& strName,
									           const TypeList& lstTypes){
	IAS_TRACER;
	Exe::Program *pResult;

	if(!getExecutableImpl(strName, lstTypes, pResult))
		IAS_THROW(ItemNotFoundException(String(strName)+createPrintableSignature(lstTypes)));

	return pResult;
}
/*************************************************************************/
//Exe::Program *ExecStore::getExecutable(const String& strName,
//									   const TypeList& lstTypes,
//									   const StringList& lstSearchPath){
//	IAS_TRACER;
//
//	Exe::Program *pResult;
//
//	if(getExecutableImpl(strName, lstTypes, pResult))
//		return pResult;
//
//	for(StringList::const_iterator it = lstSearchPath.begin();
//		it != lstSearchPath.end();
//		it++){
//		//TODO (M) delimiter
//		if(getExecutableImpl((*it)+'.'+strName, lstTypes, pResult))
//			return pResult;
//
//	}
//
//	IAS_THROW(ItemNotFoundException(String(strName)+createPrintableSignature(lstTypes)));
//}
/*************************************************************************/
::IAS::Lang::Interpreter::Exe::Program *ExecStore::createOrGetExecutable(const Model::ProgramNode* pProgramNode){

	IAS_TRACER;

	if(hmExecutables.count(pProgramNode) == 0){
    	buildExecutable(pProgramNode);
    }

	return hmExecutables[pProgramNode];
}
/*************************************************************************/
const ::IAS::Lang::Interpreter::Exe::Program *ExecStore::getExecutable(const Model::ProgramNode* pProgramNode)const{

	IAS_TRACER;

	if(hmExecutables.count(pProgramNode) == 0)
		IAS_THROW(ItemNotFoundException(pProgramNode->getQualifiedNameNode()->getQualifiedName()));

	return hmExecutables.at(pProgramNode);
}
/*************************************************************************/
bool ExecStore::getExecutableImpl(const String& strName,
								  const TypeList& lstTypes,
								  Exe::Program* &refOutput){
	IAS_TRACER;

    const Model::Model::ProgramList& lstProgramsForName=pModel->getPrograms(strName);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Program: "<<strName<<", count: "<<lstProgramsForName.size());

    for(Model::Model::ProgramList::const_iterator it = lstProgramsForName.begin();
    	it != lstProgramsForName.end();
    	it++){

    	const Model::ProgramNode* pProgramNode = *it;

    	if(hmExecutables.count(pProgramNode) == 0){
        	buildExecutable(pProgramNode);
        }

    	if(lstTypes.isAnyThing() || matchParameteres(pProgramNode,lstTypes)){
    		refOutput=hmExecutables[pProgramNode];
    		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Result: "<<(void*)refOutput<<", "
    				<<pModel->resolve(pProgramNode->getSourceLocation().getSourceID())<<":"
					<<pProgramNode->getSourceLocation().getLineNumber());
    		return true;
    	}

    }

    return false;
}
/*************************************************************************/
bool ExecStore::matchParameteres(const ::IAS::Lang::Model::ProgramNode* pProgramNode,
								 const TypeList& lstTypes)const{
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Program: "<<pProgramNode->getQualifiedNameNode()->getName()<<
			createPrintableSignature(lstTypes));

	const Exe::Program* pProgram = hmExecutables.at(pProgramNode);
	bool bSkipResult = pProgramNode->isReturningResult();

	const Exe::Dec::Parameters *pParameters = pProgram->getParameters();
	const DM::PropertyList& lstProperties = pParameters->getType()->asComplexType()->getProperties();

	if(lstTypes.size() != lstProperties.getSize() - (bSkipResult ? 1 : 0)){
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),lstTypes.size()<<"!="<<lstProperties.getSize());
		return false;
	}

	for(int iIdx = 0; iIdx<lstTypes.size(); iIdx++){

		if(! (lstTypes[iIdx]->isAssignableTo(lstProperties.getProperty(iIdx)->getType())) ){
			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),
					lstTypes[iIdx]->getName()<<""<<lstTypes[iIdx]->getFullName()
					<<"!="<<lstProperties.getProperty(iIdx)->getType()->getFullName());

			return false;
		}
	}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Match ok!");
	return true;
}
/*************************************************************************/
String ExecStore::createPrintableSignature(const TypeList& lstTypes)const{
	IAS_TRACER;

	StringStream ssResult;

	ssResult<<"(";

	for(TypeList::const_iterator it=lstTypes.begin(); it != lstTypes.end(); it++){

		if(it !=lstTypes.begin())
			ssResult<<", ";

		ssResult<<(*it)->getFullName();
	}

	ssResult<<")";

	return ssResult.str();
}
/*************************************************************************/
void ExecStore::findAllMatches(const TypeList& lstTypes, ProgramList& lstOutput){
	IAS_TRACER;

	//TODO (HM) better than linear search !!!
	//Cache ?

	for(ExecutablesMap::const_iterator it=hmExecutables.begin();
		it!=hmExecutables.end(); it++){

		const Model::ProgramNode* pProgramNode = it->first;

		if(matchParameteres(pProgramNode,lstTypes))
			lstOutput.push_back(it->second);
	}
}
/*************************************************************************/
void ExecStore::buildExecutable(const Model::ProgramNode* pProgramNode){
	IAS_TRACER;

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Building: "<<(pProgramNode->getQualifiedNameNode()->getQualifiedName()));

	try{

		Interpreter::Proc::CallbackSignature::Result aResult;
		Interpreter::Proc::CallbackRegister::Call(pProgramNode, this, pDataFactory, aResult);

	}catch(ProcessorLinkedException& e){
		//TODO (M) messaging here ?
		StringStream ssInfo;
		ssInfo<<"Executable build failed: \n"<<pModel->resolve(e.getSourceLocation().getSourceID())
				<<":"<<e.getSourceLocation().getLineNumber()<<"\t";
		try{
			Printer::CallbackRegister::Call(e.getNode(),ssInfo);
		}catch(Exception& e){
			std::cerr<<"Printer is not up to date !!!";
			e.printToStream(std::cerr);
		}
		ssInfo<<"\n";
		e.printToStream(ssInfo);
		IAS_THROW(ProcessorException(ssInfo.str()));

	}
}
/*************************************************************************/
void ExecStore::registerExecutable(const Model::ProgramNode* pProgramNode,
									::IAS::Lang::Interpreter::Exe::Program *pProgram){
	IAS_TRACER;
	hmExecutables[pProgramNode]=pProgram;
}
/*************************************************************************/
const DM::Type* ExecStore::resolveType(const String& strType, const String& strNamespace){
	IAS_TRACER;

	String strResolvedNamespace;

	if(!pModel->getNamespaceAliasDefinition(strNamespace,strResolvedNamespace))
		strResolvedNamespace = strNamespace;

	try{
		return pDataFactory->getType(strResolvedNamespace,strType);

	}catch(ItemNotFoundException& e){

		defineType(pModel->getTypeDefinitionNode(strType,strResolvedNamespace));

		return pDataFactory->getType(strResolvedNamespace,strType);
	}
}
/*************************************************************************/
void ExecStore::defineType(const Model::Dec::TypeDefinitionNode* pTypeDefinitionNode){
	IAS_TRACER;

	Interpreter::Proc::CallbackSignature::Result aResult;
	Interpreter::Proc::CallbackRegister::Call(pTypeDefinitionNode, this, pDataFactory, aResult);
}
/*************************************************************************/
Extern::ModuleStore* ExecStore::getExternalModules()const{
	IAS_TRACER;
	return ptrModuleStore;
}
/*************************************************************************/
void ExecStore::compileAll(){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"\n\n BUIDING \n");

	 Model::Model::ProgramList lstPrograms;
	 pModel->getAllPrograms(lstPrograms);

    for(Model::Model::ProgramList::const_iterator it = lstPrograms.begin();
   	it != lstPrograms.end(); it++){

    	if(hmExecutables.count(*it) == 0)
    		buildExecutable(*it);
    }


}
/*************************************************************************/
}
}
}
}
