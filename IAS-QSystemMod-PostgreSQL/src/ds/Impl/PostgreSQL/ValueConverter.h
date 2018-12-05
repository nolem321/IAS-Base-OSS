/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/ValueConverter.h
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
#ifndef _IAS_DS_Impl_PostgreSQL_ValueConverter_H_
#define _IAS_DS_Impl_PostgreSQL_ValueConverter_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/tools/Setter.h>

#include "Statement.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
/** The ValueConverter class.
 *
 */
class ValueConverter {
public:



	static void ConvertToPostgreSQL(Statement& statement, const DM::Tools::Setter *pSetter,const DM::DataObjectPtr& dm, StringStream& ssValue);
	static void ConvertFromPostgreSQL(Statement& statement, DM::Tools::Setter *pSetter, DM::DataObjectPtr& dm, const char* sValue);

};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_PostgreSQL_ValueConverter_H_ */
