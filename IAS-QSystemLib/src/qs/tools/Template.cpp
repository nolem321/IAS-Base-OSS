/*
 * File: Template.cpp
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

#include "Template.h"

#include <lang/interpreter/ProgramLoader.h>
#include <lang/interpreter/TypeList.h>
#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/model/dec/ResultDeclarationNode.h>

namespace IAS {
namespace QS {
namespace Tools {

/*************************************************************************/
Template::Template(const String& strPattern):
	::IAS::Template(strPattern){
	IAS_TRACER;
}
/*************************************************************************/
Template::~Template() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Template::Arguments::Arguments(const DM::DataObject* dmData, IAS::Lang::Interpreter::ProgramLoader *pProgramLoader, Arguments* pParentArguments , size_t iIdx):
	::IAS::Template::Arguments(pParentArguments),
	    pProgramLoader(pProgramLoader),
		dmData(dmData),
		iIdx(iIdx){

	IAS_TRACER;
	IAS_CHECK_IF_NULL(dmData);
}
/*************************************************************************/
Template::Arguments::~Arguments(){}
/*************************************************************************/
void Template::Arguments::parseFunctionCall(const String& strValue, String& strFunction, String& strArgument){
	IAS_TRACER;

	size_t iOpenPar = strValue.find('(',1);

	if( iOpenPar == String::npos)
		IAS_THROW(BadUsageException("Invalid function call in template, strKey = " + strValue));

	size_t iClosePar = strValue.find(')', iOpenPar + 1);

	if(iClosePar == String::npos )
		IAS_THROW(BadUsageException("Invalid function call in template, strKey = " + strValue));

	strFunction = strValue.substr(1, iOpenPar - 1);
	strArgument = strValue.substr(iOpenPar + 1, iClosePar - iOpenPar - 1);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"template call: "<<strFunction<<"("<<strArgument<<")");

}
/*************************************************************************/
void Template::Arguments::callFunction(const String strFunction, const DM::DataObject* dmData, String& strValue){
	IAS_TRACER;

	IAS::Lang::Interpreter::TypeList lstTypes;
	lstTypes.append(dmData->getType());

	const IAS::Lang::Interpreter::Exe::Program *pProgram = pProgramLoader->getExecutable(strFunction, lstTypes);

	IAS_DFT_FACTORY<IAS::Lang::Interpreter::Exe::ProgramContext>::PtrHolder ptrContext(
			IAS_DFT_FACTORY<IAS::Lang::Interpreter::Exe::ProgramContext>::Create(pProgramLoader->getDataFactory(), pProgram));

	if(!pProgram->isReturningResult())
		IAS_THROW(BadUsageException("Template programs must return values: "+pProgram->getName()));

	DM::DataObjectPtr dmArgument(dmData->duplicate());

	ptrContext->getParameters()->setDataObject(ptrContext->getParameters()->getType()->asComplexType()->getProperties().getProperty(0), dmArgument);
	ptrContext->execute();

	strValue = ptrContext->getParameters()->getString(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable);
}
/*************************************************************************/
bool Template::Arguments::getImpl(const String& strKey, String& strValue) {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"key: "<<strKey);

	if(strKey.compare("_index") == 0) {
		strValue = TypeTools::IntToString(iIdx);
		return true;
	}

	if(strKey.compare("_index1") == 0) {
		strValue = TypeTools::IntToString(iIdx+1);
		return true;
	}

	if(strKey[0] == ':'){

		String strFunction;
		String strArgument;

		parseFunctionCall(strKey, strFunction, strArgument);

		if(!dmData->isSet(strArgument))
			return false;

		callFunction(strFunction, dmData->getDataObject(strArgument), strValue);

		return true;
	}

	try{
		if(!dmData->isSet(strKey))
			return false;
	}catch(ItemNotFoundException& e){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"unknown property: "<<strKey);
		return false;
	}

	strValue = dmData->getString(strKey);

	return true;
}
/*************************************************************************/
Template::Arguments* Template::Arguments::createNestedImpl(const String& strKey) {

	IAS_TRACER

	IAS_THROW(InternalException("createNestedImpl() is not allowed in QS::Tools::Templates, key = " + strKey));

}
/*************************************************************************/
size_t Template::Arguments::getNestedCount(const String& strKey) {

	IAS_TRACER;

	if (hmNested.count(strKey) == 0 && dmData->isSet(strKey)) {

		const DM::DataObjectList& lstData(dmData->getList(strKey));
		hmNested[strKey] = IAS_DFT_FACTORY<NestedEntry>::Create();

		for (int iIdx = 0; iIdx < lstData.size(); iIdx++)
		hmNested[strKey]->push(IAS_DFT_FACTORY<Arguments>::Create(lstData.at(iIdx),pProgramLoader,this,iIdx));

	}

	return IAS::Template::Arguments::getNestedCount(strKey);
}
/*************************************************************************/
}
}
}
