/*
 * File: IAS-LangLib/src/lang/tools/helper/AdHocPrograms.cpp
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
#include "AdHocPrograms.h"
#include<lang/log/LogLevel.h>
#include "dm/Impl/DataFactory.h"


#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>
#include <lang/interpreter/exe/exception/InterpreterException.h>

#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>

#include <dm/gen/DataFactory.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Helper {

/*************************************************************************/
AdHocPrograms::AdHocPrograms():
	ptrDataFactory(IAS_DFT_FACTORY<DM::Impl::DataFactory>::Create(::IAS::DM::Gen::DataFactory::GetInstance())){
	IAS_TRACER;

}
/*************************************************************************/
AdHocPrograms::~AdHocPrograms() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void AdHocPrograms::execute(const String& strName,
		 	 	 	 	    const String& strSource,
							DM::DataObjectPtr& dmArgument,
							DM::DataObjectPtr& dmResult,
							StringStream& ssErrors){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	Interpreter::ProgramLoader *pProgramLoader = NULL;

	try {

		if(hmProgramLoaders.count(strSource) == 0) {

			IAS_DFT_FACTORY<Interpreter::ProgramLoader>::PtrHolder ptrProgramLoader(
					IAS_DFT_FACTORY<Interpreter::ProgramLoader>::Create(ptrDataFactory));

			ptrProgramLoader->loadModel(strName, IAS_DFT_FACTORY<Tools::Parser::LexerStringIStreamWrapper>::Create(strSource) );

			hmProgramLoaders[strSource] = pProgramLoader = ptrProgramLoader.pass();

		} else {

			pProgramLoader = hmProgramLoaders[strSource];

		}

		const Interpreter::Exe::Program *pProgram = pProgramLoader->getExecutable(strName);

		IAS_DFT_FACTORY<Interpreter::Exe::ProgramContext>::PtrHolder ptrProgramContext(
				IAS_DFT_FACTORY<Interpreter::Exe::ProgramContext>::Create(ptrDataFactory,pProgram));

		const DM::PropertyList& lstProperties(pProgram->getParameters()->getType()->asComplexType()->getProperties());

		ptrProgramContext->getParameters()->setDataObject(lstProperties.getProperty(0), dmArgument);

		ptrProgramContext->execute();

		dmResult = ptrProgramContext->getResult()->duplicate();

	} catch(Lang::Interpreter::Exe::InterpreterProgramException& e) {
		ssErrors<<"Program Exception: \n";
		ssErrors<<e.getName()<<"\n"<<e.getInfo();

	} catch(Lang::Interpreter::Exe::InterpreterException& e) {
		ssErrors<<"Intepreter Exception: \n";
		ssErrors<<e.getName()<<"\n"<<e.getInfo();

	} catch(Exception &e) {
		ssErrors<<"Engine Error: \n";
		ssErrors<<e.getName()<<"\n"<<e.getInfo();
	}

}
/*************************************************************************/
}
}
}
}
