/*
 * File: IAS-ServiceManagerLib/src/sm/cfg/DMHelper.cpp
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
#include "DMHelper.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace Cfg {

/*************************************************************************/
void DMHelper::Merge(::IAS::DM::DataObject* dmLeft, const ::IAS::DM::DataObject* dmRight) {
	IAS_TRACER;
	IAS_CHECK_IF_NULL(dmRight);

	const DM::Type* pType = dmLeft->getType();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Left: "<<pType->getName()<<":"<<pType->getURI());

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Right: "<<dmRight->getType()->getName()<<":"<<dmRight->getType()->getURI());
	if (!pType->isDataObjectType()) {
		IAS_THROW(InternalException("!pType->isDataObjectType()"));
	}

	const DM::ComplexType* pComplexType = pType->asComplexType();
	const DM::PropertyList& lstProperties = pComplexType->getProperties();

	for (int i = 0; i < lstProperties.getSize(); i++) {

		const DM::Property* pProperty = lstProperties.getProperty(i);

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Property: "<<pProperty->getName()<<", "<<i<<" of "<<lstProperties.getSize());

		if (pProperty->getIdx() >= dmRight->getType()->asComplexType()->getProperties().getSize())
			continue;

		if (dmRight->isSet(pProperty)) {

			if (!pProperty->getType()->isDataObjectType() || !dmLeft->isSet(pProperty)) {

				dmLeft->setDataObject(pProperty, dmRight->getDataObject(pProperty)->duplicate());

			} else {
				Merge(dmLeft->getDataObject(pProperty), dmRight->getDataObject(pProperty));
			}

		}/*IF: isSet */

	}/*FOR: i*/
}
/*************************************************************************/
}
}
}
