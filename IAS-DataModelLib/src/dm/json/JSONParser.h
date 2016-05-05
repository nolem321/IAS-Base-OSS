/*
 * File: IAS-DataModelLib/src/dm/json/JSONParser.h
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
#ifndef _IAS_DM_JSON_JSONPARSER_H_
#define _IAS_DM_JSON_JSONPARSER_H_

#include <commonlib/commonlib.h>

#include <commonlib/memory/mm/RegionMemoryManager.h>

#include <list>
#include "JSONLexer.h"

#include <string.h>
#include "../../dm/DataObject.h"
#include "../../dm/json/JSONLexer.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
class DataFactory;
class DataObject;

namespace JSON {
class JSONHelper;
class JSONLexer;


/*************************************************************************/
/** The class. */
 class JSONParser {
public:

	virtual ~JSONParser() throw();


	DM::DataObject* parse(const DM::Type* pTypeHint=NULL);

protected:

	JSONParser(JSONHelper* pJSONHelper, JSONLexer *pJSONLexer);

	JSONHelper*   pJSONHelper;
	const DataFactory* pDataFactory;

	IAS_DFT_FACTORY< ::IAS::DM::JSON::JSONLexer >::PtrHolder ptrJSONLexer;

	struct Comparator{
	   bool operator()(char const *a, char const *b)const{
	      return strcmp(a, b) < 0;
	   }
	};

	class ValuesMap;

	struct Node{

		Node(char *sValue){iType=T_Value;pData=sValue;};
		Node(ValuesMap *pValuesMap){iType=T_Map;pData=pValuesMap;};

		Node(const Node& o){
			iType=o.iType;
			pData=o.pData;
		};

		Node& operator=(const Node& o){
			iType=o.iType;
			pData=o.pData;
			return *this;
		};

		enum Type{
			T_Value,
			T_Map,
		};

		inline Type getType()const {return iType;};

		ValuesMap*   getMap()  const {
			if(iType != T_Map)
				IAS_THROW(InternalException("Map node expected."));
			return (ValuesMap*)pData;
		}

		const char*  getValue()const {
			if(iType != T_Value)
				IAS_THROW(InternalException("Value node expected."));
			return (char*)pData;
		}

		void *pData;
		Type iType;
	};


	typedef STLAllocator<char*>  CharsAllocator;
	typedef STLAllocator<Node>   NodeAllocator;

	struct ValuesTable : public std::list<Node, NodeAllocator >{
		inline ValuesTable(NodeAllocator& maNode):
			std::list<Node, NodeAllocator >(maNode){};

		inline const Node& getFirst()const {
			if(size()==0)
				IAS_THROW(InternalException("At least one element expected."));
			return *begin();
		}
	};

	typedef STLAllocator<ValuesTable>                            TablesAllocator;
	typedef STLAllocator< std::pair <const char*,ValuesTable*> > PairsAllocator;

	struct ValuesMap : public std::map<const char*,ValuesTable*,Comparator,PairsAllocator >{
		inline ValuesMap(Comparator&c, PairsAllocator& maPairs):
			std::map<const char*,ValuesTable*,Comparator,PairsAllocator >(c,maPairs){};
	};

	typedef STLAllocator<ValuesMap>         MapsAllocator;


	DM::DataObject* buildObject(const Node& node, const DM::Type* pTypeHint);

	void buildTree(ValuesMap *pMap);
	void buildValuesTable(ValuesTable *pValues);


	char* copyValue();
	char* copyStringValue();

	const DM::Type* getDMType(ValuesMap *pMap)const;

	RegionMemoryManager   mm;
	CharsAllocator        maChars;
	PairsAllocator        maPairs;
	MapsAllocator         maMaps;
	TablesAllocator       maTables;
	NodeAllocator         maNode;

	Comparator        comparator;
	JSONLexer::Token  iToken;
	ValuesMap         hmRoot;

	static const char *C_TypeAttr;

	friend class ::IAS::Factory<JSONParser>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_JSON_JSONPARSER_H_ */
