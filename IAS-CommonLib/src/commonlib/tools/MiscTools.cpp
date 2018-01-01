/*
 * File: IAS-CommonLib/src/commonlib/tools/MiscTools.cpp
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
#include "MiscTools.h"
#include "../logger/logger.h"
#include "../exception/BadUsageException.h"
#include "TypeTools.h"

#include <string.h>

#include <locale>
#include <algorithm>
#include "EnvTools.h"


namespace IAS {

/*************************************************************************/
String MiscTools::StrToHex(const String& strData){

	IAS_TRACER;

	const char *s=strData.c_str();

	String strResult;

	char c;
	while( (c=*s++) != 0 ){
		strResult+=CharToHex(c);
	}

	return strResult;
}

/*************************************************************************/
String MiscTools::StrToPrintableAndHex(const String& strData){

	IAS_TRACER;

	const char *s=strData.c_str();

	String strResult;

	char c;
	bool bFirst=true;
	while( (c=*s++) != 0 ){

		if(!bFirst)
			strResult+=' ';
		else
			bFirst=false;

		if(c > ' ')
			strResult+=c;
		  else
			strResult+='.';
		strResult+=':';
		strResult+=CharToHex(c);
	}

	return strResult;

}
/*************************************************************************/
String MiscTools::CharToHex(const char cChar){
	IAS_TRACER;
	String strResult;

	strResult = HexDigit( (cChar >> 4) & 0x0f);
	strResult += HexDigit(cChar & 0x0f);
	return strResult;
}
/*************************************************************************/
String MiscTools::StrToPrintableOrHex(const String& strData){

	IAS_TRACER;

	const char *s=strData.c_str();

	String strResult;

	unsigned char c;

	while( (c=*s++) != 0 ){

		if(c > ' ')
			strResult+=c;
		  else{
			strResult+='[';
			strResult+=CharToHex(c);
			strResult+=']';
		  }
	}

	return strResult;

}

/*************************************************************************/
char MiscTools::HexDigit(int  iValue){
	IAS_TRACER;
	return HexDigit((unsigned char)iValue);
}
/*************************************************************************/
char  MiscTools::HexDigit(unsigned char cValue){
	IAS_TRACER;
	if(cValue < 10)
		return cValue + '0';
	else
	  if(cValue < 16)
		return cValue - 10 + 'A';
	  else
	    IAS_THROW(BadUsageException("Hex value out of range."));

}
/*************************************************************************/
unsigned char MiscTools::HexValue(char cValue){
	IAS_TRACER;
	if(cValue >= '0' && cValue <= '9')
		return cValue - '0';
	else if(cValue >= 'A' && cValue <= 'F')
		return cValue - 'A' + 10;
	else if(cValue >= 'a' && cValue <= 'f')
		return cValue - 'a' + 10;
	  else
	    IAS_THROW(BadUsageException(String("Hex value out of range.")+TypeTools::IntToString(cValue)+"["+cValue+"]"));

}
/*************************************************************************/
void  MiscTools::BinarytoHex(unsigned char *sData, size_t iDataLen, String& strOutput){
	IAS_TRACER;

	while(iDataLen){
		strOutput+=HexDigit(*sData >> 4);
		strOutput+=HexDigit(*sData & 0x0F);
		sData++;
		iDataLen--;
	}

}
/*************************************************************************/
void  MiscTools::HexToBinary(const String& strInput, unsigned char *sData, size_t iBufLen){
	IAS_TRACER;

	const char *s=strInput.c_str();

	while(*s && *(s+1) && iBufLen--)
		*sData++ = (HexValue(*s++)<<4) + HexValue(*s++);


}
/*************************************************************************/
void MiscTools::CopyStreams(std::istream& is, std::ostream& os, size_t iLimit){
	IAS_TRACER;

    std::size_t iBufSize = 0x8000;
	char sBuffer[iBufSize];

	int iNumBytes=0;

	while(is.good() && iLimit > 0){

		if(iLimit < iBufSize)
			iBufSize = iLimit;

		is.read(sBuffer, iBufSize);

	    if(is.gcount())
		  os.write(sBuffer, is.gcount());

	    if(!os.good())
	    	IAS_THROW(BadUsageException("Error when coping streams."));

	    iNumBytes+=is.gcount();
	    iLimit-=is.gcount();
	}

	os.flush();

	IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(),TypeTools::IntToString(iNumBytes)+" bytes copied.");

}
/*************************************************************************/
String MiscTools::StreamToString(std::istream& is){
	IAS_TRACER;

	is.clear();
	is.seekg(0);

	StringStream ssTmp;
	MiscTools::CopyStreams(is, ssTmp);

	is.clear();
	is.seekg(0);

	return ssTmp.str();
}
/*************************************************************************/
static const String CBase64 =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

