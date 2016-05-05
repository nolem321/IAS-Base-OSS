/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/DSFactory.h
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
#ifndef _IAS_QS_Workers_Proc_DSFactory_H_
#define _IAS_QS_Workers_Proc_DSFactory_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>
#include <ds/api/Session.h>

#include <org/invenireaude/qsystem/workers/ds/Parameter.h>
#include <org/invenireaude/qsystem/workers/ds/Specification.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
class WorkContextManager;
}
namespace DS {

class DSManager;

/*************************************************************************/
/** The DSFactory class.
 *
 */
class DSFactory {

public:
	virtual ~DSFactory()throw();

	void createDataSource(const String& strName)const;

	static ::org::invenireaude::qsystem::workers::ds::Ext::SpecificationPtr
		DataSourceSpecsToDM(const String& strSpecs);

	static IAS::DS::API::Session::TransactionMode StringToTransactionMode(const String& strMode);

protected:

	DSFactory(const ::org::invenireaude::qsystem::workers::ds::Specification* dmSpecification,
			  DSManager* pDSManager,
			  WCM::WorkContextManager* pWorkContextManager);

	typedef HashMapWithStringKey<const ::org::invenireaude::qsystem::workers::ds::Parameter* > ParametersMap;
	ParametersMap  hmDataSources;

	DSManager* pDSManager;
	WCM::WorkContextManager* pWorkContextManager;

	friend class Factory<DSFactory>;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_DSFactory_H_ */
