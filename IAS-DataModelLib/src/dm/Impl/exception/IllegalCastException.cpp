/*
 * File: IAS-DataModelLib/src/dm/Impl/exception/IllegalCastException.cpp
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
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include <commonlib/commonlib.h>

#include "../../../dm/Impl/Type.h"

namespace IAS{
namespace DM {
namespace Impl {

/*************************************************************************/
IllegalCastException::IllegalCastException(const String& strTypeSrc,
													  const String& strTypeDst){
	IAS_TRACER;

	String strTmp(strTypeSrc);
	strTmp+="->";
	strTmp+=strTypeDst;
	this->setInfo(strTmp);
}
/*************************************************************************/
IllegalCastException::IllegalCastException(const ::IAS::DM::Type* pTypeSrc,
													   const String& strTypeDst){
	IAS_TRACER;

	String strTmp;

	if(pTypeSrc != NULL){
		strTmp+=pTypeSrc->getURI();
		strTmp+=":";
		strTmp+=pTypeSrc->getName();
	}else{
		strTmp+="?null?";
	}

	strTmp+="->";
	strTmp+=strTypeDst;

	this->setInfo(strTmp);
}

/*************************************************************************/
IllegalCastException::IllegalCastException(const ::IAS::DM::Type* pTypeSrc,
													  const ::IAS::DM::Type* pTypeDst){
	IAS_TRACER;

	String strTmp;

	if(pTypeSrc != NULL){
		strTmp+=pTypeSrc->getURI();
		strTmp+=":";
		strTmp+=pTypeSrc->getName();
	}else{
		strTmp+="?null?";
	}

	strTmp+="->";

	if(pTypeDst != NULL){
		strTmp+=pTypeDst->getURI();
		strTmp+=":";
		strTmp+=pTypeDst->getName();
	}else{
		strTmp+="?null?";
	}

	this->setInfo(strTmp);

}


/*************************************************************************/
IllegalCastException::~IllegalCastException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* IllegalCastException::getName(){
	IAS_TRACER;
	return "IllegalCastException";
}


/*************************************************************************/

} /* namespace Impl */
} /* namespace DM */
} /* namespace IAS */
