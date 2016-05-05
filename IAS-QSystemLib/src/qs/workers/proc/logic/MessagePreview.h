/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/MessagePreview.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_MessagePreview_H_
#define _IAS_QS_Workers_Proc_Logic_MessagePreview_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/MessagePreview.h>
#include <org/invenireaude/qsystem/workers/io/BrowserInput.h>

#include "LogicBase.h"

#include <qs/workers/proc/logic/Logic.h>
#include <org/invenireaude/qsystem/workers/Context.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
/** The MessagePreview class.
 *
 */
class MessagePreview : public LogicBase{
public:

	virtual ~MessagePreview() throw();

protected:
	MessagePreview(const ::org::invenireaude::qsystem::workers::logic::MessagePreview* dmParameters,
				  WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							DM::DataObjectPtr& dmData);

	::org::invenireaude::qsystem::workers::logic::Ext::MessagePreviewPtr dmParameter;
	::org::invenireaude::qsystem::workers::io::Ext::BrowserInputPtr dmBrowserParameters;

	friend class Factory<MessagePreview>;

	static const unsigned int C_MaxMessages=10000;
	static const unsigned int C_MaxPage=100;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_MessagePreview_H_ */
