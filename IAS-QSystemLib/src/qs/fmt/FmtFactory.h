/*
 * File: IAS-QSystemLib/src/qs/fmt/FmtFactory.h
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
#ifndef _IAS_QS_Fmt_FmtFactory_H_
#define _IAS_QS_Fmt_FmtFactory_H_

#include <commonlib/commonlib.h>
#include <commonlib/sys/DynamicLibrary.h>

#include <dm/datamodel.h>

#include "Formatter.h"

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
/** The FmtFactory class.
 *
 */
class FmtFactory{

public:

	virtual ~FmtFactory();



	Formatter* getFormatter(const String& strFormatter)const;

protected:

	FmtFactory(const DM::DataFactory* pDataFactory);

	Mutex theMutex;
	typedef HashMapStringToPointer<Formatter> FormatterMap;
	FormatterMap							  hmFormatters;

	typedef Formatter* (*ExternalFormatterFactoryPtr)(const DM::DataFactory* pDataFactory);

	typedef HashMapStringToPointer<SYS::DynamicLibrary> LibrariesMap;
	LibrariesMap                                        hmLibraries;

	const DM::DataFactory* pDataFactory;

	friend class Factory<FmtFactory>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_Fmt_FmtFactory_H_ */
