/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathAccessor.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_XPathAccessor_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_XPathAccessor_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include "../Expr.h"
#include "../ExprResultSetter.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {
namespace XPath {

/*************************************************************************/
/** The class. */
 class XPathAccessor {
public:


	virtual ~XPathAccessor() throw();

	void addSingleElement(const String& strName);
	void addMultiElement(const String& strName, Expr* pExpr);
	void addHashIndexElement(const String& strName, Expr* pExpr);


	const DM::Property* getValueProperty() const;

	void computeProperties(const DM::ComplexType *pComplexType);

	DM::DataObject* getTargetObject(DM::DataObject* pParent, Context *pCtx) const;
	ExprResultSetter getTargetObjectSetter(DM::DataObject* pParent, Context *pCtx) const;

	DM::DataObjectList& getTargetObjectList(DM::DataObject* pParent, Context *pCtx) const;

	void deleteDataObject(DM::DataObject* pParent, Context *pCtx)const;
	bool isSet(DM::DataObject* pParent, Context *pCtx)const;
	bool isNull(DM::DataObject* pParent, Context *pCtx)const;

	bool isArrayExp()const { return bArrayExp; };

protected:

	class Element{

	public:
		inline const String& getName() const { return strName;};
		inline Expr* getMultiExpr() { return ptrExpr; };
		inline bool isMulti() const { return bIsMulti; };
		inline bool isHashReference() const { return bIsHashIndex; };

		const DM::Property *getProperty() const ;

		void setProperty(const DM::Property *pProperty);

	protected:
		Element(String strName);
		Element(String strName,Expr* pExpr, bool bIsHashIndex = false);

		virtual ~Element(){};

		String   strName;
		bool     bIsMulti;
		bool     bIsHashIndex;
		IAS_DFT_FACTORY<Expr>::PtrHolder ptrExpr;
		const DM::Property *pProperty;

		friend class ::IAS::Factory<Element>;
	};

	typedef std::vector<Element*> ElementList;

	inline const ElementList& getElements() const { return lstElements; };


	XPathAccessor();

	void addElement(Element *pElement);

	ElementList                   lstElements;
	IAS_DFT_FACTORY<Element>::PtrHoldersCollection phcElements;

	const DM::Property  *pValueProperty;

	friend class ::IAS::Factory<XPathAccessor>;

	bool bArrayExp;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_XPathAccessor_H_ */
