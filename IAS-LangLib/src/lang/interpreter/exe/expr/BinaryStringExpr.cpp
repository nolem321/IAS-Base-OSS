/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryStringExpr.cpp
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
#include "BinaryStringExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include <lang/exception/ScriptUsageException.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class BinaryStringExprPlusString : public BinaryStringExpr {
public:
	virtual String evaluateString(Context *pCtx) const{
		IAS_TRACER;
		String strLeft  = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft+=strRight;
	};

protected:
	BinaryStringExprPlusString(Expr* pLeft, Expr* pRight):
		BinaryStringExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryStringExprPlusString>;

};

/*************************************************************************/
BinaryStringExpr::BinaryStringExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryStringExpr::~BinaryStringExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryStringExpr* BinaryStringExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryStringExpr>::PtrHolder ptrBinaryStringExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryStringExpr = IAS_DFT_FACTORY<BinaryStringExprPlusString>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a string argument."));
	}

	return ptrBinaryStringExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