/*************************************************************************/
static inline bool isBase64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

/*************************************************************************/
void MiscTools::StringToBase64(const String& strInput, String& strOutput){
	BinaryToBase64((unsigned char*)strInput.c_str(),strInput.length(),strOutput);
}
/*************************************************************************/

//TODO rewrite
/*************************************************************************/
void  MiscTools::BinaryToBase64(const unsigned  char *sData, size_t iDataLen, String& strOutput){

  int iIdx = 0;

  unsigned char bytes3[3];
  unsigned char bytes4[4];

  while (iDataLen--) {
    bytes3[iIdx++] = *(sData++);
    if (iIdx == 3) {
      bytes4[0] = (bytes3[0] & 0xfc) >> 2;
      bytes4[1] = ((bytes3[0] & 0x03) << 4) + ((bytes3[1] & 0xf0) >> 4);
      bytes4[2] = ((bytes3[1] & 0x0f) << 2) + ((bytes3[2] & 0xc0) >> 6);
      bytes4[3] = bytes3[2] & 0x3f;

      for(iIdx = 0; iIdx < 4 ; iIdx++)
    	  strOutput += CBase64[bytes4[iIdx]];
      iIdx = 0;
    }
  }

  if (iIdx)
  {
	int iIdx2;

    for(iIdx2 = iIdx; iIdx2 < 3; iIdx2++)
      bytes3[iIdx2] = '\0';

    bytes4[0] = (bytes3[0] & 0xfc) >> 2;
    bytes4[1] = ((bytes3[0] & 0x03) << 4) + ((bytes3[1] & 0xf0) >> 4);
    bytes4[2] = ((bytes3[1] & 0x0f) << 2) + ((bytes3[2] & 0xc0) >> 6);
    bytes4[3] = bytes3[2] & 0x3f;

    for (iIdx2= 0; iIdx2 < iIdx + 1; iIdx2++)
    	strOutput += CBase64[bytes4[iIdx2]];

    while((iIdx++ < 3))
    	strOutput += '=';

  }
}
/*************************************************************************/
void MiscTools::Base64ToBinary(const String& strInput, unsigned char *sData, size_t iBufferLen, size_t &iDataLen){

  int iLeft = strInput.size();
  int i = 0;
  int j = 0;
  int ii = 0;
  unsigned char bytes4[4], bytes3[3];

  iDataLen = 0;

  while (iLeft-- && ( strInput[ii] != '=') && isBase64((unsigned char)strInput[ii])) {
    bytes4[i++] = strInput[ii]; ii++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        bytes4[i] = CBase64.find(bytes4[i]);

      bytes3[0] = (bytes4[0] << 2) + ((bytes4[1] & 0x30) >> 4);
      bytes3[1] = ((bytes4[1] & 0xf) << 4) + ((bytes4[2] & 0x3c) >> 2);
      bytes3[2] = ((bytes4[2] & 0x3) << 6) + bytes4[3];

      iDataLen += 3;

      if(iDataLen > iBufferLen)
    	  IAS_THROW(BadUsageException("Error when coping streams."));


      for (i = 0; (i < 3); i++)
    	  *sData++ = bytes3[i];


      i = 0;
    }
  }



  if (i) {
    for (j = i; j <4; j++)
      bytes4[j] = 0;

    for (j = 0; j <4; j++)
      bytes4[j] = CBase64.find(bytes4[j]);

    bytes3[0] = (bytes4[0] << 2) + ((bytes4[1] & 0x30) >> 4);
    bytes3[1] = ((bytes4[1] & 0xf) << 4) + ((bytes4[2] & 0x3c) >> 2);
    bytes3[2] = ((bytes4[2] & 0x3) << 6) + bytes4[3];

    for (j = 0; (j < i - 1); j++){
    	iDataLen++;

        if(iDataLen > iBufferLen)
          IAS_THROW(BadUsageException("Error when coping streams."));

        *sData++ = bytes3[j];
    }

  }

}

