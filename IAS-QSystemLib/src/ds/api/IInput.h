/*
 * File: IAS-QSystemLib/src/ds/api/IInput.h
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
#ifndef _IAS_DS_API_IInput_H_
#define _IAS_DS_API_IInput_H_

#include <commonlib/commonlib.h>
#include <dm/tools/Setter.h>

namespace IAS {
namespace DS {
namespace API {

/*************************************************************************/
/** The Consumer class.
 *
 */
class IInput  {
public:

	virtual ~IInput() throw(){};

	virtual void addInput(const String& strTag,
			              DM::Tools::Setter *pSetter)=0;

	virtual void feedInputs(DM::DataObjectPtr& dm)=0;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_DS_API_IInput_H_ */
