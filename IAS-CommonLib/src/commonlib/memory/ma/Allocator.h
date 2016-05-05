/*
 * File: IAS-CommonLib/src/commonlib/memory/ma/Allocator.h
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

#ifndef _IAS_Allocator_H_
#define _IAS_Allocator_H_

#include <stddef.h>
#include <ostream>

#include "Factory.h"
#include "../../threads/ThreadSpecific.h"

#include <typeinfo>

namespace IAS {

class Allocator {
public:

	virtual void* allocate(size_t n)  = 0;
	virtual void free(const void* p)  = 0;
	virtual bool check(const void* p) = 0;

	//Those getters are not thread safe, use (set) with care.
	inline bool hasDisabledDestructors()const{
		return bDisabledDestructors;
	}

	inline bool hasCheckPointersOnReturn()const{
		return bCheckPointersOnReturn;
	}

	virtual void printToStream(std::ostream& os)=0;


	virtual ~Allocator()throw() {};

protected:

	Allocator():bDisabledDestructors(false),bCheckPointersOnReturn(true){};

	bool bDisabledDestructors;
	bool bCheckPointersOnReturn;
};

typedef ::IAS::Allocator* (*PtrFunAllocator)();

template<class T>
	class STLAllocator{

	 public:
		STLAllocator(Allocator* a):a(a){};

		/*
		 * STL pattern starts here.
		 */
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;

		pointer allocate(size_type n, const void * = 0) {
			return (T*) (a->allocate(sizeof(T) * n));
		}

		void deallocate(void* p, size_type) {
			if (!p)
				return;
			a->free(p);
		}

		pointer address(reference x) const {
			return &x;
		}
		const_pointer address(const_reference x) const {
			return &x;
		}

		//STLAllocator<T>& operator=(const STLAllocator<T>& o) {
		//	a=o.a;
		//	return *this;
		//}

		void construct(pointer p, const T& val) {
			new ((T*) p) T(val);
		}
		void destroy(pointer p) {
			if (p)
				p->~T();
		}

		size_type max_size() const {
			return size_t(-1);
		}

		template<class U>
		bool operator==(const STLAllocator<U>&o) const throw () {
			return a==o.a;
		}

		template<class U>
		bool operator!=(const STLAllocator<U>&o) const throw () {
			return a!=o.a;
		}

		template<class U>
		struct rebind {
			typedef STLAllocator<U> other;
		};

		template<class U>
			STLAllocator(const STLAllocator<U>& o):a(o.a){}

		template<class U>
		STLAllocator& operator=(const STLAllocator<U>& o) {
			a=o.a;
			return *this;
		}

		Allocator *a;
	};

}

namespace IAS {
template<class T, PtrFunAllocator ff, class CO = DynamicCastOperator <T> >
class AllocatorFactory: public Factory<T> {

public:
	/*
	 * STL pattern starts here.
	 */
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	AllocatorFactory() { (*ff)();	}
	AllocatorFactory(const AllocatorFactory&) {	}

	pointer allocate(size_type n, const void * = 0) {
		return (T*) ((*ff)()->allocate(sizeof(T) * n));
	}

	void deallocate(void* p, size_type) {
		if (!p)
			return;
		(*ff)()->free(p);
	}

	pointer address(reference x) const {
		return &x;
	}
	const_pointer address(const_reference x) const {
		return &x;
	}
	AllocatorFactory<T, ff>& operator=(const AllocatorFactory&) {
		return *this;
	}
	void construct(pointer p, const T& val) {
		new ((T*) p) T(val);
	}
	void destroy(pointer p) {
		if (p)
			p->~T();
	}
	size_type max_size() const {
		return size_t(-1);
	}

#ifdef __GNUC__
	template<class U>
	bool operator==(const AllocatorFactory<U, ff>&) const throw () {
		return true;
	}

	template<class U>
	bool operator!=(const AllocatorFactory<U, ff>&) const throw () {
		return false;
	}

