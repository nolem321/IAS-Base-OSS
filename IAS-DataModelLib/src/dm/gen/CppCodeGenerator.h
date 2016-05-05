/*
 * File: IAS-DataModelLib/src/dm/gen/CppCodeGenerator.h
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
#ifndef _IAS_DM_Gen_CppCodeGenerator_H_
#define _IAS_DM_Gen_CppCodeGenerator_H_

#include <commonlib/commonlib.h>

#include "../datamodel.h"

namespace IAS {
namespace DM {
namespace Gen {
/*************************************************************************/
/** The class. */
 class CppCodeGenerator {
public:

	virtual ~CppCodeGenerator() throw();

	static CppCodeGenerator* Create();

	virtual void loadModel(const String& strModelFile);

	virtual void generateCode(const String& strBaseDir, bool bSingeDataObjectFile);

	void setNamespaces(const StringList& lstNamespaces);

protected:
	CppCodeGenerator()throw();
	void init();

	IAS_DFT_FACTORY<DataFactory>::PtrHolder ptrDataFactory;
	IAS_DFT_FACTORY<XML::XSDHelper>::PtrHolder ptrXSDHelper;

	StringList lstNamespaces;

	friend class ::IAS::Factory<CppCodeGenerator>;
};

/*************************************************************************/
}
}
}


#endif /* _IAS_DM_Util_CPPCODEGENERATOR_H_ */
