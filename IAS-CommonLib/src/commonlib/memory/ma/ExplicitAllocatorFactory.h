/*
 * File: IAS-CommonLib/src/commonlib/memory/ma/ExplicitAllocatorFactory.h
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
/* ChangeLog:
 * 
 */

#ifndef _IAS_ExplicitAllocatorFactory_H_
#define _IAS_ExplicitAllocatorFactory_H_

#include "Allocator.h"

namespace IAS {

//============================================================================

template<class T, class CO = DynamicCastOperator <T> >
class ExplicitAllocatorFactory: public Factory<T> {

	struct MemHolder {
		MemHolder(void* p, Allocator *ma) :
				p(p),ma(ma) {
		}
		~MemHolder() {
			if(p)
				ma->free(p);
		}

		void release() {
			T* tmp = p;
			p = (T*) 0;
		}

		void* p;
		Allocator *ma;
	};

public:
	/*
	typedef ::IAS::PtrHolder<T, Deleter>               PtrHolder;
	typedef ::IAS::PtrSet< T, ExplicitAllocatorFactory<T>, Deleter >   PtrHoldersCollection;
	typedef ::IAS::RefCountingPtr< T, Deleter >        RefCountingPtr;
*/

	struct MemSlot{
		Allocator *ma;
		T o;
	};

	static T* Create(Allocator* ma) {
		MemSlot *slot = (MemSlot*) ma->allocate(sizeof(MemSlot));
		slot->ma=ma;
		MemHolder mh(slot,ma);
		Factory<T>::Initialize(&(slot->o));
		mh.release();
		return &(slot->o);
	}

	template<typename P1>
	static T* Create(Allocator* ma, P1 a) {
		MemSlot *slot = (MemSlot*) ma->allocate(sizeof(MemSlot));
		slot->ma=ma;
		MemHolder mh(slot,ma);
		Factory<T>::template Initialize<P1>(&(slot->o),a);
		mh.release();
		return &(slot->o);
	}

	template<typename P1, typename P2>
	static T* Create(Allocator* ma, P1 a, P2 b) {
		MemSlot *slot = (MemSlot*) ma->allocate(sizeof(MemSlot));
		slot->ma=ma;
		MemHolder mh(slot,ma);
		Factory<T>::template Initialize<P1,P2>(&(slot->o),a,b);
		mh.release();
		return &(slot->o);
	}

	template<typename P1, typename P2, typename P3>
	static T* Create(Allocator* ma, P1 a, P2 b, P3 c) {
		MemSlot *slot = (MemSlot*) ma->allocate(sizeof(MemSlot));
		slot->ma=ma;
		MemHolder mh(slot,ma);
		Factory<T>::template Initialize<P1,P2,P3>(&(slot->o),a,b,c);
		mh.release();
		return &(slot->o);
	}

	template<typename P1, typename P2, typename P3, typename P4>
	static T* Create(Allocator* ma, P1 a, P2 b, P3 c, P4 d) {
		MemSlot *slot = (MemSlot*) ma->allocate(sizeof(MemSlot));
		slot->ma=ma;
		MemHolder mh(slot,ma);
		Factory<T>::template Initialize<P1,P2,P3,P4>(&(slot->o),a,b,c,d);
		mh.release();
		return &(slot->o);
	}

	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	static T* Create(Allocator* ma, P1 a, P2 b, P3 c, P4 d, P5 e) {
		MemSlot *slot = (MemSlot*) ma->allocate(sizeof(MemSlot));
		slot->ma=ma;
		MemHolder mh(slot,ma);
		Factory<T>::template Initialize<P1,P2,P3,P4,P5>(&(slot->o),a,b,c,d,e);
		mh.release();
		return &(slot->o);
	}

	static void Free(T *p) {

		if (!p)
			return;

		CO co;

		MemSlot *slot = static_cast<MemSlot*>(co(p) - offsetof(MemSlot,o));
		void *pp=reinterpret_cast<void*>(slot);

		if(slot->ma->hasCheckPointersOnReturn() && !slot->ma->check(pp))
			return;

		if(!slot->ma->hasDisabledDestructors()){
				Factory<T>::Free(p);
			}

		slot->ma->free(pp);
	}

};
}
;

#endif /*_IAS_AllocatorManager_H_*/
