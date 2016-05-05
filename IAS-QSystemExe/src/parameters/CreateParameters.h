/*
 * File: IAS-QSystemExe/src/parameters/CreateParameters.h
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
#ifndef _IAS_QS_Parameters_CreateParameters_H_
#define _IAS_QS_Parameters_CreateParameters_H_

#include "ProgramParameters.h"
#include "org/invenireaude/qsystem/System.h"

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
/** The CreateParameters class.
 *
 */
class CreateParameters : public ::IAS::QS::Parameters::ProgramParameters{
public:

	virtual ~CreateParameters() throw();

	::org::invenireaude::qsystem::Ext::SystemPtr getSystemDescription();

protected:
	CreateParameters(int argc, char* argv[]);

	virtual void printCmdDesc(std::ostream& os) const;
	virtual void printArgsDesc(std::ostream& os) const;

	void loadXML(const String& strFileName);

	::org::invenireaude::qsystem::Ext::SystemPtr dmSystem;

	friend class ::IAS::Factory<CreateParameters>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_CreateParameters_H_ */