/*************************************************************************/
void MiscTools::Base64ToString(const String& strInput, String& strOutput){

	  int iLeft = strInput.size();
	  int i = 0;
	  int j = 0;
	  int ii = 0;
	  unsigned char bytes4[4], bytes3[3];

	  while (iLeft-- && ( strInput[ii] != '=') && isBase64((unsigned char)strInput[ii])) {
	    bytes4[i++] = strInput[ii]; ii++;
	    if (i ==4) {
	      for (i = 0; i <4; i++)
	        bytes4[i] = CBase64.find(bytes4[i]);

	      bytes3[0] = (bytes4[0] << 2) + ((bytes4[1] & 0x30) >> 4);
	      bytes3[1] = ((bytes4[1] & 0xf) << 4) + ((bytes4[2] & 0x3c) >> 2);
	      bytes3[2] = ((bytes4[2] & 0x3) << 6) + bytes4[3];

	      for (i = 0; (i < 3); i++)
	    	  strOutput += bytes3[i];
	      i = 0;
	    }
	  }

	  if (i) {
	    for (j = i; j <4; j++)
	      bytes4[j] = 0;

	    for (j = 0; j <4; j++)
	      bytes4[j] = CBase64.find(bytes4[j]);

	    bytes3[0] = (bytes4[0] << 2) + ((bytes4[1] & 0x30) >> 4);
	    bytes3[1] = ((bytes4[1] & 0xf) << 4) + ((bytes4[2] & 0x3c) >> 2);
	    bytes3[2] = ((bytes4[2] & 0x3) << 6) + bytes4[3];

	    for (j = 0; (j < i - 1); j++) strOutput += bytes3[j];
	  }

}

static std::locale aLocale(EnvTools::GetEnv("LANG").c_str());

class LocaleSetter{
	LocaleSetter(){
		std::setlocale(LC_CTYPE, aLocale.name().c_str());
	}
static LocaleSetter TheLocaleSetter;
};

LocaleSetter LocaleSetter::TheLocaleSetter;

/*************************************************************************/
String MiscTools::StrToLower(const String& strData){

	IAS_TRACER;

	size_t strLen = strData.size();

	char    result[strLen * 2];
	wchar_t wide[strLen * 2];

	if(std::mbstowcs(wide, strData.c_str(), strLen+1) == -1)
		IAS_THROW(BadUsageException("StrToLower: " + strData));

	for (int i = 0; i < strLen; ++i) wide[i] =
			tolower(wide[i], aLocale);

	std::wcstombs(result, wide, strLen+1);

	return result;
}

/*************************************************************************/
String MiscTools::StrToUpper(const String& strData){

	IAS_TRACER;

	size_t strLen = strData.size();

	char    result[strLen * 2];
	wchar_t wide[strLen * 2];

	if(std::mbstowcs(wide, strData.c_str(), strLen+1) == -1)
		IAS_THROW(BadUsageException("StrToUpper: " + strData));

	for (int i = 0; i < strLen; ++i) wide[i] =
		toupper(wide[i], aLocale);

	std::wcstombs(result, wide, strLen+1);

	return result;

}

/*************************************************************************/
}

