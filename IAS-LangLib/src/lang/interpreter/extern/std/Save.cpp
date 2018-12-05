/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/Save.cpp
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
#include "Save.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
Save::Save(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
Save::~Save() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Save::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strFileName = pParameters->getString("file");
	DM::DataObjectPtr dm   = pParameters->getDataObject("value");

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
					IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pCtx->getDataFactory()));

	if(strFileName.compare("stdout")==0){
		String strValue;
		ptrXMLHelper->save(strValue,dm,dm->getType()->getName(),"");
		std::cout<<strValue;
	}else{
		ptrXMLHelper->save((const String&)strFileName,dm,dm->getType()->getName(),"");
	}

}
/*************************************************************************/
Statement* Save::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Save>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
