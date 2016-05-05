/*
 * File: IAS-ServiceManagerExe/src/sm/cmdline/StopParameters.h
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
#ifndef _IAS_SM_CmdLine_StopParameters_H_
#define _IAS_SM_CmdLine_StopParameters_H_

#include "ProgramParameters.h"
#include "GrpAttrFeature.h"

namespace IAS {
namespace SM {
namespace CmdLine {

/*************************************************************************/
/** The StopParameters class.
 *
 */
class StopParameters : public ::IAS::SM::CmdLine::ProgramParameters,
					   public  ::IAS::SM::CmdLine::GrpAttrFeature{
public:

	virtual ~StopParameters() throw();

	bool isAsync() const { return bAsync; };

protected:
	StopParameters(int argc, char* argv[]);

	bool bAsync;

	virtual void printCmdDesc(std::ostream& os) const;
	virtual void printArgsDesc(std::ostream& os) const;

	friend class ::IAS::Factory<StopParameters>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_StopParameters_H_ */
