/*
 * File: IAS-LangLib/src/lang/model/expr/xpath/XPathNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_XPathNode_H_
#define _IAS_AS_Lang_Model_Expr_XPathNode_H_

#include <lang/model/Node.h>

#include <commonlib/commonlib.h>
#include <vector>

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
class ExprNode;
namespace XPath {


/*************************************************************************/
/** The class. */
 class XPathNode : public Node{
public:

	class Element{

	public:
		inline const String& getName() const { return strName;};
		inline const ExprNode* getMultiExpr() { return ptrExprNode; };
		inline bool isMulti() const { return bIsMulti; };

	protected:
		Element(String strName);
		Element(String strName,ExprNode* pExprNode);

		virtual ~Element(){};
		String   strName;
		bool     bIsMulti;

		IAS_DFT_FACTORY<ExprNode>::PtrHolder ptrExprNode;

		friend class ::IAS::Factory<Element>;
	};

	typedef std::vector<Element*> ElementList;

	inline const ElementList& getElements() const { return lstElements; };

	virtual ~XPathNode() throw();

	void addSingleElement(const String& strName);
	void addMultiElement(const String& strName, ExprNode* pExprNode);

protected:

	XPathNode();
	void addElement(Element *pElement);

	ElementList                   				   lstElements;
	IAS_DFT_FACTORY<Element>::PtrHoldersCollection phcElements;

	friend class ::IAS::Factory<XPathNode>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_XPATHNODE_H_ */
