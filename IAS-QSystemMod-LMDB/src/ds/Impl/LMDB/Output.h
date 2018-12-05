/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/Output.h
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
#ifndef _IAS_DS_Impl_LMDB_Output_H_
#define _IAS_DS_Impl_LMDB_Output_H_

#include <commonlib/commonlib.h>
#include <ds/api/IOutput.h>

#include "Statement.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {
class Session;
/*************************************************************************/
/** The Output class.
 *
 */
class Output :
		public virtual DS::API::IOutput {
public:

	virtual ~Output() throw();

	virtual void addOutput(DM::Tools::Setter *pSetter);
	virtual void bindOutputs();

protected:
	Output(Statement& statement);

	Statement& statement;

};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_LMDB_Output_H_ */
