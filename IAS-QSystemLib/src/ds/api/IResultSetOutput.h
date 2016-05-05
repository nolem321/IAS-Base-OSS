/*
 * File: IAS-QSystemLib/src/ds/api/IResultSetOutput.h
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
#ifndef _IAS_DS_API_IResultSetOutput_H_
#define _IAS_DS_API_IResultSetOutput_H_

#include <commonlib/commonlib.h>
#include <dm/tools/Setter.h>

namespace IAS {
namespace DS {
namespace API {

/*************************************************************************/
/** The Consumer class.
 *
 */

class IResultSetOutput  {
public:

	virtual ~IResultSetOutput() throw(){};

	virtual void addResultSetOutput(DM::Tools::Setter* pSetter, bool bOptional)=0;
	virtual void bindResultSetOutputs()=0;

	virtual bool next()=0;
	virtual void fetch(int iIdx, DM::DataObjectPtr& dm)=0;
	virtual void close()=0;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_DS_API_IResultSetOutput_H_ */
