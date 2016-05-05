/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/Output.h
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
#ifndef _IAS_TCT_Output_H
#define _IAS_TCT_Output_H


#include "commonlib/testcase/TestUnit.h"
#include <org/invenireaude/qsystem/workers/Connection.h>

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "Base.h"

namespace IAS{
namespace TCT{

class Output: public TestUnit, Base {

public:

	virtual ~Output()  throw ();

protected:
	Output(TestSuite* pTestSuite);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<Output> theTestRunner;

	struct Variant{
		int iMsgSize;
		int iNumMsgs;

		bool bSerialize;
		bool bSmallAttrs;
		bool bBigAttrs;
		bool bSend;
	};

	void send(const Variant& v);
	void receive(const Variant& v);
	void iterator(Variant& v);

	void caseAll();

	IAS_DFT_FACTORY<IAS::QS::Workers::Proc::GlobalContext>::PtrHolder ptrGlobalContext;
	IAS_DFT_FACTORY<IAS::QS::Workers::Proc::WCM::WorkContextManager>::PtrHolder ptrWorkContextManager;

	class Parameters : public IAS::QS::Workers::Proc::GlobalContext::Parameters{
			public:

			Parameters(const String& strFullCfg):strFullCfg(strFullCfg){};

				virtual ~Parameters(){};

				virtual unsigned int getNumThreads()const{return 1;};
				virtual unsigned int getOffset()const    {return 0;};
				virtual unsigned int getNumMessages()const{return 1;};
				virtual unsigned int getCommitCount()const{return 1;};

				virtual bool hasModeSpecs()const{return false;};
				virtual const String& getModeSpecs()const{return strEmpty;};

				virtual bool hasInputSpecs()const{return false;};
				virtual const String& getInputSpecs()const{return strEmpty;};

				virtual bool hasOutputSpecs()const{return false;};
				virtual const String& getOutputSpecs()const{return strEmpty;};

				virtual bool hasLogicSpecs()const{return false;};
				virtual const String& getLogicSpecs()const{return strEmpty;};

				virtual bool hasDataSourceSpecs()const{return false;};
				virtual const String& getDataSourceSpecs()const{return strEmpty;};

				virtual bool hasTXMSpecs()const{return false;};
				virtual const String& getTXMSpecs()const{return strEmpty;};

				virtual bool hasCacheSpecs()const{return false;};
				virtual const String& getCacheSpecs()const {return strEmpty;};

				virtual bool hasEventCounterSpecs()const{return false;};
				virtual const String& getEventCounterSpecs()const{return strEmpty;};

				virtual bool hasStatsPublishersSpecs()const{return false;};
				virtual const String& getStatsPublishersSpecs()const{return strEmpty;};

				virtual bool hasFullConfig()const{return true;};
				virtual const String& getFullConfig()const{ return strFullCfg;};

				virtual const StringList& getLogicParameters()const{return lstEmpty;};
				StringList lstEmpty;
				String strEmpty;
				String strFullCfg;
		};

	Parameters parameters;

	friend class ::IAS::Factory<Output>;

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
