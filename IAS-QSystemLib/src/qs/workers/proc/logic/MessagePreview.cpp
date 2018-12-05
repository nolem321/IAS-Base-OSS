/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/MessagePreview.cpp
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
#include "MessagePreview.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <org/invenireaude/qsystem/service/Message.h>
#include <org/invenireaude/qsystem/service/PreviewMessagesWindow.h>
#include <org/invenireaude/qsystem/service/PreviewMessagesSelector.h>
#include <org/invenireaude/qsystem/service/PreviewMessagesStatus.h>
#include <org/invenireaude/qsystem/service/PreviewMessages.h>
#include <org/invenireaude/qsystem/service/DataFactory.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>

#include <qs/workers/proc/exception/RollbackMeException.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"

#include "../io/BrowserInput.h"

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
MessagePreview::MessagePreview(const ::org::invenireaude::qsystem::workers::logic::MessagePreview* dmParameters,
							  WCM::WorkContextManager* pWorkContextManager):
		LogicBase(dmParameters,pWorkContextManager){

	dmBrowserParameters=workers::io::DataFactory::GetInstance()->getBrowserInputType()->createBrowserInput();
	dmBrowserParameters->setInputName("mpinput");
	dmBrowserParameters->setConnection(dmParameters->getConnection()->duplicateConnection());

	IAS_TRACER;
}
/*************************************************************************/
MessagePreview::~MessagePreview() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MessagePreview::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==MessagePreview starts:"<<
			DM::XML::XMLHelper::Stringify(pWorkContextManager->getGlobalContext()->getDataFactory(),dmData));

	service::Ext::PreviewMessagesPtr dmPreviewMessages;

	try{
		dmPreviewMessages=service::DataFactory::GetInstance()->getPreviewMessagesType()->cast(dmData);
	}catch(Exception& e){
		IAS_THROW(RollbackMeException(String("Bad request:")+e.toString()));
	}

	if(!dmPreviewMessages->isSetSelector() ||
		!dmPreviewMessages->getSelector()->isSetDestination()){
		IAS_THROW(RollbackMeException("Missing request parameters"));
	}

	dmBrowserParameters->setDestination(dmPreviewMessages->getSelector()->getDestination());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Destination: "<<dmBrowserParameters->getDestination());

	IAS_DFT_FACTORY<IO::BrowserInput>::PtrHolder ptrBrowser(
			IAS_DFT_FACTORY<IO::BrowserInput>::Create(dmBrowserParameters,pWorkContextManager));

	unsigned int iOffset=0;
	unsigned int iPageSize=C_MaxPage;

	if(dmPreviewMessages->getSelector()->isSetWindow()){

		const service::PreviewMessagesWindow* pWindow=dmPreviewMessages->getSelector()->getWindow();

		if(pWindow->isSetPageOffset())
			iOffset=pWindow->getPageOffset();

		if(iOffset > C_MaxMessages - C_MaxPage)
			iPageSize=C_MaxMessages - C_MaxPage;

		if(pWindow->isSetPageSize())
			iPageSize=pWindow->getPageSize();

		if(iPageSize > C_MaxPage)
			iPageSize=C_MaxPage;
	}

	unsigned int iNumMessages = 0;

	try{

		service::Ext::MessageList& lstMessages(dmPreviewMessages->getMessagesList());

		iNumMessages = ptrBrowser->skip(iOffset);

		if(iNumMessages == iOffset)
			while(iPageSize-- > 0){

				workers::Ext::ContextPtr dmContextTmp(workers::DataFactory::GetInstance()->createContext());

				API::Message::PtrHolder ptrMessage;

				ptrBrowser->receive(dmContextTmp,ptrMessage);

				service::Ext::MessagePtr dmServiceMessage(
						service::DataFactory::GetInstance()->getMessageType()->createMessage());

				dmServiceMessage->setContext(dmContextTmp);
				StringStream ssRawContent;
				MiscTools::CopyStreams(*(ptrMessage->getContent()),ssRawContent);
				dmServiceMessage->setRawContent(ssRawContent.str());
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"RawContent:"<<ssRawContent.str());
				lstMessages.add(dmServiceMessage);
				iNumMessages++;
			}

		iNumMessages += ptrBrowser->skip(C_MaxMessages-iNumMessages);

	}catch(EndOfDataException& e){
	}catch(Exception& e){
		IAS_THROW(RollbackMeException(e.toString()));
	}

	dmPreviewMessages->createStatus();
	dmPreviewMessages->getStatus()->setNumMessages(iNumMessages);

	//TODO getInput name? for the default output
	//TODO use logic setting for input
	pWorkContextManager->getIOManager()->getDefaultOutput()->send(dmContext,dmPreviewMessages);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==MessagePreview ends:"<<
				DM::XML::XMLHelper::Stringify(pWorkContextManager->getGlobalContext()->getDataFactory(),dmData));

}
/*************************************************************************/
}
}
}
}
}
