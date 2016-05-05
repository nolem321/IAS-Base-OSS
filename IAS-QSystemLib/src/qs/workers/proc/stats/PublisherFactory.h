/*
 * File: PublisherFactory.h
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


#ifndef _IAS_QS_Workers_Proc_Stats_PublisherFactory_H_
#define _IAS_QS_Workers_Proc_Stats_PublisherFactory_H_

#include <org/invenireaude/qsystem/workers/stats/Publisher.h>
#include <org/invenireaude/qsystem/workers/stats/Specification.h>


#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

class Publisher;
class PublisherStore;

/*************************************************************************/
/** The PublisherFactory class.
 *
 */
class PublisherFactory {
public:

	virtual ~PublisherFactory() throw();


	static ::org::invenireaude::qsystem::workers::stats::Ext::SpecificationPtr
			   SpecsToDM(const String& strSpecs);

	static Publisher* CreatePublisher(const ::org::invenireaude::qsystem::workers::stats::Publisher* dmPublisher);

protected:
	PublisherFactory();

	friend class Factory<PublisherFactory>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Stats_PublisherFactory_H_ */
