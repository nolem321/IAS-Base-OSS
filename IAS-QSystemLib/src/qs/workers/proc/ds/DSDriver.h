/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/DSDriver.h
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
#ifndef _IAS_QS_Workers_Proc_DS_DSDriver_H_
#define _IAS_QS_Workers_Proc_DS_DSDriver_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/ds/Parameter.h>

#include <ds/api.h>

#include "wrapper/Wrapper.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
	class WorkContextManager;
}
namespace DS {

/*************************************************************************/
/** The DSDriver class.
 *
 */
class DSDriver {
public:

	virtual ~DSDriver() throw();


	Wrapper::Wrapper* getStatement(const String& strSpecification, ::IAS::DM::DataObject* dm);

	class WrapperHolder : public Wrapper::Wrapper::PtrHolder {
		public:
			WrapperHolder( Wrapper::Wrapper* pWrapper, DSDriver* pDriver):
				IAS_DFT_FACTORY< Wrapper::Wrapper >::PtrHolder(pWrapper),
				pDriver(pDriver){};


			~WrapperHolder();
			private:

		DSDriver* pDriver;
	};

	::IAS::DS::API::Session* getSession();

protected:
	DSDriver(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter,
			 WCM::WorkContextManager* pWorkContextManager);

	const DM::DataFactory*  getDataFactory();

private:
	::IAS::DS::API::Session* pSession;
	const DM::DataFactory*  pDataFactory;

	typedef HashMapStringToPointer<Wrapper::Wrapper> WrappersMap;
	WrappersMap	                                    hmWrappers;

	::org::invenireaude::qsystem::workers::ds::Ext::ParameterPtr dmParameter;

	URI uriConnectionKey;
	friend class Factory<DSDriver>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_DS_DSDriver_H_ */
