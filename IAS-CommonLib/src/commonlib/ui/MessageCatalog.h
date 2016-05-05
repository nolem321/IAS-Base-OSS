/*
 * File: IAS-CommonLib/src/commonlib/ui/MessageCatalog.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef MESSAGECATALOG_H_
#define MESSAGECATALOG_H_

#include"../memory/memory.h"
#include"../types.h"
#include "../misc/InstanceFeature.h"

#include<map>

/*************************************************************************/

namespace IAS{

/** The class. */
 class MessageCatalog : public InstanceFeature<MessageCatalog>{

public:

	typedef unsigned int MsgId;

	MessageCatalog();
	virtual ~MessageCatalog();

	void fillMessageText(String& strOutput,
						 MsgId     iMessageId,
					     const std::vector<String>& tabValues);


	class MessageCatalogUpdater {
		protected:
		static void UpdateCatalog(MsgId, const String& strMessage);
	};

protected:

	typedef std::map<int,String> DisplayableMessageMap;

	void init();

	DisplayableMessageMap hmMessages;

	void loadFile(const String& strFileName);

	void update(MsgId idMsg, const String& strMessage);

	void loadExternalMessages();

	friend class Factory<MessageCatalog>;

	static const String ENV_DSP_MSGS_DIR;
	static const String ENV_DSP_MSGS_DIR_DEFALUT;
	static const char   SPECIAL_DSPMSG_CHAR;
};


}/* namespace IAS */

#endif /*MESSAGECATALOG_H_*/
