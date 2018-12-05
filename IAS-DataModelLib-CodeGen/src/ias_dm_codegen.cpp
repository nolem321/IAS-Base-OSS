/*
 * File: IAS-DataModelLib-CodeGen/src/ias_dm_codegen.cpp
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
#include <commonlib/commonlib.h>
#include "dm/datamodel.h"
#include "dm/Impl/DataFactory.h"
#include "dm/Impl/MemoryManager.h"
#include "dm/gen/CppCodeGenerator.h"

#include <stdlib.h>
#include "dm/gen/ProgramParameters.h"

using namespace IAS;
using namespace DM;
using namespace Gen;

int main(int argc, char* argv[]){

	IAS_TRACER;
	::IAS::Logger::GetInstance();

	IAS_DFT_FACTORY< Gen::ProgramParameters >::PtrHolder ptrProgramParameters;

	String strOutputDirectory;
	String strXSDFile;
	bool  bSingleDataObjectFile;
	try{

		ptrProgramParameters= IAS_DFT_FACTORY< Gen::ProgramParameters >::Create(argc,argv);

		strOutputDirectory=ptrProgramParameters->getOutputDir();
		strXSDFile=ptrProgramParameters->getXSDFile();
		bSingleDataObjectFile=ptrProgramParameters->isSingleDataObjectFile();

	}catch(BadUsageException& e){
		std::cerr<<"Bad arguments:"<<e.toString()<<"\n";
		exit(1);
	}

	std::cout<<"Starting\n";
	try{

		IAS_DFT_FACTORY< Gen::CppCodeGenerator >::PtrHolder ptrCodeGenerator;

		ptrCodeGenerator=IAS_DFT_FACTORY< Gen::CppCodeGenerator >::Create();

		StringList lstXSDFiles;
		TypeTools::Tokenize(strXSDFile,lstXSDFiles,':');

		for(StringList::const_iterator it=lstXSDFiles.begin();
			it != lstXSDFiles.end(); it++){
			ptrCodeGenerator->loadModel(*it);
		}

		ptrCodeGenerator->setNamespaces(ptrProgramParameters->getNamespacesToBeGenerated());
		ptrCodeGenerator->generateCode(strOutputDirectory,bSingleDataObjectFile);

	}catch(IAS::Exception& e){
		std::cout<<"Exception:\n";
		e.printToStream(std::cout);
		std::cout<<"\n";
	}catch(...){
		std::cout<<"Ending with exception.\n";
	}
	std::cout<<"Ending\n";
	std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"DM:\n";
	IAS::DM::Impl::MemoryManager::PrintToStream(std::cout);
	std::cout<<"Done !\n";
	IAS::TracerStats::GetInstance()->printToStream(std::cout);
}
