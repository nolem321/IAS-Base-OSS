/*
 * File: IAS-QSystemLib/src/qs/workers/proc/GlobalContext.h
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
#ifndef _IAS_QS_Workers_Proc_GlobalContext_H_
#define _IAS_QS_Workers_Proc_GlobalContext_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/spec/Specification.h>


namespace IAS {
namespace QS {
namespace Fmt{
class FmtFactory;
}

namespace Workers {
namespace Proc {
namespace Logic{
class LogicFactory;
}

namespace Cache{
class CacheStore;
}

namespace EC{
class EventCounterStore;
}

namespace Stats{
class LogicStatsStore;
class PublisherStore;
}

namespace Dict{
class DictionaryStore;
}

class ProgramProvider;

/*************************************************************************/
/** The GlobalContext class.
 *
 */
class GlobalContext {
public:

	class Parameters{
		public:

			virtual ~Parameters(){};

			virtual unsigned int getNumThreads()const = 0;
			virtual unsigned int getOffset()    const = 0;
			virtual unsigned int getNumMessages()   const = 0;
			virtual unsigned int getCommitCount()   const = 0;

			virtual bool hasModeSpecs()const=0;
			virtual const String& getModeSpecs()const  = 0;

			virtual bool hasInputSpecs()const=0;
			virtual const String& getInputSpecs()const  = 0;

			virtual bool hasOutputSpecs()const=0;
			virtual const String& getOutputSpecs()const = 0;

			virtual bool hasLogicSpecs()const=0;
			virtual const String& getLogicSpecs()const  = 0;

			virtual bool hasDataSourceSpecs()const=0;
			virtual const String& getDataSourceSpecs()const = 0;

			virtual bool hasTXMSpecs()const=0;
			virtual const String& getTXMSpecs()const = 0;

			virtual bool hasCacheSpecs()const=0;
			virtual const String& getCacheSpecs()const = 0;

			virtual bool hasEventCounterSpecs()const=0;
			virtual const String& getEventCounterSpecs()const = 0;

			virtual bool hasStatsPublishersSpecs()const=0;
			virtual const String& getStatsPublishersSpecs()const = 0;

			virtual bool hasFullConfig()const=0;
			virtual const String& getFullConfig()const=0;

			virtual const StringList& getLogicParameters()const=0;
	};

	virtual ~GlobalContext() throw();
	const ::IAS::DM::DataFactory *getDataFactory()const;

	bool allDone();
	void abort();

	ProgramProvider* getProgramProvider();

	const Fmt::FmtFactory* getFmtFactory()const;

	Logic::LogicFactory* getLogicFactory() const;

	Cache::CacheStore*       getCacheStore() const;
	EC::EventCounterStore*   getEventCounterStore() const;
	Stats::LogicStatsStore*  getLogicStatsStore() const;

	Dict::DictionaryStore*   getDictionaryStore() const;

	const ::org::invenireaude::qsystem::workers::spec::Specification* getSpecification()const;

	static void Start(const Parameters* pParameters);

	void getProgress(unsigned int& iMsgLeft, unsigned int& iMsgTotal);

protected:

	Mutex mutex;

	GlobalContext(const Parameters* pParameters);

	unsigned int iMsgLeft;
	unsigned int iMsgTotal;
	bool         bAbort;

	::IAS::DM::DataFactory* ptrDataFactory;

	IAS_DFT_FACTORY< ProgramProvider >::PtrHolder ptrProgramProvider;
	IAS_DFT_FACTORY< Fmt::FmtFactory >::PtrHolder ptrFmtFactory;

	IAS_DFT_FACTORY< Cache::CacheStore      >::PtrHolder    ptrCacheStore;
	IAS_DFT_FACTORY< EC::EventCounterStore  >::PtrHolder    ptrEventCounterStore;
	IAS_DFT_FACTORY< Stats::PublisherStore >::PtrHolder     ptrStatsPublisherStore;

	IAS_DFT_FACTORY< Dict::DictionaryStore >::PtrHolder     ptrDictionaryStore;
	IAS_DFT_FACTORY<Logic::LogicFactory>::PtrHolder         ptrLogicFactory;

	::org::invenireaude::qsystem::workers::spec::Ext::SpecificationPtr dmSpecification;

	::org::invenireaude::qsystem::workers::spec::Ext::SpecificationPtr readParameters(const Parameters* pParameters)const;

	void loadXSD();

	static void InitializeDataFactories();

	friend class Factory<GlobalContext>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_GlobalContext_H_ */
