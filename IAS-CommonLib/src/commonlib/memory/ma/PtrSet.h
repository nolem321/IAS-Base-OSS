/*
 * File: IAS-CommonLib/src/commonlib/memory/ma/PtrSet.h
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
#ifndef _IAS_PtrSet_H_
#define _IAS_PtrSet_H_

#include <set>

/*
 *
 */

namespace IAS {

/*************************************************************************/
/** The PtrSet template.
 * Holdes the pointer in the std::map object and deletes them on cleanup.
 *
 *
 */


template<class T, class F, class D>
class PtrSet {

public:
	typedef std::set<T*,std::less<T*> > PtrSTLSet; //unordered_set not available yet.

	PtrSet(){};

	virtual ~PtrSet(){
		typename PtrSTLSet::iterator it = setPtrs.begin();
		while(it != setPtrs.end() ){
			deleteObject(*it);
			it++;
		}
	};

	bool hasPointer(T* ptr){
		return setPtrs.count(ptr) > 0;
	}

	void forget(T* ptr){
		setPtrs.erase(ptr);
	}

	void delPointer(T* ptr){
		if(setPtrs.count(ptr) > 0){
			setPtrs.erase(ptr);
			deleteObject(ptr);
		}
	}

	void addPointer(T* ptr){
		setPtrs.insert(ptr);
	};

	typedef typename PtrSTLSet::const_iterator const_iterator;
	typedef typename PtrSTLSet::iterator iterator;

	const_iterator begin()const{ return setPtrs.begin(); }
	iterator begin(){ return setPtrs.begin(); }

	const_iterator end()const{ return setPtrs.end(); }
	iterator end(){ return setPtrs.end(); }

	void deleteObject(T* ptr) {
		d(ptr);
	}

	std::size_t size()const { return setPtrs.size(); }

protected:
	PtrSTLSet setPtrs;
	D d;
};

}


#endif /* PTRSet_H_ */
