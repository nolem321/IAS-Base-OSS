/*
 * File: IAS-LangLib/src/lang/interpreter/exe/ProgramContext.cpp
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
#include "ProgramContext.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "stmt/StatementLists.h"
#include "Program.h"

#include <lang/interpreter/exe/dec/Parameters.h>
#include "lang/model/dec/ResultDeclarationNode.h"

#include <lang/interpreter/exe/exception/InterpreterException.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {

/*************************************************************************/
ProgramContext::ProgramContext(const DM::DataFactory *pDataFactory, Program* pProgram){

	IAS_TRACER;

	setDataFactory(pDataFactory);
	init(pProgram);
}
/*************************************************************************/
ProgramContext::~ProgramContext() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DM::DataObject* ProgramContext::getParameters(){
	IAS_TRACER;
	return ptrParameterValues;
}
/*************************************************************************/
DM::DataObject* ProgramContext::getResult() const{
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pResultProperty);
	return ptrParameterValues->getDataObject(pResultProperty);
}
/*************************************************************************/
bool ProgramContext::hasResult() const{
	IAS_TRACER;
	return pResultProperty != 0;
}
/*************************************************************************/
DM::DataObjectList& ProgramContext::getResultAsList() const{
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pResultProperty);
	return ptrParameterValues->getList(pResultProperty);
}
/*************************************************************************/
void ProgramContext::execute(Exe::Context *pCtx){
	IAS_TRACER;
	Dec::DeclarationBlockFeature::AutoPopUp autoPopUp(this,ptrParameterValues);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Execute: "<<pProgram->getName());
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Execute: "<<pProgram->getSourceName());
	try{
		pProgram->execute(this);
	}catch(InterpreterException& e){
		e.setStatementSource(pProgram->getSourceName(),pProgram->getName());
		throw;
	}

}
/*************************************************************************/
void ProgramContext::init(Program* pProgram){
	IAS_TRACER;
	this->pProgram=pProgram;
	ptrParameterValues = pProgram->createParameters();
	if(pProgram->isReturningResult()){
		pResultProperty = pProgram->getParameters()->getType()->asComplexType()
				->getProperties().getProperty(Model::Dec::ResultDeclarationNode::CStrResultVariable);
	}
}
/*************************************************************************/
}
}
}
}
