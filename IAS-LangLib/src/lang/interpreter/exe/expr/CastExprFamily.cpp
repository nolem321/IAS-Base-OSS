/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/CastExprFamily.cpp
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
#include "CastExprFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "StringExpr.h"
#include "IntegerExpr.h"
#include "FloatExpr.h"
#include "BooleanExpr.h"
#include "DateTimeExpr.h"
#include "DateExpr.h"
#include "TimeExpr.h"
#include "DataObjectExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
CastExprFamily::CastExprFamily(Expr* pExpr, const DM::Type* pType):
			ptrExpr(pExpr){
	IAS_TRACER;
	setType(pType);
}
/*************************************************************************/
CastExprFamily::~CastExprFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
class CastStringExpr : public CastExprFamily, public StringExpr{

	virtual String evaluateString(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateString(pCtx);
	}

	protected:
		CastStringExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastStringExpr>;
};
/*************************************************************************/
class CastIntegerExpr : public CastExprFamily, public IntegerExpr{

	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateInt(pCtx);
	}

	protected:
	CastIntegerExpr(Expr* pExpr, const DM::Type* pType):
		CastExprFamily(pExpr,pType){}

	friend class Factory<CastIntegerExpr>;
};
/*************************************************************************/
class CastFloatExpr : public CastExprFamily, public FloatExpr{

	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateFloat(pCtx);
	}

	protected:
		CastFloatExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastFloatExpr>;
};
/*************************************************************************/
class CastBooleanExpr : public CastExprFamily, public BooleanExpr{

	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateBoolean(pCtx);
	}

	protected:
		CastBooleanExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastBooleanExpr>;
};
/*************************************************************************/
class CastTimeExpr : public CastExprFamily, public TimeExpr{

	virtual ::IAS::Time evaluateTime(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateTime(pCtx);
	}

	protected:
		CastTimeExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastTimeExpr>;
};
/*************************************************************************/
class CastDateExpr : public CastExprFamily, public DateExpr{

	virtual ::IAS::Date evaluateDate(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateDate(pCtx);
	}

	protected:
		CastDateExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastDateExpr>;
};
/*************************************************************************/
class CastDateTimeExpr : public CastExprFamily, public DateTimeExpr{

	virtual ::IAS::DateTime evaluateDateTime(Context *pCtx) const{
		IAS_TRACER;
		return ptrExpr->evaluateDateTime(pCtx);
	}

	protected:
		CastDateTimeExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastDateTimeExpr>;
};
/***************************************************************/
class CastDataObjectExpr : public CastExprFamily, public DataObjectExpr{

	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
		IAS_TRACER;
		DM::DataObjectPtr dmResult;
		ptrExpr->evaluate(pCtx,dmResult);

		if(dmResult->getType()->isAssignableTo(getType()))
			refResult=dmResult;
		else
			refResult = getType()->createDataObject(dmResult);

	}

	protected:
	CastDataObjectExpr(Expr* pExpr, const DM::Type* pType):
			CastExprFamily(pExpr,pType){}

	friend class Factory<CastDataObjectExpr>;
};
/*************************************************************************/
Expr* CastExprFamily::Create(Expr* pExpr, const DM::Type* pType){
	IAS_TRACER;


	DM::Type::Types iType=pType->getTypeEnum();

	pType->isBaseTypeRestriction();

	IAS_DFT_FACTORY<CastExprFamily>::PtrHolder ptrExpr;

	if(pType->isDataObjectType() || !pType->isRootType())
		ptrExpr = IAS_DFT_FACTORY<CastDataObjectExpr>::Create(pExpr,pType);
	else
		switch(iType){

		case DM::Type::BooleanType:
			ptrExpr=IAS_DFT_FACTORY<CastDataObjectExpr>::Create(pExpr,pType);
			break;

		case DM::Type::IntegerType:
			ptrExpr=IAS_DFT_FACTORY<CastIntegerExpr>::Create(pExpr,pType);
			break;

		case DM::Type::FloatType:
			ptrExpr=IAS_DFT_FACTORY<CastFloatExpr>::Create(pExpr,pType);
			break;

		case DM::Type::TextType:
			ptrExpr=IAS_DFT_FACTORY<CastStringExpr>::Create(pExpr,pType);
			break;

		case DM::Type::TimeType:
			ptrExpr=IAS_DFT_FACTORY<CastTimeExpr>::Create(pExpr,pType);
			break;

		case DM::Type::DateType:
			ptrExpr=IAS_DFT_FACTORY<CastDateExpr>::Create(pExpr,pType);
			break;

		case DM::Type::DateTimeType:
			ptrExpr=IAS_DFT_FACTORY<CastDateTimeExpr>::Create(pExpr,pType);
			break;

		case DM::Type::RawType:
			ptrExpr = IAS_DFT_FACTORY<CastDataObjectExpr>::Create(pExpr,pType);
			break;

		default:
			IAS_THROW(InternalException("cast is not supported: "+pType->getFullName()));
	}

	return ptrExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
