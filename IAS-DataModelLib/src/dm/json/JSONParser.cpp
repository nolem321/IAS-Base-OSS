/*
 * File: IAS-DataModelLib/src/dm/json/JSONParser.cpp
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
#include "../../dm/json/JSONParser.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataFactory.h"
#include "../../dm/DataObject.h"
#include "../../dm/DataObjectList.h"
#include "../../dm/json/JSONHelper.h"
#include "../../dm/json/JSONLexer.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Property.h"
#include "../../dm/PropertyList.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
namespace JSON {

const char *JSONParser::C_TypeAttr("_dmType");

/*************************************************************************/
JSONParser::JSONParser(JSONHelper* pJSONHelper, JSONLexer *pJSONLexer):
	iToken(JSONLexer::T_None),
	mm(IAS::MemoryManager::GetInstance(),1024),
	maPairs(&mm),
	maChars(&mm),
	maTables(&mm),
	maMaps(&mm),
	maNode(&mm),
	hmRoot(comparator,maPairs){
	IAS_TRACER;

	this->pJSONHelper=pJSONHelper;
	this->ptrJSONLexer=pJSONLexer;

	pDataFactory=pJSONHelper->getDataFactory();
}
/*********************************JSONParser****************************************/
JSONParser::~JSONParser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void JSONParser::buildValuesTable(ValuesTable *pValues){
	IAS_TRACER;

	bool bList=false;



	do{

		iToken=ptrJSONLexer->next();

		if(iToken==JSONLexer::T_LeftBracket){
			if(bList)
				IAS_THROW(JSONHelperException("List in lists are not supported"));
			bList=true;
			iToken=ptrJSONLexer->next();
		}

		switch(iToken){

			case JSONLexer::T_LeftBrace:
				IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"DataObject");
				{
					ValuesMap* pNewMap= new (maMaps.allocate(1)) ValuesMap(comparator,maPairs);
					buildTree(pNewMap);
					pValues->push_back(pNewMap);
				}
				iToken=ptrJSONLexer->next();
			break;

			case JSONLexer::T_StringValue:
				pValues->push_back(copyStringValue());
				iToken=ptrJSONLexer->next();
			break;

			case JSONLexer::T_NumericValue:
			case JSONLexer::T_BooleanValue:
					pValues->push_back(copyValue());
					iToken=ptrJSONLexer->next();
			break;

			case JSONLexer::T_Null:
				IAS_THROW(JSONHelperException("Not implemented value type."));
			break;
		}


	}while(iToken == JSONLexer::T_Comma && bList);

	if(bList){
		if(iToken != JSONLexer::T_RightBracket)
			IAS_THROW(JSONHelperException("Closing bracket is missing."));
		iToken=ptrJSONLexer->next();
	}

}
/*************************************************************************/
void JSONParser::buildTree(ValuesMap *pMap){
	IAS_TRACER;

	iToken=ptrJSONLexer->next();

	bool bFirst=true;
	while(iToken == JSONLexer::T_StringValue){

		char *sName=copyStringValue();

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Name:"<<sName);
		ptrJSONLexer->asset(JSONLexer::T_Colon);

		ValuesTable *pTable= new (maTables.allocate(1)) ValuesTable(maNode);
		buildValuesTable(pTable);
		(*pMap)[sName]=pTable;
		if(iToken == JSONLexer::T_Comma)
			iToken=ptrJSONLexer->next();
	}

	if(iToken != JSONLexer::T_RightBrace)
		IAS_THROW(JSONHelperException("Right brace expected."));

}
/*************************************************************************/
char* JSONParser::copyValue(){
	IAS_TRACER;

	const String& strValue=ptrJSONLexer->getCharValue();
	char *sCopy=(char*)mm.allocate(strValue.length()+1);
	strncpy(sCopy,strValue.c_str(),strValue.length()+1);
	return sCopy;
}
/*************************************************************************/
char* JSONParser::copyStringValue(){
	IAS_TRACER;

	const String& strValue=ptrJSONLexer->getCharValue();
	/*
	 * Looks that the escaping bellow is slow and
	 * it is better to do pre-check.
	 */
	if(strValue.find('\\') == String::npos)
        return copyValue();

	char *sCopy=(char*)mm.allocate(strValue.length()+1);

	/*
	 * There is enough room since the result can only be shorter.
	 * Is buffer overflow possible with std::string.c_str() ?
	 */

	const char *sOrig = strValue.c_str();
	char *sDest=sCopy;

	while(*sOrig)
		if(*sOrig != '\\'){
			*sDest++=*sOrig++;
		}else{
			sOrig++;
			switch(*sOrig++){
				case 'n': *sDest++='\n'; break;
				case 'r': *sDest++='\r'; break;
				case 't': *sDest++='\t'; break;
				case '"': *sDest++='"'; break;
				case '\\': *sDest++='\\'; break;
				default:
					*sDest++=0;
					IAS_THROW(JSONHelperException(String("Unknown escape sequence after: ")+sCopy));
			}
		}

	*sDest++=0;

	return sCopy;
}
/*************************************************************************/
DM::DataObject* JSONParser::buildObject(const Node& node, const DM::Type* pTypeHint){
	IAS_TRACER;

	//TODO some concept to store subtypes of basic types.

	if(pTypeHint && !pTypeHint->isDataObjectType()){
		if(node.getType() == Node::T_Value)
			return pTypeHint->createDataObject(node.getValue());
		else{
			pTypeHint=getDMType(node.getMap());
			if(pTypeHint){
				ValuesMap::const_iterator it=node.getMap()->find("_value");

				if(it == node.getMap()->end())
					IAS_THROW(JSONHelperException("No type hint for a simple type."));

				return pTypeHint->createDataObject(it->second->getFirst().getValue());
			}else
				IAS_THROW(JSONHelperException("No type hint for a simple type."));
		}
	}

	String strType;
	String strURI;

	Impl::DataAllocator<DataObject>::PtrHolder dm;

	ValuesMap *pMap=node.getMap();

	const DM::Type* pMapType=getDMType(pMap);

	if(pMapType)
		pTypeHint=pMapType;

	if(!pTypeHint)
		IAS_THROW(JSONHelperException("No type hint for a complex type."));

	dm = pTypeHint->createDataObject();

	const DM::ComplexType *pComplexType=pTypeHint->asComplexType();
	const DM::PropertyList& lstProperties=pComplexType->getProperties();

	for(int iIdx=0; iIdx<lstProperties.getSize();iIdx++){
		const DM::Property *pProperty=lstProperties[iIdx];

		if((*pMap).count(pProperty->getName().c_str())){

			ValuesMap::const_iterator it = (*pMap).find(pProperty->getName().c_str());

			if(it == (*pMap).end())
				IAS_THROW(InternalException("JSON empty values table (!) ?"))

			const ValuesTable* pValues=it->second;

			if(pValues->empty())
				IAS_THROW(InternalException("JSON empty values table ?"))

			if(pProperty->isMulti()){
				DataObjectList& lstDM=dm->getList(pProperty);
				for(ValuesTable::const_iterator it=pValues->begin(); it != pValues->end(); it++)
					lstDM.add(buildObject(*it, pProperty->getType()));

				}else{
					dm->setDataObject(pProperty,buildObject(*(pValues->begin()), pProperty->getType()));
				}
		}/* IF: JSON has a value */

	}/* FOR: properties */

	return dm.pass();
}
/*************************************************************************/
const DM::Type* JSONParser::getDMType(ValuesMap *pMap)const{
	IAS_TRACER;

	String strType;
	String strURI;

	if( (*pMap).count(C_TypeAttr) && ! (*pMap)[C_TypeAttr]->empty() ){
		String strValue( (*pMap)[C_TypeAttr]->getFirst().getValue() );
		TypeTools::ChopArguments(strValue,strURI,strType,'#');

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Check type:"<<strURI<<" : "<<strType);

		return pDataFactory->getType(strURI,strType);
	}else
		return NULL;
}
/*************************************************************************/
DM::DataObject* JSONParser::parse(const DM::Type* pTypeHint){
	IAS_TRACER

	ptrJSONLexer->asset(JSONLexer::T_LeftBrace);
	buildTree(&hmRoot);

	const DM::Type *pType=getDMType(&hmRoot);

	if(!pType)
		pType=pTypeHint;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Type hint: "<<(pType ? pType->getFullName() : "null"));

	return buildObject(&hmRoot,pType);
}
/*************************************************************************/
}
}
}
