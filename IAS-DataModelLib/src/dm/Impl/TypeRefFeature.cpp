/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeRefFeature.cpp
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
#include "../../dm/Impl/TypeRefFeature.h"

#include <commonlib/commonlib.h>

#include "../../dm/Impl/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
TypeRefFeature::TypeRefFeature() throw(){
	IAS_TRACER;

}

/*************************************************************************/
TypeRefFeature::~TypeRefFeature() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const ::IAS::DM::Type* TypeRefFeature::getType() const{
	IAS_TRACER;
	const ::IAS::DM::Type* pReturn = pType;
	return pReturn;
}
/*************************************************************************/
void TypeRefFeature::setParentIfEligible(IAS::DM::DataObject* pChild){
	IAS_TRACER;

	if(!bIsParentEligible)
		return;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Set parent: "<<pOwnedObjectsParent <<" of child: "<<pChild);

	SetParent(pOwnedObjectsParent,pChild);
}
/*************************************************************************/
void TypeRefFeature::unsetParentIfEligible(IAS::DM::DataObject* pChild){
	IAS_TRACER;

	if(!bIsParentEligible)
		return;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Unset old parent: "<<pOwnedObjectsParent <<" of child: "<<pChild);

	UnsetParent(pChild);
}
/*************************************************************************/
void TypeRefFeature::init(const ::IAS::DM::Type* pType, IAS::DM::DataObject *pOwnedObjectsParent){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pType);
	IAS_CHECK_IF_VALID(pOwnedObjectsParent);

	this->pType=pType;

	this->pOwnedObjectsParent=pOwnedObjectsParent;

	bIsParentEligible = ! pOwnedObjectsParent->getType()->isNSElementsType();
}
/*************************************************************************/
}
}
}
