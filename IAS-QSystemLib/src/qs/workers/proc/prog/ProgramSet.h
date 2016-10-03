/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/ProgramSet.h
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
#ifndef _IAS_QS_Workers_Proc_Prog_ProgramSet_H_
#define _IAS_QS_Workers_Proc_Prog_ProgramSet_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>

#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>


#include "../io/IOManager.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Prog {

/*************************************************************************/
/** The ProgramSet class.
 *
 */
class ProgramSet {
public:

	virtual ~ProgramSet() throw();

	class ResultHandler{
	public:
		virtual ~ResultHandler(){};

		virtual void handle(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							::IAS::Lang::Interpreter::Exe::ProgramContext *pProgramContext)=0;

		virtual void handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									 ::IAS::Lang::Interpreter::Exe::ProgramContext *pProgramContext,
									 ::IAS::Lang::Interpreter::Exe::InterpreterProgramException& e)=0;
	};

	void addProgram(const ::IAS::Lang::Interpreter::Exe::Program *pProgram,
					const String& strName);

	virtual void execute(const String& strProgramName,
						 ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						  DM::DataObject* dmData);

	virtual unsigned int execute(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 DM::DataObject* dmData);

	const ::IAS::Lang::Interpreter::Exe::Program *getProgram(const String& strProgramName)const;

	void setResultHandler(ResultHandler *pResultHandler);

protected:

	Mutex mutex;

	ProgramSet(const ::IAS::DM::DataFactory *pDataFactory, ResultHandler *pResultHandler = 0);

	struct StatsEntry{
		StatsEntry(const String& strName):strName(strName){};
		virtual ~StatsEntry(){};

		String strName;
		TimeSamplesResults tsrLoad;
		TimeSamplesResults tsrExe;
	};

	const ::IAS::DM::DataFactory *pDataFactory;

	typedef HashMapOfPointers< const ::IAS::Lang::Interpreter::Exe::Program *, StatsEntry> ProgramMap;
	ProgramMap   hmPrograms;

	typedef HashMapWithStringKey< const ::IAS::Lang::Interpreter::Exe::Program* > ProgramByNameMap;
	ProgramByNameMap								   		                      hmProgramByName;

	bool match(const ::IAS::Lang::Interpreter::Exe::Program *pProgram,
				   const ::IAS::DM::Type* pCtxType,
				   const ::IAS::DM::Type* pDataType);

	virtual void execute(const ::IAS::Lang::Interpreter::Exe::Program *pProgram,
			 	 	 ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
			 	 	 DM::DataObject* dmData);

	IAS_DFT_FACTORY<ResultHandler>::PtrHolder ptrResultHandler;

	friend class Factory<ProgramSet>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_Prog_ProgramSet_H_ */