	template<class U>
	struct rebind {
		typedef AllocatorFactory<U, ff> other;
	};

	template<class U>
	AllocatorFactory(const AllocatorFactory<U, ff>&) {
	}

	template<class U>
	AllocatorFactory& operator=(const AllocatorFactory<U, ff>&) {
		return *this;
	}
#else
	//TODO Allocator template workaround.
	template<class U>
	bool operator==(const U&) const throw () {
		return true;
	}

	template<class U>
	bool operator!=(const U&) const throw () {
		return false;
	}

	template<class U>
	struct rebind {
		typedef AllocatorFactory<U, ff> other;
	};

	template<class U>
	AllocatorFactory(const U&) {
	}

	template<class U>
	AllocatorFactory& operator=(U&) {
		return *this;
	}
#endif

	/*
	 * End of STL pattern
	 */

	struct Deleter{
		void operator()(T* p){
			Free(p);
		}
	};

	typedef ::IAS::PtrHolder<T, Deleter>               PtrHolder;
	typedef ::IAS::PtrSet< T,  AllocatorFactory<T,ff>, Deleter >   PtrHoldersCollection;
	typedef ::IAS::RefCountingPtr< T, Deleter >        RefCountingPtr;

	typedef typename ::IAS::ThreadSpecificOwner<AllocatorFactory<T, ff, CO>, T>::Pointer ThreadSpecificPtr;

	struct MemHolder {
		MemHolder(void* p) :p(reinterpret_cast<T*>(p)){}

		~MemHolder() {
			if(p)
				(*ff)()->free(p);
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
		MemHolder p( (*ff)()->allocate(sizeof(T)));
#ifdef __GNUC__
		Factory<T>::template Initialize(p);
#else
		Factory<T>::template Initialize<>(p);
#endif
		return p.pass();
	}

	template<typename P1>
	static T* Create(const P1& a) {
		MemHolder p( (*ff)()->allocate(sizeof(T)));
		Factory<T>::template Initialize<P1>(p,a);
		return p.pass();
	}

