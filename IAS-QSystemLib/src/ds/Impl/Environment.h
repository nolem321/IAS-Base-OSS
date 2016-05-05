/*
 * File: IAS-QSystemLib/src/ds/Impl/Environment.h
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
#ifndef _IAS_DS_Impl_Environment_H_
#define _IAS_DS_Impl_Environment_H_

#include <ds/api/Environment.h>

namespace IAS {

namespace QS {
namespace Fmt {
class FmtFactory;
}
}

namespace DS {
namespace Impl {
class System;
class ContentManager;

/*************************************************************************/
/** The Environment class.
 *
 */
class Environment :
		public virtual API::Environment,
		public InstanceFeature<Environment>{

public:

	virtual ~Environment() throw();

	virtual API::Connection* connect(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	void shutdown();

	void setFmtFactory(QS::Fmt::FmtFactory *pFmtFactory);
	QS::Fmt::FmtFactory *getFmtFactory()const;

protected:

	Mutex mutex;

	Environment();

	friend class Factory<Environment>;

	typedef System* (*ExternalSystemFactoryPtr)();
	ExternalSystemFactoryPtr getFactory(const String& strProtocol);

	typedef HashMapStringToPointer<SYS::DynamicLibrary> LibrariesMap;
	LibrariesMap                                        hmLibraries;

	typedef HashMapStringToPointer<Impl::System>  SystemsMap;
	SystemsMap									   hmSystems;

	IAS_DFT_FACTORY<QS::Fmt::FmtFactory>::PtrHolder ptrFmtFactory;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_DS_Impl_Environment_H_ */
