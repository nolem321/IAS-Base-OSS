/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/WhileLoop.cpp
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
#include "WhileLoop.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "../expr/BooleanExpr.h"
#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
WhileLoop::WhileLoop(Expr::BooleanExpr *pCondition,
	    			 Statement         *pStatements):
  ptrCondition(pCondition),
  ptrStatements(pStatements){
	IAS_TRACER;
}

/*************************************************************************/
WhileLoop::~WhileLoop() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void WhileLoop::execute(Context *pCtx) const{
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"WHILE:"<<(void*)this);

	while(!pCtx->isInterrupted() && ptrCondition->evaluateBoolean(pCtx)){
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"While loop:"<<(void*)this);
		ptrStatements->execute(pCtx);
	}
}
/*************************************************************************/
}
}
}
}
}
