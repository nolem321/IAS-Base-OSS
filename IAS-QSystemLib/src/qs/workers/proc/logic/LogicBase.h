/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/LogicBase.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_LogicBase_H_
#define _IAS_QS_Workers_Proc_Logic_LogicBase_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/Logic.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Routing.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include "Logic.h"
#include "../io/Input.h"
#include "../io/Output.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM{
class WorkContextManager;
}

namespace Logic {

/*************************************************************************/
/** The LogicBase class.
 *
 */
class LogicBase :
		public Logic {
public:

	virtual ~LogicBase() throw();

	virtual void receive(bool bNoWait);
	virtual void compute();

	IO::Input   *getInput();
	IO::Output  *getOutput();
	IO::Output  *getError();


protected:
	LogicBase(const ::org::invenireaude::qsystem::workers::logic::Logic* dmLogic,
			  WCM::WorkContextManager*                    pWorkContextManager);

	WCM::WorkContextManager* pWorkContextManager;

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							DM::DataObjectPtr& dmData)=0;

	virtual void computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							API::Message* pMessage);



	void tryError(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
				  DM::DataObjectPtr& dmData,
				  Exception& e);

	void tryError(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
				  API::Message* pMessage,
				  Exception& e);

	String getAttribute(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						const String& strName)const;

	void   setAttribute(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								 const String& strName,
								 const String& strValue)const;


	bool isDM()const{ return bDM; };

private:
	IO::Input  *pInput;
	IO::Output *pOutput;
	IO::Output *pError;

	String strInputName;
	String strOutputName;
	String strErrorName;

	class Context{
	public:
		virtual ~Context(){};

		virtual void receive(bool)=0;
		virtual void compute()=0;
	protected:
		Context(LogicBase *pLogicBase):pLogicBase(pLogicBase){};

		org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext;
		LogicBase *pLogicBase;
	};

	class DataModelContext :  public Context{
	public:
		virtual ~DataModelContext(){};

		virtual void receive(bool bNoWait);
		virtual void compute();

	protected:
		DataModelContext(LogicBase *pLogicBase):Context(pLogicBase){};
		DM::DataObjectPtr dmData;

		friend class Factory<DataModelContext>;
	};

	class RawContext :  public Context{
	public:
		virtual ~RawContext(){};

		virtual void receive(bool bNoWait);
		virtual void compute();

	protected:
		RawContext(LogicBase *pLogicBase):Context(pLogicBase){};

		API::Message::PtrHolder ptrMessage;

		friend class Factory<RawContext>;
	};


	IAS_DFT_FACTORY<Context>::PtrHolder ptrContext;

	bool bDM;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_LogicBase_H_ */
