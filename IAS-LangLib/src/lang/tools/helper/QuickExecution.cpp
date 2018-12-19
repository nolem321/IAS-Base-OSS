/*
 * File: IAS-LangLib/src/lang/tools/helper/QuickExecution.cpp
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
#include "QuickExecution.h"
#include<lang/log/LogLevel.h>
#include "dm/Impl/DataFactory.h"


#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>
#include <org/invenireaude/lang/builtin/DataFactory.h>

#include <dm/gen/DataFactory.h>
#include <Impl/DataFactory.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Helper {

const String CEnv_LANG_XSD="IAS_LANG_XSD";

/*************************************************************************/

::IAS::DM::DataFactory* QuickExecution::ptrDataFactory(NULL);

/*************************************************************************/
QuickExecution::QuickExecution():
		pProgram(NULL){
	IAS_TRACER;

	if(!ptrDataFactory){

		ptrDataFactory = org::invenireaude::lang::builtin::DataFactory::GetInstance()->getContaingDataFactory();

		IAS_DFT_FACTORY<DM::XML::XSDHelper>::PtrHolder ptrXSDHelper(
			IAS_DFT_FACTORY<DM::XML::XSDHelper>::Create(ptrDataFactory));

		StringList lstXSDFiles;
		IAS::EnvTools::GetEnvTokenized(CEnv_LANG_XSD,lstXSDFiles);

		for(StringList::const_iterator it = lstXSDFiles.begin();
				it != lstXSDFiles.end();
				it++){
			ptrXSDHelper->defineTypesFromFile(*it);
		}

	}

	IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::PtrHolder ptrLexerIStreamFactory;

	ptrLexerIStreamFactory = IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::Create();

	ptrLoader = IAS_DFT_FACTORY<Interpreter::ProgramLoader>::Create(ptrDataFactory,
																	ptrLexerIStreamFactory.pass());

}
/*************************************************************************/
QuickExecution::~QuickExecution() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void QuickExecution::loadXML(const String& strFileName){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"XML from:"<<strFileName);

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
				IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(ptrDataFactory));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strFileName));

	ptrInputDataObject = ptrDoc->getRootObject();

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"this= "<<(void*)this);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Loaded: "<<ptrInputDataObject->getType()->getFullName());

}
/*************************************************************************/
void QuickExecution::setXML(const String& strXML){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"XML[:"<<strXML<<"]");
	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
				IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(ptrDataFactory));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readString(strXML));

	ptrInputDataObject = ptrDoc->getRootObject();

}
/*************************************************************************/
void QuickExecution::saveXML(const String& strFileName){
	IAS_TRACER;

	if(ptrOutputDataObject.isNull())
		IAS_THROW(BadUsageException("DM object is null"));


	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"XML to:"<<strFileName);

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
					IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(ptrDataFactory));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create(ptrOutputDataObject));

	ptrXMLHelper->save(strFileName,ptrDocument);

}
/*************************************************************************/
void QuickExecution::getXML(String& strXML){
	IAS_TRACER;

	if(ptrOutputDataObject.isNull())
		IAS_THROW(BadUsageException("DM object is null"));


	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
					IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(ptrDataFactory));

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"XML ["<<strXML<<"]");

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create(ptrOutputDataObject));

	ptrXMLHelper->save(strXML,ptrDocument);

}
/*************************************************************************/
void QuickExecution::loadProgram(const String& strProgramName){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Start:"<<strProgramName);


	ptrLoader->loadModel(strProgramName);

	pProgram = ptrLoader->getExecutable(strProgramName);
}

/*************************************************************************/
void QuickExecution::execute(){
		IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"this= "<<(void*)this<<" ptr="<<(void*)ptrInputDataObject.getPointer());

	if(ptrInputDataObject.isNull())
		IAS_THROW(BadUsageException("DM object is null"));

	if(!pProgram)
		IAS_THROW(BadUsageException("Program not loaded."));


	ptrOutputDataObject.unset();
	//ptrOutputDataObject.forget();

	IAS_DFT_FACTORY<Interpreter::Exe::ProgramContext>::PtrHolder ptrContext(
	IAS_DFT_FACTORY<Interpreter::Exe::ProgramContext>::Create(ptrDataFactory,pProgram));

	ptrContext->getParameters()->setDataObject("input",ptrInputDataObject);
	ptrContext->getParameters()->setString("p1","101");

	ptrContext->execute();

	ptrOutputDataObject = ptrContext->getParameters()->getDataObject("output");


	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"DONE!");
}
/*************************************************************************/
}
}
}
}
