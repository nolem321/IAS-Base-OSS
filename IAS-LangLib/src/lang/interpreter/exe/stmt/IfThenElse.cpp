/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/IfThenElse.cpp
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
#include "IfThenElse.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
IfThenElse::IfThenElse(Expr::BooleanExpr *pCondition,
					  Statement *pThenStatements,
					  Statement *pElseStatements) {
	IAS_TRACER;

	ptrCondition=pCondition;
	ptrThenStatements=pThenStatements;

	if(pElseStatements)
		ptrElseStatements=pElseStatements;
}
/*************************************************************************/
IfThenElse::~IfThenElse() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IfThenElse::execute(Context *pCtx) const{
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"IF THEN ELSE:"<<(void*)this);

	bool bCondition = ptrCondition->evaluateBoolean(pCtx);

	if(bCondition){
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"IF TRUE:"<<(void*)this);
		ptrThenStatements->execute(pCtx);
	}else{
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"IF FALSE:"<<(void*)this);
		if(! ptrElseStatements.isNull()){
			ptrElseStatements->execute(pCtx);
		}

	}
}
/*************************************************************************/
}
}
}
}
}
