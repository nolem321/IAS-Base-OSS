/*
 * File: IAS-QSystemExe/src/parameters/ProgramParameters.h
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
#ifndef _IAS_QS_Parameters_ProgramParameters_H_
#define _IAS_QS_Parameters_ProgramParameters_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
/** The ProgramParameters class.
 *
 */
class ProgramParameters : public ::IAS::ProgramParameters {
public:

	virtual ~ProgramParameters() throw();

	virtual bool checkAndShowHelp(std::ostream& os);
	virtual void showHelp(std::ostream& os);

protected:
	ProgramParameters()throw();
	void init(int argc, char* argv[], const String& strArgSpec);

	static const String StrCommonArgSpec;

	virtual void printCmdDesc(std::ostream& os) const;
	virtual void printArgsDesc(std::ostream& os) const;


	friend class ::IAS::Factory<ProgramParameters>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_ProgramParameters_H_ */
