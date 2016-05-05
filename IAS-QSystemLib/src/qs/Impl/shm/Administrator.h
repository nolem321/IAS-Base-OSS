/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Administrator.h
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
#ifndef _IAS_QS_System_Administrator_H_
#define _IAS_QS_System_Administrator_H_

#include <commonlib/commonlib.h>
#include <qs/api/Administrator.h>
#include <qs/Impl/shm/Attachment.h>

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
/** The Administrator class.
 *
 */
class Administrator : public virtual API::Administrator {
public:

	virtual ~Administrator() throw();

	virtual ::org::invenireaude::qsystem::stats::Ext::SystemStatsPtr getStats(bool bReset);

	SHM::Attachment* getAttachment();

	static void CreateSystem(::org::invenireaude::qsystem::Ext::SystemPtr dmSystem);
	static void DeleteSystem(const String& strName);

	static void StartDistributor(const String& strName);
	static void StartCleaner(const String& strName);

	static void DisplaySystem(const String& strName, std::ostream& os);

	static void ChangeSystem(const String& strName,
			::org::invenireaude::qsystem::Ext::ActionList& lstActions);

protected:
	Administrator(SHM::Attachment* pAttachment);

	friend class Factory<Administrator>;

	SHM::Attachment *pAttachment;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Administrator_H_ */
