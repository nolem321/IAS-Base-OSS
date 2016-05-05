/*
 * File: IAS-QSystemLib/src/qs/api/Content.h
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
#ifndef _IAS_QS_API_Content_H_
#define _IAS_QS_API_Content_H_

#include <commonlib/commonlib.h>


namespace IAS {
namespace QS {
namespace API {

//TODO Store name/id

/*************************************************************************/
/** The Content class.
 *  This class could be named ContentStream.
 *  Since there are no istreambuf and ostreambuf methods the const_cast seams
 *  the most consistent option to get a reader stream from a constant value.
 *  The implementation doesn't have to be thread safe and the
 *  concurrent I/O may mess the data. It is up to the caller to ensure
 *  proper protection if needed.
 */
class Content : public std::iostream{
public:

	Content(): std::iostream(0){};

	virtual ~Content(){};

	operator std::istream&()const{
		return *const_cast<Content*>(this);
	}

};
/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Content_H_ */
