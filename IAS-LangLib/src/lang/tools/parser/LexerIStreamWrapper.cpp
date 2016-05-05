/*
 * File: IAS-LangLib/src/lang/tools/parser/LexerIStreamWrapper.cpp
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
#include "LexerIStreamWrapper.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {
/*************************************************************************/
void LexerLocation::setName(const String& strName){
	this->strName=strName;
	iLineNo=1;
}
/*************************************************************************/
const String& LexerLocation::getName() const{
	return strName;
}
/*************************************************************************/
int LexerLocation::getLineNo()const{
	return iLineNo;
}
/*************************************************************************/
String LexerLocation::asString() const{
	IAS_TRACER;
	StringStream ssResult;
	ssResult<<strName<<":"<<iLineNo;
	return ssResult.str();
}
/*************************************************************************/
/*************************************************************************/
int LexerIStreamWrapper::getChar(){
	IAS_TRACER;

	int iRes = getIS().get();

	if((char)iRes == '\n')
		iLineNo++;

	return iRes;
}
/*************************************************************************/
void LexerIStreamWrapper::ungetChar(){
	getIS().unget();

	//TODO (L) a better way
	int iRes = getIS().get();
	if((char)iRes == '\n')
			iLineNo--;

	getIS().unget();
}
/*************************************************************************/
bool LexerIStreamWrapper::isEOF(){
	return getIS().eof();
}
/*************************************************************************/
/*                                F I L E                                */
/*************************************************************************/
LexerFileIStreamWrapper::LexerFileIStreamWrapper(InputFile* pFile) throw():is(pFile->getStreamRef()){
	IAS_TRACER;

	ptrFile=pFile;
	setName(ptrFile->getName());

};
/*************************************************************************/
LexerFileIStreamWrapper::~LexerFileIStreamWrapper() throw(){
	IAS_TRACER;
}
/*************************************************************************/
LexerFileIStreamWrapper* LexerFileIStreamWrapper::Create(InputFile* pFile){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pFile);

	IAS_DFT_FACTORY<LexerFileIStreamWrapper>::PtrHolder ptrLexerIStreamWrapper;
	ptrLexerIStreamWrapper = IAS_DFT_FACTORY<LexerFileIStreamWrapper>::Create(pFile);

	return ptrLexerIStreamWrapper.pass();
}
/*************************************************************************/
LexerFileIStreamWrapper* LexerFileIStreamWrapper::Create(const String& strFileName){
	IAS_TRACER;
	IAS_DFT_FACTORY<InputFile>::PtrHolder ptrFile;
	ptrFile = IAS_DFT_FACTORY<InputFile>::Create(strFileName);
	ptrFile->open();
	return Create(ptrFile.pass());
}
/*************************************************************************/
std::istream& LexerFileIStreamWrapper::getIS(){
	IAS_TRACER;
	return is;
}

/*************************************************************************/
/*                               S T R I N G                             */
/*************************************************************************/
LexerStringIStreamWrapper::LexerStringIStreamWrapper(const String& strBuffer) throw():
ssBuffer(strBuffer)
{}
/*************************************************************************/
LexerStringIStreamWrapper::~LexerStringIStreamWrapper() throw(){
	IAS_TRACER;
}

/*************************************************************************/
LexerStringIStreamWrapper* LexerStringIStreamWrapper::Create(const String& strBuffer){
	IAS_TRACER;

	IAS_DFT_FACTORY<LexerStringIStreamWrapper>::PtrHolder ptrLexerIStreamWrapper;
	ptrLexerIStreamWrapper = IAS_DFT_FACTORY<LexerStringIStreamWrapper>::Create(strBuffer);
	ptrLexerIStreamWrapper->setName("memory");
	return ptrLexerIStreamWrapper.pass();
}
/*************************************************************************/
std::istream& LexerStringIStreamWrapper::getIS(){
	IAS_TRACER;
	return ssBuffer;
}
/*************************************************************************/

}
}
}
}
