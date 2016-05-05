/*
 * File: IAS-LangLib/src/lang/model/dec/QualifiedNameNode.h
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
#ifndef _IAS_Lang_Model_Dec_QualifiedNameNode_H_
#define _IAS_Lang_Model_Dec_QualifiedNameNode_H_

#include <commonlib/commonlib.h>
#include "../Node.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {

/*************************************************************************/
/** The QualifiedNameNode class.
 *
 */
class QualifiedNameNode : public Node {
public:

	virtual ~QualifiedNameNode() throw();

	virtual void addNextSymbol(const String& strName);

	inline const String& getName()const { return strName; };
	inline const String& getQualifiedName()const{ return strQualifiedName; };

protected:
	QualifiedNameNode(const String& strName);

	String strName;
	String strQualifiedName;
	StringList lstPrefix;

	friend class ::IAS::Factory<QualifiedNameNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Model_Dec_QualifiedNameNode_H_ */
