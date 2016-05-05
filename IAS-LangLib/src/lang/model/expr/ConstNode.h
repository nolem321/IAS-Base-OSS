/*
 * File: IAS-LangLib/src/lang/model/expr/ConstNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_CONSTNODE_H_
#define _IAS_AS_Lang_Model_Expr_CONSTNODE_H_

#include <commonlib/commonlib.h>
#include "ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {

/*************************************************************************/
/** The class. */
 class ConstNode : public ExprNode{
public:

	enum Type{
		CN_INTEGER,
		CN_FLOAT,
		CN_BOOLEAN,
		CN_STRING,
		CN_NULL
	};

	virtual ~ConstNode() throw();

	inline const String& getOriginalText() const { return strValue; };
	inline Type getType() const { return iType; };

protected:

	ConstNode(Type iType, const String& strValue);

	String strValue;
	Type iType;

	friend class ::IAS::Factory<ConstNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_CONSTNODE_H_ */
