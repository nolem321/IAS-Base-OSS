/*
 * File: IAS-CommonLib/src/commonlib/memory/ma/PtrHolder.h
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

#ifndef _IAS_PtrHolder_H_
#define _IAS_PtrHolder_H_

namespace IAS {

template <class T, class D>
class PtrHolder{

  public:

	  PtrHolder(){
		  ptr = (T*)0;
	  }

	  PtrHolder(T* ptr){
	  		  this->ptr = ptr;
	  }


	  void unset(){ this->ptr = (T*)0 ; }
	  T* pass(){ T* tmp = ptr; ptr = (T*)0 ; return tmp; };

	  ~PtrHolder(){
		  d(ptr);
	  }

	  T* operator=(T *ptr)    {  d(this->ptr); this->ptr=ptr; return ptr; };
	  operator T*()   const   {  return ptr;};
	  T* getPointer()  const  {  return ptr;};
	  T* operator->() const   {  return ptr;};
	  T& operator*() const    {  return *ptr;};
	  bool operator!() const { return (!ptr); };
	  bool isNull() const { return ptr == (void*)0; };


  private:
	  T* ptr;
	  D d;
	  PtrHolder(const PtrHolder<T,D> &ptrHolder):ptr(0){};
	  PtrHolder<T,D>& operator=(const PtrHolder<T,D> &ptrHolder){ return *this;}

};

template<typename C, class D>
class PtrCleaner{
public:
	PtrCleaner(C &c):c(c){};

	~PtrCleaner(){
		typename C::iterator it;
		for(it=c.begin();it !=c.end();it++)
			try{
				d(*it);
			}catch(...){};

	};

protected:
	C& c;
	D d;
};

};/* namespace IAS */

#endif /*IASTYPES_H_*/
