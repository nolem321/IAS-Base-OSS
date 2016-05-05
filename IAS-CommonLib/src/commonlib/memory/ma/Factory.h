/*
 * File: IAS-CommonLib/src/commonlib/memory/ma/Factory.h
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

#ifndef _IAS_Factory_H_
#define _IAS_Factory_H_

#include "PtrHolder.h"
#include "PtrSet.h"
#include "RefCountingPtr.h"

#include <memory>

namespace IAS{

//============================================================================

template<class T>
class Factory {

protected:

	static void Initialize(void *p){
		T* n = new(p) T;
	}

	template<typename P1>
	static void Initialize(void *p, const P1& a) {
		T* n = new(p) T(a);
	}

	template<typename P1, typename P2>
	static void Initialize(void *p, const P1& a, const P2& b) {
		T* n = new(p) T(a,b);
	}

	template<typename P1, typename P2, typename P3>
	static void Initialize(void *p, const P1& a, const P2& b, const P3& c) {
		T* n = new(p) T(a, b, c);
	}

	template<typename P1, typename P2, typename P3, typename P4>
	static void Initialize(void *p, const P1& a, const P2& b, const P3& c, const P4& d) {
		T* n = new(p) T(a, b, c, d);
	}

	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	static void Initialize(void *p, const P1& a, const P2& b, const P3& c, const P4& d, const P5& e) {
		T* n = new(p) T(a, b, c, d, e);
	}

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static void Initialize(void *p, const P1& a, const P2& b, const P3& c, const P4& d, const P5& e, const P6& f) {
		T* n = new(p) T(a, b, c, d, e, f);
	}

	static void Free(T *p) {
		if(p)
			p->~T();
	};


};


template<class T>
struct DynamicCastOperator {
	void* operator()(T *p){
		return dynamic_cast<void*>(p);
	}
};

template<class T>
struct StaticCastOperator {
	void* operator()(T *p){
		return static_cast<void*>(p);
	}
};


template<class T>
class StandardFactory  : public Factory<T>{

public:

	struct Deleter{
		void operator()(T* p){
			Free(p);
		}
	};

	typedef ::IAS::PtrHolder< T, Deleter >                        PtrHolder;
	typedef ::IAS::PtrSet< T, Factory<T>, Deleter >      PtrHoldersCollection;
	typedef ::IAS::RefCountingPtr< T, Deleter >                   RefCountingPtr;

	struct MemHolder {
		MemHolder(T* p) :p(p){}

		~MemHolder() {
			if(p)
				operator delete(p);
		}

		operator T*(){
			return p;
		}

		T* pass() {
			T* tmp = p;
			p =  0;
			return tmp;
		}

		T* p;
	};

	static T* Create() {
		MemHolder p((T*)operator new(sizeof(T)));
		Factory<T>::Initialize(p);
		return p.pass();
	}

	template<typename P1>
	static T* Create(P1 a) {
		MemHolder p((T*)operator new(sizeof(T)));
		Factory<T>::template Initialize<P1>(p,a);
		return p.pass();
	}

	template<typename P1, typename P2>
	static T* Create(P1 a, P2 b) {
		MemHolder p((T*)operator new(sizeof(T)));
		Factory<T>::template Initialize<P1,P2>(p,a,b);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3>
	static T* Create(P1 a, P2 b, P3 c) {
		MemHolder p((T*)operator new(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3>(p,a,b,c);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3, typename P4>
	static T* Create(P1 a, P2 b, P3 c, P4 d) {
		MemHolder p((T*)operator new(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3,P4>(p,a,b,c,d);
		return p.pass();
	}
	static void Free(T *p) {
		if(!p)
			return;
		Factory<T>::Free(p);
		operator delete((void*)p);
	};

};


};

#endif /*_IAS_Factory_H_*/
