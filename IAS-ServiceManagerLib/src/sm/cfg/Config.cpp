/*
 * File: IAS-ServiceManagerLib/src/sm/cfg/Config.cpp
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
#include "Config.h"

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "ServiceIndexer.h"
#include "DMHelper.h"
#include "ConfigException.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Cfg {
/*************************************************************************/
const String& Config::StrConfigLockFile = "Config.lck";
const String& Config::StrConfigFile = "SMServices.xml";
const String& Config::StrDeploymentFile = "SMDeployment.xml";
/*************************************************************************/
Config::Config(const String& strCfgDir): bVerbose(true), osLog(std::cerr) {

	IAS_TRACER;
	this->strCfgDir = strCfgDir;

	ptrXMLHelper = IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(DataFactory::GetInstance()->getContaingDataFactory());

	ptrServiceIndexer = IAS_DFT_FACTORY<ServiceIndexer>::Create();

	load();
}

/*************************************************************************/
Config::~Config() throw () {
	IAS_TRACER;
}
/*************************************************************************/
const ::org::invenireaude::sm::cfg::Service *Config::getService(const String& strName) const {
	IAS_TRACER;

	if (hmServicesByName.count(strName) == 0)
		IAS_THROW(BadUsageException("hmServicesByName.count(...) == 0"));

	return hmServicesByName.at(strName);
}
/*************************************************************************/
const ::org::invenireaude::sm::cfg::Service *Config::getService(unsigned int iIdx) const {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"GetService:"<<iIdx);

	return dmServiceConfig->getServicesList().at(iIdx);
}
/*************************************************************************/
const ::org::invenireaude::sm::cfg::Ext::ServiceList& Config::getServicesList() const {
	IAS_TRACER;
	return dmServiceConfig->getServicesList();
}
/*************************************************************************/
const String& Config::getLckDir()const{
	IAS_TRACER;
	return strLckDir;
}
/*************************************************************************/
::IAS::SYS::ILockable* Config::getLockObject() {
	IAS_TRACER;

	if (ptrConfigLock.isNull()) {
		String strFile = strCfgDir + "/" + StrConfigLockFile;
		std::cerr<<"test: "<<strFile<<std::endl;
		ptrConfigLock = IAS_DFT_FACTORY<SYS::FS::FileLock>::Create(strFile);
	}

	return ptrConfigLock;
}
/*************************************************************************/
bool Config::refresh() {
	IAS_TRACER;

	SYS::Locker lock(getLockObject());

	String strTmp;
	ptrConfigLock->readContent(strTmp);

	if (strTmp.compare(strVersion) == 0)
		return false;

	if(bVerbose)
		getOutput()<<"New configuration detected:"<<strTmp<<std::endl;

	load();

	return true;
}
/*************************************************************************/
void Config::save() {
	IAS_TRACER;
	saveDM();
}
/*************************************************************************/
void Config::load() {
	IAS_TRACER;

	SYS::Locker lock(getLockObject());
	ptrConfigLock->readContent(strVersion);

	hmResourceGrpByName.clear();
	hmResourceGrpForService.clear();
	hmServicesByName.clear();

	ptrServiceIndexer = IAS_DFT_FACTORY<ServiceIndexer>::Create();

	loadDM();
	indexItems();
}
/*************************************************************************/
const ::org::invenireaude::sm::cfg::ResourceGroup* Config::getMergedServiceResourceGrps(const ::org::invenireaude::sm::cfg::Service *pService ) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pService);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Service: "<<pService->getName());

	ResourceGrpForServiceMap::const_iterator it=hmResourceGrpForService.find(pService);

	if(it == hmResourceGrpForService.end()) {
		IAS_THROW(ItemNotFoundException(pService->getName()));
	}

	return it->second;
}

