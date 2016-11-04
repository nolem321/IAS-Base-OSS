/*
 * File: IAS-ServiceManagerLib/src/sm/api/ServiceManager.h
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
#ifndef _IAS_SM_API_ServiceManager_H_
#define _IAS_SM_API_ServiceManager_H_

#include <commonlib/commonlib.h>
#include "sm/cfg/Config.h"

namespace IAS {
namespace SM {

namespace API {

/*************************************************************************/
/** The ServiceManager class.
 *
 */
class ServiceManager {
public:

	virtual ~ServiceManager() throw();

	void startServices(const Cfg::GrpAttrPairList& lstGrpAttrPair);

	void runServiceCommand(const String& strServiceName);

	void stopServices(const Cfg::GrpAttrPairList& lstGrpAttrPair, bool bAsync = false);

	void printServicesStatus(const Cfg::GrpAttrPairList& lstGrpAttrPair);

	void prepareServicesStatus(const ::org::invenireaude::sm::api::Ext::GrpAttrPairList& lstGrpAttrPair,
							   ::org::invenireaude::sm::api::Ext::ServiceStatusList& lstServiceStatus);

	void watchServices(const Cfg::GrpAttrPairList& lstGrpAttrPair);

	const Cfg::Config* getConfig()const;

	void fillGrpAttrPairList(const ::org::invenireaude::sm::api::Ext::GrpAttrPairList& lstInputGrpAttrPair,
							 Cfg::GrpAttrPairList& lstOutputGrpAttrPair);

protected:
	ServiceManager();

	IAS_DFT_FACTORY<Cfg::Config>::PtrHolder ptrConfig;

	friend class ::IAS::Factory<ServiceManager>;

	class SigChildIgnore{
		public:
		SigChildIgnore();
	};

	static SigChildIgnore TheSigChildIgnore;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_API_ServiceManager_H_ */
