/*
 * File: IAS-CommonLib/src/commonlib/memory/ma/RefCountingPtr.h
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

//TODO (M?) RefCountingPointee - StandardFactory only - what is it about ?

#ifndef _IAS_RefCountingPtr_H_
#define _IAS_RefCountingPtr_H_

namespace IAS{

/*************************************************************************/
/** The RefCountingPointee class.
 */

class RefCountingPointee{
	public:

		virtual  ~RefCountingPointee(){};
		RefCountingPointee():iRefCounter(0){};
	private:
		int iRefCounter;

	friend class RefCountingBase;

//	protected:
//	virtual void destroy()=0;
};

/*************************************************************************/
/** The RefCountingBase class.
 */

class RefCountingBase{

protected:
	inline void incRefCounter(RefCountingPointee* p){
		p->iRefCounter++;

	};
	inline unsigned long decRefCounter(RefCountingPointee* p){
		return --(p->iRefCounter);
	};
//	inline void destroyRefCounter(RefCountingPointee* p){ p->destroy();};
};

/*************************************************************************/
/** The RefCountingPtr class.
 */

template <class T, class D>
class RefCountingPtr : protected RefCountingBase {

public:
	
	RefCountingPtr(T* ptr = 0)throw(){
		assign(ptr);
	}
	;
	RefCountingPtr(const RefCountingPtr& newPtrRef){
		assign(newPtrRef.ptr);
	};
	
	~RefCountingPtr() throw () {unassign();};

	RefCountingPtr& operator=(const RefCountingPtr& newPtrRef){
		if(&newPtrRef != this){
			unassign();
			assign(newPtrRef.ptr);
		}
		return *this;
	};

	RefCountingPtr& operator=(T* ptr){
		if(ptr != this->ptr){
			unassign();
			assign(ptr);
		}
		return *this;
	};
	
	void unset() { unassign(); ptr = 0; }
	T* forget() {  T* tmp=ptr; ptr = 0; return tmp; }

	bool operator==(RefCountingPtr& pointerRef) const { return (ptr == pointerRef.ptr); };
	T* getPointer()  const  {  return ptr; } ;
	T* operator->() const   {  return ptr;};
	T& operator*() const   {   return *ptr; };
	operator T*()   const  {   return ptr;};

//TODO (L) A eclipse indexer
//	template<class W>
//	operator RefCountingPtr<F,W>() const { return RefCountingPtr<F,W>(ptr);};

	bool operator!() const { return (!ptr); };
    bool isNull() const { return !ptr; };

protected:
	T* ptr;
    D d;
	void assign(T* ptr){
    	this->ptr=ptr;
    	if ( !(this->ptr) ) return;
    	incRefCounter(ptr);
    }
    
    void unassign(){
       if( !(this->ptr) ) return;
       if( decRefCounter(ptr) <= 0)
    	  deleteObject();
    }
    
    void deleteObject() {  d(this->ptr); };

};

}/* namespace IAS */

#endif /*REFCOUNTINGPTR_H_*/
