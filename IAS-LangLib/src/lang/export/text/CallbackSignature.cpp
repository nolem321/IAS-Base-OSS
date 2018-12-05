/*
 * File: IAS-LangLib/src/lang/export/text/CallbackSignature.cpp
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
namespace Export{
namespace Text {

/*************************************************************************/
CallbackSignature::CallbackCtx::CallbackCtx(bool bDeclarationOnly,
											SourceStore* pSourceStore):
											bDeclarationOnly(bDeclarationOnly),
											iIndent(0),
											pSourceStore(pSourceStore){
	IAS_TRACER;
};
/*************************************************************************/
SourceStore *CallbackSignature::CallbackCtx::getSourceStore() const{
	IAS_TRACER;
	return pSourceStore;
}
/*************************************************************************
const DM::DataFactory *CallbackSignature::CallbackCtx::getDataFactory() const{
	IAS_TRACER;
	return pDataFactory;
}
/*************************************************************************/
void CallbackSignature::printIndent(CallbackCtx *pCtx,
	     CallbackSignature::Result& aResult){

	IAS_CHECK_IF_NULL(pCtx);

	for(int i=0;i<pCtx->iIndent; i++)
		aResult.ssOutput<<"  ";
}
/*************************************************************************/
void CallbackSignature::printType(CallbackCtx *pCtx,
			   CallbackSignature::Result& aResult,
			   const String& strType,
			   const String& strNamespace){
  aResult.ssOutput<<strType<<": \""<<
    (pCtx->getSourceStore()->getExportedNamespace(strNamespace))<<"\" ";
}
/*************************************************************************/
void CallbackSignature::printFunCall(CallbackCtx *pCtx,
				  CallbackSignature::Result& aResult,
				  const String& strFunName,
				  const String& strArgs){

	aResult.ssOutput<<strFunName<<"("<<strArgs<<")";

}
/*************************************************************************/
void CallbackSignature::printKeyword(CallbackSignature::Result& aResult,
			   	  	  	  	  	  	  const String& strKeyword){

	aResult.ssOutput<<""<<strKeyword<<"";
}
/*************************************************************************/
}
}
}
}
