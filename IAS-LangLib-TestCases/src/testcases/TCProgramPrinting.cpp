/*
 * File: IAS-LangLib-TestCases/src/testcases/TCProgramPrinting.cpp
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
#include "commonlib/commonlib.h"

#include "TCProgramPrinting.h"

#include <lang/model/allmodel.h>
#include <lang/tools/parser/SourceLocation.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>

#include <lang/printer/CallbackRegister.h>
#include <lang/script/parser/Parser.h>

namespace IAS{
using namespace Lang;
using namespace Lang::Model;

namespace TCT{

//TODO (M) standarize !!!
const String CEnv_SRC_DIRS="IAS_LANG_SRC_DIRS";

/*************************************************************************/
TCProgramPrinting::TCProgramPrinting(TestSuite* pTestSuite,
		   	   	   	   	   	   	   	 const String& strProgramName):
	theTestRunner(this),
	strProgramName(strProgramName){
	IAS_TRACER;
	ptrModel = IAS_DFT_FACTORY<Lang::Model::Model>::Create();
	StringList lstSrcPath;
	IAS::EnvTools::GetEnvTokenized(CEnv_SRC_DIRS, lstSrcPath);

	IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::PtrHolder ptrLexerIStreamFactory;
	ptrLexerIStreamFactory = IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::Create();
	ptrLexerIStreamFactory->setSearchPath(lstSrcPath);

	ptrLexer=IAS_DFT_FACTORY<Script::Parser::Lexer>::Create<Tools::Parser::LexerIStreamFactory*,
															Tools::Parser::ISourceLocationStore*>(
																ptrLexerIStreamFactory.pass(),
																ptrModel.getPointer());

	ptrLexer->openObject(strProgramName);

	IAS_DFT_FACTORY<Script::Parser::Parser>::PtrHolder ptrParser(IAS_DFT_FACTORY<Script::Parser::Parser>::Create(ptrModel.getPointer()));

	ptrParser->parse(ptrLexer);

	init(pTestSuite);
}
/*************************************************************************/

TCProgramPrinting::~TCProgramPrinting() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCProgramPrinting::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::TCProgramPrinting::caseOne);
	TestUnit::init(strProgramName+"_PTR",&theTestRunner,pTestSuite);
}

/*************************************************************************/
String TCProgramPrinting::getOutputFileName() {
	IAS_TRACER;
	String strTmp = strProgramName;
	bool bChanged = false;
	String strOutputFileName;
	for (int iIdx = 0; iIdx < strTmp.length(); iIdx++) {
		char c = strTmp[iIdx];
		if (!isalpha(c) && !isdigit(c) && c != '.' && c != '_') {
			if (!bChanged)
				strOutputFileName += '_';

			bChanged = true;
		} else {
			strOutputFileName += c;
			bChanged = false;
		}
	}
	return strOutputFileName;
}

/*************************************************************************/
void TCProgramPrinting::caseOne(){
	
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Printing:"<<strProgramName);


	StringStream ssOutput;

	const Lang::Model::Model::ProgramList& lstPrograms = ptrModel->getPrograms(strProgramName);

	if(lstPrograms.size() != 1)
			IAS_THROW(InternalException("Expected exactly one program."));

	Printer::CallbackRegister::Call(*lstPrograms.begin(),ssOutput);

	String strResult(ssOutput.str());
	String strOutputFileName = getOutputFileName();
 	OutputFile::SaveString("data/output/printer/"+strOutputFileName+".new.y",strResult);

	String strOrginal;
    InputFile::LoadString("data/output/printer/"+strOutputFileName+".y",strOrginal);

    if(strOrginal.compare(strResult) != 0){
    	std::cerr<<strResult<<", "<<strResult.length()<<std::endl;
    	std::cerr<<strOrginal<<", "<<strOrginal.length()<<std::endl;

    	int iLine=1;
    	for(int i=0;i<strResult.length();i++){

    		if(strResult[i]=='\n')
    			iLine++;

    		if(strResult[i] != strOrginal[i]){
    			std::cerr<<"\n NO_MATCH  :"<<iLine<<", "<<strResult.substr(i,25)<<std::endl;
    			break;
    		}

    	}

    	IAS_THROW(BadUsageException("Do not match!"));
    }

	//Dirty tricks:
	class DeleteCallbacks : public 	::IAS::Lang::Printer::CallbackRegister {
	public:
		static void Delete () { TheInstance = 0;}
	};

	DeleteCallbacks::Delete();

	if(IAS::MemoryManager::GetInstance()->getNumerOfNew()){
		std::cout<<"ALL:\n";
		IAS::MemoryManager::GetInstance()->printToStream(std::cout);
		std::cout<<"New:\n";
		IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);
	}

}

/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
