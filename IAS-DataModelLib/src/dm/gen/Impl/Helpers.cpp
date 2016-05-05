/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/Helpers.cpp
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
#include "../../../dm/gen/Impl/Helpers.h"
#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {
/*************************************************************************/
String Helpers::convertToSymbol(const String& strText, char cEscape, bool bUpper){
	IAS_TRACER;

	StringStream ssResult;

	for(int i=0; i<strText.length(); i++){
		char c=strText[i];
		if(isalnum(c) || c == '_'){
			if(bUpper && islower(c))
				c=toupper(c);
			ssResult<<c;
		}else{
			ssResult<<cEscape;
			ssResult<<(unsigned int)c;
		}
	}

	return ssResult.str();
}
/*************************************************************************/
void Helpers::PropertyToMethod(const String& strPrefix,
								  const String& strProperty,\
								  String& strOutput){
	IAS_TRACER;

	String strName =strProperty;

	if(strProperty.compare("userData") == 0 || strProperty.compare("UserData") == 0)
		strName="UserData_";

	if(strProperty.compare("length") == 0 || strProperty.compare("Length") == 0)
		strName="Length_";

	if(strProperty.compare("type") == 0 || strProperty.compare("Type") == 0)
		strName="Type_";

	if(strProperty.compare("URI") == 0)
		strName="URI_";

	if(strProperty.compare("date") == 0 || strProperty.compare("Date") == 0)
		strName="Date_";


	strOutput=strPrefix;
	strOutput+= toupper(strName[0]);
	strOutput+=strName.substr(1);

}

/*************************************************************************/
String Helpers::PropertyToMethod(const String& strPrefix, const String& strProperty){
	IAS_TRACER;
	String strResult;
	PropertyToMethod(strPrefix,strProperty,strResult);
	return strResult;
}
/*************************************************************************/
void Helpers::ImproveURI(const String& strURI, String& strOutput){

	IAS_TRACER;

	String prefix=strURI.substr(0,10);

	if(prefix.compare("http://www") == 0)
		strOutput=strURI.substr(11);
	else
		strOutput=strURI;

	for(int i=0; i<strOutput.length(); i++){
		if(strOutput[i] == '/')
			strOutput[i]='.';
	}
}

/*************************************************************************/
void Helpers::URIToFilePath(const String& strURI, String& strOutput){
	IAS_TRACER;

	StringList lstNSParts;
	URIToList(strURI,lstNSParts);
	URIToFilePath(lstNSParts,strOutput);
}
/*************************************************************************/
void Helpers::URIToFilePath(const StringList& lstNSParts, String& strOutput){
	IAS_TRACER;

	strOutput.clear();

	for(StringList::const_iterator it=lstNSParts.begin(); it != lstNSParts.end(); it++){
		if(it != lstNSParts.begin())
			strOutput+="/";
		strOutput+=*it;
	}
}
/*************************************************************************/
String Helpers::URIToFilePath(const StringList& lstNSParts){
	IAS_TRACER;
	String strResult;
	URIToFilePath(lstNSParts,strResult);
	return strResult;
}
/*************************************************************************/
String Helpers::URIToFilePath(const String& strURI){
	IAS_TRACER;
	String strResult;
	URIToFilePath(strURI,strResult);
	return strResult;
}
/*************************************************************************/
void Helpers::URIToPrefix(const String& strURI, String& strOutput){
	IAS_TRACER;

	StringList lstOutput;

	URIToList(strURI,lstOutput);

	URIToPrefix(lstOutput, strOutput);

}
/*************************************************************************/
void Helpers::URIToPrefix(const StringList& lstNSParts, String& strOutput){

	strOutput.clear();

	for(StringList::const_iterator it=lstNSParts.begin(); it != lstNSParts.end(); it++){
		if(it != lstNSParts.begin())
			strOutput+="::";
		strOutput+=*it;
	}
}

/*************************************************************************/
String Helpers::URIToPrefix(const String& strURI){
	IAS_TRACER;
	String strResult;
	URIToPrefix(strURI,strResult);
	return strResult;
}
/*************************************************************************/
String Helpers::URIToPrefix(const StringList& lstNSParts){
	IAS_TRACER;
	String strResult;
	URIToPrefix(lstNSParts,strResult);
	return strResult;
}
/*************************************************************************/
void Helpers::URIToList(const String& strURI, StringList& lstOutput){
	IAS_TRACER;

	String strOutput;

	if(strURI.substr(0,10).compare("http://www") == 0){
		strOutput=strURI.substr(11);
	}else if(strURI.substr(0,7).compare("http://") == 0){
		strOutput=strURI.substr(8);
	}else
		strOutput=strURI;

	int iLastIdx=0;

	bool bDomain=true;

	for(int i=0; i<strOutput.length(); i++){

		if(bDomain && strOutput[i] == '.'){

			lstOutput.push_front(strOutput.substr(iLastIdx,i-iLastIdx));
			iLastIdx=i+1;

		}else if(strOutput[i] == '/'){

			if(bDomain)
				lstOutput.push_front(strOutput.substr(iLastIdx,i-iLastIdx));
			else
				lstOutput.push_back(strOutput.substr(iLastIdx,i-iLastIdx));

			iLastIdx=i+1;

			bDomain=false;
		}

	}

	if(bDomain)
		lstOutput.push_front(strOutput.substr(iLastIdx));
	else
		lstOutput.push_back(strOutput.substr(iLastIdx));

}
/*************************************************************************/
}
}
}
}
