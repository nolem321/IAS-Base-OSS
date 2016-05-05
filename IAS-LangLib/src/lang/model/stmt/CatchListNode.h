/*
 * File: IAS-LangLib/src/lang/model/stmt/CatchListNode.h
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
#ifndef _IAS_AS_Lang_Model_CatchListNode_H_
#define _IAS_AS_Lang_Model_CatchListNode_H_

#include <commonlib/commonlib.h>
#include "../Node.h"

#include <list>

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {

class CatchNode;
/*************************************************************************/
/** The class. */
 class CatchListNode :
		public Node{
public:

	typedef std::list<CatchNode*> CatchNodesList;

	void addCatchNode(CatchNode* pCatchNode);

	const CatchNodesList& getCatchNodesList() const;

	virtual ~CatchListNode() throw();

protected:
	CatchListNode();

	CatchNodesList                  lstCatchNodes;
	IAS_DFT_FACTORY<CatchNode>::PtrHoldersCollection phcCatchNodes;

	friend class ::IAS::Factory<CatchListNode>;

};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_CatchNodesLISTNODE_H_ */
