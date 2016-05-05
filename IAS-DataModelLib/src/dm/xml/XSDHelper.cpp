/*
 * File: IAS-DataModelLib/src/dm/xml/XSDHelper.cpp
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
#include "../../dm/xml/XSDHelper.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/LibXMLLexerForFile.h"
#include "../../dm/xml/XSDParser.h"
#include "../../dm/xml/XSDParserForInclude.h"

#include <limits.h>

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
XSDHelper::XSDHelper(::IAS::DM::DataFactory *pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
}
/*************************************************************************/
XSDHelper::~XSDHelper() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void XSDHelper::defineTypesFromFile(const String& strFileName, const String& strTargetNamespace){
	IAS_TRACER;

	if(fileLookup(strFileName, strTargetNamespace))
		return;

	IAS_DFT_FACTORY<XSDParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<XSDParser>::Create(this,
			IAS_DFT_FACTORY<LibXMLLexerForFile>::Create(strFileName)));

	size_t iIdx = strFileName.find_last_of('/');

	ptrParser->setWorkingDir(strFileName.substr(0,iIdx));
	ptrParser->parse();

	String strFileTNS = ptrParser->getTargetNamespace();

	if(!strTargetNamespace.empty() && strTargetNamespace.compare(strFileTNS) != 0)
		IAS_THROW(BadUsageException("Different namespace expected in xsd:import: "
				+strTargetNamespace+", got: "+strFileTNS+", file: "+strFileName));

	if(fileLookup(strFileName, strFileTNS))
		return;

	ptrParser->define();

	registerFile(strFileName,strFileTNS);
}
/*************************************************************************/

void XSDHelper::includeTypesFromFile(const String& strFileName, const String& strTargetNamespace){
	IAS_TRACER;

	if(fileLookup(strFileName, strTargetNamespace))
		return;

	IAS_DFT_FACTORY<XSDParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<XSDParserForInclude>::Create(this,
			IAS_DFT_FACTORY<LibXMLLexerForFile>::Create(strFileName), strTargetNamespace));

	size_t iIdx = strFileName.find_last_of('/');

	ptrParser->setWorkingDir(strFileName.substr(0,iIdx));
	ptrParser->parse();
	ptrParser->define();

	registerFile(strFileName, strTargetNamespace);
}
/*************************************************************************/
static inline String _normalizePath(const String& strFileName){

	char sBuffer[PATH_MAX];

	char *sRealPath = realpath(strFileName.c_str(),sBuffer);

	if(!sRealPath)
		IAS_THROW(SystemException("realpath failed for:")<<strFileName);

	String strResult(sRealPath);

	return strResult;
}
/*************************************************************************/
bool XSDHelper::fileLookup(const String& strFileName, const String& strTargetNamespace) const{
	IAS_TRACER;

	String strNormalized = buildKey(strFileName, strTargetNamespace);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"lookup: "<<strNormalized);
	return hmLoadedFiles.count(strNormalized) > 0;
}
/*************************************************************************/
String XSDHelper::buildKey(const String& strFileName, const String& strTargetNamespace)const {

	IAS_TRACER;

	String strNormalized(_normalizePath(strFileName));

	if (!strTargetNamespace.empty())
		strNormalized += "[" + strTargetNamespace + "]";

	return strNormalized;
}

/*************************************************************************/
void XSDHelper::registerFile(const String& strFileName, const String& strTargetNamespace){
	IAS_TRACER;

	String strNormalized = buildKey(strFileName, strTargetNamespace);
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"register: "<<strNormalized);

	if(hmLoadedFiles.count(strNormalized) > 0)
		IAS_THROW(InternalException(String("This file already exists:")+=strNormalized));

	hmLoadedFiles[strNormalized];
}
/*************************************************************************/
}
}
}
