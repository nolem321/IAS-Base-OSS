/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ti/GetNamespaces.cpp
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
#include "GetNamespaces.h"

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
#include <set>

namespace IAS {
namespace QS {
namespace Lang {
namespace LI {

using namespace org::invenireaude::qsystem;
using namespace ::IAS::Lang;
using namespace ::IAS::Lang::Interpreter;

/*************************************************************************/
GetNamespaces::GetNamespaces(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
GetNamespaces::~GetNamespaces() throw(){
	IAS_TRACER;
}
/*************************************************************************/
static void buildInfo(DM::DataObjectList& lstResult, const DM::DataFactory* pDataFactory){
	IAS_TRACER;

	const DM::TypeList& lstTypes(pDataFactory->getTypes());

	std::set<String> setNamespaces;

	for(int iIdx=0; iIdx<lstTypes.getSize(); iIdx++){
		String strNS(lstTypes.at(iIdx)->getURI());

		setNamespaces.insert(strNS);
	}

	for(std::set<String>::const_iterator it=setNamespaces.begin(); it != setNamespaces.end(); it++)
		lstResult.add(pDataFactory->getDefaultType(DM::Type::TextType)->createDataObject(*it));


}
/*************************************************************************/
void GetNamespaces::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);


	try{

		DM::DataObjectList& lstResult = pParameters->getList(Model::Dec::ResultDeclarationNode::CStrResultVariable);

		buildInfo( lstResult, pCtx->getDataFactory());

	}catch(Exception& e){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();
		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}

}
/*************************************************************************/
Extern::Statement* GetNamespaces::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetNamespaces>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}
