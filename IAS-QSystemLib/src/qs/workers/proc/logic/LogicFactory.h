/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/LogicFactory.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_LogicFactory_H_
#define _IAS_QS_Workers_Proc_Logic_LogicFactory_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/Logic.h>
#include <org/invenireaude/qsystem/workers/logic/LogicSpecification.h>

#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {

namespace WCM{
class WorkContextManager;
}

namespace Logic{

class Logic;

//TODO Rethink if Logics should shared per type/parameters ?
/*************************************************************************/
/** The LogicFactory class.
 *
 */
class LogicFactory {
public:

	virtual ~LogicFactory();

	typedef void (*LogicFactoryFeedPtr)(LogicFactory*);

	typedef Logic* (*LogicFactoryFunPtr)(const ::org::invenireaude::qsystem::workers::logic::Logic*, WCM::WorkContextManager*);

	Logic* createLogic(const ::org::invenireaude::qsystem::workers::logic::Logic* dmLogic,
						WCM::WorkContextManager* pWorkContextManager);

	static ::org::invenireaude::qsystem::workers::logic::Ext::LogicSpecificationPtr
		   SpecsToDM(const String& strSpecs,
					  const StringList& lstParameters);


	typedef std::map<const DM::Type*, LogicFactoryFunPtr> FactoriesMap;

	FactoriesMap hmFactories;

	typedef IAS_DFT_FACTORY<Logic>::PtrHolder PtrHolder;

	void registerExternalFactory(const DM::Type* pType, LogicFactoryFunPtr pFactory);

protected:
	LogicFactory();

	void registerExternalLibraires();

	typedef HashMapStringToPointer<SYS::DynamicLibrary> LibrariesMap;
	LibrariesMap                                        hmLibraries;

	friend class Factory<LogicFactory>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_LogicFactory_H_ */
