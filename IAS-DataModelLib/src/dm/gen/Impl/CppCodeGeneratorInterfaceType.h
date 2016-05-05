/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorInterfaceType.h
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
#ifndef _IAS_DM_Gen_CppCodeGeneratorInterfaceType_H_
#define _IAS_DM_Gen_CppCodeGeneratorInterfaceType_H_

#include <commonlib/commonlib.h>

#include <map>
#include <vector>

#include "../../../dm/gen/Impl/CppCodeGeneratorFriend.h"
#include "../../../dm/gen/Impl/Patterns.h"
#include <dm/datamodel.h>

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {

/*************************************************************************/
class CppCodeGeneratorInterfaceType : public CppCodeGeneratorFriend{
public:

	virtual ~CppCodeGeneratorInterfaceType() throw();

	void generate();

protected:
	CppCodeGeneratorInterfaceType(CppCodeGeneratorLogic* pParent);

	void generateHeader(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
						  const Type* pType);


	friend class ::IAS::Factory<CppCodeGeneratorInterfaceType>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DMWrap_Cpp_CPPCODEGENERATORLOGIC_H_ */


