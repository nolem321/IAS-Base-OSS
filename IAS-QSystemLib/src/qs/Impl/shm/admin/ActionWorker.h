/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/admin/ActionWorker.h
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
#ifndef _IAS_QS_Impl_Attachment_Admin_ActionWorker_H_
#define _IAS_QS_Impl_Attachment_Admin_ActionWorker_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/Action.h>

namespace IAS {
namespace QS {
namespace SHM  {
class Attachment;
namespace Admin {

/*************************************************************************/
/** The ActionWorker class.
 *
 */
class ActionWorker {
public:

	virtual ~ActionWorker() throw();

	virtual void work(QS::SHM::Attachment *pAttachment,::org::invenireaude::qsystem::Action* dmAction)=0;

protected:
	ActionWorker();

	friend class Factory<ActionWorker>;
};

/*************************************************************************/
}
}
}
}


#endif /* _IAS_QS_Impl_Attachment_Admin_ActionWorker_H_ */
