/*
 * File: IAS-CommonLib/src/commonlib/containers/HashMapStringToPointer.h
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

#ifndef _IAS_HashMapStringToPointer_H_
#define _IAS_HashMapStringToPointer_H_

#include "HashMapOfPointers.h"

#include "../exception/ItemNotFoundException.h"

namespace IAS {

/*************************************************************************/
/** The HashMapStringToPointer template.
 */

template <class T,
	      class A =  IAS_DFT_FACTORY<std::pair<const String, T*> >,
	      class TA =  IAS_DFT_FACTORY<T> >
class HashMapStringToPointer : public ::IAS::HashMapOfPointers<String,T,_Hash<String>, _EqualsTo<String>, A, TA>{

public:

		virtual ~HashMapStringToPointer(){}

	protected:

	friend class ::IAS::Factory<HashMapStringToPointer>;

};

/*************************************************************************************/

template <class T,
		  class A =  ::IAS::MemoryManagerFactory< std::pair<const String, T> > >
class HashMapWithStringKey : public ias_std_unordered_map<String, T,_Hash<String>, _EqualsTo<String>, A>{
	public:
		virtual ~HashMapWithStringKey(){}

		const T& at(const String& k) const{
			typename ias_std_unordered_map<String, T,_Hash<String>, _EqualsTo<String>, A>::const_iterator
				it = ias_std_unordered_map<String, T,_Hash<String>, _EqualsTo<String>, A>::find(k);
			return 	it->second;
		}

		T at(const String& k){
			typename ias_std_unordered_map<String, T,_Hash<String>, _EqualsTo<String>, A>::const_iterator
				it = ias_std_unordered_map<String, T,_Hash<String>, _EqualsTo<String>, A>::find(k);
			return 	it->second;
		}

	protected:

	friend class ::IAS::Factory<HashMapWithStringKey>;
};

/*************************************************************************************/
template <class T,
		  class A =  ::IAS::MemoryManagerFactory< std::pair<const String, T> > >
class OrderedMapWithStringKey : public std::map<String, T, std::less<String>, A>{
	public:
		virtual ~OrderedMapWithStringKey(){}

		const T& at(const String& k) const{
			typename std::map<String, T, std::less<String>, A>::const_iterator
				it = std::map<String, T, std::less<String>, A>::find(k);
			return 	it->second;
		}

		T at(const String& k){
			typename std::map<String, T, std::less<String>, A>::const_iterator
				it = std::map<String, T, std::less<String>, A>::find(k);
			return 	it->second;
		}

	protected:

	friend class ::IAS::Factory<OrderedMapWithStringKey>;
};

/*************************************************************************************/

};/* namespace IAS */

#endif /*_IAS_HASMAPOFPOINTERS_H_*/
