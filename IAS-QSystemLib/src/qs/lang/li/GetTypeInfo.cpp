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
GetTypeInfo::GetTypeInfo(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

}
/*************************************************************************/
GetTypeInfo::~GetTypeInfo() throw(){
	IAS_TRACER;
}
/*************************************************************************/
GetTypeInfo::Cache::Cache():bInitialized(false){
	IAS_TRACER;

}
/*************************************************************************/
void GetTypeInfo::Cache::init(const DM::DataFactory* pDataFactory){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	buildExtensions(pDataFactory);
	buildReferences(pDataFactory);
}
/*************************************************************************/
void GetTypeInfo::Cache::buildExtensions(const DM::DataFactory* pDataFactory){
	IAS_TRACER;

	const DM::TypeList& lstTypes(pDataFactory->getTypes());

		for(int iIdx=0; iIdx<lstTypes.getSize(); iIdx++)
			if(lstTypes.at(iIdx)->getURI().substr(0,10).compare("IAS/Script")){

			const DM::Type *pType = lstTypes.at(iIdx);

			if(!pType->isRootType())
				hmDirectExtensions[pType->getBaseType()].insert(pType);

			while(!pType->isRootType()){
				hmAllExtensions[pType->getBaseType()].insert(pType);
				pType=pType->getBaseType();
			}
	}
}
/*************************************************************************/
void GetTypeInfo::Cache::buildReferences(const DM::DataFactory* pDataFactory){
	IAS_TRACER;

	const DM::TypeList& lstTypes(pDataFactory->getTypes());

	for(int iIdx=0; iIdx<lstTypes.getSize(); iIdx++)
	if(lstTypes.at(iIdx)->getURI().substr(0,10).compare("IAS/Script")) {

		const DM::Type *pType = lstTypes.at(iIdx);
		if(pType->isDataObjectType()) {

			const DM::PropertyList& lstProperities(pType->asComplexType()->getProperties());
			for(int iIdx = 0; iIdx<lstProperities.getSize(); iIdx++) {

				const DM::Property* pProperty=lstProperities[iIdx];
				const DM::Type* pPropertyType = pProperty->getType();

				hmReferences[pPropertyType].insert(pType);
			}
		}
	}
}
/*************************************************************************/
void GetTypeInfo::Cache::getDirectExtensions(typeinfo::TypeBase* pResult, const DM::Type* pType){
	IAS_TRACER;

	if(!hmDirectExtensions.count(pType))
		return;

	for(TypesSet::const_iterator it = TheCache.hmDirectExtensions[pType].begin();
			it != TheCache.hmDirectExtensions[pType].end();it++) {

		typeinfo::TypeInfo* pTypeInfo = pResult->createDirectExtensions();

		pTypeInfo->setName((*it)->getName());
		pTypeInfo->setNamespace((*it)->getURI());

	}
}
/*************************************************************************/
void GetTypeInfo::Cache::getAllExtensions(typeinfo::TypeBase* pResult, const DM::Type* pType){
	IAS_TRACER;

	if(!hmAllExtensions.count(pType))
		return;

	for(TypesSet::const_iterator it = TheCache.hmAllExtensions[pType].begin();
			it != TheCache.hmAllExtensions[pType].end();it++) {

		typeinfo::TypeInfo* pTypeInfo = pResult->createAllExtensions();

		pTypeInfo->setName((*it)->getName());
		pTypeInfo->setNamespace((*it)->getURI());

	}
}
/*************************************************************************/
void GetTypeInfo::Cache::getReferences(typeinfo::TypeBase* pResult, const DM::Type* pType){
	IAS_TRACER;

	if(!hmReferences.count(pType))
		return;

	for(TypesSet::const_iterator it = TheCache.hmReferences[pType].begin();
			it != TheCache.hmReferences[pType].end();it++) {

		typeinfo::TypeInfo* pTypeInfo = pResult->createReferences();

		pTypeInfo->setName((*it)->getName());
		pTypeInfo->setNamespace((*it)->getURI());

	}
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
GetTypeInfo::Cache GetTypeInfo::TheCache;
/*************************************************************************/
void GetTypeInfo::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	TheCache.init(pCtx->getDataFactory());

	try{

		String strType(pParameters->getString("type"));
		String strTypeNS(pParameters->getString("typeNS"));

		bool   bDirectExtensions(pParameters->getBoolean("directExtensions"));
		bool   bAllExtensions(pParameters->getBoolean("allExtensions"));
		bool   bReferences(pParameters->getBoolean("references"));

		const DM::Type *pType = pCtx->getDataFactory()->getType(strTypeNS,strType);

		typeinfo::Ext::TypeBasePtr ptrResult;

		buildInfo(pType, ptrResult);

		if(bDirectExtensions)
			TheCache.getDirectExtensions(ptrResult,pType);

		if(bAllExtensions)
			TheCache.getAllExtensions(ptrResult,pType);

		if(bReferences)
			TheCache.getReferences(ptrResult,pType);

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
Extern::Statement* GetTypeInfo::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetTypeInfo>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

