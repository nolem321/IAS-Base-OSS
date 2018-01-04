/*
 * File: IAS-LangLib-TestCases/src/testcases/TCProgramExecution.cpp
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

#include "TCProgramExecution.h"

#include <lang/model/allmodel.h>
#include <lang/tools/helper/QuickExecution.h>

#include <lang/interpreter/proc/CallbackRegister.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
TCProgramExecution::TCProgramExecution(TestSuite* pTestSuite,
		   	   	   	   	   	   	   	   const String& strProgramName,
		   	   	   	   	   	   	   	   const String& strInputFileName):
	theTestRunner(this),
	strProgramName(strProgramName),
	strInputFileName(strInputFileName){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCProgramExecution::~TCProgramExecution() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCProgramExecution::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::TCProgramExecution::caseOne);
	TestUnit::init(strProgramName,&theTestRunner,pTestSuite);
}

/*************************************************************************/
String TCProgramExecution::getOutputFileName() {
	IAS_TRACER;
	String strTmp = strInputFileName;
	strTmp.resize(strTmp.length() - 4);
	strTmp += String("_") + this->getName();
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
void TCProgramExecution::caseOne(){

	IAS_DFT_FACTORY< ::IAS::Lang::Tools::Helper::QuickExecution >::PtrHolder ptrQuickExecution
			(IAS_DFT_FACTORY< ::IAS::Lang::Tools::Helper::QuickExecution>::Create());

	ptrQuickExecution->loadXML(String("data/input/")+strInputFileName);
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Start:"<<strProgramName);
	ptrQuickExecution->loadProgram(strProgramName);

	ptrQuickExecution->execute();

	String strResult;
	ptrQuickExecution->getXML(strResult);

	//std::cout<<strResult;

	String strOutputFileName = getOutputFileName();

 	OutputFile::SaveString("data/output/"+strOutputFileName+".new.xml",strResult);

	String strOrginal;
    InputFile::LoadString("data/output/"+strOutputFileName+".xml",strOrginal);

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
	class DeleteCallbacks : public 	::IAS::Lang::Interpreter::Proc::CallbackRegister {
	public:
		static void Delete () { TheInstance = 0;}
	};

	ptrQuickExecution=0;
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
