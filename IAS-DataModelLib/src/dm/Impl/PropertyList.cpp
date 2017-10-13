/*
 * File: IAS-DataModelLib/src/dm/Impl/PropertyList.cpp
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
#include "../../dm/Impl/PropertyList.h"
#include <commonlib/commonlib.h>

#include "../../dm/Impl/Property.h"
#include "../../dm/log/LogLevel.h"
#include "../Type.h"

namespace IAS {
namespace DM {
namespace Impl {


/*************************************************************************/
PropertyList::HashMapKey::HashMapKey(const String& strValue):String(strValue){
	//std::hash<const char*> h;
	//iHash = h.operator ()(strValue.c_str());

	iHash = 0;
	for(const char* s = strValue.c_str(); *s != 0; s++)
		  iHash = (iHash * 131) + *s;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Hash["<<strValue<<"]="<<iHash);
}
/*************************************************************************/

size_t PropertyList::HashMapKeyHash::operator()(const HashMapKey& k1) const{
	return k1.iHash;
}


/*************************************************************************/
bool PropertyList::HashMapKeyEq::operator()(const HashMapKey& k1, const HashMapKey& k2) const{

	if(k1.iHash != k2.iHash)
		return false;

	return k1.compare(k2) == 0;
}
/*************************************************************************/
::IAS::DM::Property* PropertyList::getProperty(const String& strName)const{
	IAS_TRACER;
	HashMapKey aKey(strName);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"getProperty["<<strName<<"]:"<<hmPropertiesByName.count(aKey));

	if(hmPropertiesByName.count(aKey) == 0)
		IAS_THROW(ItemNotFoundException("getProperty:" + strName + " in " + pType->getFullName()));

	return hmPropertiesByName.find(aKey)->second;
}

/*************************************************************************/
PropertyList::PropertyList(const DM::Type *pType):
	pType(pType){
	IAS_TRACER;
}
/*************************************************************************/
PropertyList::~PropertyList() throw(){
	IAS_TRACER;

	for(PropertiesTab::iterator it = tabProperties.begin();
		it != tabProperties.end();
		it++){
		ModelAllocator< ::IAS::DM::Property >::Free(*it);
	}
}
/*************************************************************************/
::IAS::DM::Property* PropertyList::getProperty(int iIdx)const{
	IAS_TRACER;
	if(iIdx < 0 || iIdx > tabProperties.size() - 1)
		IAS_THROW(ItemNotFoundException("getProperty"));

	return tabProperties[iIdx];
}
/*************************************************************************/
int PropertyList::getSize() const{
	return tabProperties.size();
}
/*************************************************************************/
void PropertyList::append(::IAS::DM::Property *pProperty){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pProperty);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"append("<<pProperty->getName()<<") at "<<tabProperties.size()<<".");

	HashMapKey aKey(pProperty->getName());

	if(hmPropertiesByName.count(aKey) > 0)
		IAS_THROW(ItemNotFoundException(String("Property exists:")+=pProperty->getName()));


	hmPropertiesByName[pProperty->getName()]=pProperty;
	tabProperties.push_back(pProperty);
}
/*************************************************************************/
}
}
}
