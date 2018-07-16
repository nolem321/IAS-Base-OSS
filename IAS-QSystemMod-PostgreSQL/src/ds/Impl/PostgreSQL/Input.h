/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Input.h
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
#ifndef _IAS_DS_Impl_PostgreSQL_Input_H_
#define _IAS_DS_Impl_PostgreSQL_Input_H_

#include <commonlib/commonlib.h>
#include <ds/api/IInput.h>

#include "Statement.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

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
		Element(String strTag,DM::Tools::Setter *pSetter):
			strTag(strTag),pSetter(pSetter){};

		Element& operator=(const Element& o){
			strTag=o.strTag;
			pSetter=o.pSetter;
			return *this;
		}
		String strTag;
		DM::Tools::Setter *pSetter;
	};

	typedef std::list<Element> ElementList;
	ElementList                lstElements;

	StringList                 lstValues;
	static const  int        CMaxNumValues = 64;
	char                      *tabValues[CMaxNumValues];
	int                       iNumValues;

	void reset();

	Statement& statement;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_PostgreSQL_Input_H_ */
