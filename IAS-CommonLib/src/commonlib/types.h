/*
 * File: IAS-CommonLib/src/commonlib/types.h
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

#ifndef IASTYPES_H_
#define IASTYPES_H_

//using namespace std;
#include <string>
#include <sstream>
#include <list>

#include "memory/mm/MemoryManager.h"

#ifdef __GNUC__
#define  ias_std_unordered_map std::unordered_map
#define  ias_std_hash          std::hash
#else
#define  ias_std_unordered_map std::tr1::unordered_map
#define  ias_std_hash          std::tr1::hash
#endif


namespace IAS{

	typedef double Float;

	typedef std::basic_string< char,
		std::char_traits<char>,
		AllocatorFactory< char, &IAS::MemoryManager::GetAllocator >
		> String;


	typedef std::basic_stringstream< char,
									 std::char_traits<char>,
									AllocatorFactory< char, &IAS::MemoryManager::GetAllocator > > StringStream;

	typedef std::list<String, AllocatorFactory<String, &IAS::MemoryManager::GetAllocator > >
			StringList;

	typedef std::list< std::pair<String,String> /*, AllocatorFactory<String, &MemoryManager::GetAllocator > */ >
			StringPairList;

};

#endif /*IASTYPES_H_*/
