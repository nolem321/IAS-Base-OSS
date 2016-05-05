/*
 * File: IAS-LangLib/src/lang/tools/parser/LexerIStreamFactoryForFiles.cpp
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
#include "LexerIStreamFactoryForFiles.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "LexerIStreamWrapper.h"

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {

/*************************************************************************/
LexerIStreamFactoryForFiles::LexerIStreamFactoryForFiles(){
	IAS_TRACER;

	StringList lstSrcPath; //TODO (L) Reload default
	setSearchPath(lstSourcePath);
}
/*************************************************************************/
LexerIStreamFactoryForFiles::~LexerIStreamFactoryForFiles() throw(){
	IAS_TRACER;
}
/*************************************************************************/
InputFile* LexerIStreamFactoryForFiles::findAndOpenFile(const String& strName) const{
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Object: "<<strName);
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Source path entries: "<<lstSourcePath.size());

	String strResult;

	for (StringList::const_iterator it = lstSourcePath.begin();
		 it != lstSourcePath.end();
		 it++) {

		strResult = *it;
		strResult += "/";
		const char *sTmp = strName.c_str();

		char c;

		while (c = *sTmp++) {

			if (c == ':' && *sTmp == ':') {
				strResult += '/';
				sTmp++;
			} else
				strResult += c;

		}

		strResult += ".y";

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Trying a file name: "<<strResult);

		try{

			IAS_DFT_FACTORY<InputFile>::PtrHolder ptrInputFile(IAS_DFT_FACTORY<InputFile>::Create(strResult));
			ptrInputFile->open();

			if(ptrInputFile->isOpenedAndGood())
				return ptrInputFile.pass();

		}catch(SystemException& e){}

	}

	IAS_THROW(ItemNotFoundException(strName));
}
/*************************************************************************/
LexerIStreamWrapper* LexerIStreamFactoryForFiles::createLexerIStream(const String& strObjectName)const{
	IAS_TRACER;

	return LexerFileIStreamWrapper::Create(findAndOpenFile(strObjectName));
}
/*************************************************************************/
void LexerIStreamFactoryForFiles::setSearchPath(const StringList& lstSourcePath){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Setting: "<<lstSourcePath.size());

	if(lstSourcePath.size() > 0)
		this->lstSourcePath=lstSourcePath;
	else{
		this->lstSourcePath.clear();
		this->lstSourcePath.push_back("data/lang");
	}

}
/*************************************************************************/
}
}
}
}
