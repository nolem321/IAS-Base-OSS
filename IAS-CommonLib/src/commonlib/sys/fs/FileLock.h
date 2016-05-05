/*
 * File: IAS-CommonLib/src/commonlib/sys/fs/FileLock.h
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
#ifndef _IAS_SYS_FS_FileLock_H_
#define _IAS_SYS_FS_FileLock_H_

#include "commonlib/types.h"
#include "../Locker.h"
#include "commonlib/memory/ma/Factory.h"

namespace IAS {
namespace SYS {
namespace FS {

/*************************************************************************/
/** The FileLock class.
 *
 */
class FileLock : public ::IAS::SYS::ILockable{
public:

	FileLock(const String& strFileName);
	virtual ~FileLock() throw();

	virtual void lock();
	virtual bool lockNoWait();
	virtual void unlock();

	virtual bool isLocked();

	virtual void writeContent(const String& strContent);
	virtual void readContent(String& strContent);

protected:

	String strFileName;


	class FileAutoClose{
		public:
		FileAutoClose(int iFD=-1);
		~FileAutoClose();

		int iFD;
	};

	FileAutoClose fileHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SYS_FS_FileLock_H_ */
