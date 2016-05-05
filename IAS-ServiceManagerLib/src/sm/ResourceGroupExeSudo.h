/*
 * File: IAS-ServiceManagerLib/src/sm/ResourceGroupExeSudo.h
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
#ifndef IAS_DM_AG_Impl_SERVICEMANAGER_47CFG_47RESOURCEGROUPEXESUDO_46H
#define IAS_DM_AG_Impl_SERVICEMANAGER_47CFG_47RESOURCEGROUPEXESUDO_46H
#include <commonlib/commonlib.h> 
#include "dm/datamodel.h" 
#include "dm/default/String.h" 
#include "dm/default/Integer.h" 
#include "dm/default/Float.h" 
#include "dm/default/Boolean.h" 
#include "org/invenireaude/sm/cfg/ResourceGroupExe.h" 
namespace servicemanager {
namespace cfg {
class ResourceGroupExeSudo: public virtual ::org::invenireaude::sm::cfg::ResourceGroupExe {
public:

	virtual int getNice() =0;
	virtual const int getNice()const =0;
	virtual ::IAS::DM::Default::Integer* getNiceDataObject() =0;
	virtual const ::IAS::DM::Default::Integer* getNiceDataObject()const =0;
	virtual void setNice(int aValue)=0;
	virtual void unsetNice()=0;
	virtual void setNiceDataObject(::IAS::DM::Default::Integer* aValue)=0;
	virtual ::IAS::String getUser() =0;
	virtual const ::IAS::String getUser()const =0;
	virtual ::IAS::DM::Default::String* getUserDataObject() =0;
	virtual const ::IAS::DM::Default::String* getUserDataObject()const =0;
	virtual void setUser(const ::IAS::String& aValue)=0;
	virtual void unsetUser()=0;
	virtual void setUserDataObject(::IAS::DM::Default::String* aValue)=0;

   virtual ResourceGroupExeSudo* duplicateResourceGroupExeSudo() const = 0;};
namespace Ext{
typedef ::IAS::RefCountingPtr< ::IAS::MemoryAllocatorFactory< ResourceGroupExeSudo >, ResourceGroupExeSudo > ResourceGroupExeSudoPtr;
class ResourceGroupExeSudoList {
	public:
	virtual void add(::org::invenireaude::sm::cfg::ResourceGroupExeSudo* pValue) = 0;
	virtual int size() const = 0;
	virtual ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* at(int iIdx) = 0;
	virtual const ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* at(int iIdx) const = 0;
};
/*************************************************************************/
class ResourceGroupExeSudoType : public virtual ::org::invenireaude::sm::cfg::Ext::ResourceGroupExeType {
	public:

	virtual ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* createResourceGroupExeSudo() const=0;
	virtual ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* createResourceGroupExeSudo(::org::invenireaude::sm::cfg::ResourceGroupExeSudo* aValue) const=0;
	virtual ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* cast(::IAS::DM::DataObject* pDataObject) const=0;
	virtual const ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* cast(const ::IAS::DM::DataObject* pDataObject) const=0;
	virtual const ::IAS::DM::Property* getUserProperty() const=0;
};
};

} /* cfg */
} /* servicemanager */
#endif
