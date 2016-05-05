/*
 * File: Messages.h
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


#ifndef _IAS_QS_UI_Messages_H_
#define _IAS_QS_UI_Messages_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace UI {

/*************************************************************************/
/** The Messages class.
 *
 */
class Messages : public IAS::MessageCatalog::MessageCatalogUpdater{

public:

	static const MessageCatalog::MsgId	MSGI_ServiceStarted             = 14001;
	static const MessageCatalog::MsgId	MSGI_ServiceStopped             = 14002;
	static const MessageCatalog::MsgId  MSGI_ServiceNotRunning          = 14003;
	static const MessageCatalog::MsgId	MSGI_ServiceRestarted           = 14004;

	static const MessageCatalog::MsgId	MSGE_ServiceFailed              = 24001;

	static const MessageCatalog::MsgId	MSGE_ConfigError                = 24010;

	Messages();
	virtual ~Messages();

protected:

	static Messages TheInstance;
};


/*************************************************************************/
}
}
}

#endif /* _IAS_Lang_UI_Messages_H_ */
