/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/ssl/Engine.cpp
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
#include <qs/log/LogLevel.h>

#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/SecureLayer.h>
#include <org/invenireaude/qsystem/workers/SSLCertificate.h>
#include <org/invenireaude/qsystem/workers/SSLCertificateFile.h>

using namespace ::org::invenireaude::qsystem::workers;

#include "Engine.h"
#include "Conversation.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {
namespace SSL {

/*************************************************************************/
class ConversationFactory : public IAS::Net::Socket::ServiceHandleFactory{
public:

	virtual ~ConversationFactory() throw(){};

	void createService(::IAS::Net::FileHandle* pFileHandle){
		IAS_TRACER;
		pEngine->insert(IAS_DFT_FACTORY<Conversation>::Create(pFileHandle,pEngine));
	}

	ConversationFactory(Engine *pEngine):
		pEngine(pEngine){};

	Engine*                 pEngine;
};

/*************************************************************************/
Engine::Engine(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
			   System *pSystem):
	Async::Engine(dmConnection,pSystem,true){
	IAS_TRACER;

	//TODO (M) common toolkit for this SSL::Context creation based on DM.

	const SSLCertificateFile *dmSSLCertificateFile=DataFactory::GetInstance()->getSSLCertificateFileType()->cast(dmConnection->getSsl()->getCert());

	String strFile(dmSSLCertificateFile->getFileName());
	String strPassword(dmSSLCertificateFile->getPassword());

	ptrContext=IAS_DFT_FACTORY<IAS::Net::SSL::Context>::Create(strFile,strPassword);

	ptrEventMonitor->addHandler(IAS_DFT_FACTORY<IAS::Net::Socket::EventHandler>::Create(
				IAS_DFT_FACTORY<ConversationFactory>::Create(this),this));
}
/*************************************************************************/
Engine::~Engine() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IAS::Net::SSL::Context* Engine::getContext(){
	IAS_TRACER;
	return ptrContext;
}
/*************************************************************************/
}
}
}
}
}
