/*
 * File: IAS-CommonLib/src/commonlib/tools/TypeTools.cpp
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
#include "TypeTools.h"

#include "../logger/logger.h"
#include "commonlib/exception/DataException.h"
#include "../exception/BadUsageException.h"
#include "string.h"

#include <stdlib.h>
#include <errno.h>

namespace IAS {

/*************************************************************************/
int TypeTools::StringToInt(const String& strValue) {
	IAS_TRACER;

	int iResult;

#if __cplusplus >= 1201103L
	try{
		iResult = std::stoi(strValue.c_str(),0,10);
	}catch(std::exception& e){
		IAS_THROW(BadUsageException("Conversion error: " + strValue));
	}
#else
	StringStream ss(strValue);
	ss >> iResult;

	if(!ss.eof())
		IAS_THROW(BadUsageException("Conversion error: [" + strValue + "]"));

#endif


	return iResult;

}

/*************************************************************************/
Float TypeTools::StringToFloat(const String& strValue) {
	StringStream ss(strValue);

	Float fResult;
	ss >> fResult;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "["<<strValue<<"]="<<fResult);

	return fResult;
}

/*************************************************************************/
bool TypeTools::StringToBoolean(const String& strValue, bool bAllowNumeric) {

	StringStream ss(strValue);

	bool bResult = false;

	if (strValue.compare("false") == 0) {
		bResult = false;
	} else if (strValue.compare("true") == 0) {
		bResult = true;
	} else {

		if (!bAllowNumeric)
			IAS_THROW(DataException(String("Bad boolean value:")+=strValue));
	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "["<<strValue<<"]="<<bResult);

	return bResult;
}

/*************************************************************************/
void TypeTools::IntToString(int iValue, String& strValue, int iWidth) {
	StringStream ss;
	if (iWidth > 0) {
		ss.width(iWidth);
		ss.fill('0');
	}
	ss << iValue;
	strValue = ss.str();
}

/*************************************************************************/
void TypeTools::FloatToString(Float fValue, String& strValue, int iWidth) {
	StringStream ss;

	ss.setf(std::ios::fixed,std::ios::floatfield);
	ss.setf(std::ios::showpoint);
	
	if (iWidth > 0) {
		ss.width(iWidth);
		ss.fill('0');
	}
	ss << fValue;
	strValue = ss.str();
}

/*************************************************************************/
void TypeTools::BoolToString(bool bValue, String& strValue) {

	strValue = bValue ? "true" : "false";
}

/*************************************************************************/
String TypeTools::FloatToString(Float fValue, int iWidth) {
	String strValue;
	FloatToString(fValue, strValue, iWidth);
	return strValue;
}

/*************************************************************************/
String TypeTools::BoolToString(bool bValue) {
	String strValue;
	BoolToString(bValue, strValue);
	return strValue;
}
/*************************************************************************/
String TypeTools::IntToString(int iValue, int iWidth) {
	String strValue;
	IntToString(iValue, strValue, iWidth);
	return strValue;
}
/*************************************************************************/
String TypeTools::CharToString(char cValue) {
	IAS_TRACER;
	String strResult;
	strResult = cValue;
	return strResult;
}
/*************************************************************************/
void TypeTools::Tokenize(const String& strInput, StringList& refOutput, char cDelimiters) {
	IAS_TRACER;

	size_t iStart = 0;
	size_t iCursor = 0;

	refOutput.clear();
	while (iCursor != String::npos) {

		iCursor = strInput.find(cDelimiters, iStart);

		if (iCursor == String::npos) {
			refOutput.push_back(strInput.substr(iStart, String::npos));
			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "["<<strInput.substr(iStart, String::npos)<<"]");
		} else {
			refOutput.push_back(strInput.substr(iStart, iCursor - iStart));
			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "["<<strInput.substr(iStart, iCursor - iStart)<<"]");
			iStart = iCursor + 1;
		}

	}
}
/*************************************************************************/
void TypeTools::ChopArguments(const String& strArgument, String& strName, String& strValue, char cDelimter ){
	IAS_TRACER;

	bool bName=true;


	strName.clear();
	strValue.clear();

	strName.reserve(strArgument.length());
	strValue.reserve(strArgument.length());

	for(String::const_iterator it=strArgument.begin(); it!=strArgument.end(); it++){
		if(*it == cDelimter && bName){
			bName=false;
		}else{
			if(bName)
				strName+=*it;
			else
				strValue+=*it;
		}
	}

	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Argument["<<strName<<"]=["<<strValue<<"]");
}
/*************************************************************************/
String TypeTools::Replace(const String& strInput, const String& strPattern, const String& strNewText){
	IAS_TRACER;

	std::size_t iPos=0;
	std::size_t iLastPos=iPos;

	String strResult;
	std::size_t iPatternLen=strPattern.length();

	while( (iPos=strInput.find(strPattern,iPos)) != String::npos){
		strResult+=strInput.substr(iLastPos,iPos - iLastPos);
		strResult+=strNewText;
		iPos+=iPatternLen;
		iLastPos=iPos;
	};

	strResult+=strInput.substr(iLastPos);
	return strResult;
}
/*************************************************************************/
}
