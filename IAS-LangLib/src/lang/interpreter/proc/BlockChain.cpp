/*
 * File: IAS-LangLib/src/lang/interpreter/proc/BlockChain.cpp
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
#include "BlockChain.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../exe/dec/DeclarationBlockFeature.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {

/*************************************************************************/
BlockChain::BlockChain(){
	IAS_TRACER;
}
/*************************************************************************/
BlockChain::~BlockChain() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void BlockChain::findVariable(const String& strVariable,
								 int& iOffset,
								 const DM::Property* &pRefProperty,
								 const DM::ComplexType* &pRefType){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(this);
	iOffset = 0;
	for(BlockChainList::const_reverse_iterator it = lstBlockChain.rbegin();
		it != lstBlockChain.rend();
		it++, iOffset++){

		const Exe::Dec::DeclarationBlockFeature* pBlock = *it;

		if(pBlock->hasVariable(strVariable)){
			pRefType     = pBlock->getType()->asComplexType();
			pRefProperty = pBlock->getVariableProperty(strVariable);

			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),strVariable<<"["<<iOffset<<"]\t"<<pRefProperty->getType()->getFullName());

			return;
		}
	}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"name:"<<strVariable<<" not found !");

	IAS_THROW(ItemNotFoundException(String("Variable: ")+=strVariable));
}
/*************************************************************************/
void BlockChain::pushBlock(const Exe::Dec::DeclarationBlockFeature *pBlock){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pBlock);
	lstBlockChain.push_back(pBlock);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"PUSH:"<<(void*)pBlock);
}
/*************************************************************************/
void BlockChain::popBlock(){
	IAS_TRACER;

	if(lstBlockChain.size() == 0)
		IAS_THROW(InternalException("popBlock:lstBlockChain.size() == 0"));

	lstBlockChain.pop_back();
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"POP:"<<lstBlockChain.size());
}
/*************************************************************************/
}
}
}
}
