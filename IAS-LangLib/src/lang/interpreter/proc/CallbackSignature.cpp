/*
 * File: IAS-LangLib/src/lang/interpreter/proc/CallbackSignature.cpp
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
#include "CallbackSignature.h"
#include<lang/log/LogLevel.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/
CallbackSignature::CallbackCtx::CallbackCtx(DM::DataFactory *pDataFactory,
											ExecStore* pExecStore):
											iIndent(0),
											pDataFactory(pDataFactory),
											pExecStore(pExecStore){
	IAS_TRACER;
	ptrBlockChain=IAS_DFT_FACTORY<BlockChain>::Create();
};
/*************************************************************************/
ExecStore *CallbackSignature::CallbackCtx::getExecStore() const{
	IAS_TRACER;
	return pExecStore;
}
/*************************************************************************/
DM::DataFactory *CallbackSignature::CallbackCtx::getDataFactory() const {
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataFactory);
	return pDataFactory;
}
/*************************************************************************/
BlockChain *CallbackSignature::CallbackCtx::getBlockChain() {
	IAS_TRACER;
	IAS_CHECK_IF_NULL(ptrBlockChain);
	return ptrBlockChain;
};
/*************************************************************************/
void CallbackSignature::printIndent(CallbackCtx *pCtx,
	     CallbackSignature::Result& aResult){

	IAS_CHECK_IF_NULL(pCtx);

	for(int i=0;i<pCtx->iIndent; i++)
		std::cout<<"  ";
}

/*************************************************************************/
}
}
}
}
