/*
 * File: IAS-DataModelLib/src/dm/gen/DataFactory.h
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
#ifndef IAS_DM_Gen_DataFactory_H
#define IAS_DM_Gen_DataFactory_H

#include "../../dm/Impl/DataFactory.h"

#include <commonlib/commonlib.h> 
#include "../../dm/gen/DataObjectList.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../datamodel.h"

namespace IAS {
namespace DM {
namespace Gen {

class DataFactory;
//TODO revert to callbacks.

/*************************************************************************/
/** The class. */
class DataFactory :
   public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DataFactory>, DataFactory >,
	public ::IAS::DM::Impl::DataFactory{
public:

	virtual ~DataFactory() throw();

	void declareBuiltInTypeTmpOveride(::IAS::DM::Type* pType);

	typedef void (*InitializerPtr)(DataFactory*);

	void initializeWith(InitializerPtr pInitializer);

protected:
   DataFactory();

   Mutex mutex;
   friend class IAS::Factory< DataFactory >;

};
/*************************************************************************/


} /* Gen */
} /* DM */
} /* IAS */
#endif