/*************************************************************************/
void Config::getServiceIdxListByGrpAttrs(const GrpAttrPairList& lstGrpAttrPairs, ServiceIdxList& refOutputList) const {
	IAS_TRACER;

	ptrServiceIndexer->getServiceIdxListByGrpAttrs(lstGrpAttrPairs, refOutputList);

}
/*************************************************************************/
void Config::indexItems() {
	IAS_TRACER;

	const Ext::ResourceGroupList& lstResourceGroup = dmDeploymentConfig->getResourcesList();
	hmResourceGrpByName.clear();

	for (int iResourceGrpIdx = 0; iResourceGrpIdx < lstResourceGroup.size(); iResourceGrpIdx++) {
		const ResourceGroup* pCurResouceGrp = lstResourceGroup.at(iResourceGrpIdx);

		if (hmResourceGrpByName.count(pCurResouceGrp->getName()) > 0)
			IAS_THROW(BadUsageException("hmResourceGrpByName.count(pCurResouceGrp->getName()) > 0"));

		hmResourceGrpByName[pCurResouceGrp->getName()] = pCurResouceGrp;
	}

	const Ext::ServiceList& lstServices = dmServiceConfig->getServicesList();
	hmServicesByName.clear();

	for (int iSvcIdx = 0; iSvcIdx < lstServices.size(); iSvcIdx++) {
		const Service* pCurService = lstServices.at(iSvcIdx);

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"ServiceName="<<pCurService->getName());

		if (hmServicesByName.count(pCurService->getName()) > 0)
			IAS_THROW(BadUsageException("hmServicesByName.count(pCurService->getName()) > 0"));

		hmServicesByName[pCurService->getName()] = pCurService;

		const Ext::GroupingAttributeList& lstGrpAttr = pCurService->getGrpAttrsList();

		for (int iAttrIdx = 0; iAttrIdx < lstGrpAttr.size(); iAttrIdx++) {
			const GroupingAttribute *pCurGrpAttr = lstGrpAttr.at(iAttrIdx);
			ptrServiceIndexer->addEntry(pCurGrpAttr->getName(), pCurGrpAttr->getValue(), iSvcIdx);
		}

		ptrServiceIndexer->addEntry("name", pCurService->getName(), iSvcIdx);

		Ext::ResourceGroupPtr dmComputedResourceGrp(DataFactory::GetInstance()->createResourceGroup());

		const IAS::DM::Default::Ext::StringList& lstResourceGrp = pCurService->getResGrpList();

		for (int iGrpIdx = 0; iGrpIdx < lstResourceGrp.size(); iGrpIdx++) {

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"lstResourceGrp="<<(lstResourceGrp.at(iGrpIdx)));

			if(hmResourceGrpByName.count(lstResourceGrp.at(iGrpIdx)) == 0)
				IAS_THROW(ConfigException(lstResourceGrp.at(iGrpIdx)+=" : not defined."));

			const ResourceGroup* dmResourceGrp = hmResourceGrpByName.at(lstResourceGrp.at(iGrpIdx));

			DMHelper::Merge(dmComputedResourceGrp, dmResourceGrp);
		}

		hmResourceGrpForService[pCurService]=dmComputedResourceGrp;
		lstResourceGrpForService.insert(dmComputedResourceGrp);
	}

	strLckDir="/var/tmp/lck";
	try{
		strLckDir=dmDeploymentConfig->getLckDir();
	}catch(...){};

	iRefreshMS=1000;
	try{
		iRefreshMS=dmDeploymentConfig->getRefreshMS();
	}catch(...){};
}
/*************************************************************************/
void Config::saveDM() {
	IAS_TRACER;

	{
		String strURL = strCfgDir + "/" + StrConfigFile;
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Services to: "<<strURL);

		ptrXMLHelper->save((const String) strURL, dmServiceConfig, "serviceConfig", "");
	}

	{
		String strURL = strCfgDir + "/" + StrDeploymentFile;
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Deployment to: "<<strURL);

		ptrXMLHelper->save((const String) strURL, dmDeploymentConfig, "deploymentConfig", "");
	}
}
/*************************************************************************/
void Config::loadDM() {
	IAS_TRACER;

	{
		String strURL = strCfgDir + "/" + StrConfigFile;
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Services from: "<<strURL);

		IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strURL));
		dmServiceConfig = DataFactory::GetInstance()->getServiceConfigType()->cast(ptrDoc->getRootObject());

	}

	{
		String strURL = strCfgDir + "/" + StrDeploymentFile;
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Deployment from: "<<strURL);

		IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strURL));
		dmDeploymentConfig = DataFactory::GetInstance()->getDeploymentConfigType()->cast(ptrDoc->getRootObject());
	}
}
/*************************************************************************/
String Config::getLogFilesBase(const Service* pService) const{
	IAS_TRACER;

	const ResourceGroup* dmResourceGrp = getMergedServiceResourceGrps(pService);

	Timestamp ts(true);
	StringStream ssFileName;
	ssFileName << dmResourceGrp->getLogDir() << "/";
	ssFileName << pService->getName() << "-";
	ssFileName << ts.toString("%Y%m%d-%H:%M:%S") << ".";
	return ssFileName.str();
}
/*************************************************************************/
void Config::copyServiceConfig(::org::invenireaude::sm::cfg::Ext::ServiceConfigPtr& ptrServiceConfig)const{
	IAS_TRACER;

	//TODO patter for mutexes in const objects
	Mutex::Locker locker(const_cast<Config*>(this)->mutexDMChange);
	ptrServiceConfig=dmServiceConfig->duplicateServiceConfig();
}
/*************************************************************************/
void Config::copyDeploymentConfig(::org::invenireaude::sm::cfg::Ext::DeploymentConfigPtr& ptrDeploymentConfig)const{
	IAS_TRACER;

	Mutex::Locker locker(const_cast<Config*>(this)->mutexDMChange);
	ptrDeploymentConfig=dmDeploymentConfig->duplicateDeploymentConfig();
}
/*************************************************************************/
}
}
}
