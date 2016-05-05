/*
 * File: IAS-LangLib/src/lang/tools/parser/LexerBase.cpp
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
#include "LexerBase.h"
#include<lang/log/LogLevel.h>

#include "LexerIStreamWrapper.h"

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {

/*************************************************************************/
LexerBase::LexerBase(LexerIStreamFactory* pLexerIStreamFactory,
					 ISourceLocationStore *pSourceLocationStore):
	iLineNo(0),
	pSourceLocationStore(pSourceLocationStore){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pLexerIStreamFactory);
	ptrLexerIStreamFactory=pLexerIStreamFactory;
}
/*************************************************************************/
LexerBase::~LexerBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void LexerBase::openObject(const String& strObjectName){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Object:"<<strObjectName);
	if(hmProcessedObjects.count(strObjectName))
		return;

	pushIStreamWrapper(ptrLexerIStreamFactory->createLexerIStream(strObjectName));
	hmProcessedObjects[strObjectName]=true;
}
/*************************************************************************/
void LexerBase::pushIStreamWrapper(LexerIStreamWrapper* pWrapper){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pWrapper);

	phcStreams.addPointer(pWrapper);
	stackStreams.push(pWrapper);
	stackSourceID.push(pSourceLocationStore->registerSource(pWrapper->getName()));
}
/*************************************************************************/
void LexerBase::popIStreamWrapper(){
	IAS_TRACER;
	stackStreams.pop();
	stackSourceID.pop();
}
/*************************************************************************/
int LexerBase::getStackSize()const{
	IAS_TRACER;
	return stackStreams.size();
}
/*************************************************************************/
const LexerLocation* LexerBase::getLocation() const{
	IAS_TRACER;

	if(stackStreams.size() == 0)
		IAS_THROW(EndOfDataException());

	return stackStreams.top();

}
/*************************************************************************/
SourceLocation LexerBase::getCachedLocation()const{
	IAS_TRACER

	if(stackSourceID.size() == 0)
				IAS_THROW(EndOfDataException());

	return SourceLocation(stackSourceID.top(), stackStreams.top()->getLineNo());
}
/*************************************************************************/
LexerIStreamWrapper* LexerBase::getActiveWrapper(){
	IAS_TRACER;
	if(stackStreams.size() == 0)
			IAS_THROW(EndOfDataException());

		return stackStreams.top();
}
/*************************************************************************/
}
}
}
}
