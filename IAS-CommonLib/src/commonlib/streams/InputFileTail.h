/*
 * File: IAS-CommonLib/src/commonlib/streams/InputFileTail.h
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
#ifndef _IAS_Streams_InputFile_H_
#define _IAS_Streams_InputFile_H_

#include "./InputFile.h"

#include <fstream>
#include "commonlib/memory/ma/Factory.h"

/*
 *
 */
namespace IAS {

class InputFileTail :public InputFile {
public:

	InputFileTail(const String& strName, bool bFollowName=false, int iPoolInterval=1000);
	virtual ~InputFileTail();

	String nextLine(int iTimeoutMS);

	static const int CInfiniteWait = -1;
protected:

	bool bFollowName;
	int iPoolInterval;
	int iLastInode;
	friend class ::IAS::Factory<InputFileTail>;
};

}

#endif /* _IAS_Streams_InputFile_H_ */
