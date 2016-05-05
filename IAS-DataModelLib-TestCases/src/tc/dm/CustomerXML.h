/*
 * File: IAS-DataModelLib-TestCases/src/tc/dm/CustomerXML.h
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
#ifndef _IAS_TC_DM_CUSTOMERXML_H_
#define _IAS_TC_DM_CUSTOMERXML_H_

#include "commonlib/commonlib.h"
#include <dm/datamodel.h>

namespace IAS {
using namespace DM;
namespace TC {
namespace DM {

/*************************************************************************/
class CustomerXML : public ::IAS::TestUnit{
public:

	virtual ~CustomerXML() throw();

	static CustomerXML* Create();

protected:
	CustomerXML(TestSuite* pTestSuite)throw();
	virtual void init(TestSuite* pTestSuite);

	IAS_DFT_FACTORY< ::IAS::DM::DataFactory >::PtrHolder ptrDataFactory;

	virtual void caseALL();
	void inspect(DataObject *pDataObject, std::ostream& os, String strIndent = "");

	::IAS::TestRunner<CustomerXML> theTestRunner;

	friend class ::IAS::Factory<CustomerXML>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_TC_DM_CUSTOMERXML_H_ */
