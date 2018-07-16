/*
 * File: IAS-DataModelLib/src/dm/urlenc/URLEncodeHelper.cpp
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
#include "../../dm/urlenc/URLEncodeHelper.h"
#include "../../dm/urlenc/exception/URLEncodeHelperException.h"
#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Property.h"
#include "../../dm/PropertyList.h"
#include "../../dm/Type.h"

#include <algorithm>

namespace IAS {
namespace DM {
namespace URLEnc {

/*************************************************************************/
const String URLEncodeHelper::C_MockURLPrefix(":///?");
/*************************************************************************/
URLEncodeHelper::URLEncodeHelper(const ::IAS::DM::DataFactory *pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
}
/*************************************************************************/
URLEncodeHelper::~URLEncodeHelper() throw(){
	IAS_TRACER;

}
/*************************************************************************/
DM::DataObjectPtr URLEncodeHelper::load(std::istream& is, const DM::Type* pTypeHint){

	IAS_TRACER;

  StringStream ss;
  ss << C_MockURLPrefix << is.rdbuf();
  URI uri(ss.str());

	Impl::DataAllocator<DataObject>::PtrHolder dm;

	if(!pTypeHint)
		IAS_THROW(URLEncodeHelperException("No type hint for a complex type."));

	dm = pTypeHint->createDataObject();

	const DM::ComplexType *pComplexType=pTypeHint->asComplexType();
	const DM::PropertyList& lstProperties=pComplexType->getProperties();

	for(int iIdx=0; iIdx<lstProperties.getSize();iIdx++){
		const DM::Property *pProperty=lstProperties[iIdx];
    String propName(pProperty->getName());
		
    if(uri.hasValue(propName)){
      
      if(pProperty->isMulti()){
        IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"Property '" << propName << "' has maxOccurs > 1");
        IAS_THROW(URLEncodeHelperException("Multivalues not implemented in URLEncode."));
      }else{
        const DM::Type* eltType(pProperty->getType());
        if(eltType->isDataObjectType()) {
          IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"Property '" << propName << "' is of complex type");
          IAS_THROW(URLEncodeHelperException("Nested structures not implemented in URLEncode."));
        } else {
          String eltValue(uri.getValue(propName));
          IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Property '" << propName << "' found with value='" << eltValue << "'");
          dm->setDataObject(pProperty, eltType->createDataObject(eltValue));
        }
      }
		} else {
      IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Property '" << propName << "' not found");
    }

	}/* FOR: properties */

	return dm.pass();
}
/*************************************************************************/
void URLEncodeHelper::save(std::ostream& os,
		   const ::IAS::DM::DataObject *pDataObject,
		   bool  bXSIType){
	IAS_TRACER;

  URI uri;
	const ::IAS::DM::Type* pType = pDataObject->getType();

  if (pType->getTypeEnum() != ::IAS::DM::Type::DataObjectType) {
    IAS_THROW(URLEncodeHelperException("Not a DataObject in root for URLEncoding."));
  } else {
	  const DataObject *pChild = NULL;
    const ::IAS::DM::PropertyList &lstProperties = pType->asComplexType()->getProperties();
    for(int iIdx=0; iIdx<lstProperties.getSize();iIdx++){
      const DM::Property *pProperty=lstProperties[iIdx];
      String propName(pProperty->getName());
			if(pProperty->isMulti()){
        IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"Property '" << propName << "' has maxOccurs > 1");
        IAS_THROW(URLEncodeHelperException("Multivalues not implemented in URLEncode."));
      } else {
        if(pDataObject->isSet(pProperty) && (pChild = pDataObject->getDataObject(pProperty)) != NULL) {
          uri.addValue(propName, pChild->toString());
        }
      }
    }
  }

  if (uri.begin() == uri.end()) {
    return;
  }

  String strURI(uri.getURIString());
  
  if (strURI.compare(0, C_MockURLPrefix.size(), C_MockURLPrefix) != 0){
    IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),strURI);
    IAS_THROW(InternalException("Unexpected URI serialization result!"));
  } else {
    os << strURI.substr(C_MockURLPrefix.size());
  }
}
/*************************************************************************/
}
}
}
