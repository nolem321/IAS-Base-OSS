/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/SelectArray.h
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
#ifndef _IAS_QS_Proc_Workers_DS_Wrapper_SelectArray_H_
#define _IAS_QS_Proc_Workers_DS_Wrapper_SelectArray_H_

#include <commonlib/commonlib.h>

#include "Wrapper.h"

#include "Select.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {
class Lexer;

/*************************************************************************/
/** The SelectArray class.
 *
 */
class SelectArray : public Select{
public:

	virtual ~SelectArray() throw();

	virtual void execute(::IAS::DM::DataObjectPtr& dm);

protected:
	SelectArray(::IAS::DS::API::Session* pSession,
		   Lexer *pLexer,
		   const ::IAS::DM::DataFactory* pDataFactory,
		   ::IAS::DM::DataObject* dm);

	class ResultSetSettersTableWithOffset : public ResultSetSettersTable{
	public:
		ResultSetSettersTableWithOffset(const DM::Type* pType);

		void setOffset(int iOffset);
		int getOffset()const;

	protected:
		int iOffset;
	};

	class TypesMap{
 	  public:
		TypesMap()throw();
		ResultSetSettersTableWithOffset& add(const String& strKey, const DM::Type* pType);
		void setDefault(const DM::Type* pType);
		const ResultSetSettersTableWithOffset& getDefault()const;
		const ResultSetSettersTableWithOffset& lookup(const DM::DataObject* dmValue)const;

		typedef ::IAS::MemoryManagerFactory<ResultSetSettersTableWithOffset, StaticCastOperator<ResultSetSettersTableWithOffset> > EntryFactory;

		typedef HashMapStringToPointer<ResultSetSettersTableWithOffset,
									   ::IAS::MemoryManagerFactory< std::pair<String, ResultSetSettersTableWithOffset*> >,
										EntryFactory > EntriesMap;

		void bind(::IAS::DS::API::IResultSetOutput* pResultSetOutput);

 	 protected:

		EntriesMap		hmEntries;

		typedef std::list<ResultSetSettersTableWithOffset*> BindOrderList;
		BindOrderList lstBindOrder;

		EntryFactory::PtrHolder ptrDefault;
	};


	unsigned int iOffset;
	unsigned int iPageSize;

	int          iSkip;
	TypesMap	 hmTypes;

	IAS_DFT_FACTORY<DM::Tools::Setter>::PtrHolder ptrArraySetter;
	IAS_DFT_FACTORY<DM::Tools::Setter>::PtrHolder ptrTypeColumnSetter;

	IAS_DFT_FACTORY<DM::Tools::Setter>::PtrHolder ptrPageSizeSetter;
	IAS_DFT_FACTORY<DM::Tools::Setter>::PtrHolder ptrPageOffsetSetter;

	friend class Factory<SelectArray>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Proc_Workers_DS_Wrapper_SelectArray_H_ */