	template<typename P1, typename P2>
	static T* Create(const P1& a, const P2& b) {
		MemHolder p( (*ff)()->allocate(sizeof(T)));
		Factory<T>::template Initialize<P1,P2>(p,a,b);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3>
	static T* Create(const P1& a, const P2& b, const P3& c) {
		MemHolder p( (*ff)()->allocate(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3>(p,a,b,c);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3, typename P4>
	static T* Create(const P1& a, const P2& b, const P3& c, const P4& d) {
		MemHolder p( (*ff)()->allocate(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3,P4>(p,a,b,c,d);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	static T* Create(const P1& a, const P2& b, const P3& c, const P4& d, const P5& e) {
		MemHolder p( (*ff)()->allocate(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3,P4,P5>(p,a,b,c,d,e);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static T* Create(const P1& a, const P2& b, const P3& c, const P4& d, const P5& e, const P6&f) {
		MemHolder p( (*ff)()->allocate(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3,P4,P5>(p,a,b,c,d,e,f);
		return p.pass();
	}

	static void Free(T *p) {
		if (!p)
			return;

		CO co;

		const void *pp;

		pp = co(p);

		if((*ff)()->hasCheckPointersOnReturn() && !(*ff)()->check(pp))
			return;

		if(!(*ff)()->hasDisabledDestructors())
			Factory<T>::Free(p);

		(*ff)()->free(pp);

	};

};

}

namespace IAS2 {
using namespace IAS;
template<class T, class CO = DynamicCastOperator <T> >
class AllocatorFactory: public Factory<T> {

public:
	/*
	 * STL pattern starts here.
	 */
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	AllocatorFactory() { }
	AllocatorFactory(const AllocatorFactory&) {	}

	pointer allocate(size_type n, const void * = 0) {
		return (T*) ::malloc(sizeof(T) * n);
	}

	void deallocate(void* p, size_type) {
		if (!p)
			return;
		::free(p);
	}

	pointer address(reference x) const {
		return &x;
	}
	const_pointer address(const_reference x) const {
		return &x;
	}
	AllocatorFactory<T>& operator=(const AllocatorFactory&) {
		return *this;
	}
	void construct(pointer p, const T& val) {
		new ((T*) p) T(val);
	}
	void destroy(pointer p) {
		if (p)
			p->~T();
	}
	size_type max_size() const {
		return size_t(-1);
	}

#ifdef __GNUC__
	template<class U>
	bool operator==(const AllocatorFactory<U>&) const throw () {
		return true;
	}

	template<class U>
	bool operator!=(const AllocatorFactory<U>&) const throw () {
		return false;
	}

	template<class U>
	struct rebind {
		typedef AllocatorFactory<U> other;
	};

	template<class U>
	AllocatorFactory(const AllocatorFactory<U>&) {
	}

	template<class U>
	AllocatorFactory& operator=(const AllocatorFactory<U>&) {
		return *this;
	}
#else
	//TODO Allocator template workaround.
	template<class U>
	bool operator==(const U&) const throw () {
		return true;
	}

	template<class U>
	bool operator!=(const U&) const throw () {
		return false;
	}

	template<class U>
	struct rebind {
		typedef AllocatorFactory<U, ff> other;
	};

	template<class U>
	AllocatorFactory(const U&) {
	}

	template<class U>
	AllocatorFactory& operator=(U&) {
		return *this;
	}
#endif

	/*
	 * End of STL pattern
	 */

	struct Deleter{
		void operator()(T* p){
			Free(p);
		}
	};

	typedef ::IAS::PtrHolder<T, Deleter>               PtrHolder;
	typedef ::IAS::PtrSet< T,  AllocatorFactory<T>, Deleter >   PtrHoldersCollection;
	typedef ::IAS::RefCountingPtr< T, Deleter >        RefCountingPtr;

	//typedef typename ::IAS::ThreadSpecificOwner<AllocatorFactory<T, ff, CO>, T>::Pointer ThreadSpecificPtr;

	struct MemHolder {
		MemHolder(void* p) :p(reinterpret_cast<T*>(p)){}

		~MemHolder() {
			if(p)
				::free(p);
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
		MemHolder p( ::malloc(sizeof(T)));
#ifdef __GNUC__
		Factory<T>::template Initialize(p);
#else
		Factory<T>::template Initialize<>(p);
#endif
		return p.pass();
	}

	template<typename P1>
	static T* Create(const P1& a) {
		MemHolder p( ::malloc(sizeof(T)));
		Factory<T>::template Initialize<P1>(p,a);
		return p.pass();
	}

	template<typename P1, typename P2>
	static T* Create(const P1& a, const P2& b) {
		MemHolder p( ::malloc(sizeof(T)));
		Factory<T>::template Initialize<P1,P2>(p,a,b);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3>
	static T* Create(const P1& a, const P2& b, const P3& c) {
		MemHolder p( ::malloc(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3>(p,a,b,c);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3, typename P4>
	static T* Create(const P1& a, const P2& b, const P3& c, const P4& d) {
		MemHolder p( ::malloc(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3,P4>(p,a,b,c,d);
		return p.pass();
	}

	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	static T* Create(const P1& a, const P2& b, const P3& c, const P4& d, const P5& e) {
		MemHolder p( ::malloc(sizeof(T)));
		Factory<T>::template Initialize<P1,P2,P3,P4,P5>(p,a,b,c,d,e);
		return p.pass();
	}

	static void Free(T *p) {
		if (!p)
			return;

		CO co;

		void *pp;

		pp = co(p);

		Factory<T>::Free(p);

		::free(pp);

	};

};

}

#endif /*_IAS_Allocator_H_*/
