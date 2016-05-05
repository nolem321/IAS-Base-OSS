/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/WrappedStatement.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_WrappedStatement_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_WrappedStatement_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
/** The WrappedStatement class.
 *
 */
//TODO make some utility and use in lang::ds::WrappedStatement
class WrappedStatement {
public:

	virtual ~WrappedStatement()throw();

	void execute(DM::DataObject* dm) const;

protected:

	WrappedStatement(const String& strDataSource, const String& strSpecification);


	String strSpecification;
	String strDataSource;

	friend class ::IAS::Factory<WrappedStatement>;
};


/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPS_WrappedStatement_H_ */
