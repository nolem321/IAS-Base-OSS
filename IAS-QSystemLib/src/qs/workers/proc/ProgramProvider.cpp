/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ProgramProvider.cpp
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
#include "ProgramProvider.h"
#include<qs/log/LogLevel.h>

#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>

#include "io/Input.h"
#include "io/Output.h"

#include "prog/ProgramSet.h"

#include <org/invenireaude/qsystem/typeinfo/Program.h>
#include <org/invenireaude/qsystem/typeinfo/SourceLocation.h>
#include <org/invenireaude/qsystem/typeinfo/Variable.h>
#include <org/invenireaude/qsystem/typeinfo/DataFactory.h>
#include <lang/model/allmodel.h>

using namespace org::invenireaude::qsystem;


namespace IAS{
using namespace Lang;

namespace QS {
namespace Workers {
namespace Proc {

//TODO (M) standarize !!!
const String CEnv_LANG_XSD="IAS_LANG_XSD";
const String CEnv_SRC_DIRS="IAS_LANG_SRC_DIRS";

/*************************************************************************/
ProgramProvider::ProgramProvider(::IAS::DM::DataFactory *pDataFactory):
		pDataFactory(pDataFactory){
	IAS_TRACER;

	StringList lstSrcPath;
	IAS::EnvTools::GetEnvTokenized(CEnv_SRC_DIRS, lstSrcPath);

	IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::PtrHolder ptrLexerIStreamFactory;
	ptrLexerIStreamFactory = IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::Create();
	ptrLexerIStreamFactory->setSearchPath(lstSrcPath);

	ptrLoader = IAS_DFT_FACTORY<Interpreter::ProgramLoader>::Create(pDataFactory,ptrLexerIStreamFactory.pass());


}
/*************************************************************************/
ProgramProvider::~ProgramProvider() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IAS::Lang::Interpreter::Exe::Program* ProgramProvider::loadProgram(const String& strProgramName){
	IAS_TRACER;

	//TODO Repeated loads ?
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Load:"<<strProgramName);

	Mutex::Locker locker(mutex);

	ptrLoader->loadModel(strProgramName);

	return ptrLoader->getExecutable(strProgramName);
}
/*************************************************************************/
void ProgramProvider::load(const String& strProgramName, Prog::ProgramSet *pProgramSet){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pProgramSet);

	pProgramSet->addProgram(loadProgram(strProgramName),strProgramName);
}
/*************************************************************************/
void ProgramProvider::getSources(const String& strProgramName,
								 DM::DataObjectList& lstPrograms){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	try{
		ptrLoader->loadModel(strProgramName);
	}catch(...){};

	Lang::Model::Model::ProgramList lstProgramNodes(ptrLoader->getModel()->getPrograms(strProgramName));

	for(Lang::Model::Model::ProgramList::const_iterator it = lstProgramNodes.begin();
		it != lstProgramNodes.end(); it++){

		typeinfo::Ext::ProgramPtr dmProgram(typeinfo::DataFactory::GetInstance()->createProgram());
		dmProgram->setName((*it)->getQualifiedNameNode()->getName());

		dmProgram->setSource(ptrLoader->getSourceStore()->exportSource(*it));

		typeinfo::Ext::VariableList& lstArgs(dmProgram->getArgsList());

		Model::Dec::DeclarationBlockFeature::DeclarationNodesList lstDeclarationNodesList((*it)->getParametersNode()->getDeclarationsListAsConst());

		for(Model::Dec::DeclarationBlockFeature::DeclarationNodesList::const_iterator itDec=lstDeclarationNodesList.begin();
			itDec != lstDeclarationNodesList.end();itDec++){

			typeinfo::Ext::VariablePtr dmVariable(typeinfo::DataFactory::GetInstance()->createVariable());

			dmVariable->setName((*itDec)->getVariable());
			dmVariable->setTypeName((*itDec)->getType());
			dmVariable->setTypeNamespace((*itDec)->getNamespace());

			lstArgs.add(dmVariable);
		}

		dmProgram->createLocation();
		dmProgram->getLocation()->setFile(ptrLoader->getModel()->resolve((*it)->getSourceLocation().getSourceID()));
		dmProgram->getLocation()->setLine((*it)->getSourceLocation().getLineNumber());

		lstPrograms.add(dmProgram);
	}

}
/*************************************************************************/
}
}
}
}
