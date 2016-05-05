/*
 * File: IAS-CommonLib/src/commonlib/sys/ipc/ResourceDescriptor.h
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
#ifndef _IAS_IPC_ResourceDescriptor_H_
#define _IAS_IPC_ResourceDescriptor_H_

#include "commonlib/types.h"

namespace IAS {
namespace IPC {
/*************************************************************************/
/** The IPCResource class.
 *
 */
class ResourceDescriptor {
public:

	virtual ~ResourceDescriptor();

	enum Mode {
		M_OWNER,
		M_USER,
		M_CLEANER
	};

	typedef unsigned int Key;
	static const Key C_PRIVATE = 0;

	virtual int getOpenFlags() const;
	bool getDeleteOnCleanUp() const;

	void setKey(Key aKey);
	void setKeyByToken(const String& strPath, int id);
	Key getKey() const;

protected:

	ResourceDescriptor(Mode iMode = M_USER)throw();
	Mode iMode;

private:
	Key  aKey;
};
/*************************************************************************/

}
}
#endif /* _IAS_IPCResource_H_ */
