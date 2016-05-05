/*
 * File: IAS-CommonLib/src/commonlib/sys/Locker.h
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
#ifndef _IAS_SYS_Locker_H_
#define _IAS_SYS_Locker_H_

namespace IAS {
namespace SYS {
/*************************************************************************/
class ILockable {
	public:
	virtual void lock()=0;
	virtual void unlock()=0;
};
/*************************************************************************/
/** The Locker class.
 *
 */
class Locker {
public:

	inline Locker(ILockable* pLocable):pLocable(pLocable){ pLocable->lock(); };
	inline ~Locker(){ pLocable->unlock(); };

protected:
	ILockable *pLocable;
};

/*************************************************************************/
}
}

#endif /* _IAS_SYS_Locker_H_ */
