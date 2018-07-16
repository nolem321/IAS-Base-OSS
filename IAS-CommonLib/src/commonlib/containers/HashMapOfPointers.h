/*
 * File: IAS-CommonLib/src/commonlib/containers/HashMapOfPointers.h
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

#ifndef _IAS_HashMapOfPointers_H_
#define _IAS_HashMapOfPointers_H_

#include <unordered_map>
#include "commonlib/memory/memory.h"
#include "commonlib/types.h"

namespace IAS {

/*************************************************************************/

inline size_t _StringHashFun(const String& strValue){

	size_t iHash = 0;

	size_t iLen = strValue.length();
	if(iLen < sizeof(long)){
		for(const char* s = strValue.c_str(); *s != 0; s++)
			  iHash = ((iHash << 5) + iHash) ^ *s;
	}else{

	int i=0;
	iLen-=sizeof(long);

	for(long *p=(long*)strValue.c_str();
		i <= iLen;
		i+=sizeof(long),p++)
			iHash = ((iHash << 5) + iHash) ^ *p;

	}

	return iHash;
}

template <class T>
struct _Hash : public ias_std_hash<T>{};


template <class T>
struct _EqualsTo : public std::equal_to<T>{};


template <>
struct _Hash<const ::IAS::String *>{
	size_t operator()(const ::IAS::String* const pValue)const{
		return _StringHashFun(*pValue);
	}
};

template <>
struct _Hash< ::IAS::String >{
	size_t operator()(const ::IAS::String& strValue)const{
		return _StringHashFun(strValue);
	}
};

template <>
struct _EqualsTo<const ::IAS::String*>{
	size_t operator()(const ::IAS::String* const x,const ::IAS::String* const y)const{
		return (*x).compare(*y) == 0;
	}
};

template <>
struct _EqualsTo< ::IAS::String >{
	size_t operator()(const ::IAS::String& x,const ::IAS::String& y)const{
		return x.compare(y) == 0;
	}
};

template <class  K,
		   class T,
		   class H = _Hash<K>,
		   class P = _EqualsTo<K>,
		   class A =  IAS_DFT_FACTORY<std::pair<const K, T*> > >
class HashMap : public ias_std_unordered_map<K,T,H,P,A> {};


/*************************************************************************/
/** The HashMapOfPointers template.
 */

template <class  K,
		   class T,
		   class H = _Hash<K>,
		   class P = _EqualsTo<K>,
		   class A =  IAS_DFT_FACTORY<std::pair<const K, T*> >,
		   class TA =  IAS_DFT_FACTORY<T> >
class HashMapOfPointers : private HashMap<K , T*, H, P, A >{
	public:

		typedef typename ias_std_unordered_map<K,T*,H,P,A>::iterator iterator;
		typedef typename ias_std_unordered_map<K,T*,H,P,A>::const_iterator const_iterator;

		virtual ~HashMapOfPointers(){
			clear();
		}

		iterator begin() { return ias_std_unordered_map<K,T*, H, P, A>::begin(); };
		iterator end() { return ias_std_unordered_map<K,T*,H, P, A>::end(); };

		const_iterator begin() const { return ias_std_unordered_map<K,T*,H, P, A>::begin(); };
		const_iterator end() const { return ias_std_unordered_map<K,T*,H, P, A>::end(); };

		iterator find(const K& k) { return ias_std_unordered_map<K,T*, H, P, A>::find(k); };
		const_iterator find(const K& k)const { return ias_std_unordered_map<K,T*, H, P, A>::find(k); };

		int  size() const {
			return ias_std_unordered_map<K,T*,H, P, A>::size();
		}

		int count(const K& k) const {
			return 	ias_std_unordered_map<K,T*,H, P, A>::count(k);
		}

		bool hasKey(const K& k) const {
				return 	ias_std_unordered_map<K,T*,H, P, A>::count(k) >0;
		}

		class ValueProxy{
			public:

			ValueProxy(T*&v):v(v){};

			operator T*(){ return v; };

			T*& operator =(T*n){
				if(n != v){
					TA::Free(v);
					v=n;
				}
				return v;
			};

			T*& operator =(const ValueProxy& pn){
				return this->operator =(pn.v);
			};

			T* operator->(){ return v;};
			T& operator*(){ return *v; };
			bool operator !(){ return !v;}

			protected:

			T*&v;

		};

		ValueProxy operator[](const K& k){
			return 	ValueProxy(ias_std_unordered_map<K,T*,H, P, A>::operator [](k));
		}

		const T* at(const K& k) const{
			typename ias_std_unordered_map<K,T*,H, P, A>::const_iterator it = ias_std_unordered_map<K,T*,H, P, A>::find(k);
			return 	it->second;
		}

		T* at(const K& k){
			typename ias_std_unordered_map<K,T*,H, P, A>::const_iterator it = ias_std_unordered_map<K,T*,H, P, A>::find(k);
			return 	it->second;
		}

		typename ias_std_unordered_map<K,T*,H, P, A>::iterator forget(typename ias_std_unordered_map<K,T*,H, P, A>::iterator it ){
			return ias_std_unordered_map<K,T*,H, P, A>::erase(it);
		}

		void forget(const K& k){

			if(!hasKey(k))
				return;

			typename ias_std_unordered_map<K,T*,H, P, A>::iterator it = ias_std_unordered_map<K,T*,H, P, A>::find(k);
			while(it != ias_std_unordered_map<K,T*,H, P, A>::end() && it->first == k)
				it=forget(it);

		}

		typename ias_std_unordered_map<K,T*,H, P, A>::iterator erase(typename ias_std_unordered_map<K,T*,H, P, A>::iterator it ){
			TA::Free(it->second);
			return ias_std_unordered_map<K,T*,H, P, A>::erase(it);
		}

		void erase(const K& k){

			if(!hasKey(k))
				return;

			typename ias_std_unordered_map<K,T*,H, P, A>::iterator it = ias_std_unordered_map<K,T*,H, P, A>::find(k);
			while(it != ias_std_unordered_map<K,T*,H, P, A>::end() && it->first == k)
				it=erase(it);

		}

		void clear(){
			typename ias_std_unordered_map<K,T*,H, P, A>::iterator it=ias_std_unordered_map<K,T*,H, P, A>::begin();
				while(it!=ias_std_unordered_map<K,T*,H, P, A>::end())
					it=erase(it);
		}
};

/*************************************************************************************/

};/* namespace IAS */

#endif /*_IAS_HASMAPOFPOINTERS_H_*/
