/*
 * File: IAS-CommonLib/src/commonlib/containers/HashMapStringPairToPointer.h
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

#ifndef _IAS_HashMapStringPairToPointer_H_
#define _IAS_HashMapStringPairToPointer_H_

#include "HashMapOfPointers.h"

namespace IAS {

/*************************************************************************/
/** The HashMapStringPairKey template.
 */

struct _HashMapStringPairKey : public std::pair<String, String>{
	public:
	_HashMapStringPairKey(const String& first, const String second): std::pair<String, String>(first,second){};


	friend std::ostream& operator<<(std::ostream& o, const _HashMapStringPairKey& k){
		o<<"("<<k.first<<","<<k.second<<")";
		return o;
	};
};

template <>
struct _Hash< _HashMapStringPairKey >{
	size_t operator()(const ::IAS::_HashMapStringPairKey& key)const{
		return _StringHashFun(key.first) + _StringHashFun(key.second);
	}
};


template <>
struct _EqualsTo< _HashMapStringPairKey >{
	size_t operator()(const ::IAS::_HashMapStringPairKey& x,const ::IAS::_HashMapStringPairKey& y)const{
		return x.first.compare(y.first) == 0 && x.second.compare(y.second) == 0;
	}
};


template <class T>
class HashMapStringPairToPointer :
	public ::IAS::HashMapOfPointers<_HashMapStringPairKey,
									T,
									_Hash<_HashMapStringPairKey>,
									_EqualsTo<_HashMapStringPairKey> >{

	public:

	typedef _HashMapStringPairKey Key;

	typename
	::IAS::HashMapOfPointers<_HashMapStringPairKey,
							T,
							_Hash<_HashMapStringPairKey>,
							_EqualsTo<_HashMapStringPairKey> >::ValueProxy atKey(const String& k1, const String& k2){

		return this->operator[](Key(k1,k2));
	};

	int count(const String& k1, const String& k2)const{
		return ::IAS::HashMapOfPointers<_HashMapStringPairKey,
				T,
				_Hash<_HashMapStringPairKey>,
				_EqualsTo<_HashMapStringPairKey> >::count(Key(k1,k2));
	};


	virtual ~HashMapStringPairToPointer(){};

protected:

};

/*************************************************************************************/

	template <class T>
	class HashMapWithStringPairKey :
		public ias_std_unordered_map<
			_HashMapStringPairKey,
			T,
			_Hash<_HashMapStringPairKey>,
			_EqualsTo<_HashMapStringPairKey>,
			IAS_DFT_FACTORY< std::pair<_HashMapStringPairKey, T> > >{

		public:

		typedef _HashMapStringPairKey Key;

		T*& atKey(const String& k1, const String& k2){
			return this->operator[](Key(k1,k2));
		};

		int count(const String& k1, const String& k2){
			return this->ias_std_unordered_map<
					_HashMapStringPairKey,
					T,
					_Hash<_HashMapStringPairKey>,
					_EqualsTo<_HashMapStringPairKey>,
					IAS_DFT_FACTORY< std::pair<_HashMapStringPairKey, T> > >::count(Key(k1,k2));
		};

		virtual ~HashMapWithStringPairKey(){};

	protected:

	};

};/* namespace IAS */

#endif /*_IAS_HASMAPOFPOINTERS_H_*/
