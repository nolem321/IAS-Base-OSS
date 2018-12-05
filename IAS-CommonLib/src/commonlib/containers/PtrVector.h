/*
 * File: IAS-CommonLib/src/commonlib/containers/PtrVector.h
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

#ifndef _IAS_PtrVector_H_
#define _IAS_PtrVector_H_

#include <vector>

#include "commonlib/memory/memory.h"
#include "commonlib/logger/logger.h"
#include "commonlib/types.h"

namespace IAS {

/*************************************************************************/
/** The PtrVector template.
 * Holdes the pointer in the std::vector object and deletes them on cleanup.
 */

template <class T, class TA = IAS_DFT_FACTORY<T*> >
class PtrVector : private ::std::vector<T*, TA >{
	public:

		typedef typename ::std::vector<T*, TA>::iterator iterator;
		typedef typename ::std::vector<T*, TA>::const_iterator const_iterator;

		virtual ~PtrVector(){
			typename ::std::vector<T*, TA>::iterator it(::std::vector<T*, TA>::begin());
			while(it!=::std::vector<T*, TA>::end()){
				IAS_DFT_FACTORY< T >::Free(*it);
				it++;
			}
		}

		iterator begin() { return ::std::vector<T*, TA>::begin(); };
		iterator end() { return ::std::vector<T*, TA>::end(); };

		const_iterator begin() const { return ::std::vector<T*, TA>::begin(); };
		const_iterator end() const{ return ::std::vector<T*, TA>::end(); };

		void clear() { ::std::vector<T*, TA>::clear(); }

		int  size() const {
			return ::std::vector<T*, TA>::size();
		}

		void push_back(T* o){
			::std::vector<T*, TA>::push_back(o);
		}

		T* operator[](int i)const {
			return 	::std::vector<T*, TA>::at(i);
		}

		typename ::std::vector<T*, TA>::iterator erase(typename ::std::vector<T*>::iterator it ){
			IAS_MEM_DELETE(*it);
			return ::std::vector<T*, TA>::erase(it);
		}

		void erase(int iIdx){
			if(iIdx < 0 || iIdx > size() - 1)
				IAS_THROW(InternalException("PtrVector::erase(): Index ot of bound."));
			typename ::std::vector<T*, TA>::iterator it=begin();
			it+=iIdx;
			IAS_MEM_DELETE(*it);
			::std::vector<T*, TA>::erase(it);
		}
};

/*************************************************************************************/

};/* namespace IAS */

#endif /*_IAS_PTRVECTOR_H_*/
