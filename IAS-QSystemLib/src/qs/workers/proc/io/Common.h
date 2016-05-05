/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/Common.h
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
#ifndef _IAS_QS_Workers_Proc_IO_Common_H_
#define _IAS_QS_Workers_Proc_IO_Common_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/io/Parameters.h>
#include <org/invenireaude/qsystem/workers/AttributeUpdate.h>
#include <qs/api.h>

#include <qs/fmt/Formatter.h>
#include <qs/fmt/FmtFactory.h>
#include <qs/workers/proc/prog/CallbackSet.h>

#include "Input.h"
#include "Output.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM{
class WorkContextManager;
}
namespace IO {

/*************************************************************************/
/** The Common class.
 *
 */
class Common :
		public Input,
		public Output{
public:

	virtual ~Common() throw();

	virtual void send(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					   DM::DataObject* dmData);

	virtual void send(const ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
			          std::istream& is);

	virtual void receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 DM::DataObjectPtr& dmData,
						 int iTimeout = Input::CDefaultTimeout);


	virtual void receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 API::Message::PtrHolder& ptrMessage,
						 int iTimeout = Input::CDefaultTimeout);


	virtual void buildContext(const API::Message* pMessage,
							   ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext)const;

	virtual void applyContext(const ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							  API::Message* pMessage)const;

	API::Session*    				getSession();
	API::Connection* 				getConnection();
	const API::Destination&         getDestination()const;

protected:

	Common(const ::org::invenireaude::qsystem::workers::io::Parameters* dmParameters,
			 WCM::WorkContextManager* pWorkContextManager);


    const Fmt::FmtFactory *pFmtFactory;

	int iTimeout;
	API::Destination                    destination;


	void updateAttributes(API::Message* pMessage)const;


	API::Responder::PtrHolder            ptrResponder;

	void receiveImpl(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 API::Message::PtrHolder& ptrMessage,
					 int iTimeout);


	virtual API::Message* get(API::Attributes* pAttributes, int iTimeout);
	virtual void put(API::Message* pMessage);


	IAS_DFT_FACTORY<Prog::CallbackSet>::PtrHolder ptrOnReceive;
	IAS_DFT_FACTORY<Prog::CallbackSet>::PtrHolder ptrOnSend;
	IAS_DFT_FACTORY<Prog::CallbackSet>::PtrHolder ptrOnNoData;

private:

	URI    uriConnectionKey;

	URI    uriOrigin;

	const ::org::invenireaude::qsystem::workers::io::Parameters *dmParameters;

	const ::org::invenireaude::qsystem::workers::Ext::AttributeUpdateList& lstAttrUpdates;

	API::Session*    				pSession;
	API::Connection* 				pConnection;

	void parse(API::Message* pMessage, DM::DataObjectPtr& dmData);
	void serialize(const DM::DataObject* dmData, API::Message* pMessage);

	static API::Session::TransactionMode StringToTransactionMode(const String& strMode);

};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IO_Common_H_ */

