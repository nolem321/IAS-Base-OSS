/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/Input.h
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
#ifndef _IAS_DS_Impl_LMDB_Input_H_
#define _IAS_DS_Impl_LMDB_Input_H_

#include <commonlib/commonlib.h>
#include <ds/api/IInput.h>

#include "Statement.h"

#include <lmdb.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
/** The Input class.
 *
 */
class Input :
		public virtual DS::API::IInput {
public:

	virtual ~Input() throw();

	virtual void addInput(const String& strTag, DM::Tools::Setter *pSetter);
	virtual void feedInputs(DM::DataObjectPtr& dm);

protected:
	Input(Statement& statement);

	struct Element{
		String strTag;
		DM::Tools::Setter *pSetter;
    String strValue;
    MDB_val mv;
	};

	Element elementKey;
  Element elementValue;

  Statement& statement;

	void feedInput(Element& e, DM::DataObjectPtr& dm);
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_LMDB_Input_H_ */
