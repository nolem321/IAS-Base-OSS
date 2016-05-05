/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ti/GetTypeInfo.cpp
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
#include "GetTypeInfo.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>


#include <org/invenireaude/qsystem/typeinfo/DataFactory.h>
#include <org/invenireaude/qsystem/typeinfo/TypeInfo.h>
#include <org/invenireaude/qsystem/typeinfo/Object.h>
#include <org/invenireaude/qsystem/typeinfo/SimpleType.h>
#include <org/invenireaude/qsystem/typeinfo/Property.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace LI {

using namespace org::invenireaude::qsystem;
using namespace ::IAS::Lang;
using namespace ::IAS::Lang::Interpreter;


/*************************************************************************/
GetTypeInfo::GetTypeInfo(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
GetTypeInfo::~GetTypeInfo() throw(){
	IAS_TRACER;
}
/*************************************************************************/
static void buildInfo(const DM::Type* pType, typeinfo::Ext::TypeBasePtr& ptrResult){
	IAS_TRACER;

	if(pType->isDataObjectType()){

		typeinfo::Ext::ObjectPtr ptrObject(typeinfo::DataFactory::GetInstance()->createObject());

		ptrObject->setName(pType->getName());
		ptrObject->setNamespace(pType->getURI());

		const DM::PropertyList& lstProperities(pType->asComplexType()->getProperties());

		for(int iIdx = 0; iIdx<lstProperities.getSize(); iIdx++){

			typeinfo::Ext::PropertyPtr ptrProperty(typeinfo::DataFactory::GetInstance()->createProperty());

			const DM::Property* pProperty=lstProperities[iIdx];

			ptrProperty->setName(pProperty->getName());

			const DM::Type* pPropertyType = pProperty->getType();

			ptrProperty->setTypeName(pPropertyType->getName());
			ptrProperty->setTypeNamespace(pPropertyType->getURI());

			ptrProperty->setIsXMLAttribute(pProperty->isXMLAttribute());
			ptrProperty->setIsList(pProperty->isMulti());

			String strDescription(pProperty->getDescription());

			if(!strDescription.empty())
				ptrProperty->setDescription(strDescription);

			ptrObject->getPropertiesList().add(ptrProperty);

		}

		ptrResult = ptrObject;

	}else{

		typeinfo::Ext::SimpleTypePtr ptrSimple(typeinfo::DataFactory::GetInstance()->createSimpleType());

		ptrSimple->setName(pType->getName());
		ptrSimple->setNamespace(pType->getURI());

		ptrResult = ptrSimple;
	}


	if(! pType->isRootType()) {

		const DM::Type* pBaseType = pType->getBaseType();

		ptrResult->createBase();
		ptrResult->getBase()->setName(pBaseType->getName());
		ptrResult->getBase()->setNamespace(pBaseType->getURI());
	}

	String strDescription(pType->getDescription());

	if(!strDescription.empty())
		ptrResult->setDescription(strDescription);
}
/*************************************************************************/
void GetTypeInfo::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);


	try{

		String strType(pParameters->getString("type"));
		String strTypeNS(pParameters->getString("typeNS"));

		const DM::Type *pType = pCtx->getDataFactory()->getType(strTypeNS,strType);

		typeinfo::Ext::TypeBasePtr ptrResult;

		buildInfo(pType, ptrResult);

		pParameters->setDataObject(Model::Dec::ResultDeclarationNode::CStrResultVariable,
				ptrResult);

	}catch(Exception& e){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();
		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));


	}

}
/*************************************************************************/
Extern::Statement* GetTypeInfo::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetTypeInfo>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}

