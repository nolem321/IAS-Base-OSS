/*
 * File: IAS-QSystemExe/src/parameters/StatusParameters.h
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
#ifndef _IAS_QS_Parameters_StatusParameters_H_
#define _IAS_QS_Parameters_StatusParameters_H_

#include "ProgramParameters.h"

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
/** The StatusParameters class.
 *
 */
class StatusParameters : public ::IAS::QS::Parameters::ProgramParameters{
public:

	virtual ~StatusParameters() throw();

	const String& getSystemName()const;

protected:
	StatusParameters(int argc, char* argv[]);

	virtual void printCmdDesc(std::ostream& os) const;
	virtual void printArgsDesc(std::ostream& os) const;

	friend class ::IAS::Factory<StatusParameters>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_StatusParameters_H_ */
