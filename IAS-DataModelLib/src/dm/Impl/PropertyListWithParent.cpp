/*
 * File: IAS-DataModelLib/src/dm/Impl/PropertyListWithParent.cpp
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
#include "../../dm/Impl/PropertyListWithParent.h"
#include <commonlib/commonlib.h>

#include "../../dm/Impl/Property.h"
#include "../../dm/log/LogLevel.h"
#include "../Type.h"

namespace IAS {
namespace DM {
namespace Impl {
/*************************************************************************/
PropertyListWithParent::PropertyListWithParent(const ::IAS::DM::PropertyList *pParent, const DM::Type *pType):
	PropertyList(pType){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pParent);
	this->pParent=pParent;
	iParentSize = pParent->getSize();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"parentSize="<<iParentSize);
}
/*************************************************************************/
::IAS::DM::Property* PropertyListWithParent::getProperty(const String& strName)const{
	IAS_TRACER;

	HashMapKey aKey(strName);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"getProperty["<<strName<<"]:"<<hmPropertiesByName.count(aKey));

	try{

		if(hmPropertiesByName.count(aKey) == 0)
			return pParent->getProperty(strName);

	}catch(ItemNotFoundException& e){
		IAS_THROW(ItemNotFoundException("getProperty:" + strName + " in " + pType->getFullName()));
	}

	return hmPropertiesByName.find(aKey)->second;
}
/*************************************************************************/
PropertyListWithParent::~PropertyListWithParent() throw(){
	IAS_TRACER;

}
/*************************************************************************/
::IAS::DM::Property* PropertyListWithParent::getProperty(int iIdx)const{
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"getProperty["<<iIdx<<"]:"<<iParentSize<<":"<<tabProperties.size());

	if(iIdx < iParentSize)
		return pParent->getProperty(iIdx);

	if(iIdx >= iParentSize && iIdx < iParentSize + tabProperties.size())
		return tabProperties[iIdx-iParentSize];

	IAS_THROW(ItemNotFoundException("getProperty"));


}
/*************************************************************************/
int PropertyListWithParent::getSize() const{
	return tabProperties.size()+iParentSize;
}
/*************************************************************************/
}
}
}
