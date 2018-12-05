/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Wrapper.h
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
#ifndef _IAS_QS_Proc_Workers_DS_Wrapper_Wrapper_H_
#define _IAS_QS_Proc_Workers_DS_Wrapper_Wrapper_H_

#include <commonlib/commonlib.h>
#include <ds/api.h>

#include <dm/tools/Setter.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {
class Lexer;

/*************************************************************************/
/** The Wrapper class.
 *
 */
class Wrapper {
public:

	virtual ~Wrapper() throw();

	virtual void execute(::IAS::DM::DataObjectPtr& dm)=0;

	static Wrapper* Create(::IAS::DS::API::Session* pSession,
							   const String& strSpecification,
							   const ::IAS::DM::DataFactory* pDataFactory,
							   ::IAS::DM::DataObject* dm);

	typedef IAS_DFT_FACTORY<Wrapper>::PtrHolder PtrHolder;

  void setReusable(bool bReusable){ this->bReusable = bReusable; }
	bool isReusable()const{ return bReusable; }

protected:
	Wrapper();
	friend class Factory<Wrapper>;


	String strSQLText;

	/*************************************************************************/

	class SettersTable {
	public:
		SettersTable(const ::IAS::DM::Type* pType);
		~SettersTable();

		typedef std::vector<String>         TagsTable;

		enum Mode{
			M_INPUT,
			M_OUTPUT,
			M_INPUT_OUTPUT
		};

		const String& addXPath(const String& strXPath, Mode iMode=M_INPUT);

		void bind(::IAS::DS::API::IInput* pIInput);
		void bindIO(::IAS::DS::API::IOutput* pIOutput);

		const TagsTable&  getTags()const{ return tabTags; }

	protected:

		typedef std::vector<DM::Tools::Setter*> SettersVector;
		typedef std::vector<Mode>                ModesVerctor;

		SettersVector         tabSetters;
		TagsTable              tabTags;
		ModesVerctor           tabModes;

		const ::IAS::DM::Type* pType;
		PtrCleaner< SettersVector, IAS_DFT_FACTORY<DM::Tools::Setter>::Deleter > _inputCleaner;
	};

	/*************************************************************************/

	class ResultSetSettersTable {
	public:
		ResultSetSettersTable(const ::IAS::DM::Type* pType);
		~ResultSetSettersTable();

		int addXPath(const String& strXPath, bool bOptional);
		void bind(::IAS::DS::API::IResultSetOutput* pResultSetOutput);

		void setType(const ::IAS::DM::Type* pType);

		DM::Tools::Setter* operator[](int iIdx){
			return tabSetters[iIdx];
		}

		size_t size()const{ return tabSetters.size(); }

		DM::DataObjectPtr dm;

		const ::IAS::DM::Type* getType()const{ return pType; }

	protected:

		typedef std::vector<DM::Tools::Setter*> SettersVector;
		typedef std::vector<bool>                OptionalVector;

		SettersVector                           tabSetters;
		OptionalVector                          tabOptional;

		const ::IAS::DM::Type* pType;
		PtrCleaner< SettersVector, IAS_DFT_FACTORY<DM::Tools::Setter>::Deleter > _inputCleaner;
	};

	/*************************************************************************/

	void handleWhere(Lexer *pLexer,
					 SettersTable& tabInputSetters,
					 DM::DataObject* dm);

	void handleWhereCondition(Lexer *pLexer,
							  SettersTable& tabInputSetters,
							  DM::DataObject* dm,
							  bool bOptional);


	TimeSamplesResults tsrExe;

	bool bReusable;
};
/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Proc_Workers_DS_Wrapper_Wrapper_H_ */
