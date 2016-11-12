/*
 * File: Template.cpp
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

#include "Template.h"


namespace IAS {
namespace QS {
namespace Tools {

/*************************************************************************/
Template::Template(const String& strPattern):
	::IAS::Template(strPattern){
	IAS_TRACER;
}
/*************************************************************************/
Template::~Template() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Template::Arguments::Arguments(const DM::DataObject* dmData, Arguments* pParentArguments , size_t iIdx):
	::IAS::Template::Arguments(pParentArguments),
		dmData(dmData),
		iIdx(iIdx){

	IAS_TRACER;
	IAS_CHECK_IF_NULL(dmData);
}
/*************************************************************************/
Template::Arguments::~Arguments(){}
/*************************************************************************/
bool Template::Arguments::getImpl(const String& strKey, String& strValue) {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"key: "<<strKey);

	if(strKey.compare("_index") == 0) {
		strValue = TypeTools::IntToString(iIdx);
		return true;
	}

	if(strKey.compare("_index1") == 0) {
		strValue = TypeTools::IntToString(iIdx+1);
		return true;
	}

	try{
		if(!dmData->isSet(strKey))
			return false;
	}catch(ItemNotFoundException& e){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"unknow property: "<<strKey);
		return false;
	}

	strValue = dmData->getString(strKey);

	return true;
}
/*************************************************************************/
Template::Arguments* Template::Arguments::createNestedImpl(const String& strKey) {

	IAS_TRACER

	if(!dmData->isSet(strKey))
		IAS_THROW(ItemNotFoundException(strKey));

	return IAS_DFT_FACTORY<Arguments>::Create(dmData->getDataObject(strKey),this);
}
/*************************************************************************/
size_t Template::Arguments::getNestedCount(const String& strKey) {

	IAS_TRACER;

	if (hmNested.count(strKey) == 0 && dmData->isSet(strKey)) {

		const DM::DataObjectList& lstData(dmData->getList(strKey));
		hmNested[strKey] = IAS_DFT_FACTORY<NestedEntry>::Create();

		for (int iIdx = 0; iIdx < lstData.size(); iIdx++)
		hmNested[strKey]->push(IAS_DFT_FACTORY<Arguments>::Create(lstData.at(iIdx),this,iIdx));

	}

	return IAS::Template::Arguments::getNestedCount(strKey);
}
/*************************************************************************/
}
}
}
