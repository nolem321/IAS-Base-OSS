/*
 * File: IAS-LangLib/src/lang/tools/helper/AdHocPrograms.h
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
#ifndef _IAS_AS_Lang_Tools_Helper_AdHocPrograms_H_
#define _IAS_AS_Lang_Tools_Helper_AdHocPrograms_H_


#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/Impl/DataFactory.h>

#include <lang/interpreter/proc/processor.h>
#include <lang/interpreter/ProgramLoader.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Helper {

/*************************************************************************/
/** The class. */
class AdHocPrograms : public InstanceFeature<AdHocPrograms> {
	public:

	virtual ~AdHocPrograms() throw();

	void execute(const String& strName,
				 const String& strSource,
				 DM::DataObjectPtr& args,
				 DM::DataObjectPtr& result,
				 StringStream& ssErrors);

protected:

	AdHocPrograms();

	IAS_DFT_FACTORY<IAS::DM::Impl::DataFactory>::PtrHolder ptrDataFactory;

	typedef HashMapStringToPointer<Interpreter::ProgramLoader> ProgramLoaderMap;

	ProgramLoaderMap hmProgramLoaders;

	Mutex mutex;

	friend class ::IAS::Factory<AdHocPrograms>;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Tools_Helper_AdHocPrograms_H_ */
