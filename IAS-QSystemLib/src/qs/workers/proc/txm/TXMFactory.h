/*
 * File: IAS-QSystemLib/src/qs/workers/proc/txm/TXMFactory.h
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
#ifndef _IAS_QS_Workers_Proc_TXMFactory_H_
#define _IAS_QS_Workers_Proc_TXMFactory_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/txm/Specification.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM{
class WorkContextManager;
}
namespace TXM {

class TXMManager;

/*************************************************************************/
/** The TXMFactory class.
 *
 */
class TXMFactory {

public:

	virtual ~TXMFactory()throw();

	void createTransactionManager(const String& strName)const;

	static ::org::invenireaude::qsystem::workers::txm::Ext::SpecificationPtr
		TransactionManagerSpecsToDM(const String& strSpecs);


	TXMFactory(const ::org::invenireaude::qsystem::workers::txm::Specification* dmSpecification,
			   TXMManager* pTXMManager);

protected:
	typedef HashMapWithStringKey<const ::org::invenireaude::qsystem::workers::txm::Parameter* > ParametersMap;
	ParametersMap  hmTXManagers;

	TXMManager* pTXMManager;
	WCM::WorkContextManager* pWorkContextManager;

	friend class Factory<TXMFactory>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_TXMFactory_H_ */
