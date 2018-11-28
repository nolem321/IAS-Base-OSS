/*
 * File: IAS-QSystemLib/src/qs/lang/msgs/MessagePreview.cpp
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
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>

#include <qs/workers/proc/io/IOManager.h>
#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/IOFactory.h>
#include <qs/workers/proc/io/BrowserInput.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/BrowserInput.h>

#include <org/invenireaude/qsystem/service/Message.h>
#include <org/invenireaude/qsystem/service/PreviewMessagesWindow.h>
#include <org/invenireaude/qsystem/service/PreviewMessagesSelector.h>
#include <org/invenireaude/qsystem/service/PreviewMessagesStatus.h>
#include <org/invenireaude/qsystem/service/PreviewMessages.h>
#include <org/invenireaude/qsystem/service/DataFactory.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <qs/workers/proc/exception/RollbackMeException.h>


using namespace ::IAS::Lang::Interpreter;
using namespace ::IAS::QS::Workers::Proc;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Msgs {

/*************************************************************************/
MessagePreview::MessagePreview(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

}
/*************************************************************************/
MessagePreview::~MessagePreview() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MessagePreview::browse(DM::DataObject* pParameters) const {

	IAS_TRACER;

	::org::invenireaude::qsystem::workers::io::Ext::BrowserInputPtr dmBrowserParameters;

	service::Ext::PreviewMessagesPtr dmPreviewMessages;

	DM::DataObjectPtr dmMsg(pParameters->getDataObject("request"));
	try {

		dmPreviewMessages = service::DataFactory::GetInstance()->getPreviewMessagesType()->cast(dmMsg);

	} catch (Exception& e) {
		IAS_THROW(BadUsageException(String("Bad request:") + e.toString()));
	}

	if (!dmPreviewMessages->isSetSelector()
			|| !dmPreviewMessages->getSelector()->isSetDestination()
		    || !dmPreviewMessages->getSelector()->isSetConnectionAlias()) {
		IAS_THROW(BadUsageException("Missing request parameters"));
	}

	String strURI("registry://");
	strURI += dmPreviewMessages->getSelector()->getConnectionAlias();

	URI uri(strURI);

	dmBrowserParameters = workers::io::DataFactory::GetInstance()->createBrowserInput();
	IO::IOFactory::UpdateConnection(uri,dmBrowserParameters->createConnection());


	dmBrowserParameters->setDestination(dmPreviewMessages->getSelector()->getDestination());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Destination: "<<dmBrowserParameters->getDestination());

	IAS_DFT_FACTORY<IO::BrowserInput>::PtrHolder ptrBrowser(
			IAS_DFT_FACTORY<IO::BrowserInput>::Create(dmBrowserParameters,pWorkContext));

	unsigned int iOffset = 0;
	unsigned int iPageSize = C_MaxPage;
	size_t       iMsgSizeLimit = C_DftMsgSizeLimit;

	if (dmPreviewMessages->getSelector()->isSetMsgSizeLimit())
		iMsgSizeLimit = dmPreviewMessages->getSelector()->
				getMsgSizeLimit();

	if (dmPreviewMessages->getSelector()->isSetWindow()) {
		const service::PreviewMessagesWindow* pWindow =
				dmPreviewMessages->getSelector()->getWindow();
		if (pWindow->isSetPageOffset())
			iOffset = pWindow->getPageOffset();

		if (iOffset > C_MaxMessages - C_MaxPage)
			iPageSize = C_MaxMessages - C_MaxPage;

		if (pWindow->isSetPageSize())
			iPageSize = pWindow->getPageSize();

		if (iPageSize > C_MaxPage)
			iPageSize = C_MaxPage;
	}
	unsigned int iNumMessages = 0;
	try {

		service::Ext::MessageList& lstMessages(
				dmPreviewMessages->getMessagesList());

		iNumMessages = ptrBrowser->skip(iOffset);

		if (iNumMessages == iOffset)
			while (iPageSize-- > 0) {

				workers::Ext::ContextPtr dmContextTmp(
						workers::DataFactory::GetInstance()->createContext());

				API::Message::PtrHolder ptrMessage;

				ptrBrowser->receive(dmContextTmp, ptrMessage);

				service::Ext::MessagePtr dmServiceMessage(
						service::DataFactory::GetInstance()->getMessageType()->createMessage());

				dmServiceMessage->setContext(dmContextTmp);

				StringStream ssRawContent;
				//TODO (H) Limit the message size (browse or copy?)
				MiscTools::CopyStreams(*(ptrMessage->getContent()),ssRawContent,iMsgSizeLimit);

				dmServiceMessage->setRawContent(ssRawContent.str());
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"RawContent:"<<ssRawContent.str());

				lstMessages.add(dmServiceMessage);
				iNumMessages++;
			}

		iNumMessages += ptrBrowser->skip(C_MaxMessages - iNumMessages);

	} catch (EndOfDataException& e) {
	}
	dmPreviewMessages->createStatus();
	dmPreviewMessages->getStatus()->setNumMessages(iNumMessages);

	pParameters->setDataObject(String(::IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
			dmPreviewMessages);
}

/*************************************************************************/
void MessagePreview::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	try{

		browse(pParameters);

	}catch(Exception& e){

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}


}
/*************************************************************************/
Extern::Statement* MessagePreview::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<MessagePreview>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

