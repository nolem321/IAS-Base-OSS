/*
 * File: IAS-DataModelLib-CodeGen/src/dm/gen/ProgramParameters.h
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
#ifndef _IAS_DM_Gen_ProgramParameters_H_
#define _IAS_DM_Gen_ProgramParameters_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
namespace Gen {

/*************************************************************************/
class ProgramParameters : public ::IAS::ProgramParameters {
public:

	virtual ~ProgramParameters() throw();

	const String& getXSDFile() const;
	const String& getOutputDir() const;

	//TODO is it still valid ?
	bool  isSingleDataObjectFile() const;

	const StringList& getNamespacesToBeGenerated()const;

protected:
	ProgramParameters(int argc, char* argv[]);

	StringList lstNamespaces;

	friend class ::IAS::Factory<ProgramParameters>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Gen_ProgramParameters_H_ */
