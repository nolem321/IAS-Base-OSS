/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/LogicalUnaryOperFamily.cpp
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
#include "LogicalUnaryOperFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class LogicalUnaryOperNot : public LogicalUnaryOperFamily {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bChild = ptrChild->evaluateBoolean(pCtx);
		return !bChild;
	};

protected:
	LogicalUnaryOperNot(const DM::DataFactory* pDataFactory,BooleanExpr* pChild):
		LogicalUnaryOperFamily(pDataFactory,pChild){}

	friend class ::IAS::Factory<LogicalUnaryOperNot>;

};
/*************************************************************************/
LogicalUnaryOperFamily::LogicalUnaryOperFamily(const DM::DataFactory* pDataFactory, BooleanExpr* pChild){
	IAS_TRACER;
	ptrChild=pChild;
	setType(pDataFactory->getDefaultType(DM::Type::BooleanType));
}
/*************************************************************************/
LogicalUnaryOperFamily::~LogicalUnaryOperFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BooleanExpr* LogicalUnaryOperFamily::Create(const DM::DataFactory* pDataFactory,
											BooleanExpr* pChild,
											TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pChild);

	IAS_DFT_FACTORY<LogicalUnaryOperFamily>::PtrHolder ptrLogicalUnaryOper;

	if(aTypeInfoProxy == &typeid(Model::Expr::LogicalNotNode)){
		ptrLogicalUnaryOper = IAS_DFT_FACTORY<LogicalUnaryOperNot>::Create(pDataFactory,pChild);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrLogicalUnaryOper.pass();

}
/*************************************************************************/
}
}
}
}
}
