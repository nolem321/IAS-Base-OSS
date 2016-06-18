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
Config::Entry::Entry(const String& strDirName):strDirName(strDirName){
	IAS_TRACER;
}
/*************************************************************************/
Config::Entry::~Entry(){
	IAS_TRACER;
}
/*************************************************************************/
const String& Config::Entry::getDirName(){
	IAS_TRACER;
	return strDirName;
}
/*************************************************************************/
bool Config::Entry::checkVersion(){
	IAS_TRACER;
	String strVersion;
	getLockObject()->readContent(strVersion);

	bool bResult = strVersion.compare(this->strVersion) != 0;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Check Version: ["<<strVersion<<"] ? ["<<this->strVersion<<"]="<<bResult);

	this->strVersion=strVersion;


	return bResult;
}
/*************************************************************************/
SYS::FS::FileLock* Config::Entry::getLockObject() {
	IAS_TRACER;

	if (ptrConfigLock.isNull()) {
		String strFile = strDirName + "/" + StrConfigLockFile;
		ptrConfigLock = IAS_DFT_FACTORY<SYS::FS::FileLock>::Create(strFile);
	}

	return ptrConfigLock;
}
/*************************************************************************/
Config::Config(const String& strCfgDirs):
		bVerbose(true),
		osLog(std::cerr){

	IAS_TRACER;


	ptrXMLHelper = IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(DataFactory::GetInstance()->getContaingDataFactory());
	ptrServiceIndexer = IAS_DFT_FACTORY<ServiceIndexer>::Create();

	StringList lstCfgDirs;
	IAS::TypeTools::Tokenize(strCfgDirs, lstCfgDirs, ':');

	for(StringList::const_iterator it=lstCfgDirs.begin(); it != lstCfgDirs.end(); it++){

		hmConfigDirs[*it]=IAS_DFT_FACTORY<Entry>::Create(*it);
	}

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
bool Config::refresh() {
	IAS_TRACER;

	bool bChanged = false;

	for(ConfigDirsMap::const_iterator it = hmConfigDirs.begin(); !bChanged && it != hmConfigDirs.end(); it++) {

		Entry *pEntry=it->second;
		bChanged = pEntry->checkVersion();

		if(bVerbose && bChanged)
			getOutput()<<"New configuration detected: "<<it->first<<std::endl;

	}

	if(!bChanged)
		return false;

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

	if(hmConfigDirs.size() == 0)
		IAS_THROW(ConfigException("Empty service list."));

	hmResourceGrpByName.clear();
	hmResourceGrpForService.clear();
	hmServicesByName.clear();

	ptrServiceIndexer = IAS_DFT_FACTORY<ServiceIndexer>::Create();

	bool bFirst = true;

	for(ConfigDirsMap::const_iterator it = hmConfigDirs.begin(); it != hmConfigDirs.end(); it++) {

		Entry *pEntry=it->second;

		SYS::Locker lock(pEntry->getLockObject());

		pEntry->checkVersion();

		loadDM(pEntry->getDirName(), it==hmConfigDirs.begin());
	}

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


}
/*************************************************************************/
void Config::saveDM() {
	IAS_TRACER;
/*
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
	*/
}
/*************************************************************************/
void Config::loadDM(const String& strCfgDir, bool bOverwrite) {
	IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Loading from: "<<strCfgDir);

		IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocS(ptrXMLHelper->readFile(strCfgDir + "/" + StrConfigFile));
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocD(ptrXMLHelper->readFile(strCfgDir + "/" + StrDeploymentFile));

		Ext::ServiceConfigPtr  dmServiceConfig;
		Ext::DeploymentConfigPtr  dmDeploymentConfig;

		dmServiceConfig = DataFactory::GetInstance()->getServiceConfigType()->cast(ptrDocS->getRootObject());
		dmDeploymentConfig = DataFactory::GetInstance()->getDeploymentConfigType()->cast(ptrDocD->getRootObject());

		dmDeploymentConfig->setLckDir(EnvTools::Substitute(dmDeploymentConfig->getLckDir()));

		/* substitute in deployment */
		Ext::ResourceGroupList& lstRGList(dmDeploymentConfig->getResourcesList());

		for(int iIdx = 0; iIdx< lstRGList.size(); iIdx++) {

			lstRGList.at(iIdx)->setLogDir(EnvTools::Substitute(lstRGList.at(iIdx)->getLogDir()));
			Ext::VariableList& lstVarList(lstRGList.at(iIdx)->getEnv()->getVarsList());

			for(int iIdxVar = 0; iIdxVar < lstVarList.size(); iIdxVar++) {
				Ext::VariablePtr dmVariable = lstVarList.at(iIdxVar);
				dmVariable->setValue(EnvTools::Substitute(dmVariable->getValue()));
			}
		}

		if(bOverwrite){

			this->dmServiceConfig=dmServiceConfig;
			this->dmDeploymentConfig=dmDeploymentConfig;
			strLckDir="/var/tmp/lck";

			try{
				strLckDir=dmDeploymentConfig->getLckDir();
			}catch(...){};

			iRefreshMS=1000;
			try{
				iRefreshMS=dmDeploymentConfig->getRefreshMS();
			}catch(...){};

		}else{

			Ext::ServiceList& lstServices(dmServiceConfig->getServicesList());
			Ext::ServiceList& lstTargetServices(this->dmServiceConfig->getServicesList());

			for(int iIdx=0;iIdx<lstServices.size();iIdx++){
				lstTargetServices.add(lstServices.at(iIdx)->duplicateService());
			}

			if(dmDeploymentConfig->isSetLckDir() && dmDeploymentConfig->getLckDir().compare(strLckDir) != 0)
				IAS_THROW(ConfigException("You must have the same LckDirs in all merged SM configurations: "+strCfgDir+" vs. value of "+ strLckDir));

			if(dmDeploymentConfig->isSetRefreshMS() && dmDeploymentConfig->getRefreshMS() != iRefreshMS)
				IAS_THROW(ConfigException("You must have the same LckDirs in all merged SM configurations: "+strCfgDir));

			Ext::ResourceGroupList& lstResGroups(dmDeploymentConfig->getResourcesList());
			Ext::ResourceGroupList& lstTargetResGroups(this->dmDeploymentConfig->getResourcesList());

			for(int iIdx=0; iIdx < lstResGroups.size(); iIdx++){
				lstTargetResGroups.add(lstResGroups.at(iIdx)->duplicateResourceGroup());
			}

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
