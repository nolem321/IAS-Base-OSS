/*
 * File: IAS-LangLib/src/lang/interpreter/exe/Context.cpp
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
#include "Context.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "stmt/StatementLists.h"

#include "lang/model/dec/DeclarationNode.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {

/*************************************************************************/
Context::Context() : bIsInterrupted(false), pDataFactory(NULL){
	IAS_TRACER;
	pResultProperty=NULL;
}
/*************************************************************************/
Context::~Context() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const DM::DataFactory* Context::getDataFactory() const{
	IAS_TRACER;
	return pDataFactory;
}
/*************************************************************************/
Expr::ExprResultSetter Context::getResultSetter(){
	IAS_TRACER;

	if(!pResultProperty)
		IAS_THROW(BadUsageException("No result setter, probably a RETURN with a value not allowed."));

	return Expr::ExprResultSetter(ptrParameterValues,pResultProperty);
}
/*************************************************************************/
void Context::pushBlock(DM::DataObject *pVariables){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"PUSH:"<<(void*)pVariables);

	IAS_CHECK_IF_VALID(pVariables);
	lstVariablesChain.push_back(pVariables);
}
/*************************************************************************/
void Context::popBlock(){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"POP:"<<lstVariablesChain.size());

	if(lstVariablesChain.size() == 0)
		IAS_THROW(InternalException("popBlock:lstVariablesChain.size() == 0"));

//	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(DM::XML::XMLHelper::Create(pDataFactory));
//	String strOutput;
//	ptrXMLHelper->save(strOutput,lstVariablesChain.at(lstVariablesChain.size()-1),"t","t");

	lstVariablesChain.pop_back();
}
/*************************************************************************/
DM::DataObject* Context::getBlockVariables(int iOffset){
	IAS_TRACER;

	if(lstVariablesChain.size() - 1 < iOffset  ||
	   iOffset < 0)
			IAS_THROW(InternalException("getBlockVariables: bad offset!"));

	DM::DataObject* pDM= lstVariablesChain.at(lstVariablesChain.size() - iOffset -1);

	IAS_CHECK_IF_VALID(pDM);
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"Result ["<<iOffset<<"]="<<pDM);
	return pDM;
}
/*************************************************************************/
void Context::setDataFactory(const DM::DataFactory *pDataFactory){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
	this->pDataFactory=pDataFactory;
}
/*************************************************************************/
}
}
}
}
