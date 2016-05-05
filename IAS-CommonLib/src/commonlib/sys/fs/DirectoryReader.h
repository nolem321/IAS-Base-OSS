/*
 * File: IAS-CommonLib/src/commonlib/sys/fs/DirectoryReader.h
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
#ifndef _IAS_SYS_FS_DirectoryReader_H_
#define _IAS_SYS_FS_DirectoryReader_H_

#include "commonlib/types.h"
#include "commonlib/containers/PtrVector.h"

#include <list>

namespace IAS {
namespace SYS {
namespace FS {

/*************************************************************************/
/** The DirectoryReader class.
 *
 */
class DirectoryReader {
public:

	enum FileType{
		FT_FILE     = 'r',
		FT_DIR      = 'd',
		FT_BLOCKDEV = 'b',
		FT_CHARDEV  = 'c',
		FT_PIPE     = 'p',
		FT_SOCKET   = 's',
		FT_LINK     = 'l',
	    FT_UNKNOWN  = '?'
	};

	struct Entry {

		Entry(FileType iType, String   strFile);
		virtual ~Entry(){};
		FileType iType;
		String   strFile;


	};

	DirectoryReader(const String& strDir);
	virtual ~DirectoryReader() throw();

	void read();

	typedef PtrVector<Entry> EntriesList;

	//TODO (L?) remove this ?
	const EntriesList& getEntries() const;

	typedef EntriesList::const_iterator const_iterator;

	inline const_iterator begin()const { return lstEntries.begin(); }
	inline const_iterator end()const { return lstEntries.end(); }
	inline unsigned int   size() const { return lstEntries.size(); }
protected:


	String strDir;

	EntriesList lstEntries;

	friend class ::IAS::Factory<DirectoryReader>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SYS_FS_DirectoryReader_H_ */
