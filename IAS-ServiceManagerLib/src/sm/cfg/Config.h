/*
 * File: IAS-ServiceManagerLib/src/sm/cfg/Config.h
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
#ifndef _IAS_SM_Cfg_Config_H_
#define _IAS_SM_Cfg_Config_H_

#include <commonlib/commonlib.h>
#include <commonlib/sys/fs/FileLock.h>

#include "dataobjects.h"
#include <dm/datamodel.h>
#include "types.h"

namespace IAS {
namespace SM {
namespace Cfg {

class ServiceIndexer;

/*************************************************************************/
/** The Config class.
 *
 */
class Config {
public:

	virtual ~Config() throw();

	bool refresh();

	void save();
	void load();

	void getServiceIdxListByGrpAttrs(const GrpAttrPairList& lstGrpAttrPairs,
							         ServiceIdxList& refOutputList) const;

	const ::org::invenireaude::sm::cfg::Service *getService(unsigned int iIdx)const;
	const ::org::invenireaude::sm::cfg::Service *getService(const String& strName)const;

	const ::org::invenireaude::sm::cfg::Ext::ServiceList& getServicesList()const;

	const ::org::invenireaude::sm::cfg::ResourceGroup* getMergedServiceResourceGrps(const ::org::invenireaude::sm::cfg::Service *pService ) const;

	const String& getLckDir()const;

	bool isVerbose() const {return bVerbose;};

	std::ostream& getOutput()const { return osLog;};
	int           getRefeshMS()const { return iRefreshMS;};

	String getLogFilesBase(const ::org::invenireaude::sm::cfg::Service* pService)const;

	void copyServiceConfig(::org::invenireaude::sm::cfg::Ext::ServiceConfigPtr& ptrServiceConfig)const;
	void copyDeploymentConfig(::org::invenireaude::sm::cfg::Ext::DeploymentConfigPtr& ptrDeploymentConfig)const;

protected:
	Config(const String& strCfgDirs);

	static const String& StrConfigFile;
	static const String& StrDeploymentFile;
	static const String& StrConfigLockFile;

	StringList lstCfgDirs;

	::org::invenireaude::sm::cfg::Ext::ServiceConfigPtr     dmServiceConfig;
	::org::invenireaude::sm::cfg::Ext::DeploymentConfigPtr  dmDeploymentConfig;

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper;

	void loadDM();
	void saveDM();

	void indexItems();

	IAS_DFT_FACTORY<ServiceIndexer>::PtrHolder   ptrServiceIndexer;


	String strVersion;

	::IAS::SYS::ILockable* getLockObject();
	IAS_DFT_FACTORY<SYS::FS::FileLock>::PtrHolder ptrConfigLock;

	typedef HashMapWithStringKey< const ::org::invenireaude::sm::cfg::Service* > ServiceByNameMap;
	ServiceByNameMap                                                       hmServicesByName;

	typedef HashMapWithStringKey< const ::org::invenireaude::sm::cfg::ResourceGroup* > ResourceGrpByNameMap;
	ResourceGrpByNameMap             											hmResourceGrpByName;

	typedef ias_std_unordered_map<const ::org::invenireaude::sm::cfg::Service*,
							      const ::org::invenireaude::sm::cfg::ResourceGroup*> ResourceGrpForServiceMap;
	ResourceGrpForServiceMap             			 						 hmResourceGrpForService;


	Mutex mutexDMChange;

	String strLckDir;

	bool bVerbose;
	std::ostream& osLog;
	int  iRefreshMS;


	//The hash map may be used by threads and some std::pairs will interact with RefCountingPointers
	std::set< ::org::invenireaude::sm::cfg::Ext::ResourceGroupPtr > lstResourceGrpForService;

	friend class ::IAS::Factory<Config>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Cfg_Config_H_ */


