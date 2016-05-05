/*
 * File: IAS-QSystemExe/src/parameters/ProcessorParameters.h
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
#ifndef _IAS_QS_Parameters_ProcessorParameters_H_
#define _IAS_QS_Parameters_ProcessorParameters_H_

#include "ProgramParameters.h"
#include <climits>

#include <qs/workers/proc/GlobalContext.h>

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
/** The ProcessorParameters class.
 *
 */
class ProcessorParameters :
		public ::IAS::QS::Workers::Proc::GlobalContext::Parameters,
		public ::IAS::QS::Parameters::ProgramParameters{
public:

	virtual ~ProcessorParameters() throw();

	virtual bool hasModeSpecs()const;
	virtual const String& getModeSpecs()const;

	virtual bool hasInputSpecs()const;
	virtual bool hasOutputSpecs()const;
	virtual bool hasLogicSpecs()const;
	virtual bool hasDataSourceSpecs()const;
	virtual bool hasTXMSpecs()const;
	virtual bool hasCacheSpecs()const;
	virtual bool hasEventCounterSpecs()const;
	virtual bool hasStatsPublishersSpecs()const;


	virtual const String& getInputSpecs()const;
	virtual const String& getOutputSpecs()const;
	virtual const String& getLogicSpecs()const;
	virtual const String& getDataSourceSpecs()const;
	virtual const String& getTXMSpecs()const;
	virtual const String& getCacheSpecs()const;
	virtual const String& getEventCounterSpecs()const;
	virtual const String& getStatsPublishersSpecs()const;

	virtual bool hasFullConfig()const;
	virtual const String& getFullConfig()const;

	static const long   C_MaxMessages = 0x7fffffff /*TODO (LL) eclipse warning UINT_MAX & inconsistent types*/;
	static const String C_DefaultMode;

	virtual unsigned int getNumThreads()const;
	virtual unsigned int getOffset()    const;
	virtual unsigned int getNumMessages()   const;
	virtual unsigned int getCommitCount()   const;



	virtual const StringList& getLogicParameters()const;

protected:
	ProcessorParameters(int argc, char* argv[]);

	virtual void printCmdDesc(std::ostream& os) const;
	virtual void printArgsDesc(std::ostream& os) const;

	friend class ::IAS::Factory<ProcessorParameters>;

	static const String C_strEmpty;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_ProcessorParameters_H_ */
